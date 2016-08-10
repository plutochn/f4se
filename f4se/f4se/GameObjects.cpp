#include "f4se/GameObjects.h"
#include "f4se/GameReferences.h"

bool TESObjectARMA::GetNodeName(char * dstBuff, TESNPC * npc, TESObjectARMO * armor)
{
	if(npc) {
		UInt32 sex = npc ? CALL_MEMBER_FN(npc, GetSex)() : 0;
		sprintf_s(dstBuff, MAX_PATH, " (%08X)[%d]/ (%08X)", formID, sex, armor->formID);
		return true;
	}

	return false;
}
