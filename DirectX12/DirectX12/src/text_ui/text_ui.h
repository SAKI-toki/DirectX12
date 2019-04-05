/**
* @file text_ui.h
* @brief テキストクラス
* @author 石山　悠
* @date 2019/03/18
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include <memory>
#include <dwrite.h>
#include <d2d1_3.h>
#include <d3d11on12.h>
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
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	TextUi();
	~TextUi()noexcept;

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