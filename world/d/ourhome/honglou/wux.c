// cracked by vikee 2/09/2002   vikee@263.net
// Room: /u/hkgroup/wux
inherit ROOM;

void create ()
{
  set ("short", "ÐÇÍ¤");
  set ("long", @LONG

¡¡¡¡¡¡¡¡ÌìÉÏÐÇÐÇÁÁ¾§¾§¡£

LONG);

  set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"pavilion",
]));
  set("outdoors", "/u/hkgroup");

  setup();
}
