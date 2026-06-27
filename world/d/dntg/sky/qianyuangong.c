// cracked by vikee 2/09/2002   vikee@263.net
//sgzl

#include <room.h>
inherit ROOM;

void create()
{
set("short", "Ç¬Ôª¹¬");
set("long", @LONG
    
LONG );


set("exits", ([
  "south"   : __DIR__"shenpinggong",
  "north"   : __DIR__"lingxiao",
]));


set("objects", ([
]));



setup();
}
