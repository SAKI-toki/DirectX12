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

#pragma region public

/**
* @brief ���s�p�R�}���h���X�g�̏�����
* @return �����������ǂ���
*/
HRESULT ExecuteCommandList::Init()
{
	HRESULT hr = S_OK;

	hr = CreatePipeline();
	if (FAILED(hr))return hr;
	hr = CreateCommandAllocator();
	if (FAILED(hr))return hr;
	hr = CreateCommandList();
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
	hr = Device::getinstance()->BeginSceneSet(command_list);
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

	hr = Device::getinstance()->ExecuteCommand(command_list, command_allocator, pipeline.Get());
	if (FAILED(hr))return hr;

	return hr;
}

/**
* @brief �R�}���h���X�g�̃Q�b�^
* @return �R�}���h���X�g
*/
ComPtr<ID3D12GraphicsCommandList>& ExecuteCommandList::GetCommandList()
{
	return (command_list);
}

/**
* @brief �p�C�v���C���X�e�[�g�̃Q�b�^
* @return �p�C�v���C���X�e�[�g
*/
ComPtr<ID3D12PipelineState>& ExecuteCommandList::GetPipeline()
{
	return (pipeline);
}

#pragma endregion

#pragma region private

/**
* @brief ���s�p�̃R�}���h�A���P�[�^�[�̍쐬
* @return �����������ǂ���
*/
HRESULT ExecuteCommandList::CreateCommandAllocator()
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
HRESULT ExecuteCommandList::CreateCommandList()
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
	hr = Execute();
	if (FAILED(hr))return hr;

	return hr;
}

#pragma endregion