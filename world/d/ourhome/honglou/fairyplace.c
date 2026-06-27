// cracked by vikee 2/09/2002   vikee@263.net
// Room: /u/hkgroup/fairyplace
inherit ROOM;

void create ()
{
  set ("short", "太虚幻境");
  set ("long", @LONG

　　　　问谁幻入华胥境　千古风流造业人

LONG);

  set("exits", ([ /* sizeof() == 1 */
  "down" : __DIR__"main",
]));
  set("objects", ([
           __DIR__"npc/fairygirl": 1,
]));

  setup();
}
