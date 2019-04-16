#include "botpch.h"
#include "../../playerbot.h"
#include "LearnTaxiAction.h"

#include "../../ServerFacade.h"

using namespace ai;

bool LearnTaxiAction::Execute(Event event)
{
	ObjectGuid guid;

	WorldPacket &p = event.getPacket();
	if (p.empty())
	{
		Player* master = GetMaster();
		if (master)
			guid = master->GetSelectionGuid();
	}
	else
	{
		p.rpos(0);
		p >> guid;
	}

	if (!guid)
		return false;

	Creature *pCreature = bot->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_NONE);
	if (!pCreature)
		return false;
    
	GossipMenuItemsMapBounds pMenuItemBounds = sObjectMgr.GetGossipMenuItemsMapBounds(pCreature->GetCreatureInfo()->GossipMenuId);
    for (auto itr = pMenuItemBounds.first; itr != pMenuItemBounds.second; ++itr)
    {
        uint32 npcflags = pCreature->GetUInt32Value(UNIT_NPC_FLAGS);

        if (!(itr->second.npc_option_npcflag & npcflags))
            continue;
        
        if (itr->second.option_id == GOSSIP_OPTION_TAXIVENDOR && bot->GetSession()->SendLearnNewTaxiNode(pCreature))
        {
            ai->TellMasterNoFacing("I learned a new taxi node");
        	return true;
        }
    }

	return false;
}