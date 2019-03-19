/**
* @file text_ui.h
* @brief テキストクラス
* @author 石山　悠
* @date 2019/03/18
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include <dwrite.h>
#include <d2d1_3.h>
#include <d3d11on12.h>
#include <vector>
#include <string>
#include <saki/singleton.h>
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"d3d11.lib")

/**
* @brief テキストクラス
*/
class TextUi :public saki::singleton<TextUi>
{
	/**
	* @brief テキスト情報構造体
	*/
	struct TextBlock
	{
		std::wstring text;
		D2D1_RECT_F layout;
		bool use_custom_color;
		ComPtr<ID2D1SolidColorBrush> custom_text_brush;
		bool use_custom_format;
		ComPtr<IDWriteTextFormat> custom_text_format;
	};
	//d3dデバイス
	ComPtr<ID3D11DeviceContext> d3d11_device_context;
	ComPtr<ID3D11On12Device> d3d11_on_12_device;
	HRESULT CreateD3DDevice(ComPtr<ID3D12Device>& d3d12_device,
		ComPtr<ID3D12CommandQueue>& command_queue);
	//d2dデバイス
	ComPtr<IDWriteFactory> dwrite_factory;
	ComPtr<ID2D1Factory3> d2d_factory;
	ComPtr<ID2D1Device2> d2d1_device;
	ComPtr<ID2D1DeviceContext2> d2d1_device_context;
	HRESULT CreateD2DDevice();
	//レンダーターゲット
	std::vector<ComPtr<ID3D11Resource>> wrapped_render_targets;
	std::vector<ComPtr<ID2D1Bitmap1>> d2d_render_targets;
	HRESULT CreateWrappedRenderTargets(ComPtr<ID3D12Resource>* render_targets);
	//テキストデバイス
	ComPtr<ID2D1SolidColorBrush> default_text_brush;
	ComPtr<IDWriteTextFormat> default_text_format;
	//描画するテキストの情報を格納
	std::vector<TextBlock> text_blocks;
public:
	HRESULT Init(UINT frame_count,
		ComPtr<ID3D12Device>& d3d12_device,
		ComPtr<ID3D12CommandQueue>& command_queue, ComPtr<ID3D12Resource>* render_targets);
	HRESULT Render(UINT frame_index);
	void DrawString(const std::wstring& text, const Vec2& pos);
	void DrawStringColor(const std::wstring& text, const Vec2& pos,
		const ComPtr<ID2D1SolidColorBrush>& text_brush);
	void DrawStringFormat(const std::wstring& text, const Vec2& pos,
		const ComPtr<IDWriteTextFormat>& text_format);
	void DrawStringColorFormat(const std::wstring& text, const Vec2& pos,
		const ComPtr<ID2D1SolidColorBrush>& text_brush, const ComPtr<IDWriteTextFormat>& text_format);

	ComPtr<IDWriteTextFormat> CreateTextFormat(
		const float font_size = 1.0f,
		const DWRITE_FONT_WEIGHT font_weight = DWRITE_FONT_WEIGHT_NORMAL,
		const DWRITE_FONT_STYLE font_style = DWRITE_FONT_STYLE_NORMAL,
		const DWRITE_FONT_STRETCH font_stretch = DWRITE_FONT_STRETCH_NORMAL,
		const DWRITE_TEXT_ALIGNMENT text_alignment = DWRITE_TEXT_ALIGNMENT_LEADING);
	ComPtr<ID2D1SolidColorBrush> CreateTextBrush(const UINT32 color);
};