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
	HRESULT Init(const std::string& model_key, const WCHAR* model_path, 
		const std::string& texture_key, const WCHAR* texture_path);
	HRESULT UpdateTransform(const Transform&);
	HRESULT Draw(ComPtr<ID3D12GraphicsCommandList>&);
};