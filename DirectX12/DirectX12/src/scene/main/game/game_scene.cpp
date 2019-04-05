#include "game_scene.h"

/**
* @brief ゲームシーンのpimplイディオム
*/
class GameScene::Impl
{

};

#pragma region public

/**
* @brief ゲームシーンのコンストラクタ
*/
GameScene::GameScene() :
	pimpl(new Impl{})
{}

//デストラクタのデフォルト指定
GameScene::~GameScene()noexcept = default;

/**
* @brief ゲームシーンの初期化
* @return 成功したかどうか
*/
HRESULT GameScene::Init()
{
	HRESULT hr = S_OK;

	return hr;
}

/**
* @brief ゲームシーンの更新
* @param scene_ptr 現在のシーンのポインタ
* @param hr 成功したかどうかを格納する
* @return 次のシーンのポインタ
*/
ScenePtrType GameScene::Update(ScenePtrType scene_ptr, HRESULT& hr)
{
	hr = S_OK;
	return scene_ptr;
}

/**
* @brief ゲームシーンの描画
* @return 成功したかどうか
*/
HRESULT GameScene::Render()
{
	HRESULT hr = S_OK;

	return hr;
}

/**
* @brief ゲームシーンの破棄
* @return 成功したかどうか
*/
HRESULT GameScene::Destroy()
{
	HRESULT hr = S_OK;

	return hr;
}

#pragma endregion