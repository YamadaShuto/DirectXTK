//
// Game.cpp
//

#include "Game.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
using namespace MyLibrary;

float RandomRange(float min_value, float max_value)
{
	// 0~1
	float value = (float)rand() / RAND_MAX;
	value = min_value + (max_value - min_value) * value;
	return value;
}

Game::Game(HINSTANCE hInstance, int nCmdShow)
	: Framework(hInstance, nCmdShow)
{
}

void Game::Initialize()
{
	DeviceResources* deviceResources = DeviceResources::GetInstance();

	// Pass mouse handle to window library
	MouseUtil::GetInstance()->SetWindow(DeviceResources::GetInstance()->GetWindow());
	
	// Get window rect
	RECT windowRect = deviceResources->GetOutputSize();
	// Create debug camera
	m_Camera = std::make_unique<DebugCamera>(windowRect.right- windowRect.left, windowRect.bottom - windowRect.top);

	{
		// Initialize and setting Obj3D
		Obj3D::CommonDef def;
		def.pCamera = m_Camera.get();
		def.pDevice = deviceResources->GetD3DDevice();
		def.pDeviceContext = deviceResources->GetD3DDeviceContext();
		// Initialization based on setting
		Obj3D::InitializeCommon(def);
	}
	// Load skydome
	m_ObjSkydome = std::make_unique<Obj3D>();
	m_ObjSkydome->LoadModel(L"skydome");
	m_ObjSkydome->DisableLighting();	
	// Create particle manager
	ParticleEffectManager* particleMan = ParticleEffectManager::getInstance();
	particleMan->Initialize();
	particleMan->SetCamera(m_Camera.get());

	// Load texture for fire emitter
	OriginalEmitter2::LoadTexture();

	// Create fire emitter
	m_FlameEmitter = std::make_unique<OriginalEmitter2>(Vector3(0, 0, 0));
	m_FlameEmitter->SetVelocity(Vector3(0, 0, 0));
	m_FlameEmitter->SetTime(500);
	//m_ParticleEffectManager->Entry(
	//	220,	// 生存時間
	//	Vector3(0, 0, 0),	// ワールド座標
	//	Vector3(0, 0, 0),	// 速度
	//	Vector3(0, 0, 0),	// 加速度
	//	0, 360,	// 回転角（開始時、終了時）
	//	2, 10,	// スケール（開始時、終了時）
	//	Color(1, 1, 0, 1.0f), Color(1, 0.2f, 0, 1.0)	// 色（開始時、終了時）
	//);
}

void Game::Finalize()
{

}

#pragma region Frame Update
/// <summary>
/// Update every frame
/// </summary>
/// <param name="timer">Tiem information</param>
void Game::Update(StepTimer const& timer)
{
	MouseUtil::GetInstance()->Update();
	m_Camera->Update();

	m_FlameEmitter->Update();

	// Fire ball
	/*
	m_ParticleEffectManager->Entry(
	// lifetime
		RandomRange(60, 120),
		// World position
		Vector3(0, 0, 0),	
		// Speed
		Vector3(0, RandomRange(0.03f, 0.05f), RandomRange(0.03f, 0.08f)),
		// Acceleration
		Vector3(0, 0, 0),
		// Rotaion Angle (Start , End)
		RandomRange(0,100), 1080,	
		// Scale (Start , End)
		RandomRange(2, 4), 0.5f,
		//Color (Start , End)
		Color(1, RandomRange(0.0, 0.1f), 0, 0.1f), Color(1, 0.2f, 0, 0)
	);*/
	ParticleEffectManager::getInstance()->Update();
}
#pragma endregion

#pragma region Frame Render
/// <summary>
/// Draw every frame
/// </summary>
void Game::Render()
{
	//m_ObjSkydome->Draw();
	ParticleEffectManager::getInstance()->Draw();
}
#pragma endregion
