// cracked by vikee 2/09/2002   vikee@263.net
#include <armor.h>

inherit BOOTS;

void create()
{
  set_name( "ˮţƤѥ", ({ "shuiniu pixue", "pixue", "xue" }) );
  set_weight(2000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "˫");
    set("long", "һ˫��ͲˮţƤѥ��\n");
    set("value", 650);
    set("material", "boots");
    set("armor_prop/dodge", 5);
  }
  setup();
}

