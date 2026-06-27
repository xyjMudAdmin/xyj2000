// cracked by vikee 2/09/2002   vikee@263.net
#include <armor.h>

inherit BOOTS;

void create()
{
  set_name( "µÇÉ½åì", ({ "dengshan ji", "ji" }) );
  set_weight(1000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "Ë«");
    set("long", "Ò»Ë«ÊæÊÊµÄµÇÉ½åì¡£\n");
    set("value", 80);
    set("material", "boots");
    set("armor_prop/dodge", 2);
  }
  setup();
}

