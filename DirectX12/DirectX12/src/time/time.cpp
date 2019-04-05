/**
* @file time.cpp
* @brief 時間を管理するクラスのメンバ関数を定義
* @author 石山　悠
* @date 2019/03/05
*/
#include "time.h"
#include "../text_ui/text_ui.h"
#include <saki/clock.h>
#include <string>
#include <sstream>
#include <iomanip>

/**
* @brief 時間を管理するクラスのpimplイディオム
*/
class Time::Impl
{
public:
	//時間を測る
	saki::clock my_clock;
	//経過時間(スケール反映)
	float elapsed_time = 0.0f;
	//経過時間(スケール反映なし)
	float elapsed_time_not_scale = 0.0f;
	//時間のスケール
	float time_scale = 1.0f;
};

#pragma region public

/**
* @brief 時間を管理するクラスのコンストラクタ
*/
Time::Time() :
	pimpl(new Impl{})
{}

//デストラクタのデフォルト指定
Time::~Time()noexcept = default;

/**
* @brief 時間の更新、毎フレーム呼ぶ
*/
void Time::UpdateTime()
{
	pimpl->elapsed_time_not_scale = pimpl->my_clock.end_and_start<float>(saki::clock::DURATION::SECOND);
	pimpl->elapsed_time = pimpl->elapsed_time_not_scale * pimpl->time_scale;
}

/**
* @brief スケールを反映した経過時間の取得
* @return 経過時間(スケールを反映)
*/
float Time::GetElapsedTime()
{
	return pimpl->elapsed_time;
}

/**
* @brief スケールを反映しない経過時間の取得
* @return 経過時間(スケールを反映しない)
*/
float Time::GetElapsedTimeNotScale()
{
	return pimpl->elapsed_time_not_scale;
}

/**
* @brief 時間のスケールのセッタ
* @param scale セットするスケール
*/
void Time::SetTimeScale(float scale)
{
	pimpl->time_scale = scale;
}

/**
* @brief 時間のスケールのゲッタ
* @return 時間のスケール
*/
float Time::GetTimeScale()
{
	return pimpl->time_scale;
}

/**
* @brief Fpsの描画
* @param pos 位置
*/
void Time::DrawFps(const Vec2& pos)
{
	//ここだけで完結させるために静的にする
	static UINT update_count = 0;
	static constexpr double update_delay = 1.0;
	static double sum_time = 0;
	static std::wstring fps{ L"FPS:60.00" };
	sum_time += Time::getinstance()->GetElapsedTimeNotScale();
	++update_count;
	//一定時間経過したら更新
	if (sum_time > update_delay)
	{
		std::wstringstream wss;
		wss << "FPS:" << std::fixed << std::setprecision(2) << 1.0f / (sum_time / update_count);
		fps.clear();
		wss >> fps;
		update_count = 0;
		sum_time = 0;
	}
	TextUi::getinstance()->DrawString(fps, pos);
}

#pragma endregion