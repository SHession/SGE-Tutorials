
#pragma once
#include <SGD3D.h>
#include <SGDS.h>



class Game1 :
	public SGE::Framework::Game
{
public:
	Game1();
	~Game1();

private:
	void Initialize();
	void Draw();
	void Update(SGE::Framework::GameTime deltaTime);
	void LoadContent();
	void CleanUp();

	SGE::Graphics::PixelShader PShader;
	SGE::Graphics::VertexShader VShader;

};

