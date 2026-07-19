// /adm/daemons/daye_d.c
// 散财大爷发钱记账 daemon —— for /d/city/npc/daye.c (没钱管你大爷要)
//
// New-player starter gold, handed out once and only once:
//   * Each character may claim ONCE, ever. The first ask grants 3 gold;
//     every later ask by that same character gives nothing.
//   * Per IP address, at most 6 gold is EVER handed out (i.e. at most two
//     fresh characters per IP). This stops someone spinning up a string of
//     throwaway IDs to claim the starter gold and funnel it onto one main.
//
// Records are permanent (no daily reset) and persist to /data/daye_d.o.

inherit F_SAVE;

#define GRANT          3      // gold granted on a character's first (only) ask
#define IP_TOTAL_CAP   6      // lifetime cap of gold handed out per IP address

mapping name_rec;   // player id  -> gold already granted (key present == 已领取)
mapping ip_rec;     // ip address -> total gold ever granted to that IP

void create()
{
    if( !restore() ) { name_rec = ([ ]); ip_rec = ([ ]); }
    if( !mapp(name_rec) ) name_rec = ([ ]);
    if( !mapp(ip_rec) )   ip_rec   = ([ ]);
}

string query_save_file() { return DATA_DIR + "daye_d"; }

// Decide how much to grant this asker.
//   > 0  : amount of gold to give (always GRANT)
//   -1   : this character has already claimed its one-time starter gold
//   -2   : this IP has reached its lifetime cap (likely alt farming)
//    0   : error / no usable player
int request_gold(object who)
{
    string id, ip;
    int gip;

    if( !objectp(who) ) return 0;

    id = (string)who->query("id");
    if( !stringp(id) ) return 0;

    ip = query_ip_number(who);
    if( !stringp(ip) ) ip = "unknown";

    if( name_rec[id] ) return -1;                 // already claimed (once-ever)

    gip = ip_rec[ip];
    if( gip + GRANT > IP_TOTAL_CAP ) return -2;    // IP lifetime cap reached

    name_rec[id] = GRANT;
    ip_rec[ip]   = gip + GRANT;
    save();
    return GRANT;
}

// ---- wizard / debugging helpers -----------------------------------------
mapping query_records() { return ([ "name" : name_rec, "ip" : ip_rec ]); }

int clear_records()
{
    name_rec = ([ ]);
    ip_rec   = ([ ]);
    save();
    return 1;
}
