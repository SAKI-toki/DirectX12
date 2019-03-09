/**
* @file obj.cpp
* @brief Obj�N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/02/17
*/
#include "obj_model.h"

HRESULT ObjModel::LoadObjModel(const std::string& _key, const WCHAR* path)
{
	HRESULT hr = S_OK;

	key = _key;
	hr = ObjModelManager::getinstance()->LoadObjModel(key, path);
	if (FAILED(hr))return hr;

	return hr;
}
void ObjModel::SetObjModel(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	ObjModelManager::getinstance()->SetObjModel(key, command_list);
}