// /d/city/npc/daye.c
// 没钱管你大爷要 —— 南城客栈里赖着不走的散财大爷
//
// 玩家指令：  ask Da Ye about money
// 发放规则由 /adm/daemons/daye_d 记账：
//   * 每个角色一辈子只能领一次，头一回给 3 金子，之后不再给
//   * 同一 IP 总共最多发 6 金子（防止开小号领钱后倒贴给大号）

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
        return "头一遭见你吧？拿去做盘缠——大爷可只送这一回！\n";
    }
    if( r == -1 )
        return "你不是领过了吗？大爷的钱可不是大风刮来的，没有第二回！\n";
    if( r == -2 )
        return "你们换张脸就来诓大爷的钱？当我看不出来！这地方没你的份儿了。\n";

    return "大爷今儿手头紧，改日再说。\n";
}
