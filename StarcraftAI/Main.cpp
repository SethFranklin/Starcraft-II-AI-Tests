
#define _SCL_SECURE_NO_WARNINGS
#include <sc2api/sc2_api.h>

#include "Main.h"
#include "Debug.h"
#include "ZergBot.h"

using namespace sc2;

void Main::Start(int argc, char* argv[])
{

	Coordinator coordinator;
	coordinator.LoadSettings(argc, argv);

	ZergBot Bot;

	coordinator.SetParticipants({
		CreateParticipant(Bot.GetRace(), &Bot),
		CreateComputer(Race::Zerg)
	});

	coordinator.LaunchStarcraft();

	coordinator.StartGame(sc2::kMapBelShirVestigeLE);

	while (coordinator.Update())
	{


	}

	Debug::Log("Game Over");

	Debug::Prompt();

}