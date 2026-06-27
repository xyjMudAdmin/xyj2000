// cracked by vikee 2/09/2002   vikee@263.net
// shoupi.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("ÀÇÆ¤È¹", ({"wolf skirt", "skirt"}));
	set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "¼þ");
                set("value", 100);
		set("armor_prop/armor", 5);

        }
        setup();
}

