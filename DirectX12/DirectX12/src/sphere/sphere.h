/**
* @file sphere.h
* @brief スフィアクラス
* @author 石山　悠
* @date 2019/03/12
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include "../texture/texture.h"
#include "../command_list/Bundle/bundle.h"

/**
* @brief スフィアクラス
*/
class Sphere
{
	static constexpr int VERT_NUM = 32;//一つの弧を作る頂点の数
	static constexpr int ARC_NUM = 32;//球を作る弧の数
	/**
	* @brief 頂点情報
	*/
	struct Vertex3D
	{
		Float3 pos;
		Float3 nor;
		Float2 uv;
	};
	/**
	* @brief 球体の定数構造体
	*/
	struct SphereConstant
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
	HRESULT CreateSphere();
	HRESULT CreateBuffer();
	Texture texture;
	Bundle bundle;
	HRESULT SetBundle();
public:
	HRESULT Init(const std::wstring& tex_path, ComPtr<ID3D12PipelineState>& com_pipeline);
	HRESULT UpdateTransform(const Transform& transform);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>& com_command_list);
};