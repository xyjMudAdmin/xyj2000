// cracked by vikee 2/09/2002   vikee@263.net
inherit __DIR__"piggy_two.c";

void create()
{
    ::create();

    set ("short", "Ë«ÈË¹°Öí·¿");
    set("exits", ([
        "east": __DIR__"club3",
    ]) );
}
