/**
* @file scene_manager.h
* @brief シーンを管理するクラスのメンバ関数を定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "scene_manager.h"
#include "../base/scene_base.h"
#include "../main/title/title_scene.h"

/**
* @brief シーンを管理するクラスのpimplイディオム
*/
class SceneManager::Impl
{
public:
	ScenePtrType scene_ptr = std::make_shared<TitleScene>();
};

#pragma region public

/**
* @brief シーンを管理するクラスのコンストラクタ
*/
SceneManager::SceneManager() :
	pimpl(new Impl{})
{}

//デストラクタのデフォルト指定
SceneManager::~SceneManager()noexcept = default;

/**
* @brief シーンを管理するクラスの初期化
* @return 成功したかどうか
*/
HRESULT SceneManager::Init()
{
	HRESULT hr = S_OK;

	hr = pimpl->scene_ptr->Init();
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief シーンを管理するクラスの更新
* @return 成功したかどうか
*/
HRESULT SceneManager::Update()
{
	HRESULT hr = S_OK;

	auto next_scene_ptr = pimpl->scene_ptr->Update(pimpl->scene_ptr, hr);
	if (FAILED(hr))return hr;

	if (next_scene_ptr != pimpl->scene_ptr)
	{
		hr = pimpl->scene_ptr->Destroy();
		if (FAILED(hr))return hr;
		pimpl->scene_ptr = next_scene_ptr;
		hr = pimpl->scene_ptr->Init();
		if (FAILED(hr))return hr;
	}

	return hr;
}

/**
* @brief シーンを管理するクラスの描画
* @return 成功したかどうか
*/
HRESULT SceneManager::Render()
{
	HRESULT hr = S_OK;

	hr = pimpl->scene_ptr->Render();
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief シーンを管理するクラスの破棄
* @return 成功したかどうか
*/
HRESULT SceneManager::Destroy()
{
	HRESULT hr = S_OK;

	hr = pimpl->scene_ptr->Destroy();
	if (FAILED(hr))return hr;

	return hr;
}

#pragma endregion