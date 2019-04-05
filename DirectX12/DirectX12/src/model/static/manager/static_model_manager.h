/**
* @file static_model_manager.h
* @brief �A�j���[�V�����Ȃ����f���N���X�̊Ǘ��N���X
* @author �ΎR�@�I
* @date 2019/03/18
*/
#pragma once
#include "../../../common/d3d12.h"
#include "../../../common/alias.h"
#include <saki/singleton.h>
#include <string>
#include <memory>

/**
* @brief �A�j���[�V�����Ȃ����f���N���X�̊Ǘ��N���X
*/
class StaticModelManager :public saki::singleton<StaticModelManager>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	StaticModelManager();
	~StaticModelManager()noexcept;
	HRESULT LoadModel(const std::wstring&);
	void SetModel(const std::wstring& key,
		ComPtr<ID3D12GraphicsCommandList>& com_command_list);
	unsigned int GetPolygonNum(const std::wstring& key);
};