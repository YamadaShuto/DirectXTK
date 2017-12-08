#pragma once

#include "Emitter.h"

/// <summary>
/// Frame emitter
/// </summary>
class FlameEmitter : public Emitter
{
public:
	// Constructor
	FlameEmitter(Vector3 position);
	// Update processing
	void Update();
protected:
};