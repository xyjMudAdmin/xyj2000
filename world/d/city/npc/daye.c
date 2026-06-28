// /d/city/npc/daye.c
// 没钱管你大爷要 —— 南城客栈里赖着不走的散财大爷
//
// 玩家指令：  ask Da Ye about money      （每次给 5 金子）
// 每日限额由 /adm/daemons/daye_d 统一记账：
//   * 同一角色每天最多 50 金子（战斗经验 > 50000 时降为 5 金子）
//   * 同一 IP 每天最多 50 金子（防止开小号刷钱）

inherit NPC;

#define DAYE_D "/adm/daemons/daye_d"

string ask_money();

void create()
{
    set_name("没钱管你大爷要", ({ "da ye", "daye" }));
    set("title", "南城客栈");
    set("gender", "男性");
    set("age", 66);
    set("long",
        "一个衣着体面、却赖在客栈里不走的老头儿，\n"
        "见人就拍着胸脯嚷嚷：「没钱？管你大爷要！」\n");

    set("attitude", "peaceful");
    set("combat_exp", 120000);
    set_skill("unarmed", 120);
    set_skill("dodge", 120);
    set_skill("parry", 120);
    set("force", 3000);
    set("force_factor", 40);
    setup();

    set("inquiry", ([
        "money" : (: ask_money :),
        "钱"    : (: ask_money :),
        "gold"  : (: ask_money :),
        "金子"  : (: ask_money :),
    ]) );
}

string ask_money()
{
    object me = this_player();
    int r;

    if( !objectp(me) ) return 0;

    r = (int)DAYE_D->request_gold(me);

    if( r > 0 ) {
        add_money("gold", r);
        command("give " + r + " gold to " + me->query("id"));
        command("tell " + me->query("id") + " 孩子，挣钱不容易, 省着点儿花，奥！");
        return "拿去，别说大爷小气——花光了再来！\n";
    }
    if( r == -1 )
        return "去去去，今儿个给你的够多啦，明天请早！\n";
    if( r == -2 )
        return "你们换张脸就来诓大爷的钱？当我看不出来！今天到此为止。\n";

    return "大爷今儿手头紧，改日再说。\n";
}
