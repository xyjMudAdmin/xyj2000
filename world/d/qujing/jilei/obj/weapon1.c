// cracked by vikee 2/09/2002   vikee@263.net
#include <weapon.h>

inherit BLADE;

void create()
{
  set_name("Å£Í·µ¶", ({ "niutou dao", "dao", "blade" }) );
  init_blade(35);
  set("unit", "°Ñ");
  set_weight(700);
  if( clonep() )
     set_default_object(__FILE__);
  else {
    set("value", 110);
    set("material", "bone");
  }
  setup();
}

