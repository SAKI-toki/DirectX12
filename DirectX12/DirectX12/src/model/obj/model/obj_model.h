#pragma once
#include "manager/obj_model_manager.h"

class ObjModel
{
	std::string key;
public:
	HRESULT LoadObjModel(const std::string&, const WCHAR*);
	void SetObjModel(ComPtr<ID3D12GraphicsCommandList>&);
};