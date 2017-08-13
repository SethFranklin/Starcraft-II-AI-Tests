
#pragma once

#define _SCL_SECURE_NO_WARNINGS
#include <sc2api/sc2_api.h>

#include "Bot.h"

class ZergBot : public Bot
{

public:

	ZergBot();
	~ZergBot();

	virtual void OnGameStart();
	virtual void OnStep();
	virtual void OnUnitIdle(const sc2::Unit& IdleUnit);

private:

	struct _Impl;
	_Impl* Impl;

	int OrderIndex = 0;

	void TryBuildStructure(sc2::AbilityID StructureAbility);
	sc2::Unit GetNearestStructure(sc2::Point2D Position, sc2::UnitTypeID StructureToFind);

};