/**
* @file shader.h
* @brief �V�F�[�_�[�N���X
* @author �ΎR�@�I
* @date 2019/03/09
*/
#pragma once
#include "manager/shader_manager.h"
#include <memory>

/**
* @brief �V�F�[�_�[�N���X
*/
class Shader
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Shader();
	~Shader()noexcept;
	Shader(Shader&&)noexcept;
	Shader& operator=(Shader&&)noexcept;
	HRESULT LoadShader(const std::wstring& path, 
		const std::string& entry, const std::string& target);
	ComPtr<ID3DBlob>& GetShader();
};