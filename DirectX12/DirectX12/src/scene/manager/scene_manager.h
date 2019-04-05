/**
* @file scene_manager.h
* @brief �V�[�����Ǘ�����N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "../../common/d3d12.h"
#include <saki/singleton.h>
#include <memory>

/**
* @brief �V�[�����Ǘ�����N���X
*/
class SceneManager :public saki::singleton<SceneManager>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	SceneManager();
	~SceneManager()noexcept;
	HRESULT Init();
	HRESULT Update();
	HRESULT Render();
	HRESULT Destroy();
};