/**
* @file shader_manager.h
* @brief シェーダーを管理するクラス
* @author 石山　悠
* @date 2019/03/09
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"
#include <saki/singleton.h>
#include <unordered_map>
#include <string>

/**
* @brief シェーダーを管理するクラス
*/
class ShaderManager :public saki::singleton<ShaderManager>
{
	friend class Shader;
	std::unordered_map<std::wstring, ComPtr<ID3DBlob>> shader_data_map;
	HRESULT LoadShader(const std::wstring&, const std::wstring&, const std::string&, const std::string&);
	ComPtr<ID3DBlob>& GetShader(const std::wstring&);
};