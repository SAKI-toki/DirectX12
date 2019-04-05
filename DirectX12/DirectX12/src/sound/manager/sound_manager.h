/**
* @file sound_manager.h
* @brief サウンドを管理するクラス
* @author 石山　悠
* @date 2018/12/20
*/
#pragma once
#include <saki/singleton.h>
#include <xaudio2.h>
#include <string>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"xaudio2.lib")
#include <memory>

/**
* @brief サウンドのデータ
*/
struct SoundData
{
	DWORD wav_size;
	WAVEFORMATEX* pwfex;
	BYTE* buffer;
};

/**
* @brief サウンドを管理するクラス
*/
class SoundManager :public saki::singleton<SoundManager>
{
	class Impl;
	std::unique_ptr<Impl> pimpl;
public:
	SoundManager();
	~SoundManager()noexcept;
	HRESULT Init();
	HRESULT LoadSound(const std::wstring& path);
	SoundData GetSound(const std::wstring& key);
	IXAudio2* GetIxaudio();
};