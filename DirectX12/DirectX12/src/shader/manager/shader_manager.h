/**
* @file shader_manager.h
* @brief �V�F�[�_�[���Ǘ�����N���X
* @author �ΎR�@�I
* @date 2019/03/09
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"
#include <saki/singleton.h>
#include <unordered_map>
#include <string>

/**
* @brief �V�F�[�_�[���Ǘ�����N���X
*/
class ShaderManager :public saki::singleton<ShaderManager>
{
	/**
	* @brief �V�F�[�_�[�̏��\����
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