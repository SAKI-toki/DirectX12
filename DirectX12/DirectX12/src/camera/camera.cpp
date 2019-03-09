/**
* @file camera.cpp
* @brief カメラクラスの関数定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "camera.h"
#include "../common/window_size.h"

/**
* @brief カメラの初期化
*/
void Camera::Init()
{
	MatrixUpdate();
}

/**
* @brief カメラの更新
*/
void Camera::Update()
{
	MatrixUpdate();
}

/**
* @brief ビュー行列の取得
* @return ビュー行列
*/
Matrix Camera::GetView()const
{
	return view;
}

/**
* @brief プロジェクション行列の取得
* @return プロジェクション行列
*/
Matrix Camera::GetProjection()const
{
	return projection;
}

/**
* @brief ビュー行列とプロジェクション行列をかけた行列の取得
* @return ビュー行列とプロジェクション行列をかけた行列
*/
Matrix Camera::GetViewMulProjection()const
{
	return view_mul_projection;
}

/**
* @brief 行列の更新
*/
void Camera::MatrixUpdate()
{
	view = DirectX::XMMatrixLookAtLH(pos, lookat, up);
	projection = DirectX::XMMatrixPerspectiveFovLH(
		fov, static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT),
		NEAR_Z, FAR_Z);
	view_mul_projection = view * projection;
}

/**
* @brief 位置のゲッタ
* @return 位置
*/
Vector Camera::GetPos()const
{
	return pos;
}

/**
* @brief 位置のセッタ
* @param _pos 新しいカメラの位置
*/
void Camera::SetPos(const Vector& _pos)
{
	pos = _pos;
}

/**
* @brief 注視点のゲッタ
* @return 注視点
*/
Vector Camera::GetLookAt()const
{
	return lookat;
}

/**
* @brief 注視点のセッタ
* @param _lookat 新しい注視点
*/
void Camera::SetLookAt(const Vector& _lookat)
{
	lookat = _lookat;
}