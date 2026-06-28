#!/usr/bin/env python3
"""xyj2000 static map analyzer (v1)."""
import os, re, sys, argparse
from collections import defaultdict, deque

STD_DIRS = {
    "north", "south", "east", "west",
    "northeast", "northwest", "southeast", "southwest",
    "up", "down", "enter", "out", "leave",
}
EXITS_RE = re.compile(r'set\s*\(\s*"exits"\s*,')

def read(path):
    with open(path, "rb") as f:
        raw = f.read()
    for enc in ("utf-8", "gb18030"):
        try:
            return raw.decode(enc)
        except UnicodeDecodeError:
            continue
    return raw.decode("utf-8", "replace")

def strip_comments(line):
    i = line.find("//")
    return line if i == -1 else line[:i]

def extract_exits_block(text):
    m = EXITS_RE.search(text)
    if not m:
        return None
    j = text.find("([", m.end())
    if j == -1:
        return None
    depth, k = 0, j
    while k < len(text):
        c = text[k]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return text[j:k + 1]
        k += 1
    return None

PAIR_RE = re.compile(r'"([^"]+)"\s*:\s*([^,]+?)\s*(?:,|$)', re.M)

def resolve_target(raw, file_dir):
    tokens = re.findall(r'__DIR__|"[^"]*"', raw)
    if not tokens:
        return None, raw.strip()
    out = ""
    for t in tokens:
        if t == "__DIR__":
            out += file_dir.rstrip("/") + "/"
        else:
            out += t[1:-1]
    if not out.startswith("/"):
        return None, raw.strip()
    return os.path.normpath(out), None

def domain(room):
    parts = room.strip("/").split("/")
    return parts[1] if len(parts) > 1 and parts[0] == "d" else parts[0]

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("root")
    ap.add_argument("--origin", default="/d/city/center")
    ap.add_argument("--scan", default="d")
    args = ap.parse_args()
    root = os.path.abspath(args.root)
    scan_root = os.path.join(root, args.scan)
    exits = defaultdict(list)
    files = set()
    unresolved = []
    for dp, _, fns in os.walk(scan_root):
        for fn in fns:
            if not fn.endswith(".c"):
                continue
            fpath = os.path.join(dp, fn)
            room = "/" + os.path.relpath(fpath, root)[:-2]
            room = "/" + os.path.normpath(room).lstrip("/")
            files.add(room)
            text = read(fpath)
            block = extract_exits_block(text)
            if not block:
                continue
            block = "\n".join(strip_comments(l) for l in block.splitlines())
            file_dir = os.path.dirname(room)
            for dirkey, rhs in PAIR_RE.findall(block):
                tgt, bad = resolve_target(rhs, file_dir)
                if bad is not None:
                    unresolved.append((room, dirkey, bad))
                    continue
                exits[room].append((dirkey, tgt))
    origin = args.origin
    walk = defaultdict(set)
    for r, lst in exits.items():
        for d, t in lst:
            if d in STD_DIRS:
                walk[r].add(t)
    seen = set()
    if origin in files:
        q = deque([origin]); seen.add(origin)
        while q:
            r = q.popleft()
            for t in walk.get(r, ()):
                if t in files and t not in seen:
                    seen.add(t); q.append(t)
    dead = sorted({(r, d, t) for r, lst in exits.items()
                   for d, t in lst if t not in files})
    inbound = defaultdict(set)
    for r in walk:
        for t in walk[r]:
            inbound[t].add(r)
    orphans = sorted(r for r in files if r != origin and not inbound.get(r))
    oneway = sorted((r, t) for r in walk for t in walk[r]
                    if t in files and r not in walk.get(t, ()))
    unreachable = sorted(files - seen) if origin in files else []
    seams = sorted({(r, t) for r in walk for t in walk[r]
                    if t in files and domain(r) != domain(t)})
    def head(s): print(f"\n=== {s} ===")
    print(f"origin={origin}  rooms_on_disk={len(files)}  reachable_walkable={len(seen)}")
    head(f"DEAD REFS  [{len(dead)}]")
    for r, d, t in dead: print(f"  {r}  -{d}->  {t}.c  (missing)")
    head(f"ONE-WAY walkable exits  [{len(oneway)}]")
    for r, t in oneway: print(f"  {r}  -->  {t}   (no return)")
    head(f"ORPHANS (no inbound walkable exit)  [{len(orphans)}]")
    for r in orphans: print(f"  {r}")
    head(f"UNREACHABLE from origin (walkable)  [{len(unreachable)}]")
    for r in unreachable: print(f"  {r}")
    head(f"CROSS-DOMAIN SEAMS  [{len(seams)}]")
    for r, t in seams: print(f"  {r}  -->  {t}")
    head(f"UNRESOLVED targets (parser gaps)  [{len(unresolved)}]")
    for r, d, raw in unresolved: print(f"  {r}  -{d}->  {raw!r}")

if __name__ == "__main__":
    main()
