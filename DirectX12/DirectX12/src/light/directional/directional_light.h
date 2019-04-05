/**
* @file directional_light.h
* @brief 平行光源クラス
* @author 石山　悠
* @date 2019/03/29
*/
#pragma once
#include "../../common/alias.h"
#include "../../common/d3d12.h"
#include <saki/singleton.h>
#include <memory>

/**
* @brief 平行光源クラス
*/
class DirectionalLight :public saki::singleton<DirectionalLight>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	DirectionalLight();
	~DirectionalLight()noexcept;
	HRESULT Init(ComPtr<ID3D12Device>& device);
	HRESULT Update();
	HRESULT SetConstantBuffer(ComPtr<ID3D12GraphicsCommandList>& command_list);
	Vec3 GetPos()const;
	void SetPos(const Vec3& vec);
};