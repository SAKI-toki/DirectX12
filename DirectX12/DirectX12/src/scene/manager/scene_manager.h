#pragma once
#include "../base/scene_base.h"
#include <saki/singleton.h>

class SceneManager :public saki::singleton<SceneManager>
{
	HRESULT load_resource_result = S_OK;
	ScenePtrType scene_ptr;
public:
	HRESULT Init();
	HRESULT Update();
	HRESULT Render();
	HRESULT Destroy();
};