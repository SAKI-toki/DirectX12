/**
* @file sprite.h
* @brief �X�v���C�g�N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include "../texture/texture.h"
#include "../command_list/Bundle/bundle.h"

class Sprite
{
	/**
	* @brief ���_���
	*/
	struct Vertex2D
	{
		Float3 pos;
		Float2 uv;
	};
	/**
	* @brief �萔�o�b�t�@�ɑ�����
	*/
	struct SpriteConstant
	{
		Matrix m;
		Float4 col;
	};
	ComPtr<ID3D12Resource> vertex_buffer;
	D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateBuffer();
	HRESULT CreatePlane();
	Texture texture;
	Bundle bundle;
	HRESULT SetBundle();
public:
	HRESULT Init(const std::wstring&, ComPtr<ID3D12PipelineState>&);
	HRESULT UpdateTransform(const Transform&);
	HRESULT UpdateColor(const Float4&);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>&);
};