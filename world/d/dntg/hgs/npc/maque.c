// cracked by vikee 2/09/2002   vikee@263.net
inherit NPC;

void create()
{
  set_name("ÂéÈ¸", ({"maque"}));
  set("race", "Ò°ÊŞ");
  set("age", 20);
  set("long", "Ò»Ö»Ğ¡ÂéÈ¸£¬¶¤ÔÚÊ÷ÉÒ¶ùÉÏ¡£\n");
  set("combat_exp", 50000);
  set("limbs", ({ "Í·²¿", "ÉíÌå", "³á°ò", "×ó½Å","ÓÒ½Å", "Î²°Í" }) );
  set("verbs", ({ "bite"}));

  set_skill("dodge", 20);
  set_skill("parry", 20);
  set_skill("unarmed", 20);

  setup();
}
