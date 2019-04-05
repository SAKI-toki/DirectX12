#pragma once
#include "../../base/scene_base.h"
#include <memory>

class TitleScene :public SceneBase
{
	struct Impl;
	std::unique_ptr<Impl> pimpl;
public:
	TitleScene();
	~TitleScene()noexcept;
	HRESULT Init()override;
	ScenePtrType Update(ScenePtrType, HRESULT&)override;
	HRESULT Render()override;
	HRESULT Destroy()override;
};