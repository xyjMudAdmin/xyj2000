// cracked by vikee 2/09/2002   vikee@263.net
//

#include <ansi.h>

inherit ITEM;

string *prefixs = ({
  "锦面",
  "缎面",
  "鹅绒",
  "丝绣",
});

string *names = ({
  "",
  "大",
  "扶手",
  "靠背",
  "折叠",
  "安乐",
});

string *suffixs = ({
  "长椅",
  "躺椅",
});

void create()
{
  set_name(prefixs[random(sizeof(prefixs))]+names[random(sizeof(names))]+
           suffixs[random(sizeof(suffixs))], ({ "chair" }));
  set_weight(28000);
  set("long", "这是一把椅子。\n" );
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "把");
    set("material", "stone");
    set("value", 2000);
    set("no_sell", 1);
  }
  setup();
}

void init ()
{
  object me = this_object();
  object where = environment(me);

  if (where && userp(where))
  {
    remove_call_out ("destruct_me");
    call_out ("destruct_me",900+random(900),me);
  }
}

void destruct_me (object me)
{
  destruct (me);
}

// deterministic variant selector — wizard/agent use only.
// usage: call chair->morph(N)   (flat integer, quote-free)
// index: N = prefix*12 + name*2 + suffix
// returns 1 ok, -1 not wizard, -2 master object, -3 out of range
int morph (int i)
{
  int nn = sizeof(names);
  int ns = sizeof(suffixs);

  if (! this_player() || ! wizardp(this_player()))
    return -1;
  if (! clonep(this_object()))
    return -2;
  if (i < 0 || i >= sizeof(prefixs)*nn*ns)
    return -3;
  set_name (prefixs[i/(nn*ns)] + names[(i/ns)%nn] + suffixs[i%ns],
            ({ "chair" }));
  return 1;
}
