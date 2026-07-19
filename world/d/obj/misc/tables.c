// cracked by vikee 2/09/2002   vikee@263.net
//

#include <ansi.h>

inherit ITEM;

string *prefixs = ({
  "大",
  "小",
  "黑",
  "方",
  "圆",
  "白漆",
  "青漆",
  "紫漆",
});

string *names = ({
  "木",
  "仙",
  "镶玉",
  "兽脚",
});

string *suffixs = ({
  "桌",
  "案",
});

void create()
{
  set_name(prefixs[random(sizeof(prefixs))]+names[random(sizeof(names))]+
           suffixs[random(sizeof(suffixs))], ({ "table" }));
  set_weight(30000);
  set("long", "这是一张桌子。\n" );
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "张");
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
// usage: call table->morph(N)   (flat integer, quote-free)
// index: N = prefix*8 + name*2 + suffix
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
            ({ "table" }));
  return 1;
}
