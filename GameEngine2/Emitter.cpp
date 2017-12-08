#include "Emitter.h"

using namespace MyLibrary;

void Emitter::LoadTexture()
{
	// Load texture
	ParticleEffectManager::getInstance()->LoadTexture(0,L"Resources/Textures/effect1.png");
	ParticleEffectManager::getInstance()->LoadTexture(1, L"Resources/Textures/effect2.png");
	ParticleEffectManager::getInstance()->LoadTexture(2, L"Resources/Textures/asuna.png");
}

// Get the specified range of random number
float Emitter::RandomRange(float min_value, float max_value)
{
	// 0~1
	float value = (float)rand() / RAND_MAX;
	value = min_value + (max_value - min_value) * value;
	return value;
}