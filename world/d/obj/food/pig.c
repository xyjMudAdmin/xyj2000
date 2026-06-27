// cracked by vikee 2/09/2002   vikee@263.net
// pig

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("ºìÉÕÜòÜßÖí", ({"zhu rou", "pig"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "Ò»´ó¿éÏãÅçÅçµÄºìÉÕ»¨µñÜòÜßÖíÈâ¡£\n");
                set("unit", "¿é");
                set("value", 50);
                set("food_remaining", 2);
                set("food_supply", 60);
        }
}

