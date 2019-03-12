#include "shader.h"

HRESULT Shader::LoadShader(const std::wstring& path, const std::string& entry, const std::string& target)
{
	HRESULT hr = S_OK;

	KeyGenerate(path, entry, target);
	hr = ShaderManager::getinstance()->LoadShader(key, path, entry, target);
	if (FAILED(hr))return hr;

	return hr;
}

ComPtr<ID3DBlob>& Shader::GetShader()
{
	return ShaderManager::getinstance()->GetShader(key);
}

void Shader::KeyGenerate(const std::wstring& path, const std::string& entry, const std::string& target)
{
	std::string entry_target = entry + target;
	size_t size = entry_target.size();
	std::unique_ptr<char[]> char_ptr(new char[size + 1]);
	for (unsigned int i = 0; i < size; ++i)
	{
		char_ptr[i] = entry_target[i];
	}
	char_ptr[size] = '\0';
	std::unique_ptr<WCHAR[]> wchar_ptr(new wchar_t[size + 1]);
	mbstowcs_s(nullptr, wchar_ptr.get(), size + 1, char_ptr.get(), _TRUNCATE);
	key = path + std::wstring(wchar_ptr.get());
}