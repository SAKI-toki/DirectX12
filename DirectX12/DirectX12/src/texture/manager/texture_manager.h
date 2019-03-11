/**
* @file texture_manager.h
* @brief テクスチャを管理するクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../../common/d3d12.h"
#include "../../common/alias.h"
#include <saki/singleton.h>
#include <unordered_map>
#include <string>

/**
* @brief テクスチャを管理するクラス
*/
class TextureManager :public saki::singleton<TextureManager>
{
	/**
	* @brief テクスチャの情報構造体
	*/
	struct TextureData
	{
		int width, height;
		ComPtr<ID3D12Resource> texture;
		ComPtr<ID3D12DescriptorHeap> dh_texture;
	};
	std::unordered_map<std::wstring, TextureData> texture_data_map;
	friend class Texture;
	HRESULT LoadTexture(const std::wstring&);
	void SetTexture(const std::wstring&, ComPtr<ID3D12GraphicsCommandList>&);
	int GetWidth(const std::wstring&);
	int GetHeight(const std::wstring&);
};