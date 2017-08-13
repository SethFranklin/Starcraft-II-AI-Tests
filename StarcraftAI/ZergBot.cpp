
#define _SCL_SECURE_NO_WARNINGS
#include <sc2api/sc2_api.h>

#include <cmath>

#include "ZergBot.h"
#include "Debug.h"

using namespace sc2;

ABILITY_ID BuildOrder[] =
{

	ABILITY_ID::BUILD_SPAWNINGPOOL,
	ABILITY_ID::TRAIN_DRONE,
	ABILITY_ID::TRAIN_OVERLORD,
	ABILITY_ID::TRAIN_OVERLORD,
	ABILITY_ID::TRAIN_QUEEN

};

int Length = 5;

struct ZergBot::_Impl
{

	

};

ZergBot::ZergBot()
{

	Impl = new _Impl();

	SetRace(Zerg);

}

ZergBot::~ZergBot()
{

	delete Impl;

}

void ZergBot::OnGameStart()
{

	Debug::Log("Zerg Bot START!");

}

void ZergBot::OnStep()
{

	if (BuildOrder[OrderIndex] == ABILITY_ID::BUILD_SPAWNINGPOOL && Observation()->GetMinerals() >= 200.0)
	{

		TryBuildStructure(ABILITY_ID::BUILD_SPAWNINGPOOL);
		OrderIndex++;

	}

	const ObservationInterface* observation = Observation();

	Unit BuildUnit;

	Units TryUnits = observation->GetUnits(Unit::Alliance::Self);

	for (const Unit& a : TryUnits)
	{

		if (a.unit_type == UNIT_TYPEID::ZERG_LARVA && OrderIndex < Length && BuildOrder[OrderIndex] != ABILITY_ID::BUILD_SPAWNINGPOOL && BuildOrder[OrderIndex] != ABILITY_ID::TRAIN_QUEEN && observation->GetMinerals() >= 100)
		{

			Actions()->UnitCommand(a, BuildOrder[OrderIndex]);

			OrderIndex++;

			return;

		}
		else if (a.unit_type == UNIT_TYPEID::ZERG_LARVA && OrderIndex >= Length && observation->GetMinerals() >= 25)
		{

			Actions()->UnitCommand(a, ABILITY_ID::TRAIN_QUEEN);

		}

	}

}

void ZergBot::TryBuildStructure(sc2::AbilityID StructureAbility)
{

	const ObservationInterface* observation = Observation();

	Unit BuildUnit;

	Units TryUnits = observation->GetUnits(Unit::Alliance::Self);

	for (const Unit& UnitToTry : TryUnits)
	{

		for (const UnitOrder OrderToTry : UnitToTry.orders)
		{

			if (OrderToTry.ability_id == StructureAbility) return; // Return if a unit's already building it

		}

		if (UnitToTry.unit_type == UNIT_TYPEID::ZERG_DRONE) BuildUnit = UnitToTry;

	}

	float Radius = 10;
	float Angle = GetRandomScalar() * 3.14159265358979323846;

	Point2D Position = (GetNearestStructure(BuildUnit.pos, UNIT_TYPEID::ZERG_HATCHERY).pos) + Point2D(Radius * std::cos(Angle), Radius * std::sin(Angle));

	Actions()->UnitCommand(BuildUnit, StructureAbility, Position);

}

bool exists = false;

void ZergBot::OnUnitIdle(const Unit& IdleUnit)
{

	switch (IdleUnit.unit_type.ToType())
	{

		case UNIT_TYPEID::ZERG_HATCHERY:

			if (OrderIndex < Length && BuildOrder[OrderIndex] == ABILITY_ID::TRAIN_QUEEN && Observation()->GetMinerals() >= 150.0 && !exists)
			{

				Actions()->UnitCommand(IdleUnit, BuildOrder[OrderIndex]);

				OrderIndex++;

			}

			break;

		case UNIT_TYPEID::ZERG_QUEEN:

			exists = true;

			break;

	}

}

Unit ZergBot::GetNearestStructure(Point2D Position, UnitTypeID StructureToFind)
{

	const ObservationInterface* observation = Observation();

	Unit Closest;
	float Distance = -1.0;

	Units TryUnits = observation->GetUnits(Unit::Alliance::Self);

	for (const Unit& UnitToTry : TryUnits)
	{

		if (UnitToTry.unit_type == StructureToFind)
		{

			float NewDistance = DistanceSquared2D(Position, UnitToTry.pos);

			if (Distance < 0 || NewDistance < Distance)
			{

				Distance = NewDistance;
				Closest = UnitToTry;

			}

		}

	}

	if (Distance < 0) return TryUnits[0];
	else return Closest;

}