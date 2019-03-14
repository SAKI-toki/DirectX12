/**
* @file title_scene.cpp
* @brief タイトルシーンクラスの関数定義
* @author 石山　悠
* @date 2019/03/13
*/
#include "title_scene.h"
#include "../../../device/device.h"
#include <saki/random.h>
#include "../../../input/keyboard/keyboard_input.h"

#pragma region public

/**
* @brief タイトルシーンの初期化
* @return 成功したかどうか
*/
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

	hr = cube_command_list.Init();
	if (FAILED(hr))return hr;
	hr = sprite_command_list.Init();
	if (FAILED(hr))return hr;
	hr = sphere_command_list.Init();
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief タイトルシーンの更新
* @param scene_ptr 現在のシーンのポインタ
* @param hr 成功したかどうかを格納する
* @return 次のシーンのポインタ
*/
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
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_3))
	{
		hr = GenerateSprite();
		if (FAILED(hr))return scene_ptr;
	}
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_4))
	{
		DeleteSprite();
	}
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_5))
	{
		hr = GenerateSphere();
		if (FAILED(hr))return scene_ptr;
	}
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_6))
	{
		DeleteSphere();
	}
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_7))
	{
		NNN = 1;
	}
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_8))
	{
		NNN = 2;
	}
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_9))
	{
		NNN = 3;
	}


	for (auto&& cube : cubes)
	{
		auto rot = cube.transform.get_rot();
		rot.x += 0.01f;
		rot.y += 0.02f;
		rot.z += 0.03f;
		cube.transform.set_rot(rot);
		hr = cube.cube.UpdateTransform(cube.transform);
		if (FAILED(hr))return scene_ptr;
	}
	for (auto&& sprite : sprites)
	{
		auto rot = sprite.transform.get_rot();
		rot.x += 0.01f;
		rot.y += 0.02f;
		rot.z += 0.03f;
		sprite.transform.set_rot(rot);
		hr = sprite.sprite.UpdateTransform(sprite.transform);
		if (FAILED(hr))return scene_ptr;
	}
	for (auto&& sphere : spheres)
	{
		auto rot = sphere.transform.get_rot();
		rot.x += 0.01f;
		rot.y += 0.02f;
		rot.z += 0.03f;
		sphere.transform.set_rot(rot);
		hr = sphere.sphere.UpdateTransform(sphere.transform);
		if (FAILED(hr))return scene_ptr;
	}

	return scene_ptr;
}

/**
* @brief タイトルシーンの描画
* @return 成功したかどうか
*/
HRESULT TitleScene::Render()
{
	HRESULT hr = S_OK;

	if (NNN == 1)
	{
		hr = cube_command_list.BeginScene();
		if (FAILED(hr))return hr;
		for (auto&& c : cubes)
		{
			hr = c.cube.Draw(cube_command_list.GetCommandList());
			if (FAILED(hr))return hr;
		}
		hr = cube_command_list.Execute();
		if (FAILED(hr))return hr;
	}
	else if (NNN == 2)
	{
		hr = sprite_command_list.BeginScene();
		if (FAILED(hr))return hr;
		for (auto&& c : sprites)
		{
			hr = c.sprite.Draw(sprite_command_list.GetCommandList());
			if (FAILED(hr))return hr;
		}
		hr = sprite_command_list.Execute();
		if (FAILED(hr))return hr;
	}
	else
	{
		hr = sphere_command_list.BeginScene();
		if (FAILED(hr))return hr;
		for (auto&& c : spheres)
		{
			hr = c.sphere.Draw(sphere_command_list.GetCommandList());
			if (FAILED(hr))return hr;
		}
		hr = sphere_command_list.Execute();
		if (FAILED(hr))return hr;
	}

	return hr;
}

/**
* @brief タイトルシーンの破棄
* @return 成功したかどうか
*/
HRESULT TitleScene::Destroy()
{
	HRESULT hr = S_OK;

	return hr;
}

#pragma endregion

#pragma region private

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
	itr += saki::random(0, cubes.size() - 1);
	cubes.erase(itr);
}

HRESULT TitleScene::GenerateSprite()
{
	HRESULT hr = S_OK;

	sprites.push_back(Sprites{});
	std::wstring path = L"resources/texture/sample";
	auto rand = saki::random(1, 3);
	switch (rand)
	{
	case 1:
		path += std::wstring(L"1");
		break;
	case 2:
		path += std::wstring(L"4");
		break;
	case 3:
		path += std::wstring(L"3");
		break;
	//case 4:
	//	path += std::wstring(L"4");
	//	break;
	}
	hr = (sprites.end() - 1)->sprite.Init(path, sprite_command_list.GetPipeline());
	if (FAILED(hr))return hr;
	(sprites.end() - 1)->transform.set_pos(
		{ saki::random(-5.0f, 5.0f), saki::random(-5.0f, 5.0f), saki::random(-5.0f, 5.0f) });
	(sprites.end() - 1)->transform.set_scale({ 0.003f,0.003f,0.003f });

	return hr;
}

void TitleScene::DeleteSprite()
{
	if (sprites.size() <= 0)return;
	auto itr = sprites.begin();
	itr += saki::random(0, sprites.size() - 1);
	sprites.erase(itr);
}

HRESULT TitleScene::GenerateSphere()
{
	HRESULT hr = S_OK;

	spheres.push_back(Spheres{});
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
	hr = (spheres.end() - 1)->sphere.Init(path, sphere_command_list.GetPipeline());
	if (FAILED(hr))return hr;
	(spheres.end() - 1)->transform.set_pos(
		{ saki::random(-5.0f, 5.0f), saki::random(-5.0f, 5.0f), saki::random(-5.0f, 5.0f) });

	return hr;
}

void TitleScene::DeleteSphere()
{
	if (spheres.size() <= 0)return;
	auto itr = spheres.begin();
	itr += saki::random(0, spheres.size() - 1);
	spheres.erase(itr);
}

#pragma endregion