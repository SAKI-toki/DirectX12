#pragma once
#include "../../base/scene_base.h"
#include "../../../cube/cube.h"
#include "../../../cube/command_list/cube_command_list.h"
#include <vector>

class TitleScene :public SceneBase
{
	CubeCommandList cube_command_list;
	struct Cubes
	{
		Cube cube;
		Transform transform;
	};
	std::vector<Cubes> cubes;
	HRESULT GenerateCube();
	void DeleteCube();
public:
	HRESULT Init()override;
	ScenePtrType Update(ScenePtrType, HRESULT&)override;
	HRESULT Render()override;
	HRESULT Destroy()override;
};