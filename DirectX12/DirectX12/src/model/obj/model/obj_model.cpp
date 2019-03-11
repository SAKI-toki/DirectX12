/**
* @file obj.cpp
* @brief Obj�N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/02/17
*/
#include "obj_model.h"

HRESULT ObjModel::LoadObjModel(const std::wstring& _path)
{
	HRESULT hr = S_OK;

	path = _path;
	hr = ObjModelManager::getinstance()->LoadObjModel(path);
	if (FAILED(hr))return hr;

	return hr;
}
void ObjModel::SetObjModel(ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	ObjModelManager::getinstance()->SetObjModel(path, command_list);
}