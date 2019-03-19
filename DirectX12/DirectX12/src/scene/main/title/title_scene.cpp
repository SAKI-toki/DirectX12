/**
* @file title_scene.cpp
* @brief �^�C�g���V�[���N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/03/13
*/
#include "title_scene.h"
#include "../../../text_ui/text_ui.h"
#include "../../../time/time.h"
#include <string>
#include <sstream>

#pragma region public

/**
* @brief �^�C�g���V�[���̏�����
* @return �����������ǂ���
*/
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

	return hr;
}

/**
* @brief �^�C�g���V�[���̍X�V
* @param scene_ptr ���݂̃V�[���̃|�C���^
* @param hr �����������ǂ������i�[����
* @return ���̃V�[���̃|�C���^
*/
ScenePtrType TitleScene::Update(ScenePtrType scene_ptr, HRESULT& hr)
{
	static float time = 0.0f;
	time += Time::getinstance()->GetElapsedTime();
	auto x = std::cos(time) * 1100;
	auto y = std::sin(time*0.7f) * 400 + 450;
	UINT32 r = static_cast<UINT32>(std::abs(std::sin(time*1.7f) * 255/2 - 255 / 2));
	UINT32 g = static_cast<UINT32>(std::abs(std::cos(time*2.7f) * 255));
	//�F(�u���b�V��)
	auto color = TextUi::getinstance()->CreateTextBrush((r << 16) + (g << 8) + 255);
	//�t�H�[�}�b�g
	auto format = TextUi::getinstance()->CreateTextFormat(1.0f,
		DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, DWRITE_TEXT_ALIGNMENT_CENTER);
	TextUi::getinstance()->DrawStringColorFormat(L" SAKI chan SakiCppLibrary", { x,y }, color, format);
	return scene_ptr;
}

/**
* @brief �^�C�g���V�[���̕`��
* @return �����������ǂ���
*/
HRESULT TitleScene::Render()
{
	HRESULT hr = S_OK;

	return hr;
}

/**
* @brief �^�C�g���V�[���̔j��
* @return �����������ǂ���
*/
HRESULT TitleScene::Destroy()
{
	HRESULT hr = S_OK;

	return hr;
}

#pragma endregion

#pragma region private



#pragma endregion