#pragma once
#include "manager/obj_model_manager.h"

class ObjModel
{
	std::wstring key;
public:
	HRESULT LoadObjModel(const std::wstring&);
	void SetObjModel(ComPtr<ID3D12GraphicsCommandList>&);
};