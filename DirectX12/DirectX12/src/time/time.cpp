/**
* @file time.cpp
* @brief 時間を管理するクラスのメンバ関数を定義
* @author 石山　悠
* @date 2019/03/05
*/
#include "time.h"

/**
* @brief 時間の更新、毎フレーム呼ぶ
*/
void Time::UpdateTime()
{
	elapsed_time = my_clock.end_and_start<float>(saki::clock::DURATION::SECOND);
}

/**
* @brief スケールを反映した経過時間の取得
* @return 経過時間(スケールを反映)
*/
float Time::GetElapsedTime()
{
	return elapsed_time * time_scale;
}

/**
* @brief スケールを反映しない経過時間の取得
* @return 経過時間(スケールを反映しない)
*/
float Time::GetElapsedTimeNotScale()
{
	return elapsed_time;
}

/**
* @brief 時間のスケールのセッタ
* @param scale セットするスケール
*/
void Time::SetTimeScale(float scale)
{
	time_scale = scale;
}

/**
* @brief 時間のスケールのゲッタ
* @return 時間のスケール
*/
float Time::GetTimeScale()
{
	return time_scale;
}