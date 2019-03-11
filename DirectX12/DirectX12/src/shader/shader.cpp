#include "shader.h"

HRESULT Shader::LoadShader(const std::wstring& _path, const std::string& entry, const std::string& target)
{
	HRESULT hr = S_OK;

	path = _path;
	hr = ShaderManager::getinstance()->LoadShader(path, entry, target);
	if (FAILED(hr))return hr;

	return hr;
}

ComPtr<ID3DBlob>& Shader::GetShader()
{
	return ShaderManager::getinstance()->GetShader(path);
}