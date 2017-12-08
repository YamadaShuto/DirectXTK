//
// Game.h
//

#pragma once

#include <DirectXMath.h>
#include <DirectXColors.h>

#include "MyLibrary.h"
#include "FlameEmitter.h"
#include "ExplosionEmitter.h"
#include "OriginalEmitter.h"
#include "OriginalEmitter2.h"



class Game : public MyLibrary::Framework
{
public:

	Game(HINSTANCE hInstance, int nCmdShow);

    void Initialize() override;

	void Finalize() override;

private:

    void Update(MyLibrary::StepTimer const& timer);
    void Render();

	// Debug camera
	std::unique_ptr<MyLibrary::DebugCamera> m_Camera;
	// Skydome
	std::unique_ptr<MyLibrary::Obj3D> m_ObjSkydome;
	// Fire emitter
	std::unique_ptr<OriginalEmitter2> m_FlameEmitter;
};