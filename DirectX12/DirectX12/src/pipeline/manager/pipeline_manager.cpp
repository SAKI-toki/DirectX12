/**
* @file pipeline_manager.cpp
* @brief パイプラインを管理するクラスの関数定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "pipeline_manager.h"
#include "../../device/device.h"
#include "../../common/message_box.h"

HRESULT PipelineManager::CreatePipeline(
	const std::string& key, const WCHAR* vertex_shader_path, const WCHAR* pixel_shader_path,
	const bool is_3d, const bool is_single_color)
{
	HRESULT hr = S_OK;


	auto itr = pipeline_data_map.find(key);
	//既に読み込んでいる場合
	if (itr != std::end(pipeline_data_map)) { return hr; }
	ComPtr<ID3DBlob> vertex_shader{};
	ComPtr<ID3DBlob> pixel_shader{};
	UINT compile_flg = 0;
#ifdef _DEBUG
	compile_flg = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	hr = D3DCompileFromFile(vertex_shader_path, nullptr, nullptr, "vs", "vs_5_0",
		compile_flg, 0, vertex_shader.GetAddressOf(), nullptr);
	if (FAILED(hr))
	{
		Comment(L"頂点シェーダーのコンパイルに失敗", L"pipeline_manager.cpp/PipelineManager::CreatePipeline");
		return hr;
	}
	hr = D3DCompileFromFile(pixel_shader_path, nullptr, nullptr, "ps", "ps_5_0",
		compile_flg, 0, pixel_shader.GetAddressOf(), nullptr);
	if (FAILED(hr))
	{
		Comment(L"ピクセルシェーダーのコンパイルに失敗", L"pipeline_manager.cpp/PipelineManager::CreatePipeline");
		return hr;
	}
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_state_desc{};

	//シェーダーの設定
	pipeline_state_desc.VS.pShaderBytecode = vertex_shader->GetBufferPointer();
	pipeline_state_desc.VS.BytecodeLength = vertex_shader->GetBufferSize();
	pipeline_state_desc.PS.pShaderBytecode = pixel_shader->GetBufferPointer();
	pipeline_state_desc.PS.BytecodeLength = pixel_shader->GetBufferSize();


	//サンプル系の設定
	pipeline_state_desc.SampleDesc.Count = 1;
	pipeline_state_desc.SampleDesc.Quality = 0;
	pipeline_state_desc.SampleMask = UINT_MAX;

	//レンダーターゲットの設定
	pipeline_state_desc.NumRenderTargets = 1;
	pipeline_state_desc.RTVFormats[0] = DXGI_FORMAT_B8G8R8A8_UNORM;

	//三角形に設定
	pipeline_state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;


	//ルートシグネチャ
	pipeline_state_desc.pRootSignature = Device::getinstance()->GetRootSignature().Get();


	//ラスタライザステートの設定
	pipeline_state_desc.RasterizerState.CullMode = (is_3d) ? D3D12_CULL_MODE_BACK : D3D12_CULL_MODE_NONE;
	pipeline_state_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	pipeline_state_desc.RasterizerState.FrontCounterClockwise = FALSE;
	pipeline_state_desc.RasterizerState.DepthBias = 0;
	pipeline_state_desc.RasterizerState.DepthBiasClamp = 0;
	pipeline_state_desc.RasterizerState.SlopeScaledDepthBias = 0;
	pipeline_state_desc.RasterizerState.DepthClipEnable = is_3d;
	pipeline_state_desc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	pipeline_state_desc.RasterizerState.AntialiasedLineEnable = FALSE;
	pipeline_state_desc.RasterizerState.MultisampleEnable = FALSE;


	//ブレンドステートの設定
	for (int i = 0; i < _countof(pipeline_state_desc.BlendState.RenderTarget); ++i) {

		if (is_3d)
		{
			pipeline_state_desc.BlendState.RenderTarget[i].BlendEnable = FALSE;
			pipeline_state_desc.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND_ONE;
			pipeline_state_desc.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND_ZERO;
		}
		else
		{
			pipeline_state_desc.BlendState.RenderTarget[i].BlendEnable = TRUE;
			pipeline_state_desc.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND_SRC_ALPHA;
			pipeline_state_desc.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		}
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


	//デプスステンシルステートの設定
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
	ComPtr<ID3D12PipelineState> pipeline_state;
	if (is_3d)
	{
		if (is_single_color)
		{
			D3D12_INPUT_ELEMENT_DESC input_element_desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },

			};
			//インプットレイアウトの設定
			pipeline_state_desc.InputLayout.pInputElementDescs = input_element_desc;
			pipeline_state_desc.InputLayout.NumElements = _countof(input_element_desc);
			hr = Device::getinstance()->GetDevice()->CreateGraphicsPipelineState(
				&pipeline_state_desc, IID_PPV_ARGS(&pipeline_state));
			if (FAILED(hr))
			{
				Comment(L"グラフィックスパイプラインステートの作成に失敗",
					L"pipeline_manager.cpp/PipelineManager::CreatePipeline");
				return hr;
			}
		}
		else
		{
			D3D12_INPUT_ELEMENT_DESC input_element_desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },

			};
			//インプットレイアウトの設定
			pipeline_state_desc.InputLayout.pInputElementDescs = input_element_desc;
			pipeline_state_desc.InputLayout.NumElements = _countof(input_element_desc);
			hr = Device::getinstance()->GetDevice()->CreateGraphicsPipelineState(
				&pipeline_state_desc, IID_PPV_ARGS(&pipeline_state));
			if (FAILED(hr))
			{
				Comment(L"グラフィックスパイプラインステートの作成に失敗",
					L"pipeline_manager.cpp/PipelineManager::CreatePipeline");
				return hr;
			}
		}
	}
	else
	{
		if (is_single_color)
		{
			D3D12_INPUT_ELEMENT_DESC input_element_desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			};
			//インプットレイアウトの設定
			pipeline_state_desc.InputLayout.pInputElementDescs = input_element_desc;
			pipeline_state_desc.InputLayout.NumElements = _countof(input_element_desc);
			hr = Device::getinstance()->GetDevice()->CreateGraphicsPipelineState(
				&pipeline_state_desc, IID_PPV_ARGS(&pipeline_state));
			if (FAILED(hr))
			{
				Comment(L"グラフィックスパイプラインステートの作成に失敗",
					L"pipeline_manager.cpp/PipelineManager::CreatePipeline");
				return hr;
			}
		}
		else
		{
			D3D12_INPUT_ELEMENT_DESC input_element_desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			};
			//インプットレイアウトの設定
			pipeline_state_desc.InputLayout.pInputElementDescs = input_element_desc;
			pipeline_state_desc.InputLayout.NumElements = _countof(input_element_desc);
			hr = Device::getinstance()->GetDevice()->CreateGraphicsPipelineState(
				&pipeline_state_desc, IID_PPV_ARGS(&pipeline_state));
			if (FAILED(hr))
			{
				Comment(L"グラフィックスパイプラインステートの作成に失敗",
					L"pipeline_manager.cpp/PipelineManager::CreatePipeline");
				return hr;
			}
		}
	}

	pipeline_data_map.insert(std::make_pair(key, pipeline_state));
	return hr;
}

void PipelineManager::SetPipeline(const std::string& key, ComPtr<ID3D12GraphicsCommandList>& ccommand_list)
{
	auto itr = pipeline_data_map.find(key);
	ccommand_list->SetPipelineState(itr->second.Get());
}

ComPtr<ID3D12PipelineState>& PipelineManager::GetPipeline(const std::string& key)
{
	auto itr = pipeline_data_map.find(key);
	return itr->second;
}