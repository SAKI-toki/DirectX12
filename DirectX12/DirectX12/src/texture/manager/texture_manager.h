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
#include <string>
#include <memory>

/**
* @brief テクスチャを管理するクラス
*/
class TextureManager :public saki::singleton<TextureManager>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	TextureManager();
	~TextureManager()noexcept;
	HRESULT LoadTexture(const std::wstring& path);
	void SetTexture(const std::wstring& key, 
		ComPtr<ID3D12GraphicsCommandList>& com_command_list);
	int GetWidth(const std::wstring& key);
	int GetHeight(const std::wstring& key);
};