// cracked by vikee 2/09/2002   vikee@263.net
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("°¢À­²®³¤ÅÛ", ({ "chang pao", "pao", "cloth" }) );
	set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "¼þ");
                set("value", 80);
		set("armor_prop/armor", 2);

        }
        setup();
}

