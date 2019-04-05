/**
* @file sprite.cpp
* @brief �X�v���C�g�N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/02/08
*/
#include "sprite.h"
#include "../device/device.h"
#include "../camera/camera.h"
#include "../common/message_box.h"
#include "../texture/texture.h"
#include "../command_list/Bundle/bundle.h"

/**
* @brief �X�v���C�g��pimpl�C�f�B�I��
*/
class Sprite::Impl
{
public:
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
	HRESULT UpdateTransform(const Transform& transform);
};

#pragma region public

/**
* @brief �X�v���C�g�̃R���X�g���N�^
*/
Sprite::Sprite() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�A���[�u�R���X�g���N�^�A���[�u������Z�q�̃f�t�H���g�w��
Sprite::~Sprite()noexcept = default;
Sprite::Sprite(Sprite&&)noexcept = default;
Sprite& Sprite::operator=(Sprite&&)noexcept = default;

/**
* @brief �X�v���C�g�̏�����
* @param path �e�N�X�`���̃p�X
* @param pipeline �`�悷��p�C�v���C��
* @return �����������ǂ���
*/
HRESULT Sprite::Init(const std::wstring& path, ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	hr = pimpl->CreateBuffer();
	if (FAILED(hr))return hr;
	hr = pimpl->texture.LoadTexture(path);
	if (FAILED(hr))return hr;
	hr = pimpl->CreatePlane();
	if (FAILED(hr))return hr;
	hr = pimpl->bundle.Init(pipeline);
	if (FAILED(hr))return hr;
	hr = pimpl->SetBundle();
	if (FAILED(hr))return hr;
	hr = pimpl->bundle.Close();
	if (FAILED(hr))return hr;
	hr = pimpl->UpdateTransform({});
	if (FAILED(hr))return hr;
	hr = UpdateColor({ 1.0f,1.0f,1.0f,1.0f });
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief Color�̍X�V
* @return �����������ǂ���
*/
HRESULT Sprite::UpdateColor(const Float4& color)
{
	HRESULT hr = S_OK;

	Sprite::Impl::SpriteConstant *buf{};
	hr = pimpl->constant_buffer->Map(0, nullptr, reinterpret_cast<void**>(&buf));
	if (FAILED(hr))
	{
		Comment(L"�萔�o�b�t�@��Map�Ɏ��s",
			L"sprite.cpp/Sprite::UpdateColor");
		return hr;
	}
	buf->col = color;
	pimpl->constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

/**
* @brief �X�v���C�g�̕`��
* @param transform �ʒu���]�A�g�k
* @param command_list ���߂𑗂�R�}���h���X�g
* @return �����������ǂ���
*/
HRESULT Sprite::Draw(const Transform& transform, ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	HRESULT hr = S_OK;

	hr = pimpl->UpdateTransform(transform);
	if (FAILED(hr))return hr;
	//�e�N�X�`�����Z�b�g
	pimpl->texture.SetTexture(command_list);
	command_list->ExecuteBundle(pimpl->bundle.GetCommandList().Get());

	return hr;
}

#pragma endregion

#pragma region private

/**
* @brief �o�b�t�@�̍쐬
* @return �����������ǂ���
*/
HRESULT Sprite::Impl::CreateBuffer()
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
			L"sprite.cpp/Sprite::CreateBuffer");
		return hr;
	}

	resource_desc.Width = sizeof(Vertex2D) * 4;
	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertex_buffer));
	if (FAILED(hr))
	{
		Comment(L"���_�o�b�t�@�p�̃��\�[�X�ƃq�[�v�̍쐬�Ɏ��s",
			L"sprite.cpp/Sprite::CreateBuffer");
		return hr;
	}
	vertex_buffer_view.BufferLocation = vertex_buffer->GetGPUVirtualAddress();
	vertex_buffer_view.StrideInBytes = sizeof(Vertex2D);
	vertex_buffer_view.SizeInBytes = sizeof(Vertex2D) * 4;

	return hr;
}

/**
* @brief �̍쐬
* @return �����������ǂ���
*/
HRESULT Sprite::Impl::CreatePlane()
{
	HRESULT hr = S_OK;

	float texture_size_x = static_cast<float>(texture.GetWidth());
	float texture_size_y = static_cast<float>(texture.GetHeight());
	if (texture_size_x == -1.0f || texture_size_y == -1.0f)
	{
		Comment(L"����Ƀe�N�X�`���̃T�C�Y��ǂݍ��߂܂���ł���",
			L"sprite.cpp/Sprite::CreatePlane");
		return E_FAIL;
	}
	Vertex2D *vb{};
	hr = vertex_buffer->Map(0, nullptr, reinterpret_cast<void**>(&vb));
	if (FAILED(hr))
	{
		delete[](vb);
		Comment(L"���_�o�b�t�@��Map�Ɏ��s", L"sprite.cpp/Sprite::CreatePlane");
		return hr;
	}
	vb[0] = Vertex2D{ Float3{-texture_size_x,-texture_size_y,0.0f},Float2{0,1} };
	vb[1] = Vertex2D{ Float3{-texture_size_x,+texture_size_y,0.0f},Float2{0,0} };
	vb[2] = Vertex2D{ Float3{+texture_size_x,-texture_size_y,0.0f},Float2{1,1} };
	vb[3] = Vertex2D{ Float3{+texture_size_x,+texture_size_y,0.0f},Float2{1,0} };
	vertex_buffer->Unmap(0, nullptr);
	vb = nullptr;

	return hr;
}

/**
* @brief �o���h���ɃR�}���h���Z�b�g����
* @return �����������ǂ���
*/
HRESULT Sprite::Impl::SetBundle()
{
	HRESULT hr = S_OK;

	decltype(auto) bundle_command_list = bundle.GetCommandList();

	bundle_command_list->SetGraphicsRootSignature(Device::getinstance()->GetRootSignature().Get());

	//�萔�o�b�t�@���Z�b�g
	bundle_command_list->SetGraphicsRootConstantBufferView(0, constant_buffer->GetGPUVirtualAddress());

	bundle_command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	bundle_command_list->IASetVertexBuffers(0, 1, &vertex_buffer_view);

	//�`��
	bundle_command_list->DrawInstanced(4, 1, 0, 0);
	return hr;
}

/**
* @brief Transform�̍X�V
*/
HRESULT Sprite::Impl::UpdateTransform(const Transform& transform)
{
	HRESULT hr = S_OK;

	auto world = DirectX::XMMatrixIdentity();
	auto scale = transform.get_scale();
	Matrix scale_mat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	auto rot = transform.get_rot();
	Matrix rot_mat = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	auto pos = transform.get_pos();
	Matrix pos_mat = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	world = world * scale_mat * rot_mat * pos_mat;
	Matrix mat = DirectX::XMMatrixTranspose(world * Camera::getinstance()->GetViewMulProjection());
	SpriteConstant *buf{};
	hr = constant_buffer->Map(0, nullptr, reinterpret_cast<void**>(&buf));
	if (FAILED(hr))
	{
		Comment(L"�萔�o�b�t�@��Map�Ɏ��s",
			L"sprite.cpp/Sprite::UpdateTransform");
		return hr;
	}
	buf->m = mat;
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

#pragma endregion