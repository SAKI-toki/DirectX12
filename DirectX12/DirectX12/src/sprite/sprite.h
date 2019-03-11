/**
* @file sprite.h
* @brief スプライトクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../common/d3d12.h"
#include "../texture/texture.h"
#include "../pipeline/pipeline.h"

class Sprite
{
	struct Vertex2D
	{
		Float3 pos;
		Float2 uv;
	};
	ComPtr<ID3D12Resource> vertex_buffer;
	D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateBuffer();
	HRESULT CreatePlane();
	Texture texture;
	Pipeline pipeline;
public:
	HRESULT Init(const std::wstring&);
	HRESULT UpdateTransform(const Transform&);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>&);
};