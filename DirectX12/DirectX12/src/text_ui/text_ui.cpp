#include "text_ui.h"
#include "../common/message_box.h"
#include "../common/window_size.h"

#pragma region public

/**
* @brief テキストUIの初期化
* @param frame_count フレーム数
* @param d3d12_device DirectX12の3Dデバイス
* @param command_queue コマンドキュー
* @param render_targets ラッピングするレンダーターゲット
* @return 成功したかどうか
*/
HRESULT TextUi::Init(UINT frame_count,
	ComPtr<ID3D12Device>& d3d12_device,
	ComPtr<ID3D12CommandQueue>& command_queue,
	ComPtr<ID3D12Resource>* render_targets)
{
	HRESULT hr = S_OK;

	wrapped_render_targets.resize(frame_count);
	d2d_render_targets.resize(frame_count);
	hr = CreateD3DDevice(d3d12_device, command_queue);
	if (FAILED(hr))return hr;
	hr = CreateD2DDevice();
	if (FAILED(hr))return hr;
	hr = CreateWrappedRenderTargets(render_targets);
	if (FAILED(hr))return hr;
	default_text_brush = CreateTextBrush(0xffffff);
	default_text_format = CreateTextFormat();

	return hr;
}

/**
* @brief 描画
* @param frame_index 描画するレンダーターゲットのインデックス
* @return 成功したかどうか
*/
HRESULT TextUi::Render(UINT frame_index)
{
	HRESULT hr = S_OK;

	ID3D11Resource* resources[] = { wrapped_render_targets[frame_index].Get() };
	d2d1_device_context->SetTarget(d2d_render_targets[frame_index].Get());
	d3d11_on_12_device->AcquireWrappedResources(resources, _countof(resources));
	d2d1_device_context->BeginDraw();
	for (auto&& text_block : text_blocks)
	{
		d2d1_device_context->DrawTextW(
			text_block.text.c_str(),
			static_cast<UINT>(text_block.text.length()),
			(text_block.use_custom_format ? text_block.custom_text_format.Get() : default_text_format.Get()), 
			text_block.layout,
			(text_block.use_custom_color ? text_block.custom_text_brush.Get() : default_text_brush.Get()));
	}
	hr = d2d1_device_context->EndDraw();
	if (FAILED(hr))
	{
		Comment(L"ドローの終了時にエラー発生",
			L"text_ui.cpp/TextUi::Render");
		return hr;
	}
	d3d11_on_12_device->ReleaseWrappedResources(resources, _countof(resources));
	d3d11_device_context->Flush();
	text_blocks.clear();

	return hr;
}

/**
* @brief 描画する文字列を登録
* @param text 描画するテキスト
* @param pos 描画位置
* @return 成功したかどうか
*/
void TextUi::DrawString(const std::wstring& text, const Vec2& pos)
{
	text_blocks.push_back({ text
		,D2D1::RectF(pos.x,pos.y,static_cast<float>(WINDOW_WIDTH),static_cast<float>(WINDOW_HEIGHT)),
		false,{},false,{} });
}

/**
* @brief 描画する文字列を登録(色指定)
* @param text 描画するテキスト
* @param pos 描画位置
* @param text_brush 使用する色(brush)
* @return 成功したかどうか
*/
void TextUi::DrawStringColor(const std::wstring& text, const Vec2& pos, const ComPtr<ID2D1SolidColorBrush>& text_brush)
{
	text_blocks.push_back({ text
		,D2D1::RectF(pos.x,pos.y,static_cast<float>(WINDOW_WIDTH),static_cast<float>(WINDOW_HEIGHT)),
		true,text_brush,false,{} });
}

/**
* @brief 描画する文字列を登録(フォーマット指定)
* @param text 描画するテキスト
* @param pos 描画位置
* @param text_format 使用するフォーマット
* @return 成功したかどうか
*/
void TextUi::DrawStringFormat(const std::wstring& text, const Vec2& pos,
	const ComPtr<IDWriteTextFormat>& text_format)
{
	text_blocks.push_back({ text
		,D2D1::RectF(pos.x,pos.y,static_cast<float>(WINDOW_WIDTH),static_cast<float>(WINDOW_HEIGHT)),
		false,{},true,text_format });
}

/**
* @brief 描画する文字列を登録(色、フォーマット指定)
* @param text 描画するテキスト
* @param pos 描画位置
* @param text_brush 使用する色(brush)
* @param text_format 使用するフォーマット
* @return 成功したかどうか
*/
void TextUi::DrawStringColorFormat(const std::wstring& text, const Vec2& pos,
	const ComPtr<ID2D1SolidColorBrush>& text_brush, const ComPtr<IDWriteTextFormat>& text_format)
{
	text_blocks.push_back({ text
		,D2D1::RectF(pos.x,pos.y,static_cast<float>(WINDOW_WIDTH),static_cast<float>(WINDOW_HEIGHT)),
		true,text_brush,true,text_format });
}

/**
* @brief テキストのブラッシュを作成
* @param color 色
* @return 作成したテキストのブラッシュ
*/
ComPtr<ID2D1SolidColorBrush> TextUi::CreateTextBrush(const UINT32 color)
{
	ComPtr<ID2D1SolidColorBrush> text_brush;

	HRESULT hr = S_OK;
	hr = d2d1_device_context->CreateSolidColorBrush(D2D1::ColorF(color), &text_brush);
	if (FAILED(hr))
	{
		Comment(L"ブラッシュの作成に失敗",
			L"text_ui.cpp/TextUi::CreateTextBrush");
		throw 0;
	}

	return text_brush;
}

/**
* @brief テキストのフォーマットを作成
* @param font_size フォントのサイズ
* @param font_weight フォントの太さ
* @param font_style フォントのスタイル
* @param font_stretch フォントのストレッチ
* @param text_alignment テキストのアライメント
* @return 作成したテキストのフォーマット
*/
ComPtr<IDWriteTextFormat> TextUi::CreateTextFormat(
	const float font_size,
	const DWRITE_FONT_WEIGHT font_weight,
	const DWRITE_FONT_STYLE font_style,
	const DWRITE_FONT_STRETCH font_stretch,
	const DWRITE_TEXT_ALIGNMENT text_alignment)
{
	ComPtr<IDWriteTextFormat> text_format;
	HRESULT hr = S_OK;

	hr = dwrite_factory->CreateTextFormat(
		L"Arial", nullptr, font_weight,font_style,font_stretch,
		WINDOW_HEIGHT* font_size / 30.0f, L"en-us", &text_format
	);
	if (FAILED(hr))
	{
		Comment(L"テキストフォーマットの作成に失敗",
			L"text_ui.cpp/TextUi::CreateTextFormat");
		throw 0;
	}
	hr = text_format->SetTextAlignment(text_alignment);
	if (FAILED(hr))
	{
		Comment(L"テキストアライメントのセットに失敗",
			L"text_ui.cpp/TextUi::CreateTextFormat");
		throw 0;
	}
	hr = text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	if (FAILED(hr))
	{
		Comment(L"パラグラフアライメントのセットに失敗",
			L"text_ui.cpp/TextUi::CreateTextFormat");
		throw 0;
	}

	return text_format;
}

#pragma endregion

#pragma region private

/**
* @brief D3Dデバイスの作成
* @param d3d12_device DirectX12の3Dデバイス
* @param command_queue コマンドキュー
* @return 成功したかどうか
*/
HRESULT TextUi::CreateD3DDevice(ComPtr<ID3D12Device>& d3d12_device,
	ComPtr<ID3D12CommandQueue>& command_queue)
{
	HRESULT hr = S_OK;

	UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	ComPtr<ID3D11Device> d3d11_device;
	ID3D12CommandQueue* command_queues[] = { command_queue.Get() };
	hr = D3D11On12CreateDevice(d3d12_device.Get(), flags, nullptr, 0,
		reinterpret_cast<IUnknown**>(command_queues), _countof(command_queues),
		0, &d3d11_device, &d3d11_device_context, nullptr);
	if (FAILED(hr))
	{
		Comment(L"12に乗っかる11のデバイスの作成に失敗",
			L"text_ui.cpp/TextUi::CreateD3DDevice");
		return hr;
	}

	hr = d3d11_device.As(&d3d11_on_12_device);
	if (FAILED(hr))
	{
		Comment(L"12に乗っかる11のデバイスのインターフェイスの取得に失敗",
			L"text_ui.cpp/TextUi::CreateD3DDevice");
		return hr;
	}
#ifdef _DEBUG
	ComPtr<ID3D12InfoQueue> info_queue;
	if (SUCCEEDED(d3d12_device->QueryInterface(IID_PPV_ARGS(&info_queue))))
	{
		D3D12_MESSAGE_SEVERITY severities[] =
		{
			D3D12_MESSAGE_SEVERITY_INFO,
		};

		D3D12_MESSAGE_ID denyIds[] =
		{
			D3D12_MESSAGE_ID_INVALID_DESCRIPTOR_HANDLE,
		};

		D3D12_INFO_QUEUE_FILTER filter = {};
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;

		hr = info_queue->PushStorageFilter(&filter);
		if (FAILED(hr))
		{
			Comment(L"ストレージフィルタをストレージフィルタスタックにpushに失敗",
				L"text_ui.cpp/TextUi::CreateD3DDevice");
			return hr;
		}
	}
#endif

	return hr;
}

/**
* @brief D2Dデバイスの作成
* @return 成功したかどうか
*/
HRESULT TextUi::CreateD2DDevice()
{
	HRESULT hr = S_OK;
	D2D1_FACTORY_OPTIONS d2d_factory_options{};
#ifdef _DEBUG
	d2d_factory_options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	ComPtr<IDXGIDevice> dxgi_device;
	hr = d3d11_on_12_device.As(&dxgi_device);
	if (FAILED(hr))
	{
		Comment(L"DXGIデバイスのインターフェイスの取得に失敗",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory3),
		&d2d_factory_options, &d2d_factory);
	if (FAILED(hr))
	{
		Comment(L"D2D1ファクトリーの作成に失敗",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	hr = d2d_factory->CreateDevice(dxgi_device.Get(), &d2d1_device);
	if (FAILED(hr))
	{
		Comment(L"D2D1デバイスの作成に失敗",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	hr = d2d1_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &d2d1_device_context);
	if (FAILED(hr))
	{
		Comment(L"D2D1デバイスコンテキストの作成に失敗",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	d2d1_device_context->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &dwrite_factory);
	if (FAILED(hr))
	{
		Comment(L"DwriteFactroyの作成に失敗",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	return hr;
}

/**
* @brief ラッピングしたレンダーターゲットの作成
* @param render_targets ラッピングするレンダーターゲット
* @return 成功したかどうか
*/
HRESULT TextUi::CreateWrappedRenderTargets(ComPtr<ID3D12Resource>* render_targets)
{
	HRESULT hr = S_OK;

	D2D1_BITMAP_PROPERTIES1 bitmap_properties = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));

	for (UINT i = 0; i < wrapped_render_targets.size(); ++i)
	{
		D3D11_RESOURCE_FLAGS d3d11_flgs{ D3D11_BIND_RENDER_TARGET };
		hr = d3d11_on_12_device->CreateWrappedResource(render_targets[i].Get(),
			&d3d11_flgs,
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			IID_PPV_ARGS(&wrapped_render_targets[i]));
		if (FAILED(hr))
		{
			Comment(L"リソースのラッピングに失敗",
				L"text_ui.cpp/TextUi::CreateWrappedRenderTargets");
			return hr;
		}
		ComPtr<IDXGISurface> surface;
		hr = wrapped_render_targets[i].As(&surface);
		if (FAILED(hr))
		{
			Comment(L"レンダーターゲットのインターフェイスの取得に失敗",
				L"text_ui.cpp/TextUi::CreateWrappedRenderTargets");
			return hr;
		}
		hr = d2d1_device_context->CreateBitmapFromDxgiSurface(
			surface.Get(), &bitmap_properties, &d2d_render_targets[i]);
		if (FAILED(hr))
		{
			Comment(L"ビットマップの作成に失敗",
				L"text_ui.cpp/TextUi::CreateWrappedRenderTargets");
			return hr;
		}
	}

	return hr;
}

#pragma endregion
