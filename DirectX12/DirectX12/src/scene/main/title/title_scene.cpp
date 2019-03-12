#include "title_scene.h"
#include "../../../device/device.h"
#include <saki/random.h>
#include "../../../input/keyboard/keyboard_input.h"

HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;
	hr = cube_command_list.Init();
	if (FAILED(hr))return hr;
	return hr;
}

ScenePtrType TitleScene::Update(ScenePtrType scene_ptr, HRESULT& hr)
{
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_1))
	{
		hr = GenerateCube();
		if (FAILED(hr))return scene_ptr;
	}
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_2))
	{
		DeleteCube();
	}
	for (auto&& c : cubes)
	{
		auto rot = c.transform.get_rot();
		rot.x += 0.01f;
		rot.y += 0.02f;
		rot.z += 0.03f;
		c.transform.set_rot(rot);
		hr = c.cube.UpdateTransform(c.transform);
		if (FAILED(hr))return scene_ptr;
	}
	return scene_ptr;
}

HRESULT TitleScene::Render()
{
	HRESULT hr = S_OK;

	hr = cube_command_list.BeginScene();
	if (FAILED(hr))return hr;
	for (auto&& c : cubes)
	{
		hr = c.cube.Draw(cube_command_list.GetCommandList());
		if (FAILED(hr))return hr;
	}
	hr = cube_command_list.Execute();
	if (FAILED(hr))return hr;

	return hr;
}

HRESULT TitleScene::Destroy()
{
	HRESULT hr = S_OK;

	return hr;
}

HRESULT TitleScene::GenerateCube()
{
	HRESULT hr = S_OK;

	cubes.push_back(Cubes{});
	std::wstring path = L"resources/texture/sample";
	switch (saki::random(1, 4))
	{
	case 1:
		path += std::wstring(L"1");
		break;
	case 2:
		path += std::wstring(L"2");
		break;
	case 3:
		path += std::wstring(L"3");
		break;
	case 4:
		path += std::wstring(L"4");
		break;
	}
	hr = (cubes.end() - 1)->cube.Init(path, cube_command_list.GetPipeline());
	if (FAILED(hr))return hr;
	(cubes.end() - 1)->transform.set_pos(
		{ saki::random(-5.0f, 5.0f), saki::random(-5.0f, 5.0f), saki::random(-5.0f, 5.0f) });

	return hr;
}

void TitleScene::DeleteCube()
{
	if (cubes.size() <= 0)return;
	auto itr = cubes.begin();
	itr += saki::random(0ULL, cubes.size() - 1);
	cubes.erase(itr);
}