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
	graphics->LoadPShader(L"PixelShader.hlsl", "PS2" , &PShader2);
	graphics->LoadVShader(L"VertexShader.hlsl", "VS" , &VShader);

	graphics->LoadObj(L"Media\\Models\\Cars\\CarNormal.obj", &car);
	graphics->LoadTexture(L"Media\\Models\\Cars\\Car-blue.png", &carTexture);

	graphics->LoadObj(L"Media\\Models\\Rock\\rock.obj", &rock);
	graphics->LoadTexture(L"Media\\Models\\Rock\\rock.jpg", &rockTexture);

	graphics->LoadObj(L"Media\\Models\\Tile\\Tile.obj", &tile);
	graphics->LoadTexture(L"Media\\Models\\Tile\\Tile.png", &tileTexture);

	audio->LoadWav("Media\\Audio\\EngineNoise.wav", &engine);
	audio->LoadWav("Media\\Audio\\CarHorn.wav", &horn);

	struct CB_LIGHTING{
		float lightDirection[4];
	 };

	graphics->CreateConstantBuffer(sizeof(CB_LIGHTING), &CBLighting);
	CB_LIGHTING lighting = {0,1.41,1.41,0};
	graphics->UpdateConstantBuffer(&lighting, &CBLighting);
}

void Game1::Initialize(){
	/*Initialize method
	Use this method to initialize the variable of the game

	For Example:
		Score = 10;
		Health = 3;
	*/

	player = Player();
	player.Mesh(car);
	player.Texture(carTexture);

	for(int i =0; i < 100; i++){
		SGE::Framework::GameObject tempObject;
		tempObject.Mesh(rock);
		tempObject.Texture(rockTexture);

		tempObject.MoveTo((rand() % 2000) - 1000, -7.5, (rand() % 2000) - 1000);

		rocks.push_back(tempObject);
	}

	for(int i =0; i < 1; i++){
		SGE::Framework::GameObject tempObject;
		tempObject.Mesh(tile);
		tempObject.Texture(tileTexture);

		tempObject.MoveTo(0, -7.5, 0);
		tempObject.ScaleTo(100,0,100);

		tiles.push_back(tempObject);
	}

	audio->Loop(&engine);
}

void Game1::Update(SGE::Framework::GameTime gameTime){
	/*Update method
	This method is called once per frame and should be used to update game logic
	
	For Example:
		if(Collision) Health--;
	*/

	if(input.GetKeyState(SGE::Input::ESCAPE) == SGE::Input::KeyDown)
		Exit();

	using namespace SGE::Input;

	engine.volume = player.speed;
	audio->SetVolume(&engine);
		
	if(input.GetKeyState(W) == Key)	{
		player.speed++;
	}
	if(input.GetKeyState(S) == Key)	{
		player.speed--;
	}
	if(input.GetKeyState(A) == Key)	{
		player.RotateBy(0,-(((player.speed - 250)/-250.0) + 1) * gameTime.GetDeltaTime(), 0);
	}
	if(input.GetKeyState(D) == Key)	{
		player.RotateBy(0,(((player.speed - 250)/-250.0) + 1) * gameTime.GetDeltaTime(), 0);
	}

	if(input.GetKeyState(SPACE) == KeyDown){
		audio->Play(&horn);
	}


	player.Update(gameTime);


	SGE::Vector4 playerDirection = player.CurrentDirection();
	int distance = 100;
	//distance = 50 + (50 * (player.speed/250.0));
	SGE::Vector4 cameraPos = SGE::Vector4(player.Position().x - (playerDirection.x * distance), player.Position().y - (playerDirection.y * distance) + 20, 
		player.Position().z - (playerDirection.z * distance));
	graphics->PositionCamera(cameraPos, player.Position());

	
}

void Game1::Draw(){
	/*Draw method
	This method is called once per frame and should be used to render graphics
	
	For Example:
		graphics->Clear();
		graphics->DrawGameObject(player);
		graphics->Draw();
	*/

	float color[4] = {145/255.0,221/255.0,237/255.0,0};
	graphics->Clear(color);

	graphics->SetPShader(&PShader2);
	graphics->DrawGameObject(&player);

	graphics->SetPShader(&PShader);
	for (int i =0; i < rocks.size(); i++){
		graphics->DrawGameObject(&rocks[i]);
	}

	for (int i =0; i < tiles.size(); i++){
		graphics->DrawGameObject(&tiles[i]);
	}

	graphics->Draw();
}

void Game1::CleanUp(){
	/*CleanUp method
	This method is used to perform any required memory mangment at the end of the game
	
	For Example:
		if(player) delete player;
	*/
	
}