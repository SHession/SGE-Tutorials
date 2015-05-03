#include "Game1.h"


Game1::Game1()
{
	/*Constructor of the Game Class
	Use this method to assign a new graphics and audio device
	(An graphics an audio device is required)

	For Example:
		graphics = new SGD3D::DirectXDevice();
		audio = new SGDS::DirectSoundDevice();
	*/

	graphics = new SGD3D::DirectXDevice();
	audio = new SGDS::DirectSoundDevice();
	

}


Game1::~Game1()
{
}

void Game1::LoadContent(){
	/*Load Content method
	Use this method to load in the game content 
	(At least a pixel and vertex shader is required)
	
	For Example:
		graphics->LoadPShader(L"PixelShader.hlsl", "PS" , &PShader);
		graphics->LoadVShader(L"VertexShader.hlsl", "VS" , &VShader);
	*/

	//Load Shaders
	graphics->LoadPShader(L"PixelShader.hlsl", "PS" , &PShader);
	graphics->LoadVShader(L"VertexShader.hlsl", "VS" , &VShader);


	graphics->LoadObj(L"Media\\Models\\Cars\\Car.obj", &mesh);
	graphics->LoadTexture(L"Media\\Models\\Cars\\Car-red.png", &texture);
	

}

void Game1::Initialize(){
	/*Initialize method
	Use this method to initialize the variable of the game

	For Example:
		Score = 10;
		Health = 3;
	*/

	gameObject.Mesh(mesh);
	gameObject.Texture(texture);

	graphics->PositionCamera(SGE::Vector4(0,3,-10),SGE::Vector4(0,0,0));

	gameObject.MoveTo(0,0,200);
}

void Game1::Update(SGE::Framework::GameTime gameTime){
	/*Update method
	This method is called once per frame and should be used to update game logic
	
	For Example:
		if(Collision) Health--;
	*/

	gameObject.RotateTo(-gameTime.GetElapsedTime(),0,0);

	gameObject.MoveForwardBy(5);

	graphics->PositionCamera(SGE::Vector4(0,3,-10), gameObject.Position());

	if(input.GetKeyState(SGE::Input::ESCAPE) == SGE::Input::KeyDown)
		Exit();
}

void Game1::Draw(){
	/*Draw method
	This method is called once per frame and should be used to render graphics
	
	For Example:
		graphics->Clear();
		graphics->DrawGameObject(player);
		graphics->Draw();
	*/
	graphics->Clear();

	graphics->DrawGameObject(&gameObject);

	graphics->Draw();
}

void Game1::CleanUp(){
	/*CleanUp method
	This method is used to perform any required memory mangment at the end of the game
	
	For Example:
		if(player) delete player;
	*/
	
}