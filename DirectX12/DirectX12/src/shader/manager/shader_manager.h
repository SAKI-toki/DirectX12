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
	/**
	* @brief シェーダーの情報構造体
	*/
	struct ShaderData
	{
		ComPtr<ID3DBlob> vertex_shader;
		ComPtr<ID3DBlob> pixel_shader;
	};
	friend class Shader;
	std::unordered_map<std::string, ShaderData> shader_data_map;
	HRESULT LoadShader(const std::string&, const WCHAR*);
};