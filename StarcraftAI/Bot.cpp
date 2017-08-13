
#define _SCL_SECURE_NO_WARNINGS
#include <sc2api/sc2_api.h>

#include "Bot.h"

sc2::Race Bot::GetRace()
{

	return Race;

}

void Bot::SetRace(sc2::Race NewRace)
{

	Race = NewRace;

}