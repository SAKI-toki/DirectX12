/**
* @file scene_manager.h
* @brief �V�[�����Ǘ�����N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2019/02/08
*/
#include "scene_manager.h"
#include "../base/scene_base.h"
#include "../main/title/title_scene.h"

/**
* @brief �V�[�����Ǘ�����N���X��pimpl�C�f�B�I��
*/
class SceneManager::Impl
{
public:
	ScenePtrType scene_ptr = std::make_shared<TitleScene>();
};

#pragma region public

/**
* @brief �V�[�����Ǘ�����N���X�̃R���X�g���N�^
*/
SceneManager::SceneManager() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�̃f�t�H���g�w��
SceneManager::~SceneManager()noexcept = default;

/**
* @brief �V�[�����Ǘ�����N���X�̏�����
* @return �����������ǂ���
*/
HRESULT SceneManager::Init()
{
	HRESULT hr = S_OK;

	hr = pimpl->scene_ptr->Init();
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief �V�[�����Ǘ�����N���X�̍X�V
* @return �����������ǂ���
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
* @brief �V�[�����Ǘ�����N���X�̕`��
* @return �����������ǂ���
*/
HRESULT SceneManager::Render()
{
	HRESULT hr = S_OK;

	hr = pimpl->scene_ptr->Render();
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief �V�[�����Ǘ�����N���X�̔j��
* @return �����������ǂ���
*/
HRESULT SceneManager::Destroy()
{
	HRESULT hr = S_OK;

	hr = pimpl->scene_ptr->Destroy();
	if (FAILED(hr))return hr;

	return hr;
}

#pragma endregion