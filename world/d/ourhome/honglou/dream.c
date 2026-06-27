// cracked by vikee 2/09/2002   vikee@263.net
// Room: /u/hkgroup/dream.c

inherit ROOM;

void create ()
{
  set ("short", "×íÃÎÍ¤");
  set ("long", @LONG

´©ÁÖº££¬¿çÑ©Ô­£¬Æø³åÏöºº¡£

LONG);

  set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"path1",
]));
  set("light_up", 1);
  set("no_fight", 1);

  setup();
}
