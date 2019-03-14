#pragma once
#include "model/obj_model.h"
#include "../../texture/texture.h"
#include "../../command_list/Bundle/bundle.h"

class Obj
{
	ObjModel model;
	Texture texture;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateBuffer();
	Bundle bundle;
	HRESULT SetBundle();
public:
	HRESULT Init(const std::wstring& model_path,
		const std::wstring& texture_path, 
		ComPtr<ID3D12PipelineState>& com_pipeline);
	HRESULT UpdateTransform(const Transform& transform);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>& com_command_list);
};