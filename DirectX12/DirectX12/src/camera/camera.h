/**
* @file camera.h
* @brief カメラクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../common/alias.h"
#include <saki/singleton.h>
#include <saki/math/degree_radian_conversion.h>

/**
* @brief カメラクラス
*/
class Camera :public saki::singleton<Camera>
{
	//近い距離
	static constexpr float NEAR_Z = 0.1f;
	//遠い距離
	static constexpr float FAR_Z = 100.0f;
	//行列
	Matrix view, projection, view_mul_projection;
	//各要素
	Vector pos, lookat, up;
	//行列
	static constexpr float fov = saki::to_radian(60.0f);
	//行列の更新
	void MatrixUpdate();
public:
	Camera();
	void Update();
	Matrix GetView()const;
	Matrix GetProjection()const;
	Matrix GetViewMulProjection()const;
	Vector GetPos()const;
	void SetPos(const Vector& camera_pos);
	Vector GetLookAt()const;
	void SetLookAt(const Vector& camera_look_at);
};