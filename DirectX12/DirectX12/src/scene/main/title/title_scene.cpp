/**
* @file title_scene.cpp
* @brief �^�C�g���V�[���N���X�̊֐���`
* @author �ΎR�@�I
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

/**
* @brief �^�C�g���V�[����pimpl�C�f�B�I��
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
};

#pragma region public

/**
* @brief �^�C�g���V�[���̃R���X�g���N�^
*/
TitleScene::TitleScene() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�̃f�t�H���g�w��
TitleScene::~TitleScene()noexcept = default;

/**
* @brief �^�C�g���V�[���̏�����
* @return �����������ǂ���
*/
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;
	hr = pimpl->cube_command_list.Init();
	if (FAILED(hr))return hr;
	for (int i = 0; i < 2; ++i)
	{
		pimpl->cubes.push_back({});
		hr = pimpl->cubes.rbegin()->model.Init(
			L"resources/texture/monster.sakitex",
			pimpl->cube_command_list.GetPipeline());
		if (FAILED(hr))return hr;
	}
	pimpl->cubes[0].transform.set_pos({ 0.0f,-6.0f,0.0f });
	pimpl->cubes[0].transform.set_scale({ 10.0f,1.0f,10.0f });
	pimpl->cubes[1].transform.set_pos({ 0.0f,2.0f,-1.0f });
	Camera::getinstance()->SetPos({ 0.0f,8.0f,-10.0f });
	Camera::getinstance()->LookAt({ 0.0f,-3.0f,0.0f });

	return hr;
}

/**
* @brief �^�C�g���V�[���̍X�V
* @param scene_ptr ���݂̃V�[���̃|�C���^
* @param hr �����������ǂ������i�[����
* @return ���̃V�[���̃|�C���^
*/
ScenePtrType TitleScene::Update(ScenePtrType scene_ptr, HRESULT & hr)
{
	hr = S_OK;


	return scene_ptr;
}

/**
* @brief �^�C�g���V�[���̕`��
* @return �����������ǂ���
*/
HRESULT TitleScene::Render()
{
	HRESULT hr = S_OK;

	hr = pimpl->cube_command_list.BeginScene();
	if (FAILED(hr))return hr;
	for (auto&& s : pimpl->cubes)
	{
		hr = s.model.Draw(s.transform, pimpl->cube_command_list.GetCommandList());
		if (FAILED(hr))return hr;
	}
	hr = pimpl->cube_command_list.Execute();
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