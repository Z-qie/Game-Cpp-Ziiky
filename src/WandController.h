#pragma once

class Zy21586Engine;
class Wand;

class WandController
{
private:
	Wand* m_pWand{ nullptr };
	int m_iCoolDownShoot{ 300 };//0.3s
	int m_iNextShootTime{ 0 };

public:
	WandController(Wand* m_pWand);
	~WandController();

	void castSpell();
};

