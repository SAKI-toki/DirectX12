#include "text_ui.h"
#include "../common/message_box.h"
#include "../common/window_size.h"

#pragma region public

/**
* @brief �e�L�X�gUI�̏�����
* @param frame_count �t���[����
* @param d3d12_device DirectX12��3D�f�o�C�X
* @param command_queue �R�}���h�L���[
* @param render_targets ���b�s���O���郌���_�[�^�[�Q�b�g
* @return �����������ǂ���
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
* @brief �`��
* @param frame_index �`�悷�郌���_�[�^�[�Q�b�g�̃C���f�b�N�X
* @return �����������ǂ���
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
		Comment(L"�h���[�̏I�����ɃG���[����",
			L"text_ui.cpp/TextUi::Render");
		return hr;
	}
	d3d11_on_12_device->ReleaseWrappedResources(resources, _countof(resources));
	d3d11_device_context->Flush();
	text_blocks.clear();

	return hr;
}

/**
* @brief �`�悷�镶�����o�^
* @param text �`�悷��e�L�X�g
* @param pos �`��ʒu
* @return �����������ǂ���
*/
void TextUi::DrawString(const std::wstring& text, const Vec2& pos)
{
	text_blocks.push_back({ text
		,D2D1::RectF(pos.x,pos.y,static_cast<float>(WINDOW_WIDTH),static_cast<float>(WINDOW_HEIGHT)),
		false,{},false,{} });
}

/**
* @brief �`�悷�镶�����o�^(�F�w��)
* @param text �`�悷��e�L�X�g
* @param pos �`��ʒu
* @param text_brush �g�p����F(brush)
* @return �����������ǂ���
*/
void TextUi::DrawStringColor(const std::wstring& text, const Vec2& pos, const ComPtr<ID2D1SolidColorBrush>& text_brush)
{
	text_blocks.push_back({ text
		,D2D1::RectF(pos.x,pos.y,static_cast<float>(WINDOW_WIDTH),static_cast<float>(WINDOW_HEIGHT)),
		true,text_brush,false,{} });
}

/**
* @brief �`�悷�镶�����o�^(�t�H�[�}�b�g�w��)
* @param text �`�悷��e�L�X�g
* @param pos �`��ʒu
* @param text_format �g�p����t�H�[�}�b�g
* @return �����������ǂ���
*/
void TextUi::DrawStringFormat(const std::wstring& text, const Vec2& pos,
	const ComPtr<IDWriteTextFormat>& text_format)
{
	text_blocks.push_back({ text
		,D2D1::RectF(pos.x,pos.y,static_cast<float>(WINDOW_WIDTH),static_cast<float>(WINDOW_HEIGHT)),
		false,{},true,text_format });
}

/**
* @brief �`�悷�镶�����o�^(�F�A�t�H�[�}�b�g�w��)
* @param text �`�悷��e�L�X�g
* @param pos �`��ʒu
* @param text_brush �g�p����F(brush)
* @param text_format �g�p����t�H�[�}�b�g
* @return �����������ǂ���
*/
void TextUi::DrawStringColorFormat(const std::wstring& text, const Vec2& pos,
	const ComPtr<ID2D1SolidColorBrush>& text_brush, const ComPtr<IDWriteTextFormat>& text_format)
{
	text_blocks.push_back({ text
		,D2D1::RectF(pos.x,pos.y,static_cast<float>(WINDOW_WIDTH),static_cast<float>(WINDOW_HEIGHT)),
		true,text_brush,true,text_format });
}

/**
* @brief �e�L�X�g�̃u���b�V�����쐬
* @param color �F
* @return �쐬�����e�L�X�g�̃u���b�V��
*/
ComPtr<ID2D1SolidColorBrush> TextUi::CreateTextBrush(const UINT32 color)
{
	ComPtr<ID2D1SolidColorBrush> text_brush;

	HRESULT hr = S_OK;
	hr = d2d1_device_context->CreateSolidColorBrush(D2D1::ColorF(color), &text_brush);
	if (FAILED(hr))
	{
		Comment(L"�u���b�V���̍쐬�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateTextBrush");
		throw 0;
	}

	return text_brush;
}

/**
* @brief �e�L�X�g�̃t�H�[�}�b�g���쐬
* @param font_size �t�H���g�̃T�C�Y
* @param font_weight �t�H���g�̑���
* @param font_style �t�H���g�̃X�^�C��
* @param font_stretch �t�H���g�̃X�g���b�`
* @param text_alignment �e�L�X�g�̃A���C�����g
* @return �쐬�����e�L�X�g�̃t�H�[�}�b�g
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
		Comment(L"�e�L�X�g�t�H�[�}�b�g�̍쐬�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateTextFormat");
		throw 0;
	}
	hr = text_format->SetTextAlignment(text_alignment);
	if (FAILED(hr))
	{
		Comment(L"�e�L�X�g�A���C�����g�̃Z�b�g�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateTextFormat");
		throw 0;
	}
	hr = text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	if (FAILED(hr))
	{
		Comment(L"�p���O���t�A���C�����g�̃Z�b�g�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateTextFormat");
		throw 0;
	}

	return text_format;
}

#pragma endregion

#pragma region private

/**
* @brief D3D�f�o�C�X�̍쐬
* @param d3d12_device DirectX12��3D�f�o�C�X
* @param command_queue �R�}���h�L���[
* @return �����������ǂ���
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
		Comment(L"12�ɏ������11�̃f�o�C�X�̍쐬�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateD3DDevice");
		return hr;
	}

	hr = d3d11_device.As(&d3d11_on_12_device);
	if (FAILED(hr))
	{
		Comment(L"12�ɏ������11�̃f�o�C�X�̃C���^�[�t�F�C�X�̎擾�Ɏ��s",
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
			Comment(L"�X�g���[�W�t�B���^���X�g���[�W�t�B���^�X�^�b�N��push�Ɏ��s",
				L"text_ui.cpp/TextUi::CreateD3DDevice");
			return hr;
		}
	}
#endif

	return hr;
}

/**
* @brief D2D�f�o�C�X�̍쐬
* @return �����������ǂ���
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
		Comment(L"DXGI�f�o�C�X�̃C���^�[�t�F�C�X�̎擾�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory3),
		&d2d_factory_options, &d2d_factory);
	if (FAILED(hr))
	{
		Comment(L"D2D1�t�@�N�g���[�̍쐬�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	hr = d2d_factory->CreateDevice(dxgi_device.Get(), &d2d1_device);
	if (FAILED(hr))
	{
		Comment(L"D2D1�f�o�C�X�̍쐬�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	hr = d2d1_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &d2d1_device_context);
	if (FAILED(hr))
	{
		Comment(L"D2D1�f�o�C�X�R���e�L�X�g�̍쐬�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	d2d1_device_context->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &dwrite_factory);
	if (FAILED(hr))
	{
		Comment(L"DwriteFactroy�̍쐬�Ɏ��s",
			L"text_ui.cpp/TextUi::CreateD2DDevice");
		return hr;
	}
	return hr;
}

/**
* @brief ���b�s���O���������_�[�^�[�Q�b�g�̍쐬
* @param render_targets ���b�s���O���郌���_�[�^�[�Q�b�g
* @return �����������ǂ���
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
			Comment(L"���\�[�X�̃��b�s���O�Ɏ��s",
				L"text_ui.cpp/TextUi::CreateWrappedRenderTargets");
			return hr;
		}
		ComPtr<IDXGISurface> surface;
		hr = wrapped_render_targets[i].As(&surface);
		if (FAILED(hr))
		{
			Comment(L"�����_�[�^�[�Q�b�g�̃C���^�[�t�F�C�X�̎擾�Ɏ��s",
				L"text_ui.cpp/TextUi::CreateWrappedRenderTargets");
			return hr;
		}
		hr = d2d1_device_context->CreateBitmapFromDxgiSurface(
			surface.Get(), &bitmap_properties, &d2d_render_targets[i]);
		if (FAILED(hr))
		{
			Comment(L"�r�b�g�}�b�v�̍쐬�Ɏ��s",
				L"text_ui.cpp/TextUi::CreateWrappedRenderTargets");
			return hr;
		}
	}

	return hr;
}

#pragma endregion
