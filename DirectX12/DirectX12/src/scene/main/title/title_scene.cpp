/**
* @file title_scene.cpp
* @brief タイトルシーンクラスの関数定義
* @author 石山　悠
* @date 2019/03/13
*/
#include "title_scene.h"
#include "../../../text_ui/text_ui.h"
#include "../../../time/time.h"
#include "../../../input/keyboard/keyboard_input.h"
#include "../../../camera/camera.h"
#include "../../../light/directional/directional_light.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <saki/random.h>
#include <vector>
#include "../../../cube/cube.h"
#include "../../../cube/command_list/cube_command_list.h"
#include "../../../sphere/sphere.h"
#include "../../../sphere/command_list/sphere_command_list.h"

/**
* @brief タイトルシーンのpimplイディオム
*/
struct TitleScene::Impl
{
public:
	CubeCommandList cube_command_list;
	struct cube_struct
	{
		Cube model;
		Transform transform;
	};
	std::vector<cube_struct> cubes;
	SphereCommandList sphere_command_list;
	struct sphere_struct
	{
		Sphere model;
		Transform transform;
	};
	std::vector<sphere_struct> spheres;
};

#pragma region public

/**
* @brief タイトルシーンのコンストラクタ
*/
TitleScene::TitleScene() :
	pimpl(new Impl{})
{}

//デストラクタのデフォルト指定
TitleScene::~TitleScene()noexcept = default;

/**
* @brief タイトルシーンの初期化
* @return 成功したかどうか
*/
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

	hr = pimpl->sphere_command_list.Init();
	if (FAILED(hr))return hr;
	pimpl->spheres.push_back({});

	hr = pimpl->spheres[0].model.Init(L"resources/texture/background.sakitex", pimpl->sphere_command_list.GetPipeline());
	if (FAILED(hr))return hr;
	pimpl->spheres[0].transform.set_scale({ 1.0f,1.0f,1.0f });
	Camera::getinstance()->SetPos({ 0.0f,0.0f,-10.0f });
	Camera::getinstance()->LookAt({});

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
	hr = S_OK;

	auto rot = pimpl->spheres[0].transform.get_rot();

	rot.x += 0.01f;
	rot.y += 0.02f;
	rot.z += 0.03f;

	pimpl->spheres[0].transform.set_rot(rot);

	return scene_ptr;
}

/**
* @brief タイトルシーンの描画
* @return 成功したかどうか
*/
HRESULT TitleScene::Render()
{
	HRESULT hr = S_OK;

	hr = pimpl->sphere_command_list.BeginScene();
	if (FAILED(hr))return hr;
	for (auto&& s : pimpl->spheres)
	{
		hr = s.model.Draw(s.transform, pimpl->sphere_command_list.GetCommandList());
		if (FAILED(hr))return hr;
	}
	hr = pimpl->sphere_command_list.Execute();
	if (FAILED(hr))return hr;

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



#pragma endregion