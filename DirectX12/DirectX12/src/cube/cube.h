/**
* @file cube.h
* @brief �L���[�u�N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "../common/d3d12.h"
#include "../common/alias.h"
#include <memory>
#include <string>

/**
* @brief �L���[�u�N���X
*/
class Cube
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Cube();
	~Cube()noexcept;
	Cube& operator=(Cube&&)noexcept;
	Cube(Cube&&)noexcept;
	HRESULT Init(const std::wstring& tex_path, ComPtr<ID3D12PipelineState>& com_pipeline);
	HRESULT Draw(const Transform& transform, ComPtr<ID3D12GraphicsCommandList>& com_command_list);
};