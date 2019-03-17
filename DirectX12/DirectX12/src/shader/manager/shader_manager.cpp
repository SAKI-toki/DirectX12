/**
* @file shader_manager.cpp
* @brief シェーダーを管理するクラスのメンバ関数を定義
* @author 石山　悠
* @date 2019/03/09
*/
#include "shader_manager.h"
#include "../../common/message_box.h"

/**
* @brief シェーダーの読み込み
* @param key キー
* @param path シェーダーのパス
* @param entry エントリー
* @param target ターゲット
* @return 成功したかどうか
*/
HRESULT ShaderManager::LoadShader(const std::wstring& key, const std::wstring& path,
	const std::string& entry, const std::string& target)
{
	HRESULT hr = S_OK;

	auto itr = shader_data_map.find(key);
	//既に読み込んでいる場合
	if (itr != std::end(shader_data_map)) { return hr; }
	
	UINT compile_flg = 0;
#ifdef _DEBUG
	compile_flg = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ComPtr<ID3DBlob> blob;
	hr = D3DCompileFromFile(path.c_str(), nullptr, nullptr, entry.c_str(), target.c_str(),
		compile_flg, 0, blob.GetAddressOf(), nullptr);
	if (FAILED(hr))
	{
		Comment(L"シェーダーのコンパイルに失敗", 
			L"shader_manager.cpp/ShaderManager::LoadShader");
		return hr;
	}
	shader_data_map.insert(std::make_pair(key, blob));
	return hr;
}

/**
* @brief シェーダーのゲッタ
* @param key キー
* @return シェーダー
*/
ComPtr<ID3DBlob>& ShaderManager::GetShader(const std::wstring& key)
{
	auto itr = shader_data_map.find(key);
	if (itr == shader_data_map.end())throw 0;
	return (itr->second);
}
