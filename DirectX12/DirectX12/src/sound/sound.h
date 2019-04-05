/**
* @file sound.h
* @brief サウンドクラスの宣言
* @author 石山　悠
* @date 2018/12/20
*/
#pragma once
#include "manager/sound_manager.h"
#include <memory>

/**
* @brief サウンドクラス
*/
class Sound
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	Sound();
	~Sound();
	Sound(Sound&&)noexcept;
	Sound& operator=(Sound&&)noexcept;
	HRESULT Init(const std::wstring& path, const bool is_loop, const bool is_awake);
	void Play();
	void Pause();
	void Stop();
	bool IsPlay();
	void SetVolume(float volume);
	float GetVolume()const;
};