/**
* @file cube_command_list.cpp
* @brief �L���[�u�p�̃R�}���h���X�g�N���X�̊֐����`
* @author �ΎR�@�I
* @date 2019/03/11
*/
#include "cube_command_list.h"
#include "../../device/device.h"
#include "../../common/message_box.h"
#include "../../shader/shader.h"

/**
* @brief �L���[�u�p�̃p�C�v���C�����쐬
* @return �����������ǂ���
*/
HRESULT CubeCommandList::CreatePipeline()
{
	HRESULT hr = S_OK;

	Shader vertex_shader, pixel_shader;
	//���_�V�F�[�_�[
	hr = vertex_shader.LoadShader(L"resources/shader/SimpleShader3D.hlsl", "vs", "vs_5_0");
	if (FAILED(hr))return hr;
	//�s�N�Z���V�F�[�_�[
	hr = pixel_shader.LoadShader(L"resources/shader/SimpleShader3D.hlsl", "ps", "ps_5_0");
	if (FAILED(hr))return hr;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_state_desc{};
	//�V�F�[�_�[�̐ݒ�
	pipeline_state_desc.VS.pShaderBytecode = vertex_shader.GetShader()->GetBufferPointer();
	pipeline_state_desc.VS.BytecodeLength = vertex_shader.GetShader()->GetBufferSize();
	pipeline_state_desc.PS.pShaderBytecode = pixel_shader.GetShader()->GetBufferPointer();
	pipeline_state_desc.PS.BytecodeLength = pixel_shader.GetShader()->GetBufferSize();


	//�T���v���n�̐ݒ�
	pipeline_state_desc.SampleDesc.Count = 1;
	pipeline_state_desc.SampleDesc.Quality = 0;
	pipeline_state_desc.SampleMask = UINT_MAX;

	//�����_�[�^�[�Q�b�g�̐ݒ�
	pipeline_state_desc.NumRenderTargets = 1;
	pipeline_state_desc.RTVFormats[0] = DXGI_FORMAT_B8G8R8A8_UNORM;

	//�O�p�`�ɐݒ�
	pipeline_state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	//���[�g�V�O�l�`��
	pipeline_state_desc.pRootSignature = Device::getinstance()->GetRootSignature().Get();


	//���X�^���C�U�X�e�[�g�̐ݒ�
	pipeline_state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
	pipeline_state_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	pipeline_state_desc.RasterizerState.FrontCounterClockwise = FALSE;
	pipeline_state_desc.RasterizerState.DepthBias = 0;
	pipeline_state_desc.RasterizerState.DepthBiasClamp = 0;
	pipeline_state_desc.RasterizerState.SlopeScaledDepthBias = 0;
	pipeline_state_desc.RasterizerState.DepthClipEnable = TRUE;
	pipeline_state_desc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	pipeline_state_desc.RasterizerState.AntialiasedLineEnable = FALSE;
	pipeline_state_desc.RasterizerState.MultisampleEnable = FALSE;


	//�u�����h�X�e�[�g�̐ݒ�
	for (int i = 0; i < _countof(pipeline_state_desc.BlendState.RenderTarget); ++i)
	{
		pipeline_state_desc.BlendState.RenderTarget[i].BlendEnable = FALSE;
		pipeline_state_desc.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND_ONE;
		pipeline_state_desc.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND_ZERO;
		pipeline_state_desc.BlendState.RenderTarget[i].BlendOp = D3D12_BLEND_OP_ADD;
		pipeline_state_desc.BlendState.RenderTarget[i].SrcBlendAlpha = D3D12_BLEND_ONE;
		pipeline_state_desc.BlendState.RenderTarget[i].DestBlendAlpha = D3D12_BLEND_ZERO;
		pipeline_state_desc.BlendState.RenderTarget[i].BlendOpAlpha = D3D12_BLEND_OP_ADD;
		pipeline_state_desc.BlendState.RenderTarget[i].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		pipeline_state_desc.BlendState.RenderTarget[i].LogicOpEnable = FALSE;
		pipeline_state_desc.BlendState.RenderTarget[i].LogicOp = D3D12_LOGIC_OP_CLEAR;
	}
	pipeline_state_desc.BlendState.AlphaToCoverageEnable = FALSE;
	pipeline_state_desc.BlendState.IndependentBlendEnable = FALSE;


	//�f�v�X�X�e���V���X�e�[�g�̐ݒ�
	pipeline_state_desc.DepthStencilState.DepthEnable = TRUE;
	pipeline_state_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	pipeline_state_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	pipeline_state_desc.DepthStencilState.StencilEnable = FALSE;
	pipeline_state_desc.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
	pipeline_state_desc.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

	pipeline_state_desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	pipeline_state_desc.DepthStencilState.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	pipeline_state_desc.DepthStencilState.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	pipeline_state_desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	D3D12_INPUT_ELEMENT_DESC input_element_desc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};
	//�C���v�b�g���C�A�E�g�̐ݒ�
	pipeline_state_desc.InputLayout.pInputElementDescs = input_element_desc;
	pipeline_state_desc.InputLayout.NumElements = _countof(input_element_desc);

	hr = Device::getinstance()->GetDevice()->CreateGraphicsPipelineState(
		&pipeline_state_desc, IID_PPV_ARGS(&(GetPipeline())));
	if (FAILED(hr))
	{
		Comment(L"�O���t�B�b�N�X�p�C�v���C���X�e�[�g�̍쐬�Ɏ��s",
			L"cube_command_list.cpp/CobeCommandList::CreatePipeline");
		return hr;
	}

	return hr;
}