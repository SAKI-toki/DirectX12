#pragma once
#include "model/obj_model.h"
#include "../../texture/texture.h"
#include "../../pipeline/pipeline.h"

class Obj
{
	ObjModel model;
	Texture texture;
	Pipeline pipeline;
	ComPtr<ID3D12Resource> constant_buffer;
	HRESULT CreateBuffer();
public:
	HRESULT Init(const std::wstring& model_path,
		const std::wstring& texture_path);
	HRESULT UpdateTransform(const Transform& transform);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>& com_command_list);
};