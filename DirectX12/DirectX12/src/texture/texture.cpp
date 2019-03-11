/**
* @file texture.cpp
* @brief テクスチャクラスの関数定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "texture.h"

HRESULT Texture::LoadTexture(const std::wstring& _path)
{
	path = _path;
	return TextureManager::getinstance()->LoadTexture(path);
}

void Texture::SetTexture(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	TextureManager::getinstance()->SetTexture(path, command_list);
}

int Texture::GetWidth()
{
	return TextureManager::getinstance()->GetWidth(path);
}

int Texture::GetHeight()
{
	return TextureManager::getinstance()->GetHeight(path);
}