#pragma once

#include "Emitter.h"

/// <summary>
/// Explosion emitter
/// </summary>
class ExplosionEmitter : public Emitter
{
public:
	// Constructor
	ExplosionEmitter(Vector3 position);
	// Update processing
	void Update();
protected:
};