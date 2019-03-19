/**
* @file time.h
* @brief 時間を管理するクラス
* @author 石山　悠
* @date 2019/03/05
*/
#pragma once
#include "../common/alias.h"
#include <saki/clock.h>
#include <saki/singleton.h>

/**
* @brief 時間を管理するクラス
*/
class Time :public saki::singleton<Time>
{
	//時間を測る
	saki::clock my_clock;
	//経過時間(スケール反映)
	float elapsed_time = 0.0f;
	//経過時間(スケール反映なし)
	float elapsed_time_not_scale = 0.0f;
	//時間のスケール
	float time_scale = 1.0f;

public:
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