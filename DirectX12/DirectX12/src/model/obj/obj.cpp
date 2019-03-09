#include "obj.h"
#include "../../device/device.h"
#include "../../camera/camera.h"
#include "../../common/message_box.h"

HRESULT Obj::Init(const std::string& model_key, const WCHAR* model_path,
	const std::string& texture_key, const WCHAR* texture_path)
{
	HRESULT hr = S_OK;

	hr = CreateBuffer();
	if (FAILED(hr))return hr;
	hr = model.LoadObjModel(model_key, model_path);
	if (FAILED(hr))return hr;
	hr = texture.LoadTexture(texture_key, texture_path);
	if (FAILED(hr))return hr;
	hr = pipeline.CreatePipeline("obj", L"resources/shader/SimpleShader3D.hlsl",
		L"resources/shader/SimpleShader3D.hlsl", true, false);
	if (FAILED(hr))return hr;

	return hr;
}

HRESULT Obj::UpdateTransform(const Transform& transform)
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
	Matrix *buf{};
	hr = constant_buffer->Map(0, nullptr, (void**)&buf);
	if (FAILED(hr))
	{
		Comment(L"定数バッファのMapに失敗", L"obj.cpp/Obj::UpdateTransform");
		return hr;
	}
	*buf = mat;
	constant_buffer->Unmap(0, nullptr);
	buf = nullptr;

	return hr;
}

HRESULT Obj::Draw(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	HRESULT hr = S_OK;

	//定数バッファをセット
	command_list->SetGraphicsRootConstantBufferView(0, constant_buffer->GetGPUVirtualAddress());

	//テクスチャをセット
	texture.SetTexture(command_list);
	//パイプラインのセット
	pipeline.SetPipeline(command_list);
	//モデルの描画
	model.SetObjModel(command_list);


	return hr;
}

HRESULT Obj::CreateBuffer()
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
		Comment(L"定数バッファ用のリソースとヒープの作成に失敗", L"obj.cpp/Obj::CreateBuffer");
		return hr;
	}

	return hr;
}