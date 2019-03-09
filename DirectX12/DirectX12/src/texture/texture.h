/**
* @file texture.h
* @brief テクスチャクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "manager/texture_manager.h"
class Texture
{
	std::string key;
public:
	HRESULT LoadTexture(const std::string&, const WCHAR*);
	void SetTexture(ComPtr<ID3D12GraphicsCommandList>&);
	int GetWidth();
	int GetHeight();
	std::string GetKey()const;
};