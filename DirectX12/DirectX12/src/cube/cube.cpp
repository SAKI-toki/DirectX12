/**
* @file cube.cpp
* @brief �L���[�u�N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/02/08
*/
#include "cube.h"
#include "../texture/texture.h"
#include "../command_list/Bundle/bundle.h"
#include "../device/device.h"
#include "../camera/camera.h"
#include "../common/message_box.h"
#include "../light/directional/directional_light.h"

/**
* @brief �L���[�u��pimpl�C�f�B�I��
*/
class Cube::Impl
{
	/**
	* @brief ���_�̍\����
	*/
	struct Vertex3D
	{
		Float3 pos;
		Float3 nor;
		Float2 uv;
	};
	/**
	* @brief �L���[�u�p�̒萔�\����
	*/
	struct CubeConstant
	{
		Matrix wvp;
		Matrix world;
		Matrix view;
		Matrix projection;
	};
	ComPtr<ID3D12Resource> vertex_buffer;
	D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view{};
	ComPtr<ID3D12Resource> index_buffer;
	D3D12_INDEX_BUFFER_VIEW index_buffer_view{};
	ComPtr<ID3D12Resource> constant_buffer;
public:
	Texture texture;
	Bundle bundle;
	HRESULT UpdateTransform(const Transform& transform);
	HRESULT CreateBuffer();
	HRESULT CreateCube();
	HRESULT SetBundle();
};

#pragma region public

/**
* @brief �R���X�g���N�^
*/
Cube::Cube() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�A���[�u�R���X�g���N�^�A���[�u������Z�q�̃f�t�H���g�w��
Cube::~Cube()noexcept = default;
Cube& Cube::operator=(Cube&&)noexcept = default;
Cube::Cube(Cube&&)noexcept = default;

/**
* @brief �L���[�u�̏�����
* @param path �e�N�X�`���̃p�X
* @param pipeline �`�悷��p�C�v���C��
* @return �����������ǂ���
*/
HRESULT Cube::Init(const std::wstring& path, ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	hr = pimpl->CreateBuffer();
	if (FAILED(hr))return hr;
	hr = pimpl->CreateCube();
	if (FAILED(hr))return hr;
	hr = pimpl->texture.LoadTexture(path);
	if (FAILED(hr))return hr;
	hr = pimpl->bundle.Init(pipeline);
	if (FAILED(hr))return hr;
	hr = pimpl->SetBundle();
	if (FAILED(hr))return hr;
	hr = pimpl->bundle.Close();
	if (FAILED(hr))return hr;
	hr = pimpl->UpdateTransform({});
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief �L���[�u�̕`��
* @param transform �ʒu���]�A�g�k
* @param command_list ���߂𑗂�R�}���h���X�g
* @return �����������ǂ���
*/
HRESULT Cube::Draw(const Transform& transform, ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	HRESULT hr = S_OK;

	hr = pimpl->UpdateTransform(transform);
	if (FAILED(hr))return hr;
	//�e�N�X�`�����Z�b�g
	pimpl->texture.SetTexture(command_list);
	pimpl->bundle.SetExecuteCommandList(command_list);

	return hr;
}

#pragma endregion

#pragma region pimpl

/**
* @brief �o�b�t�@�̍쐬
* @return �����������ǂ���
*/
HRESULT Cube::Impl::CreateBuffer()
{
	HRESULT hr = S_OK;

	D3D12_HEAP_PROPERTIES heap_properties{};
	heap_properties.Type = D3D12_HEAP_TYPE_UPLOAD;
	heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap_properties.CreationNodeMask = 0;
	heap_properties.VisibleNodeMask = 0;

	D3D12_RESOURCE_DESC resource_desc{};
	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resource_desc.Width = 256;
	resource_desc.Height = 1;
	resource_desc.DepthOrArraySize = 1;
	resource_desc.MipLevels = 1;
	resource_desc.Format = DXGI_FORMAT_UNKNOWN;
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;


	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&constant_buffer));
	if (FAILED(hr))
	{
		Comment(L"�萔�o�b�t�@�p�̃��\�[�X�ƃq�[�v�̍쐬�Ɏ��s",
			L"cube.cpp/Cube::Impl::CreateBuffer");
		return hr;
	}

	//���_�̐�
	resource_desc.Width = sizeof(Vertex3D) * 24;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertex_buffer));
	if (FAILED(hr))
	{
		Comment(L"���_�o�b�t�@�p�̃��\�[�X�ƃq�[�v�̍쐬�Ɏ��s",
			L"cube.cpp/Cube::Impl::CreateBuffer");
		return hr;
	}
	vertex_buffer_view.BufferLocation = vertex_buffer->GetGPUVirtualAddress();
	vertex_buffer_view.StrideInBytes = sizeof(Vertex3D);
	vertex_buffer_view.SizeInBytes = sizeof(Vertex3D) * 24;

	//�C���f�b�N�X�̐�
	resource_desc.Width = sizeof(WORD) * 36;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&index_buffer));
	if (FAILED(hr))
	{
		Comment(L"�C���f�b�N�X�o�b�t�@�p�̃��\�[�X�ƃq�[�v�̍쐬�Ɏ��s",
			L"cube.cpp/Cube::Impl::CreateBuffer");
		return hr;
	}

	index_buffer_view.BufferLocation = index_buffer->GetGPUVirtualAddress();
	index_buffer_view.SizeInBytes = sizeof(WORD) * 36;
	index_buffer_view.Format = DXGI_FORMAT_R16_UINT;

	return hr;
}

/**
* @brief �L���[�u�̍쐬
* @return �����������ǂ���
*/
HRESULT Cube::Impl::CreateCube()
{
	HRESULT hr = S_OK;
	//���_�̐ݒ�
	{
		Vertex3D *vb{};
		hr = vertex_buffer->Map(0, nullptr, reinterpret_cast<void**>(&vb));
		if (FAILED(hr))
		{
			delete[](vb);
			Comment(L"���_�o�b�t�@��Map�Ɏ��s",
				L"cube.cpp/Cube::Impl::CreateCube");
			return hr;
		}
		vb[0] = Vertex3D{ Float3{-0.5f,-0.5f,-0.5f},Float3{0.0f,0.0f,-1.0f},Float2{0,1} };
		vb[1] = Vertex3D{ Float3{-0.5f,0.5f,-0.5f},Float3{0.0f,0.0f,-1.0f},Float2{0,0} };
		vb[2] = Vertex3D{ Float3{0.5f,-0.5f,-0.5f},Float3{0.0f,0.0f,-1.0f},Float2{1,1} };
		vb[3] = Vertex3D{ Float3{0.5f,0.5f,-0.5f},Float3{0.0f,0.0f,-1.0f},Float2{1,0} };

		vb[4] = Vertex3D{ Float3{-0.5f,0.5f,0.5f},Float3{0.0f,0.0f,1.0f},Float2{0,0} };
		vb[5] = Vertex3D{ Float3{-0.5f,-0.5f,0.5f},Float3{0.0f,0.0f,1.0f},Float2{0,1} };
		vb[6] = Vertex3D{ Float3{0.5f,0.5f,0.5f},Float3{0.0f,0.0f,1.0f},Float2{1,0} };
		vb[7] = Vertex3D{ Float3{0.5f,-0.5f,0.5f},Float3{0.0f,0.0f,1.0f},Float2{1,1} };

		vb[8] = Vertex3D{ Float3{-0.5f,0.5f,0.5f},Float3{-1.0f,0.0f,0.0f},Float2{0,0} };
		vb[9] = Vertex3D{ Float3{-0.5f,0.5f,-0.5f},Float3{-1.0f,0.0f,0.0f},Float2{1,0} };
		vb[10] = Vertex3D{ Float3{-0.5f,-0.5f,0.5f},Float3{-1.0f,0.0f,0.0f},Float2{0,1} };
		vb[11] = Vertex3D{ Float3{-0.5f,-0.5f,-0.5f},Float3{-1.0f,0.0f,0.0f},Float2{1,1} };

		vb[12] = Vertex3D{ Float3{0.5f,0.5f,0.5f},Float3{1.0f,0.0f,0.0f},Float2{0,0} };
		vb[13] = Vertex3D{ Float3{0.5f,-0.5f,0.5f},Float3{1.0f,0.0f,0.0f},Float2{1,0} };
		vb[14] = Vertex3D{ Float3{0.5f,0.5f,-0.5f},Float3{1.0f,0.0f,0.0f},Float2{0,1} };
		vb[15] = Vertex3D{ Float3{0.5f,-0.5f,-0.5f},Float3{1.0f,0.0f,0.0f},Float2{1,1} };

		vb[16] = Vertex3D{ Float3{-0.5f,0.5f,0.5f},Float3{0.0f,1.0f,0.0f},Float2{0,0} };
		vb[17] = Vertex3D{ Float3{0.5f,0.5f,0.5f},Float3{0.0f,1.0f,0.0f},Float2{1,0} };
		vb[18] = Vertex3D{ Float3{-0.5f,0.5f,-0.5f},Float3{0.0f,1.0f,0.0f},Float2{0,1} };
		vb[19] = Vertex3D{ Float3{0.5f,0.5f,-0.5f},Float3{0.0f,1.0f,0.0f},Float2{1,1} };

		vb[20] = Vertex3D{ Float3{-0.5f,-0.5f,0.5f},Float3{0.0f,-1.0f,0.0f},Float2{0,0} };
		vb[21] = Vertex3D{ Float3{-0.5f,-0.5f,-0.5f},Float3{0.0f,-1.0f,0.0f},Float2{1,0} };
		vb[22] = Vertex3D{ Float3{0.5f,-0.5f,0.5f},Float3{0.0f,-1.0f,0.0f},Float2{0,1} };
		vb[23] = Vertex3D{ Float3{0.5f,-0.5f,-0.5f},Float3{0.0f,-1.0f,0.0f},Float2{1,1} };
		vertex_buffer->Unmap(0, nullptr);
		vb = nullptr;
	}
	//�C���f�b�N�X�̐ݒ�
	{
		WORD *ib{};
		hr = index_buffer->Map(0, nullptr, reinterpret_cast<void**>(&ib));
		if (FAILED(hr))
		{
			Comment(L"�C���f�b�N�X�o�b�t�@��Map�Ɏ��s",
				L"cube.cpp/Cube::Impl::CreateCube");
			return hr;
		}
		ib[0] = 0; ib[1] = 1; ib[2] = 2; ib[3] = 3; ib[4] = 2; ib[5] = 1;
		ib[6] = 4; ib[7] = 5; ib[8] = 6; ib[9] = 7; ib[10] = 6; ib[11] = 5;
		ib[12] = 8; ib[13] = 9; ib[14] = 10; ib[15] = 11; ib[16] = 10; ib[17] = 9;
		ib[18] = 12; ib[19] = 13; ib[20] = 14; ib[21] = 15; ib[22] = 14; ib[23] = 13;
		ib[24] = 16; ib[25] = 17; ib[26] = 18; ib[27] = 19; ib[28] = 18; ib[29] = 17;
		ib[30] = 20; ib[31] = 21; ib[32] = 22; ib[33] = 23; ib[34] = 22; ib[35] = 21;
		index_buffer->Unmap(0, nullptr);
		ib = nullptr;
	}
	return hr;
}

/**
* @brief �o���h���ɃR�}���h���Z�b�g����
* @return �����������ǂ���
*/
HRESULT Cube::Impl::SetBundle()
{
	HRESULT hr = S_OK;

	decltype(auto) bundle_command_list = bundle.GetCommandList();

	bundle_command_list->SetGraphicsRootSignature(Device::getinstance()->GetRootSignature().Get());

	//�萔�o�b�t�@���Z�b�g
	bundle_command_list->SetGraphicsRootConstantBufferView(0, constant_buffer->GetGPUVirtualAddress());

	bundle_command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	bundle_command_list->IASetVertexBuffers(0, 1, &vertex_buffer_view);
	bundle_command_list->IASetIndexBuffer(&index_buffer_view);

	//�`��
	bundle_command_list->DrawIndexedInstanced(36, 1, 0, 0, 0);

	return hr;
}

/**
* @brief Transform�̍X�V
* @param transform �V����Transform
* @return �����������ǂ���
*/
HRESULT Cube::Impl::UpdateTransform(const Transform& transform)
{
	HRESULT hr = S_OK;

	auto scale = transform.get_scale();
	Matrix scale_mat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	auto rot = transform.get_rot();
	Matrix rot_mat = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	auto pos = transform.get_pos();
	Matrix pos_mat = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	Matrix world = scale_mat * rot_mat * pos_mat;
	Matrix mat = DirectX::XMMatrixTranspose(world * Camera::getinstance()->GetViewMulProjection());
	CubeConstant *buf{};
	hr = constant_buffer->Map(0, nullptr, reinterpret_cast<void**>(&buf));
	if (FAILED(hr))
	{
		Comment(L"�萔�o�b�t�@��Map�Ɏ��s",
			L"cube.cpp/Cube::Impl::UpdateTransform");
		return hr;
	}
	buf->wvp = mat;
	buf->world = DirectX::XMMatrixTranspose(world);
	buf->view = DirectX::XMMatrixTranspose(Camera::getinstance()->GetView());
	buf->projection = DirectX::XMMatrixTranspose(Camera::getinstance()->GetProjection());
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

#pragma endregion