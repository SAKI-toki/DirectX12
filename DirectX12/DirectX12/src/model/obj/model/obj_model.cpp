/**
* @file obj.cpp
* @brief Objクラスの関数定義
* @author 石山　悠
* @date 2019/02/17
*/
#include "obj_model.h"

HRESULT ObjModel::LoadObjModel(const std::wstring& path)
{
	HRESULT hr = S_OK;

	key = path;
	hr = ObjModelManager::getinstance()->LoadObjModel(key);
	if (FAILED(hr))return hr;

	return hr;
}
void ObjModel::SetObjModel(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	ObjModelManager::getinstance()->SetObjModel(key, command_list);
}