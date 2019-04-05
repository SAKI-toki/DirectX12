/**
* @file sphere.h
* @brief �X�t�B�A�N���X
* @author �ΎR�@�I
* @date 2019/03/12
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include <memory>
#include <string>

/**
* @brief �X�t�B�A�N���X
*/
class Sphere
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Sphere();
	~Sphere()noexcept;
	Sphere(Sphere&&)noexcept;
	Sphere& operator=(Sphere&&)noexcept;
	HRESULT Init(const std::wstring& tex_path, ComPtr<ID3D12PipelineState>& com_pipeline);
	HRESULT Draw(const Transform& transform, ComPtr<ID3D12GraphicsCommandList>& com_command_list);
};