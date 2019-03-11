/**
* @file cube.h
* @brief キューブクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include "../texture/texture.h"
#include "../pipeline/pipeline.h"

/**
* @brief キューブクラス
*/
class Cube
{
	/**
	* @brief 頂点の構造体
	*/
	struct Vertex3D
	{
		Float3 pos;
		Float3 nor;
		Float2 uv;
	};
	/**
	* @brief キューブ用の定数構造体
	*/
	struct CubeConstant
	{
		Matrix m;
	};
	ComPtr<ID3D12Resource> vertex_buffer;
	D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
	ComPtr<ID3D12Resource> index_buffer;
	D3D12_INDEX_BUFFER_VIEW index_buffer_view;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateBuffer();
	HRESULT CreateCube();
	Texture texture;
	Pipeline pipeline;

public:
	HRESULT Init(const std::wstring&);
	HRESULT UpdateTransform(const Transform&);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>&);
};