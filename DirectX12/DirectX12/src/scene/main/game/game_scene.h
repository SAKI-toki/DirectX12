#pragma once
#include "../../base/scene_base.h"
#include <memory>

class GameScene :public SceneBase
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	GameScene();
	~GameScene()noexcept;
	HRESULT Init()override;
	ScenePtrType Update(ScenePtrType, HRESULT&)override;
	HRESULT Render()override;
	HRESULT Destroy()override;
};