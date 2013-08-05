/*
 * Copyright (C) 2008 - 2011 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010 - 2011 Myth Project <http://bitbucket.org/sun/myth-core/>
 *
 * Myth Project's source is based on the Trinity Project source, you can find the
 * link to that easily in Trinity Copyrights. Myth Project is a private community.
 * To get access, you either have to donate or pass a developer test.
 * You can't share Myth Project's sources! Only for personal use.
 */

#include "ScriptPCH.h"

#define SAY_GAMESBEGIN_1        -1469004
#define SAY_GAMESBEGIN_2        -1469005
#define SAY_VAEL_INTRO          -1469006

#define GOSSIP_ITEM_1           "I've made no mistakes."
#define GOSSIP_ITEM_2           "You have lost your mind, Nefarius. You speak in riddles."
#define GOSSIP_ITEM_3           "Please do."

#define CREATURE_BRONZE_DRAKANOID       14263
#define CREATURE_BLUE_DRAKANOID         14261
#define CREATURE_RED_DRAKANOID          14264
#define CREATURE_GREEN_DRAKANOID        14262
#define CREATURE_BLACK_DRAKANOID        14265

#define CREATURE_CHROMATIC_DRAKANOID    14302
#define CREATURE_NEFARIAN               11583

#define ADD_X1 -7591.151855f
#define ADD_X2 -7514.598633f
#define ADD_Y1 -1204.051880f
#define ADD_Y2 -1150.448853f
#define ADD_Z1 476.800476f
#define ADD_Z2 476.796570f

#define NEF_X   -7445
#define NEF_Y   -1332
#define NEF_Z   536

#define HIDE_X  -7592
#define HIDE_Y  -1264
#define HIDE_Z  481

#define SPELL_SHADOWBOLT        21077
#define SPELL_FEAR              26070

//And then have him spawn "Nefarian" for phase 2

class boss_victor_nefarius : public CreatureScript
{
public:
    boss_victor_nefarius() : CreatureScript("boss_victor_nefarius") {}

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->SEND_GOSSIP_MENU(7198, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                pPlayer->SEND_GOSSIP_MENU(7199, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                pPlayer->CLOSE_GOSSIP_MENU();
                DoScriptText(SAY_GAMESBEGIN_1, pCreature);
                CAST_AI(boss_victor_nefarius::boss_victor_nefariusAI, pCreature->AI())->BeginEvent(pPlayer);
                break;
        }
        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_1 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(7134, pCreature->GetGUID());
        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_victor_nefariusAI (pCreature);
    }

    struct boss_victor_nefariusAI : public ScriptedAI
    {
        boss_victor_nefariusAI(Creature *c) : ScriptedAI(c)
        {
            NefarianGUID = 0;
            switch (urand(0,19))
            {
                case 0:
                    DrakType1 = CREATURE_BRONZE_DRAKANOID;
                    DrakType2 = CREATURE_BLUE_DRAKANOID;
                    break;
                case 1:
                    DrakType1 = CREATURE_BRONZE_DRAKANOID;
                    DrakType2 = CREATURE_RED_DRAKANOID;
                    break;
                case 2:
                    DrakType1 = CREATURE_BRONZE_DRAKANOID;
                    DrakType2 = CREATURE_GREEN_DRAKANOID;
                    break;
                case 3:
                    DrakType1 = CREATURE_BRONZE_DRAKANOID;
                    DrakType2 = CREATURE_BLACK_DRAKANOID;
                    break;
                case 4:
                    DrakType1 = CREATURE_BLUE_DRAKANOID;
                    DrakType2 = CREATURE_BRONZE_DRAKANOID;
                    break;
                case 5:
                    DrakType1 = CREATURE_BLUE_DRAKANOID;
                    DrakType2 = CREATURE_RED_DRAKANOID;
                    break;
                case 6:
                    DrakType1 = CREATURE_BLUE_DRAKANOID;
                    DrakType2 = CREATURE_GREEN_DRAKANOID;
                    break;
                case 7:
                    DrakType1 = CREATURE_BLUE_DRAKANOID;
                    DrakType2 = CREATURE_BLACK_DRAKANOID;
                    break;
                case 8:
                    DrakType1 = CREATURE_RED_DRAKANOID;
                    DrakType2 = CREATURE_BRONZE_DRAKANOID;
                    break;
                case 9:
                    DrakType1 = CREATURE_RED_DRAKANOID;
                    DrakType2 = CREATURE_BLUE_DRAKANOID;
                    break;
                case 10:
                    DrakType1 = CREATURE_RED_DRAKANOID;
                    DrakType2 = CREATURE_GREEN_DRAKANOID;
                    break;
                case 11:
                    DrakType1 = CREATURE_RED_DRAKANOID;
                    DrakType2 = CREATURE_BLACK_DRAKANOID;
                    break;
                case 12:
                    DrakType1 = CREATURE_GREEN_DRAKANOID;
                    DrakType2 = CREATURE_BRONZE_DRAKANOID;
                    break;
                case 13:
                    DrakType1 = CREATURE_GREEN_DRAKANOID;
                    DrakType2 = CREATURE_BLUE_DRAKANOID;
                    break;
                case 14:
                    DrakType1 = CREATURE_GREEN_DRAKANOID;
                    DrakType2 = CREATURE_RED_DRAKANOID;
                    break;
                case 15:
                    DrakType1 = CREATURE_GREEN_DRAKANOID;
                    DrakType2 = CREATURE_BLACK_DRAKANOID;
                    break;
                case 16:
                    DrakType1 = CREATURE_BLACK_DRAKANOID;
                    DrakType2 = CREATURE_BRONZE_DRAKANOID;
                    break;
                case 17:
                    DrakType1 = CREATURE_BLACK_DRAKANOID;
                    DrakType2 = CREATURE_BLUE_DRAKANOID;
                    break;
                case 18:
                    DrakType1 = CREATURE_BLACK_DRAKANOID;
                    DrakType2 = CREATURE_GREEN_DRAKANOID;
                    break;
                case 19:
                    DrakType1 = CREATURE_BLACK_DRAKANOID;
                    DrakType2 = CREATURE_RED_DRAKANOID;
                    break;
            }
        }

        uint32 SpawnedAdds;
        uint32 AddSpawnTimer;
        uint32 ShadowBoltTimer;
        uint32 FearTimer;
        uint32 MindControlTimer;
        uint32 ResetTimer;
        uint32 DrakType1;
        uint32 DrakType2;
        uint64 NefarianGUID;
        uint32 NefCheckTime;

        void Reset()
        {
            SpawnedAdds = 0;
            AddSpawnTimer = 10000;
            ShadowBoltTimer = 5000;
            FearTimer = 8000;
            ResetTimer = 900000;
            NefarianGUID = 0;
            NefCheckTime = 2000;

            me->SetUInt32Value(UNIT_NPC_FLAGS,1);
            me->setFaction(35);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void BeginEvent(Player *pTarget)
        {
            DoScriptText(SAY_GAMESBEGIN_2, me);

            /*
            list <Player*>::const_iterator i = sMapMgr->GetMap(me->GetMapId(), me)->GetPlayers().begin();

            for (i = sMapMgr->GetMap(me->GetMapId(), me)->GetPlayers().begin(); i != sMapMgr->GetMap(me->GetMapId(), me)->GetPlayers().end(); ++i)
            {
            AttackStart((*i));
            }
            */
            me->SetUInt32Value(UNIT_NPC_FLAGS,0);
            me->setFaction(103);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            AttackStart(pTarget);
        }

        void EnterCombat(Unit * /*who*/)
        {
        }

        void MoveInLineOfSight(Unit *who)
        {
            if (who && who->GetTypeId() == TYPEID_PLAYER && me->IsHostileTo(who))
            {
                me->AddThreat(who, 0.0f);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (SpawnedAdds < 42)
            {
                if (ShadowBoltTimer <= diff)
                {
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        DoCast(pTarget, SPELL_SHADOWBOLT);

                    ShadowBoltTimer = urand(3000,10000);
                } else ShadowBoltTimer -= diff;

                if (FearTimer <= diff)
                {
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        DoCast(pTarget, SPELL_FEAR);

                    FearTimer = 10000 + (rand()%10000);
                } else FearTimer -= diff;

                if (AddSpawnTimer <= diff)
                {
                    uint32 CreatureID;
                    Creature* Spawned = NULL;
                    Unit *pTarget = NULL;

                    if (urand(0,2) == 0)
                        CreatureID = CREATURE_CHROMATIC_DRAKANOID;
                    else
                        CreatureID = DrakType1;

                    ++SpawnedAdds;

                    Spawned = me->SummonCreature(CreatureID,ADD_X1,ADD_Y1,ADD_Z1,5.000f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);
                    if (pTarget && Spawned)
                    {
                        Spawned->AI()->AttackStart(pTarget);
                        Spawned->setFaction(103);
                    }

                    if (urand(0,2) == 0)
                        CreatureID = CREATURE_CHROMATIC_DRAKANOID;
                    else
                        CreatureID = DrakType2;

                    ++SpawnedAdds;

                    Spawned = me->SummonCreature(CreatureID,ADD_X2,ADD_Y2,ADD_Z2,5.000f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,5000);
                    pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);
                    if (pTarget && Spawned)
                    {
                        Spawned->AI()->AttackStart(pTarget);
                        Spawned->setFaction(103);
                    }

                    if (SpawnedAdds >= 42)
                    {
                        me->InterruptNonMeleeSpells(false);

                        DoCast(me, 33356);

                        DoCast(me, 8149);

                        DoTeleportTo(HIDE_X,HIDE_Y,HIDE_Z);
                        me->AddUnitState(UNIT_STAT_FLEEING);

                        Creature* Nefarian = me->SummonCreature(CREATURE_NEFARIAN,NEF_X,NEF_Y,NEF_Z,0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,120000);
                        pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);
                        if (pTarget && Nefarian)
                        {
                            Nefarian->AI()->AttackStart(pTarget);
                            Nefarian->setFaction(103);
                            NefarianGUID = Nefarian->GetGUID();
                        }
                        else sLog->outError("TSCR: Blackwing Lair: Unable to spawn nefarian properly.");
                    }

                    AddSpawnTimer = 4000;
                } else AddSpawnTimer -= diff;
            }
            else if (NefarianGUID)
            {
                if (NefCheckTime <= diff)
                {
                    Unit* Nefarian = Unit::GetCreature((*me),NefarianGUID);

                    if (!Nefarian || !Nefarian->isAlive())
                    {
                        NefarianGUID = 0;
                        me->DespawnOrUnsummon();
                    }

                    NefCheckTime = 2000;
                } else NefCheckTime -= diff;
            }
        }
    };
};

void AddSC_boss_victor_nefarius()
{
    new boss_victor_nefarius();
}