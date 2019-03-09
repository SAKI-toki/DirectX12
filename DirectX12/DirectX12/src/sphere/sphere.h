#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include "../pipeline/pipeline.h"

class Sphere
{
	static constexpr int VERT_NUM = 32;//一つの弧を作る頂点の数
	static constexpr int ARC_NUM = 32;//球を作る弧の数
	struct Vertex3D
	{
		Float3 pos;
		Float3 nor;
	};
	//球体の定数構造体
	struct SphereConstant
	{
		Matrix m;
		Float4 col;
	};
	ComPtr<ID3D12Resource> vertex_buffer;
	D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
	ComPtr<ID3D12Resource> index_buffer;
	D3D12_INDEX_BUFFER_VIEW index_buffer_view;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateSphere();
	HRESULT CreateBuffer();
	Pipeline pipeline;
public:
	HRESULT Init(Float4); 
	HRESULT UpdateTransform(const Transform&);
	HRESULT UpdateColor(const Float4&);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>&);
};