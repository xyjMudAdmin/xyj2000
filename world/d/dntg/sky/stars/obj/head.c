// cracked by vikee 2/09/2002   vikee@263.net
#include <armor.h>
#include "self_destruct.c"

inherit HEAD;

void create()
{
        set_name("Í·¿ø", ({ "head"}) );
        set_weight(700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "¶¥");
		set("long", "Ò»¶¥Í·¿ø¡£\n");
                set("value", 300);
                set("material", "cloth");
                set("armor_prop/armor", 1);
		set("armor_prop/personality", 1);
        }
        setup();
}

