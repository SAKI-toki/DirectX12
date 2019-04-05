/**
* @file sprite.h
* @brief スプライトクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include <memory>
#include <string>

/**
* @brief スプライトクラス
*/
class Sprite
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Sprite();
	~Sprite()noexcept;
	Sprite(Sprite&&)noexcept;
	Sprite& operator=(Sprite&&)noexcept;
	HRESULT Init(const std::wstring& path, ComPtr<ID3D12PipelineState>& pipeline);
	HRESULT UpdateColor(const Float4& color);
	HRESULT Draw(const Transform& transform, ComPtr<ID3D12GraphicsCommandList>& command_list);
};