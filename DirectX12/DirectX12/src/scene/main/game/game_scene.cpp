#include "game_scene.h"

/**
* @brief �Q�[���V�[����pimpl�C�f�B�I��
*/
class GameScene::Impl
{

};

#pragma region public

/**
* @brief �Q�[���V�[���̃R���X�g���N�^
*/
GameScene::GameScene() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�̃f�t�H���g�w��
GameScene::~GameScene()noexcept = default;

/**
* @brief �Q�[���V�[���̏�����
* @return �����������ǂ���
*/
HRESULT GameScene::Init()
{
	HRESULT hr = S_OK;

	return hr;
}

/**
* @brief �Q�[���V�[���̍X�V
* @param scene_ptr ���݂̃V�[���̃|�C���^
* @param hr �����������ǂ������i�[����
* @return ���̃V�[���̃|�C���^
*/
ScenePtrType GameScene::Update(ScenePtrType scene_ptr, HRESULT& hr)
{
	hr = S_OK;
	return scene_ptr;
}

/**
* @brief �Q�[���V�[���̕`��
* @return �����������ǂ���
*/
HRESULT GameScene::Render()
{
	HRESULT hr = S_OK;

	return hr;
}

/**
* @brief �Q�[���V�[���̔j��
* @return �����������ǂ���
*/
HRESULT GameScene::Destroy()
{
	HRESULT hr = S_OK;

	return hr;
}

#pragma endregion