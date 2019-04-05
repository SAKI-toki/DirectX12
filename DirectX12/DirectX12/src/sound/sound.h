/**
* @file sound.h
* @brief �T�E���h�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/12/20
*/
#pragma once
#include "manager/sound_manager.h"
#include <memory>

/**
* @brief �T�E���h�N���X
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