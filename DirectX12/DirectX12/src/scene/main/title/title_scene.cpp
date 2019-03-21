/**
* @file title_scene.cpp
* @brief タイトルシーンクラスの関数定義
* @author 石山　悠
* @date 2019/03/13
*/
#include "title_scene.h"
#include "../../../text_ui/text_ui.h"
#include "../../../time/time.h"
#include "../../../input/keyboard/keyboard_input.h"
#include "../../../camera/camera.h"
#include <string>
#include <sstream>
#include <iomanip>

#pragma region public

/**
* @brief タイトルシーンの初期化
* @return 成功したかどうか
*/
HRESULT TitleScene::Init()
{
	HRESULT hr = S_OK;

	hr = sm_command_list.Init();
	if (FAILED(hr))return hr;
	hr = model.Init(L"resources/model/humanoid.sakimdl", sm_command_list.GetPipeline());
	if (FAILED(hr))return hr;
	return hr;
}

/**
* @brief タイトルシーンの更新
* @param scene_ptr 現在のシーンのポインタ
* @param hr 成功したかどうかを格納する
* @return 次のシーンのポインタ
*/
ScenePtrType TitleScene::Update(ScenePtrType scene_ptr, HRESULT& hr)
{
	auto rot = transform.get_rot();
	//rot.y += 0.05f;
	//rot.x += 0.01f;
	transform.set_rot(rot);
	hr = model.UpdateTransform(transform);
	if (FAILED(hr))return scene_ptr;

	static Vec3 camera_rot{};
	constexpr float speed = 0.05f;
	if (KeyboardInput::getinstance()->GetKey(DIK_W))
	{
		camera_rot.x += speed;
	}
	if (KeyboardInput::getinstance()->GetKey(DIK_S))
	{
		camera_rot.x -= speed;
	}
	if (KeyboardInput::getinstance()->GetKey(DIK_D))
	{
		camera_rot.y -= speed;
	}
	if (KeyboardInput::getinstance()->GetKey(DIK_A))
	{
		camera_rot.y += speed;
	}
	static float distance = 50.0f;
	static float move_speed = 2.0f;
	if (KeyboardInput::getinstance()->GetKey(DIK_UPARROW))
	{
		distance += move_speed;
	}
	if (KeyboardInput::getinstance()->GetKey(DIK_DOWNARROW))
	{
		distance -= move_speed;
	}
	Matrix m = DirectX::XMMatrixIdentity();
	m *= DirectX::XMMatrixTranslation(0, 0, -distance);
	m *= DirectX::XMMatrixRotationRollPitchYaw(camera_rot.x, camera_rot.y, 0);
	DirectX::XMFLOAT4X4 f4x4;
	DirectX::XMStoreFloat4x4(&f4x4, m);
	Camera::getinstance()->SetPos(
		{ f4x4.m[3][0],f4x4.m[3][1],f4x4.m[3][2] });
	auto rotz = Camera::getinstance()->GetRotZ();
	if (KeyboardInput::getinstance()->GetKey(DIK_RIGHTARROW))
	{
		rotz += speed;
	}
	if (KeyboardInput::getinstance()->GetKey(DIK_LEFTARROW))
	{
		rotz -= speed;
	}
	Camera::getinstance()->SetRotZ(rotz);
	Camera::getinstance()->LookAt(transform.get_pos());

	//カメラの情報を表示
	{
		auto text_pos = Vec2{ 5.0f,5.0f };
		TextUi::getinstance()->DrawString(L"CameraInfo", text_pos);
		text_pos.y += 40.0f;
		{
			std::wstringstream camera_pos_text;
			auto cam_pos = Camera::getinstance()->GetPos();
			camera_pos_text << std::fixed << std::setprecision(3) << L"Pos/ X:" << cam_pos.x << L" Y:" << cam_pos.y << L" Z:" << cam_pos.z;
			TextUi::getinstance()->DrawString(camera_pos_text.str(), text_pos);
			text_pos.y += 35.0f;
		}
	}
	return scene_ptr;
}

/**
* @brief タイトルシーンの描画
* @return 成功したかどうか
*/
HRESULT TitleScene::Render()
{
	HRESULT hr = S_OK;

	hr = sm_command_list.BeginScene();
	if (FAILED(hr))return hr;
	hr = model.Draw(sm_command_list.GetCommandList());
	if (FAILED(hr))return hr;
	hr = sm_command_list.Execute();
	if (FAILED(hr))return hr;
	return hr;
}

/**
* @brief タイトルシーンの破棄
* @return 成功したかどうか
*/
HRESULT TitleScene::Destroy()
{
	HRESULT hr = S_OK;

	return hr;
}

#pragma endregion

#pragma region private



#pragma endregion