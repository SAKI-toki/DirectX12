/**
* @file shader_manager.h
* @brief �V�F�[�_�[���Ǘ�����N���X
* @author �ΎR�@�I
* @date 2019/03/09
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"
#include <saki/singleton.h>
#include <string>
#include <memory>

/**
* @brief �V�F�[�_�[���Ǘ�����N���X
*/
class ShaderManager :public saki::singleton<ShaderManager>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	ShaderManager();
	~ShaderManager()noexcept;
	HRESULT LoadShader(const std::wstring&, const std::wstring&, const std::string&, const std::string&);
	ComPtr<ID3DBlob>& GetShader(const std::wstring&);
};