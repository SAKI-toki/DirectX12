/**
* @file title_scene.cpp
* @brief タイトルシーンクラスの関数定義
* @author 石山　悠
* @date 2019/03/13
*/
#include "title_scene.h"
#include "../../../text_ui/text_ui.h"
#include "../../../time/time.h"
#include <string>
#include <sstream>

#pragma region public

/**
* @brief タイトルシーンの初期化
* @return 成功したかどうか
*/
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

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
	static float time = 0.0f;
	time += Time::getinstance()->GetElapsedTime();
	auto x = std::cos(time) * 1100;
	auto y = std::sin(time*0.7f) * 400 + 450;
	UINT32 r = static_cast<UINT32>(std::abs(std::sin(time*1.7f) * 255/2 - 255 / 2));
	UINT32 g = static_cast<UINT32>(std::abs(std::cos(time*2.7f) * 255));
	//色(ブラッシュ)
	auto color = TextUi::getinstance()->CreateTextBrush((r << 16) + (g << 8) + 255);
	//フォーマット
	auto format = TextUi::getinstance()->CreateTextFormat(1.0f,
		DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER);
	TextUi::getinstance()->DrawStringColorFormat(L" SAKI chan SakiCppLibrary", { x,y }, color, format);
	return scene_ptr;
}

/**
* @brief タイトルシーンの描画
* @return 成功したかどうか
*/
HRESULT TitleScene::Render()
{
	HRESULT hr = S_OK;

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