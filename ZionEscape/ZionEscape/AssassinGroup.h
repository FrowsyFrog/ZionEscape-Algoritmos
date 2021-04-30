#pragma once
#include "Assassin.h"

ref class AssassinGroup
{
	List<Assassin^>^ assassins;
	Entity^ targetEntity;
	Pathfinding^ pathfinding;

public:
	AssassinGroup(Entity^ t, Pathfinding^ pf): targetEntity(t), pathfinding(pf) {
		assassins = gcnew List<Assassin^>();
	}

	void SpawnAssassin(Point pos) {
		assassins->Add(gcnew Assassin(pos, 1, 3, 1));
	}

	void ActionAssasins(Graphics^ g) {

		for (unsigned currentAssassin = this->assassins->Count; currentAssassin > 0; --currentAssassin) {

			assassins[currentAssassin-1]->SetTargetPosition(targetEntity->GetPivotPosition(), pathfinding);
			assassins[currentAssassin-1]->HandleMovement();
			assassins[currentAssassin-1]->MoveEntity(g);
			assassins[currentAssassin-1]->ShowSprite(g);

			if (CollisionAssassin(assassins[currentAssassin-1])) {
				//Sub lifepoint entity
				targetEntity->SetLifePoints(targetEntity->GetLifePoints() - assassins[currentAssassin - 1]->GetDamagePoints());
				//Delete ptr
				this->assassins[currentAssassin-1] = nullptr;
				delete this->assassins[currentAssassin-1];
				//Delete from the list
				assassins->Remove(assassins[currentAssassin-1]);
			}
		}
	}

	bool CollisionAssassin(Assassin^ assassin) {
		if (assassin->GetDrawingArea().IntersectsWith(targetEntity->GetDrawingArea())) return true;
		return false;
	}

	void AnimateAssassins() {
		for each (Assassin ^ assassin in assassins)
		{
			assassin->AnimateEnitity();
		}
	}
};

