/**
* @file bundle.cpp
* @brief �o���h���N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/03/11
*/
#include "bundle.h"
#include "../../device/device.h"
#include "../../common/message_box.h"
#include "../Execute/execute_command_list.h"

/**
* @brief �o���h����pimpl�C�f�B�I��
*/
class Bundle::Impl
{
public:
	ComPtr<ID3D12CommandAllocator> command_allocator;
	ComPtr<ID3D12GraphicsCommandList> command_list;
	HRESULT CreateCommandAllocator();
	HRESULT CreateCommandList(ComPtr<ID3D12PipelineState>& com_pipeline);
};

#pragma region public

/**
* @brief �o���h���̃R���X�g���N�^
*/
Bundle::Bundle() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�A���[�u�R���X�g���N�^�A���[�u������Z�q�̃f�t�H���g�w��
Bundle::~Bundle()noexcept = default;
Bundle::Bundle(Bundle&&)noexcept = default;
Bundle& Bundle::operator=(Bundle&&)noexcept = default;

/**
* @brief �o���h���̏�����
* @param pipeline �o���h���̃p�C�v���C��
* @return �����������ǂ���
*/
HRESULT Bundle::Init(ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	hr = pimpl->CreateCommandAllocator();
	if (FAILED(hr))return hr;
	hr = pimpl->CreateCommandList(pipeline);
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief �o���h����Close����(�R�}���h����ꂽ��Ɉ�x�����Ăяo��)
* @return �����������ǂ���
*/
HRESULT Bundle::Close()
{
	HRESULT hr = S_OK;

	hr = pimpl->command_list->Close();
	if (FAILED(hr))
	{
		Comment(L"�o���h���p�̃R�}���h���X�g��Close�Ɏ��s",
			L"bundle.cpp/Bundle::Close");
		return hr;
	}

	return hr;
}

/**
* @brief ���s�p�̃R�}���h���X�g�̃Z�b�g
* @param execute_command_list �Z�b�g��������s�p�̃R�}���h���X�g
* @return �����������ǂ���
*/
void Bundle::SetExecuteCommandList(ComPtr<ID3D12GraphicsCommandList>& execute_command_list)
{
	execute_command_list->ExecuteBundle(pimpl->command_list.Get());
}

/**
* @brief �R�}���h���X�g�̃Q�b�^
* @return �R�}���h���X�g
*/
ComPtr<ID3D12GraphicsCommandList>& Bundle::GetCommandList()
{
	return (pimpl->command_list);
}

#pragma endregion

#pragma region pimpl

/**
* @brief �o���h���̃R�}���h�A���P�[�^�[�̍쐬
* @return �����������ǂ���
*/
HRESULT Bundle::Impl::CreateCommandAllocator()
{
	HRESULT hr = S_OK;

	//D3D12_COMMAND_LIST_TYPE_BUNDLE���w�肷��
	hr = Device::getinstance()->GetDevice()->
		CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_BUNDLE,
			IID_PPV_ARGS(&command_allocator));
	if (FAILED(hr))
	{
		Comment(L"�o���h���p�̃R�}���h�A���P�[�^�[�̍쐬�Ɏ��s",
			L"bundle.cpp/Bundle::CreateCommandAllocator");
		return hr;
	}

	return hr;
}

/**
* @brief �o���h���̃R�}���h���X�g�̍쐬
* @return �����������ǂ���
*/
HRESULT Bundle::Impl::CreateCommandList(ComPtr<ID3D12PipelineState>& pipeline)
{
	HRESULT hr = S_OK;

	//D3D12_COMMAND_LIST_TYPE_BUNDLE���w�肷��
	hr = Device::getinstance()->GetDevice()->
		CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_BUNDLE,
			command_allocator.Get(), pipeline.Get(), IID_PPV_ARGS(&command_list));
	if (FAILED(hr))
	{
		Comment(L"�o���h���p�̃R�}���h���X�g�̍쐬�Ɏ��s",
			L"bundle.cpp/Bundle::CreateCommandList");
		return hr;
	}

	return hr;
}

#pragma endregion