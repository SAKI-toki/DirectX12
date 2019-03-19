/**
* @file sphere.h
* @brief �X�t�B�A�N���X
* @author �ΎR�@�I
* @date 2019/03/12
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include "../texture/texture.h"
#include "../command_list/Bundle/bundle.h"

/**
* @brief �X�t�B�A�N���X
*/
class Sphere
{
	static constexpr int VERT_NUM = 32;//��̌ʂ���钸�_�̐�
	static constexpr int ARC_NUM = 32;//�������ʂ̐�
	/**
	* @brief ���_���
	*/
	struct Vertex3D
	{
		Float3 pos;
		Float3 nor;
		Float2 uv;
	};
	/**
	* @brief ���̂̒萔�\����
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