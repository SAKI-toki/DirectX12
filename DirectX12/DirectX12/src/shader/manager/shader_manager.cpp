/**
* @file shader_manager.cpp
* @brief �V�F�[�_�[���Ǘ�����N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2019/03/09
*/
#include "shader_manager.h"
#include "../../common/message_box.h"
#include <unordered_map>

/**
* @brief �V�F�[�_�[���Ǘ�����N���X��pimpl�C�f�B�I��
*/
class ShaderManager::Impl
{
public:
	std::unordered_map<std::wstring, ComPtr<ID3DBlob>> shader_data_map;
};

#pragma region public

/**
* @brief �V�F�[�_�[���Ǘ�����N���X�̃R���X�g���N�^
*/
ShaderManager::ShaderManager() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�̃f�t�H���g�w��
ShaderManager::~ShaderManager()noexcept = default;

/**
* @brief �V�F�[�_�[�̓ǂݍ���
* @param key �L�[
* @param path �V�F�[�_�[�̃p�X
* @param entry �G���g���[
* @param target �^�[�Q�b�g
* @return �����������ǂ���
*/
HRESULT ShaderManager::LoadShader(const std::wstring& key, const std::wstring& path,
	const std::string& entry, const std::string& target)
{
	HRESULT hr = S_OK;

	auto itr = pimpl->shader_data_map.find(key);
	//���ɓǂݍ���ł���ꍇ
	if (itr != std::end(pimpl->shader_data_map)) { return hr; }

	UINT compile_flg = 0;
#ifdef _DEBUG
	compile_flg = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ComPtr<ID3DBlob> blob;
	hr = D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.c_str(), target.c_str(),
		compile_flg, 0, blob.GetAddressOf(), nullptr);
	if (FAILED(hr))
	{
		Comment((std::wstring(L"�V�F�[�_�[�̃R���p�C���Ɏ��s/") + key).c_str(),
			L"shader_manager.cpp/ShaderManager::LoadShader");
		return hr;
	}
	pimpl->shader_data_map.insert(std::make_pair(key, blob));
	return hr;
}

/**
* @brief �V�F�[�_�[�̃Q�b�^
* @param key �L�[
* @return �V�F�[�_�[
*/
ComPtr<ID3DBlob>& ShaderManager::GetShader(const std::wstring & key)
{
	auto itr = pimpl->shader_data_map.find(key);
	if (itr == pimpl->shader_data_map.end())throw 0;
	return (itr->second);
}

#pragma endregion