/**
* @file execute_command_list.cpp
* @brief ���s�p�R�}���h���X�g�N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/03/11
*/
#include "execute_command_list.h"
#include "../../device/device.h"
#include "../../common/message_box.h"
#include "../Bundle/bundle.h"

/**
* @brief ���s�p�R�}���h���X�g��pimpl�C�f�B�I��
*/
class ExecuteCommandList::Impl
{
public:
	ComPtr<ID3D12CommandAllocator> command_allocator;
	ComPtr<ID3D12GraphicsCommandList> command_list;
	ComPtr<ID3D12PipelineState> pipeline;
	HRESULT CreateCommandAllocator();
	HRESULT CreateCommandList();
};

#pragma region public

/**
* @brief ���s�p�R�}���h���X�g�̃R���X�g���N�^
*/
ExecuteCommandList::ExecuteCommandList() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�A���[�u�R���X�g���N�^�A���[�u������Z�q�̃f�t�H���g�w��
ExecuteCommandList::~ExecuteCommandList()noexcept = default;
ExecuteCommandList::ExecuteCommandList(ExecuteCommandList&&)noexcept = default;
ExecuteCommandList& ExecuteCommandList::operator=(ExecuteCommandList&&)noexcept = default;

/**
* @brief ���s�p�R�}���h���X�g�̏�����
* @return �����������ǂ���
*/
HRESULT ExecuteCommandList::Init()
{
	HRESULT hr = S_OK;

	hr = CreatePipeline();
	if (FAILED(hr))return hr;
	hr = pimpl->CreateCommandAllocator();
	if (FAILED(hr))return hr;
	hr = pimpl->CreateCommandList();
	if (FAILED(hr))return hr;
	hr = Execute();
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief �`��J�n
* @return �����������ǂ���
*/
HRESULT ExecuteCommandList::BeginScene()
{
	HRESULT hr = S_OK;

	//�`��J�n���ɕK�v�Ȃ��̂��Z�b�g����
	hr = Device::getinstance()->BeginSceneSet(pimpl->command_list);
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief �`��
* @return �����������ǂ���
*/
HRESULT ExecuteCommandList::Execute()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->ExecuteCommand(
		pimpl->command_list, pimpl->command_allocator, pimpl->pipeline.Get());
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief �R�}���h���X�g�̃Q�b�^
* @return �R�}���h���X�g
*/
ComPtr<ID3D12GraphicsCommandList>& ExecuteCommandList::GetCommandList()
{
	return (pimpl->command_list);
}

/**
* @brief �p�C�v���C���X�e�[�g�̃Q�b�^
* @return �p�C�v���C���X�e�[�g
*/
ComPtr<ID3D12PipelineState>& ExecuteCommandList::GetPipeline()
{
	return (pimpl->pipeline);
}

#pragma endregion

#pragma region pimpl

/**
* @brief ���s�p�̃R�}���h�A���P�[�^�[�̍쐬
* @return �����������ǂ���
*/
HRESULT ExecuteCommandList::Impl::CreateCommandAllocator()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->GetDevice()->
		CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, 
			IID_PPV_ARGS(&command_allocator));
	if (FAILED(hr))
	{
		Comment(L"�R�}���h�A���P�[�^�[�̍쐬�Ɏ��s",
			L"command_list.cpp/CommandList::CreateCommandAllocator");
		return hr;
	}

	return hr;
}

/**
* @brief ���s�p�̃R�}���h���X�g�̍쐬
* @return �����������ǂ���
*/
HRESULT ExecuteCommandList::Impl::CreateCommandList()
{
	HRESULT hr = S_OK;

	hr = Device::getinstance()->GetDevice()->
		CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
			command_allocator.Get(), pipeline.Get(), 
			IID_PPV_ARGS(&command_list));
	if (FAILED(hr))
	{
		Comment(L"�R�}���h���X�g�̍쐬�Ɏ��s",
			L"command_list.cpp/CommandList::CreateCommandList");
		return hr;
	}

	return hr;
}

#pragma endregion