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
	static constexpr float FAR_Z = 10000.0f;
	//視野
	static constexpr float fov = saki::to_radian(60.0f);
	//行列
	Matrix view, projection, view_mul_projection;
	//位置,向きベクトル
	Vec3 pos, forward_vector;
	//行列の更新
	void MatrixUpdate();
	//Z軸回転
	float rot_z;
public:
	Camera();
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