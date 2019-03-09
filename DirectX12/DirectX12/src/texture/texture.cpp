/**
* @file texture.cpp
* @brief テクスチャクラスの関数定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "texture.h"

HRESULT Texture::LoadTexture(const std::string& _key, const WCHAR* path)
{
	key = _key;
	return TextureManager::getinstance()->LoadTexture(key, path);
}

void Texture::SetTexture(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	TextureManager::getinstance()->SetTexture(key, command_list);
}

int Texture::GetWidth()
{
	return TextureManager::getinstance()->GetWidth(key);
}

int Texture::GetHeight()
{
	return TextureManager::getinstance()->GetHeight(key);
}

std::string Texture::GetKey()const
{
	return key;
}