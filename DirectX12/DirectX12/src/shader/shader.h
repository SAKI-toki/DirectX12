/**
* @file shader.h
* @brief シェーダークラス
* @author 石山　悠
* @date 2019/03/09
*/
#pragma once
#include "manager/shader_manager.h"
#include <memory>

/**
* @brief シェーダークラス
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