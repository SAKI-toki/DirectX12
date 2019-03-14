#pragma once
#include "../../base/scene_base.h"
#include "../../../cube/cube.h"
#include "../../../cube/command_list/cube_command_list.h"
#include "../../../sprite/sprite.h"
#include "../../../sprite/command_list/sprite_command_list.h"
#include "../../../sphere/sphere.h"
#include "../../../sphere/command_list/sphere_command_list.h"
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
	SpriteCommandList sprite_command_list;
	struct Sprites
	{
		Sprite sprite;
		Transform transform;
	};
	std::vector<Sprites> sprites;
	HRESULT GenerateSprite();
	void DeleteSprite();
	SphereCommandList sphere_command_list;
	struct Spheres
	{
		Sphere sphere;
		Transform transform;
	};
	std::vector<Spheres> spheres;
	HRESULT GenerateSphere();
	void DeleteSphere();
	int NNN = 1;
public:
	HRESULT Init()override;
	ScenePtrType Update(ScenePtrType, HRESULT&)override;
	HRESULT Render()override;
	HRESULT Destroy()override;
};