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
#include "../command_list/Bundle/bundle.h"

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
		Matrix world;
		Float4 light;
	};
	ComPtr<ID3D12Resource> vertex_buffer;
	D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
	ComPtr<ID3D12Resource> index_buffer;
	D3D12_INDEX_BUFFER_VIEW index_buffer_view;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateBuffer();
	HRESULT CreateCube();
	Texture texture;
	Bundle bundle;
	HRESULT SetBundle();
public:
	HRESULT Init(const std::wstring& tex_path, ComPtr<ID3D12PipelineState>& com_pipeline);
	HRESULT UpdateTransform(const Transform& transform);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>& com_command_list);
};