#include "Player.h"


Player::Player(void)
{
	GameObject::GameObject();

	speed =0;
}


Player::~Player(void)
{
}

void Player::Update(SGE::Framework::GameTime gameTime){
	using namespace SGE::Framework;

	MoveForwardBy(speed * gameTime.GetDeltaTime());

	if(speed > 250) speed = 250; 
	if(speed < 0) speed = 0;

}