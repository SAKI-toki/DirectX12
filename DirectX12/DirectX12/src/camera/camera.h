/**
* @file camera.h
* @brief カメラクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../common/alias.h"
#include <saki/singleton.h>
#include <memory>

/**
* @brief カメラクラス
*/
class Camera :public saki::singleton<Camera>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Camera();
	~Camera()noexcept;
	void Update();
	Matrix GetView()const;
	Matrix GetProjection()const;
	Matrix GetViewMulProjection()const;
	Vec3 GetForward()const;
	void SetForward(const Vec3& camera_forward);
	void LookAt(const Vec3& look_at);
	Vec3 GetPos()const;
	void SetPos(const Vec3& camera_pos);
	float GetRotZ()const;
	void SetRotZ(const float camera_rot_z);
};