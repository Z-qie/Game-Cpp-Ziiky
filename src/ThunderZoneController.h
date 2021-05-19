#pragma once


class Zy21586Engine;
class ThunderZone;

class ThunderZoneController
{
private:
	ThunderZone* m_pThunderZone{ nullptr };
	int m_iCastInterval{ 200 };//0.3s
	int m_iNextCastTime{ 0 };

public:
	ThunderZoneController(ThunderZone* pThunderZone);
	~ThunderZoneController();

	void castSpell();
	void searchForEnemy();

};

