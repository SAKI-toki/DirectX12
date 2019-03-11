/**
* @file texture.h
* @brief �e�N�X�`���N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "manager/texture_manager.h"
class Texture
{
	std::wstring path;
public:
	HRESULT LoadTexture(const std::wstring&);
	void SetTexture(ComPtr<ID3D12GraphicsCommandList>&);
	int GetWidth();
	int GetHeight();
};