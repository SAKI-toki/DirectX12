/**
* @file camera.cpp
* @brief カメラクラスの関数定義
* @author 石山　悠
* @date 2019/02/08
*/
#include "camera.h"
#include "../common/window_size.h"
#include <cmath>
#include <saki/math/pi.h>
#include <saki/math/degree_radian_conversion.h>

/**
* @brief カメラクラスのpimplイディオム
*/
class Camera::Impl
{
public:
	//近い距離
	static constexpr float NEAR_Z = 0.1f;
	//遠い距離
	static constexpr float FAR_Z = 10000.0f;
	//視野
	static constexpr float fov = saki::to_radian(60.0f);
	//行列
	Matrix view, projection, view_mul_projection;
	//位置
	Vec3 pos{ 0.0f,0.0f,-10.0f };
	//向き
	Vec3 forward_vector{ 0.0f,0.0f,1.0f };
	//Z軸回転
	float rot_z{ 0.0f };
	//行列の更新
	void MatrixUpdate();
};

#pragma region public

/**
* @brief カメラのコンストラクタ
*/
Camera::Camera() :
	pimpl(new Impl{})
{
	pimpl->MatrixUpdate();
}

//デストラクタのデフォルト指定
Camera::~Camera()noexcept = default;
/**
* @brief カメラの更新
*/
void Camera::Update()
{
	pimpl->MatrixUpdate();
}

/**
* @brief ビュー行列の取得
* @return ビュー行列
*/
Matrix Camera::GetView()const
{
	return pimpl->view;
}

/**
* @brief プロジェクション行列の取得
* @return プロジェクション行列
*/
Matrix Camera::GetProjection()const
{
	return pimpl->projection;
}

/**
* @brief ビュー行列とプロジェクション行列をかけた行列の取得
* @return ビュー行列とプロジェクション行列をかけた行列
*/
Matrix Camera::GetViewMulProjection()const
{
	return pimpl->view_mul_projection;
}

/**
* @brief 向きベクトルのゲッタ
* @return 向きベクトル
*/
Vec3 Camera::GetForward()const
{
	return pimpl->forward_vector;
}

/**
* @brief 向きベクトルのセッタ
* @param camera_forward_vector 新しい向きベクトル
*/
void Camera::SetForward(const Vec3& camera_forward_vector)
{
	//向きが0,0,0の場合は何も処理しない
	if (camera_forward_vector == Vec3{})return;
	pimpl->forward_vector = camera_forward_vector;
	pimpl->forward_vector.normalize();
}

/**
* @brief 見たい位置から向きベクトルをセットする
* @param look_at 見たい位置
*/
void Camera::LookAt(const Vec3 & look_at)
{
	//見たい位置とカメラの位置が同じ場合は何も処理しない
	if (look_at == pimpl->pos)return;
	Camera::getinstance()->SetForward(look_at - pimpl->pos);
}

/**
* @brief 位置のゲッタ
* @return 位置
*/
Vec3 Camera::GetPos()const
{
	return pimpl->pos;
}

/**
* @brief 位置のセッタ
* @param _pos 新しいカメラの位置
*/
void Camera::SetPos(const Vec3 & camera_pos)
{
	pimpl->pos = camera_pos;
}

/**
* @brief カメラのz軸回転のゲッタ
* @return カメラのz軸回転
*/
float Camera::GetRotZ()const
{
	return pimpl->rot_z;
}

/**
* @brief カメラのz軸回転のセッタ
* @param camera_rot_z 新しいカメラのz軸回転
*/
void Camera::SetRotZ(const float camera_rot_z)
{
	pimpl->rot_z = camera_rot_z;
}

#pragma endregion

#pragma region pimpl

/**
* @brief 行列の更新
*/
void Camera::Impl::MatrixUpdate()
{
	Vector vec_pos{ pos.x,pos.y,pos.z };
	Vector vec_look_at = DirectX::XMVectorAdd(vec_pos, { forward_vector.x, forward_vector.y, forward_vector.z });
	//ビュー行列
	view = DirectX::XMMatrixLookAtLH(vec_pos, vec_look_at, { 0.0f,1.0f,0.0f });
	//プロジェクション行列
	projection = DirectX::XMMatrixPerspectiveFovLH(
		fov, static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT),
		NEAR_Z, FAR_Z);
	//2D用のプロジェクション
	//projection = DirectX::XMMatrixOrthographicLH(
	//	static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), NEAR_Z, FAR_Z);
	//ビューとプロジェクション行列をかける(Z軸回転を考慮)
	view_mul_projection = view * DirectX::XMMatrixRotationRollPitchYaw(0, 0, rot_z) * projection;
}

#pragma endregion