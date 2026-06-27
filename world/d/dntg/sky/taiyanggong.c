// cracked by vikee 2/09/2002   vikee@263.net
//sgzl

#include <room.h>
inherit ROOM;

void create()
{
set("short", "Ì«Ñô¹¬");
set("long", @LONG
    
LONG );


set("exits", ([
  "north"   : __DIR__"shenpinggong",
  "south"   : __DIR__"tonglugong",
  "west"   : __DIR__"huayuedian",
  "east"   : __DIR__"pixiangdian",
]));


set("objects", ([
]));



setup();
}
