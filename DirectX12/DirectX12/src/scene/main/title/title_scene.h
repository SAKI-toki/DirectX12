#pragma once
#include "../../base/scene_base.h"
#include "../../../model/static/static_model.h"
#include "../../../model/static/command_list/static_model_command_list.h"
#include <vector>

class TitleScene :public SceneBase
{
	StaticModelCommandList sm_command_list;
	struct SM_STRUCT
	{
		StaticModel model;
		Transform transform;
	};
	std::vector<SM_STRUCT> sm_list;
public:
	HRESULT Init()override;
	ScenePtrType Update(ScenePtrType, HRESULT&)override;
	HRESULT Render()override;
	HRESULT Destroy()override;
};