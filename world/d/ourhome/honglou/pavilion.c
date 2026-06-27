// cracked by vikee 2/09/2002   vikee@263.net
// Room: /u/hkgroup/pavilion
inherit ROOM;

void create ()
{
  set ("short", "Çß·¼Í¤");
  set ("long", @LONG

¡¡¡¡ÈÆµÌÁø½èÈı¸İ´ä£¬¸ô°¶»¨·ÖÒ»ÂöÏã¡£

LONG);

  set("exits", ([ /* sizeof() == 4 */
  "west" : __DIR__"wux",
  "south" : __DIR__"path1",
  "north" : __DIR__"yard1",
  "down" : __DIR__"kat",
]));
  set("outdoors", "/u/hkgroup");

  setup();
}
