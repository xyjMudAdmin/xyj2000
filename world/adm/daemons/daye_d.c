// /adm/daemons/daye_d.c
// 散财大爷每日发钱记账 daemon ——  for /d/city/npc/daye.c (没钱管你大爷要)
//
// Enforces, per UTC calendar day:
//   * per-character cap : 50 gold normally, 5 gold if combat_exp > 50000
//   * per-IP cap        : 50 gold total across ALL characters on that IP
//                         (this is the anti-alt-farming guard)
// Gold is handed out in fixed 5-gold chunks through request_gold().
//
// Records persist to /data/daye_d.o and reset automatically at the UTC
// day boundary (compared against a stored day index, so a reboot mid-day
// keeps the running totals).

inherit F_SAVE;

#define GIVE_EACH    5        // gold granted per successful ask
#define NORMAL_CAP   50       // per-character daily cap
#define RICH_CAP     5        // per-character daily cap when combat_exp > RICH_EXP
#define RICH_EXP     50000    // experience threshold for the reduced cap
#define IP_CAP       50       // per-IP daily cap (sum over all that IP's characters)

mapping name_rec;   // player id  -> gold already given today
mapping ip_rec;     // ip address -> gold already given today
int     day_no;     // UTC day index the two mappings belong to

int today() { return time() / 86400; }

void roll_day()
{
    if( day_no != today() ) {
        day_no   = today();
        name_rec = ([ ]);
        ip_rec   = ([ ]);
        save();
    }
}

void create()
{
    if( !restore() ) day_no = today();
    if( !mapp(name_rec) ) name_rec = ([ ]);
    if( !mapp(ip_rec) )   ip_rec   = ([ ]);
    roll_day();
}

string query_save_file() { return DATA_DIR + "daye_d"; }

// Decide how much to grant this asker.
//   > 0  : amount of gold to give (always GIVE_EACH)
//   -1   : this character has hit its own daily cap
//   -2   : this IP has hit the shared daily cap (likely an alt)
//    0   : error / no usable player
int request_gold(object who)
{
    string id, ip;
    int    cap, gname, gip;

    if( !objectp(who) ) return 0;
    roll_day();

    id = (string)who->query("id");
    if( !stringp(id) ) return 0;

    ip = query_ip_number(who);
    if( !stringp(ip) ) ip = "unknown";   // linkdead / no socket -> own bucket

    cap = ( (int)who->query("combat_exp") > RICH_EXP ) ? RICH_CAP : NORMAL_CAP;

    gname = name_rec[id];   // missing key -> 0
    gip   = ip_rec[ip];

    if( gname + GIVE_EACH > cap )    return -1;   // personal cap reached
    if( gip   + GIVE_EACH > IP_CAP ) return -2;   // IP cap reached

    name_rec[id] = gname + GIVE_EACH;
    ip_rec[ip]   = gip   + GIVE_EACH;
    save();
    return GIVE_EACH;
}

// ---- wizard / debugging helpers -----------------------------------------
mapping query_records()
{
    roll_day();
    return ([ "day" : day_no, "name" : name_rec, "ip" : ip_rec ]);
}

int clear_records()
{
    name_rec = ([ ]);
    ip_rec   = ([ ]);
    day_no   = today();
    save();
    return 1;
}
