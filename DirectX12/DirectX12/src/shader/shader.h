#pragma once
#include "manager/shader_manager.h"
class Shader
{
	std::wstring key;
	void KeyGenerate(const std::wstring& path, const std::string& entry, const std::string& target);
public:
	HRESULT LoadShader(const std::wstring& path, const std::string& entry, const std::string& target);
	ComPtr<ID3DBlob>& GetShader();
};