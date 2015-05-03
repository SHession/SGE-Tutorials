#pragma once
#include "sge.h"
class Player :
	public SGE::Framework::GameObject
{
public:
	Player(void);
	~Player(void);

	void Update(SGE::Framework::GameTime gameTime);

	int speed;
};

