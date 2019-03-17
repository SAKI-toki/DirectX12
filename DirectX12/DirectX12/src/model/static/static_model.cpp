/**
* @file static_model.cpp
* @brief �A�j���[�V�����Ȃ����f���N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/03/18
*/
#include "static_model.h"
#include "../../common/message_box.h"
#include "../../camera/camera.h"
#include "../../device/device.h"

#pragma region public

/**
* @brief �A�j���[�V�����Ȃ����f���N���X�̏�����
* @param model_path ���f���̃p�X
* @param pipeline �`�悷��p�C�v���C��
* @return �����������ǂ���
*/
HRESULT StaticModel::Init(const std::wstring& model_path,
	ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	key = model_path;
	hr = CreateBuffer();
	if (FAILED(hr))return hr;
	hr = StaticModelManager::getinstance()->LoadModel(key);
	if (FAILED(hr))return hr;
	hr = bundle.Init(pipeline);
	if (FAILED(hr))return hr;
	hr = SetBundle();
	if (FAILED(hr))return hr;
	hr = bundle.Close();
	if (FAILED(hr))return hr;
	hr = UpdateTransform({});
	if (FAILED(hr))return hr;
	hr = UpdateColor({ 1.0f,1.0f, 1.0f, 1.0f });
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief Transform�̍X�V
* @param transform �V����Transform
* @return �����������ǂ���
*/
HRESULT StaticModel::UpdateTransform(const Transform& transform)
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
	StaticModelConstant *buf{};
	hr = constant_buffer->Map(0, nullptr, (void**)&buf);
	if (FAILED(hr))
	{
		Comment(L"�萔�o�b�t�@��Map�Ɏ��s",
			L"static_model.cpp/StaticModel::UpdateTransform");
		return hr;
	}
	buf->m = mat;
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

/**
* @brief Color�̍X�V
* @param color �V����Color
* @return �����������ǂ���
*/
HRESULT StaticModel::UpdateColor(const Float4& color)
{
	HRESULT hr = S_OK;
	
	StaticModelConstant *buf{};
	hr = constant_buffer->Map(0, nullptr, (void**)&buf);
	if (FAILED(hr))
	{
		Comment(L"�萔�o�b�t�@��Map�Ɏ��s",
			L"static_model.cpp/StaticModel::UpdateColor");
		return hr;
	}
	buf->col = color;
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

/**
* @brief ���f���̕`��
* @param command_list ���߂𑗂�R�}���h���X�g
* @return �����������ǂ���
*/
HRESULT StaticModel::Draw(ComPtr<ID3D12GraphicsCommandList>& command_list)
{

	HRESULT hr = S_OK;

	bundle.SetExecuteCommandList(command_list);

	return hr;
}

#pragma endregion

#pragma region private

/**
* @brief �o�b�t�@�̍쐬
* @return �����������ǂ���
*/
HRESULT StaticModel::CreateBuffer()
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
			L"static_model.cpp/StaticModel::CreateBuffer");
		return hr;
	}

	return hr;
}

/**
* @brief �o���h���ɃR�}���h���Z�b�g����
* @return �����������ǂ���
*/
HRESULT StaticModel::SetBundle()
{
	HRESULT hr = S_OK;

	decltype(auto) bundle_command_list = bundle.GetCommandList();

	bundle_command_list->SetGraphicsRootSignature(Device::getinstance()->GetRootSignature().Get());
	//�萔�o�b�t�@���Z�b�g
	bundle_command_list->SetGraphicsRootConstantBufferView(0, constant_buffer->GetGPUVirtualAddress());

	//���f���̕`��
	StaticModelManager::getinstance()->SetModel(key, bundle_command_list);

	return hr;
}

#pragma endregion