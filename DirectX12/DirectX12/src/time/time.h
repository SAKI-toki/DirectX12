/**
* @file time.h
* @brief 時間を管理するクラス
* @author 石山　悠
* @date 2019/03/05
*/
#pragma once
#include "../common/alias.h"
#include <saki/singleton.h>
#include <memory>

/**
* @brief 時間を管理するクラス
*/
class Time :public saki::singleton<Time>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Time();
	~Time()noexcept;
	//時間の更新
	//毎フレーム呼ぶこと
	void UpdateTime();
	//スケールを反映した経過時間を取得
	float GetElapsedTime();
	//スケールを反映しない経過時間を取得
	float GetElapsedTimeNotScale();
	//スケールのセッタ
	void SetTimeScale(float);
	//スケールのゲッタ
	float GetTimeScale();
	//FPSの描画
	void DrawFps(const Vec2& pos);
};