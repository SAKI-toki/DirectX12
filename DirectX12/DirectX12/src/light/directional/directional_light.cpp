/**
* @file directional_light.cpp
* @brief ���s�����N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2019/03/29
*/
#include "directional_light.h"
#include "../../common/message_box.h"

/**
* @brief ���s������pimpl�C�f�B�I��
*/
class DirectionalLight::Impl
{
public:
	/**
	* @brief ���s�����̒萔�\����
	*/
	struct DirectionalLightConstant
	{
		Float4 pos;
		//Matrix light_vp;
	};
	//���C�g�̈ʒu
	Vec3 light_pos{ 2.0f, 6.5f, -1.0f };
	//���C�g�̒萔�o�b�t�@
	ComPtr<ID3D12Resource> constant_buffer;
};

#pragma region public

/**
* @brief ���s�����N���X�̃R���X�g���N�^
*/
DirectionalLight::DirectionalLight() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�̃f�t�H���g�w��
DirectionalLight::~DirectionalLight()noexcept = default;

/**
* @brief ���s�����̏�����
* @param device �f�o�C�X
* @return �����������ǂ���
*/
HRESULT DirectionalLight::Init(ComPtr<ID3D12Device>& device)
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

	hr = device->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pimpl->constant_buffer));
	if (FAILED(hr))
	{
		Comment(L"�萔�o�b�t�@�p�̃��\�[�X�ƃq�[�v�̍쐬�Ɏ��s",
			L"directional_light.cpp/DirectionalLight::Init");
		return hr;
	}

	return hr;
}

/**
* @brief ���s�����̍X�V
* @return �����������ǂ���
*/
HRESULT DirectionalLight::Update()
{
	HRESULT hr = S_OK;

	DirectionalLight::Impl::DirectionalLightConstant* buf{};
	hr = pimpl->constant_buffer->Map(0, nullptr, reinterpret_cast<void**>(&buf));
	if (FAILED(hr))
	{
		Comment(L"�萔�o�b�t�@��Map�Ɏ��s",
			L"directional_light.cpp/DirectionalLight::Update");
		return hr;
	}
	buf->pos = Float4{ pimpl->light_pos.x,pimpl->light_pos.y,pimpl->light_pos.z,0.0f };

	pimpl->constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

/**
* @brief �萔�o�b�t�@�̃Z�b�g
* @param command_list �Z�b�g����R�}���h���X�g
* @return �����������ǂ���
*/
HRESULT DirectionalLight::SetConstantBuffer(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	HRESULT hr = S_OK;

	command_list->SetGraphicsRootConstantBufferView(2, pimpl->constant_buffer->GetGPUVirtualAddress());

	return hr;
}

/**
* @brief ���s�����̈ʒu�̃Q�b�^
* @return ���s�����̈ʒu
*/
Vec3 DirectionalLight::GetPos()const
{
	return pimpl->light_pos;
}

/**
* @brief ���s�����̈ʒu�̃Z�b�^
* @param pos ���s�����̐V�����ʒu
*/
void DirectionalLight::SetPos(const Vec3& pos)
{
	//�ʒu��{0,0,0}�̏ꍇ�͉����������Ȃ�
	if (pos == Vec3{})return;
	pimpl->light_pos = pos;
}

#pragma endregion