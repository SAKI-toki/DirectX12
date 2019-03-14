/**
* @file texture_manager.h
* @brief �e�N�X�`�����Ǘ�����N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"
#include <saki/singleton.h>
#include <unordered_map>
#include <string>

/**
* @brief �e�N�X�`�����Ǘ�����N���X
*/
class TextureManager :public saki::singleton<TextureManager>
{
	friend class Texture;
	/**
	* @brief �e�N�X�`���̏��\����
	*/
	struct TextureData
	{
		int width, height;
		ComPtr<ID3D12Resource> texture;
		ComPtr<ID3D12DescriptorHeap> dh_texture;
	};
	std::unordered_map<std::wstring, TextureData> texture_data_map;
	HRESULT LoadTexture(const std::wstring& path);
	void SetTexture(const std::wstring& key, 
		ComPtr<ID3D12GraphicsCommandList>& com_command_list);
	int GetWidth(const std::wstring& key);
	int GetHeight(const std::wstring& key);
};