#pragma once
#include "manager/shader_manager.h"
class Shader
{
	std::wstring path;
public:
	HRESULT LoadShader(const std::wstring&, const std::string&, const std::string&);
	ComPtr<ID3DBlob>& GetShader();
};