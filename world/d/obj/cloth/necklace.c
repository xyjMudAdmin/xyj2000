// cracked by vikee 2/09/2002   vikee@263.net
#include <armor.h>

inherit NECK;

void create()
{
        set_name("œÓ¡¥", ({ "necklace" }) );
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "¥Æ");
                set("material", "pearl");
		set("value", 100);
                set("armor_prop/armor", 2);
        }
        setup();
}

