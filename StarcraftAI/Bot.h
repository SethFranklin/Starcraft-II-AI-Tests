
#pragma once

#define _SCL_SECURE_NO_WARNINGS
#include <sc2api/sc2_api.h>

class Bot : public sc2::Agent
{

public:

	sc2::Race GetRace();

	virtual void OnGameStart() = 0;
	virtual void OnStep() = 0;
	virtual void OnUnitIdle(const sc2::Unit& IdleUnit) = 0;

protected:

	void SetRace(sc2::Race NewRace);

private:

	sc2::Race Race;

};