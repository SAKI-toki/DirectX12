/**
* @file shader_manager.cpp
* @brief シェーダーを管理するクラスのメンバ関数を定義
* @author 石山　悠
* @date 2019/03/09
*/
#include "shader_manager.h"
#include "../../common/message_box.h"

HRESULT ShaderManager::LoadShader(const std::wstring& path, 
	const std::string& entry, const std::string& target)
{
	HRESULT hr = S_OK;

	auto itr = shader_data_map.find(path);
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
	shader_data_map.insert(std::make_pair(path, blob));
	return hr;
}

ComPtr<ID3DBlob>& ShaderManager::GetShader(const std::wstring& path)
{
	return (shader_data_map.find(path)->second);
}