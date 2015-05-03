// SGE.h

#pragma once
#include <Windows.h>
#include <ctime>
#include <map>

namespace SGE {
	//Forward Declertaions
	namespace Framework {
		struct GameDescription;
		class GameObject;
	}

	struct Vector4{
		double x, y, z, w;

		Vector4(){
			x = 0; y =0; z= 0; w= 1;
		};
		Vector4(double X, double Y, double Z, double W){
			x = X; y =Y; z= Z; w= W;
		};
		Vector4(double X, double Y, double Z){
			x = X; y =Y; z= Z; w= 0;
		};
	};

	namespace Graphics {
		struct VertexShader{
			int index;
			VertexShader(){
				index = -1;
			}
		};

		struct PixelShader{
			int index;
			PixelShader(){
				index = -1;
			}
		};

		struct ConstantBuffer{
			int index;
			ConstantBuffer(){
				index= -1;
			}
		};

		struct Mesh{
			int index;
			Mesh () {
				index = -1;
			}
		};

		struct Texture{
			int index;
			Texture(){
				index = -1;
			}
		};

		//Abstract class for a graphics device
		class GraphicDevice{
			public:
				virtual HRESULT InitializeDevice(Framework::GameDescription *gameDescription, HWND hWnd) = 0;
				virtual HRESULT ProcessContent() = 0;
				virtual HRESULT PositionCamera(Vector4 position, Vector4 at) = 0;
				virtual HRESULT Draw() = 0;
				virtual HRESULT DrawMesh(Graphics::Mesh*, SGE::Graphics::Texture* texture, Vector4 position, Vector4 scale, Vector4 rotation) = 0;
				virtual HRESULT DrawGameObject(Framework::GameObject*) = 0;
				virtual HRESULT Clear() = 0;
				virtual HRESULT Clear(float[4]) = 0;
				virtual HRESULT CleanUp() = 0;

				
				virtual HRESULT LoadObj(wchar_t * filename, Mesh* mesh) = 0;				
				virtual HRESULT LoadTexture(wchar_t* filename, Texture* texture) = 0;
				virtual HRESULT LoadVShader(wchar_t* filename, char* entryPoint, VertexShader *shader) = 0;
				virtual HRESULT LoadPShader(wchar_t* filename, char* entryPoint, PixelShader *shader) = 0;

				virtual HRESULT SetVShader(VertexShader *shader) = 0;
				virtual HRESULT SetPShader(PixelShader *shader) = 0;

				virtual HRESULT CreateConstantBuffer(size_t byteWidth , ConstantBuffer *buffer) = 0;
				virtual HRESULT UpdateConstantBuffer(void * data, ConstantBuffer *buffer) = 0;
		};
	}

	namespace Sound{
		//Abstract class for a sound device
		struct Sound{
			int index;
			float volume;

			Sound(){
				index = -1;
				volume = 0;
			}
		};

		class SoundDevice{
			public:
				virtual HRESULT InitializeDevice(HWND hWnd) = 0;
				virtual HRESULT LoadWav(char* filename, Sound *sound) = 0;
				virtual HRESULT Play(Sound *sound) = 0;
				virtual HRESULT Loop(Sound *sound) = 0;
				virtual HRESULT Stop(Sound *sound) = 0;
				virtual HRESULT SetVolume(Sound *sound) = 0;
				virtual HRESULT CleanUp() = 0;
		};

	}

	namespace Input{
	    enum Keys {
			A = 0x41, B = 0X42, C = 0X43, D = 0x44, E = 0X45,
			F = 0x46, G = 0X47, H = 0X48, I = 0x49, J = 0X4A,
			K = 0x4B, L = 0X4C, M = 0X4D, N = 0x4E, O = 0X4F,
			P = 0x50, Q = 0X51, R = 0X52, S = 0x53, T = 0X54,
			U = 0X55, V = 0X56, W = 0x57, X = 0X58, Y = 0x59,
			Z = 0X5A,
			UP = 0x26, LEFT = 0X25, RIGHT = 0X27, DOWN = 0X28,
			D0 = 0X30, D1 = 0X31, D2 = 0X32, D3 = 0X33,
			D4 = 0X34, D5 = 0X35, D6 = 0X36, D7 = 0X37,
			D8 = 0X38, D9 = 0X39,
			ENTER = 0x0D, BACKSPACE = 0X08, TAB = 0X09, CLEAR = 0X0C,
			SHIFT = 0X10, ESCAPE = 0x1b, SPACE = 0x20, 
			LMB = 0x01, RMB = 0x02, MMB = 0x04, 
		};

		enum KeyState{
			KeyDown = 1, Key = 2, KeyUp = 3, NotKey = 0
		};

		//Tracks keyboard inputs
		class GameInputs{
			public:
				GameInputs();
				void HandleInput(MSG msg);
				void Update();
				__declspec( dllexport ) Vector4 GetMousePosition();
				__declspec( dllexport ) KeyState GetKeyState(Keys key);
			private:
				std::map<Keys,int> state;
		};

	}

	namespace Framework {
		struct GameDescription{
			int width;
			int height;
			bool fullscreen;
		};

		//Tracks the time stats of a game
		class GameTime{
			public:
				GameTime();
				void Update();
				__declspec( dllexport ) double GetDeltaTime();
				__declspec( dllexport ) double GetElapsedTime();

			private:
				clock_t elapsedTime;
				clock_t deltaTime;
				clock_t lastTime;
		};

		//Game object class can be used for objects within a game
		class GameObject{
			public:
				__declspec( dllexport ) GameObject();
				__declspec( dllexport ) GameObject(Vector4 position, Vector4 rotation , Vector4 scale , SGE::Graphics::Mesh mesh, SGE::Graphics::Texture texture);
				__declspec( dllexport ) ~GameObject();

				__declspec( dllexport ) virtual void Update(GameTime gameTime);
				__declspec( dllexport ) void MoveTo(double x, double y, double z);
				__declspec( dllexport ) void MoveBy(double x, double y, double z);
				__declspec( dllexport ) void RotateTo(double x, double y, double z);
				__declspec( dllexport ) void RotateBy(double x, double y, double z);
				__declspec( dllexport ) void ScaleTo(double x, double y, double z);
				__declspec( dllexport ) void ScaleBy(double x, double y, double z);
				__declspec( dllexport ) void MoveForwardBy(double distance);

				Vector4 Position() const {return position;}
				Vector4 Rotation() const {return rotation;}
				Vector4 Scale() const {return scale;}

				SGE::Graphics::Mesh Mesh() const{ return _mesh;}
				void Mesh(SGE::Graphics::Mesh mesh) {_mesh = mesh;}

				SGE::Graphics::Texture Texture() const{ return _texture;}
				void Texture(SGE::Graphics::Texture texture) {_texture = texture;}

				SGE::Vector4 InitialDirection() const{ return initialRotation;}

				SGE::Vector4 CurrentDirection() const {return currentRotation;}
				void CurrentDirection(SGE::Vector4  rotation) {currentRotation = rotation;}

			private:
				Vector4 position;
				Vector4 rotation;
				Vector4 scale;

				Vector4 initialRotation;
				Vector4 currentRotation;

				SGE::Graphics::Mesh _mesh;
				SGE::Graphics::Texture _texture;


		};

		//Game class provides the structure of a game similar to XNA 
		class Game{
			public:
				__declspec( dllexport ) Game();
				__declspec( dllexport ) ~Game();
				__declspec( dllexport ) HRESULT Run(GameDescription* gameDescription, HINSTANCE hInstance, int nCmdShow);
			private:
				HINSTANCE						hInst;
				HWND							mainWnd;
				GameTime						gameTime;
				bool							gameLoop;

				HRESULT InitializeWindow(GameDescription* gameDescription, HINSTANCE hInstance, int nCmdShow);
				static HRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
			protected:
				Graphics::GraphicDevice *		graphics;
				Sound::SoundDevice *			audio;
				Input::GameInputs				input;

				__declspec( dllexport ) virtual void LoadContent();
				__declspec( dllexport ) virtual void Initialize();
				__declspec( dllexport ) virtual void Update(GameTime gameTime);
				__declspec( dllexport ) virtual void Draw();
				__declspec( dllexport ) virtual void CleanUp();

				__declspec( dllexport ) virtual void Exit();
				__declspec( dllexport ) virtual void Restart();
		};
	}
}
