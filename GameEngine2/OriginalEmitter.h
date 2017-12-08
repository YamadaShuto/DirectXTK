#pragma once

#include "Emitter.h"

/// <summary>
/// Frame emitter
/// </summary>
class OriginalEmitter : public Emitter
{
public:
	// Constructor
	OriginalEmitter(Vector3 position);
	// Update processing
	void Update();
protected:
	bool m_flag;
};