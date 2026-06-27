# Known Issues (intentional non-fixes & deferred work)

## Unresolved angle-bracket includes (17) — LEFT AS-IS
These reference headers that exist in neither xyj2000 nor xyj450 (the working
reference). All are dead/unused code not loaded during normal play. xyj450
ships them in the same broken state and runs fine.

### Networking daemons (vestigial intermud — never loaded)
- adm/daemons/network/{mail_serv,ms,netmail,pingd,pingtcp,telnetd,userid}.c
  and include/net/macros.h
- Missing headers: uid.h, priv.h, mailer.h, net/post.h, net/uid.h
- Decision: leave as-is. Intermud is dead infrastructure for a private server.

### Old Kaifeng quest NPCs (orphaned archive — not referenced by any room)
- d/kaifeng/npc/old/{bei,shan,zhi}.c
- Missing headers: quest_fd.h, quest_gv.h, quest_ak.h, quest_kl.h (+ reporting.h
  exists only at d/huanggong/npc/reporting.h, not locally)
- Verified: no room loads npc/old/*; live Kaifeng uses a different, complete roster.
- Decision: leave as-is.

## Classical-text books — salvaged (Phase A done), content repair deferred (Phase B)
- Files (21): d/obj/books-nonskill/text/{hmeng001,002,004,010,016,017,018,020,
  021,022,023,024,036,037, xyj02,03,05,06,08}, d/ourhome/honglou/poem/{poem238,244}
- Root cause: GB byte-stream desync corruption present in ALL upstream branches
  (xyj2000, xyj450, xyj2006 ship them identically damaged - ~20yr-old damage).
- Phase A (DONE): byte-walk salvage to valid UTF-8; clean text preserved, each
  damaged span marked with the character U+25A1. Books load and render in-game.
- Phase B (DEFERRED, low priority): replace marked gaps with public-domain
  canonical text (西游记 / 红楼梦). Original GB bytes preserved in *.gbbak as the
  repair source.
