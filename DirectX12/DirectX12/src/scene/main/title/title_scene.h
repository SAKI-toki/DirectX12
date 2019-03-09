#pragma once
#include "../../base/scene_base.h"

class TitleScene :public SceneBase
{
public:
	HRESULT Init()override;
	ScenePtrType Update(ScenePtrType, HRESULT&)override;
	HRESULT Render()override;
	HRESULT Destroy()override;
};