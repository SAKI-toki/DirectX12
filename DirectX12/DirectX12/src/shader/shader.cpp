/**
* @file shader.cpp
* @brief シェーダークラスのメンバ関数を定義
* @author 石山　悠
* @date 2019/03/09
*/
#include "shader.h"

/**
* @brief シェーダークラスのpimplイディオム
*/
class Shader::Impl
{
public:
	std::wstring key;
	void KeyGenerate(const std::wstring& path, 
		const std::string& entry, const std::string& target);
};

#pragma region public

Shader::Shader() :
	pimpl(new Impl{})
{}

//デストラクタ、ムーブコンストラクタ、ムーブ代入演算子のデフォルト指定
Shader::~Shader()noexcept = default;
Shader::Shader(Shader&&)noexcept = default;
Shader& Shader::operator=(Shader&&)noexcept = default;

/**
* @brief シェーダーの読み込み
* @param path シェーダーのパス
* @param entry エントリー
* @param target ターゲット
* @return 成功したかどうか
*/
HRESULT Shader::LoadShader(const std::wstring& path, 
	const std::string& entry, const std::string& target)
{
	HRESULT hr = S_OK;

	pimpl->KeyGenerate(path, entry, target);
	hr = ShaderManager::getinstance()->LoadShader(pimpl->key, path, entry, target);
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief シェーダーのゲッタ
* @return シェーダー
*/
ComPtr<ID3DBlob>& Shader::GetShader()
{
	return ShaderManager::getinstance()->GetShader(pimpl->key);
}

#pragma endregion 

#pragma region pimpl

/**
* @brief マネージャーに送る用のキーを生成する
*/
void Shader::Impl::KeyGenerate(const std::wstring& path,
	const std::string& entry, const std::string& target)
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

#pragma endregion