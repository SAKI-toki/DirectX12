/**
* @file texture.cpp
* @brief �e�N�X�`���N���X�̊֐���`
* @author �ΎR�@�I
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