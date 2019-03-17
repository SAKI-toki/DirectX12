/**
* @file title_scene.cpp
* @brief �^�C�g���V�[���N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/03/13
*/
#include "title_scene.h"
#include "../../../device/device.h"
#include <saki/random.h>
#include "../../../input/keyboard/keyboard_input.h"

#pragma region public

/**
* @brief �^�C�g���V�[���̏�����
* @return �����������ǂ���
*/
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

	hr = sm_command_list.Init();
	if (FAILED(hr))return hr;

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
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_1))
	{
		sm_list.push_back({});
		hr = (sm_list.end() - 1)->model.Init(
			L"resources/model/Dragon.sakimdl",
			sm_command_list.GetPipeline());
		if (FAILED(hr))return scene_ptr;
		(sm_list.end() - 1)->transform.set_pos(
			{ saki::random(-5.0f, 5.0f), saki::random(-5.0f, 5.0f), saki::random(-5.0f, 5.0f) });
		(sm_list.end() - 1)->model.UpdateColor(
			{ saki::random(0.0f, 1.0f), saki::random(0.0f, 1.0f), saki::random(0.0f, 1.0f)
			,1.0f });
		(sm_list.end() - 1)->transform.set_scale({ 0.1f, 0.1f, 0.1f });

	}
	if (KeyboardInput::getinstance()->GetKeyDown(DIK_2))
	{
		if (sm_list.size() > 0)
		{
			auto itr = sm_list.begin();
			itr += saki::random(0, sm_list.size() - 1);
			sm_list.erase(itr);
		}
	}

	for (auto&& sm : sm_list)
	{
		auto rot = sm.transform.get_rot();
		rot.x += 0.01f;
		rot.y += 0.02f;
		rot.z += 0.03f;
		sm.transform.set_rot(rot);
		hr = sm.model.UpdateTransform(sm.transform);
		if (FAILED(hr))return scene_ptr;
	}

	return scene_ptr;
}

/**
* @brief �^�C�g���V�[���̕`��
* @return �����������ǂ���
*/
HRESULT TitleScene::Render()
{
	HRESULT hr = S_OK;

	hr = sm_command_list.BeginScene();
	if (FAILED(hr))return hr;
	for (auto&& sm : sm_list)
	{
		hr = sm.model.Draw(sm_command_list.GetCommandList());
		if (FAILED(hr))return hr;
	}
	hr = sm_command_list.Execute();
	if (FAILED(hr))return hr;

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