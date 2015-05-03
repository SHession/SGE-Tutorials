
#pragma once
#include <SGD3D.h>
#include <SGDS.h>
#include <vector>
#include "Player.h"


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
	SGE::Graphics::PixelShader PShader2;
	SGE::Graphics::VertexShader VShader;
	SGE::Graphics::ConstantBuffer CBLighting;

	SGE::Graphics::Mesh car;
	SGE::Graphics::Texture carTexture;

	SGE::Graphics::Mesh rock;
	SGE::Graphics::Texture rockTexture;

	SGE::Graphics::Mesh tile;
	SGE::Graphics::Texture tileTexture;
	
	Player player;
	
	SGE::Sound::Sound engine;
	SGE::Sound::Sound horn;

	std::vector<SGE::Framework::GameObject> rocks;
	std::vector<SGE::Framework::GameObject> tiles;

};

