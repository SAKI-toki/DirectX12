#pragma once
#include "../../base/scene_base.h"
#include <vector>
#include "../../../model/static/static_model.h"
#include "../../../model/static/command_list/static_model_command_list.h"

class TitleScene :public SceneBase
{
	StaticModelCommandList sm_command_list;
	StaticModel model;
	Transform transform;
public:
	HRESULT Init()override;
	ScenePtrType Update(ScenePtrType, HRESULT&)override;
	HRESULT Render()override;
	HRESULT Destroy()override;
};