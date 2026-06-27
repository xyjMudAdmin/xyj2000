// cracked by vikee 2/09/2002   vikee@263.net
#include <armor.h>

inherit BOOTS;

void create()
{
	set_name( "É®Ð¬", ({ "seng xie", "xie" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "Ë«");
		set("long", "Ò»Ë«Ô²¿ÚÇà²¼É®Ð¬¡£");
		set("value", 6000);
		set("material", "boots");
		set("armor_prop/dodge", 5);
	}
	setup();
}
