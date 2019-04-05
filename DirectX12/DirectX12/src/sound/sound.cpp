/**
* @file sound.cpp
* @brief サウンドクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/12/20
*/
#include "sound.h"
#include "../common/message_box.h"

class Sound::Impl
{
public:
	//音声
	IXAudio2SourceVoice* source;
	//サウンドのデータ
	SoundData sound_data;
	//名前(キー)
	std::wstring key;
	//バッファ
	XAUDIO2_BUFFER buffer{};
};

#pragma region public

/**
* @brief サウンドクラスのコンストラクタ
*/
Sound::Sound() :
	pimpl(new Impl{})
{}

/**
* @brief サウンドクラスのデストラクタ
*/
Sound::~Sound()
{
	if (pimpl->source)pimpl->source->DestroyVoice();
}

//ムーブコンストラクタ、ムーブ代入演算子のデフォルト指定
Sound::Sound(Sound&&)noexcept = default;
Sound& Sound::operator=(Sound&&)noexcept = default;

/**
* @brief サウンドクラスの初期化
* @param path パス
* @param is_loop ループするかどうか
* @param is_awake すぐ再生するかどうか
* @return 成功したかどうか
*/
HRESULT Sound::Init(const std::wstring& path, const bool is_loop, const bool is_awake)
{
	HRESULT hr = S_OK;
	pimpl->key = path;
	//ロード
	hr = SoundManager::getinstance()->LoadSound(path);
	if (FAILED(hr))return hr;
	//サウンドのデータの取得
	pimpl->sound_data = SoundManager::getinstance()->GetSound(path);
	pimpl->buffer.pAudioData = pimpl->sound_data.buffer;
	pimpl->buffer.Flags = XAUDIO2_END_OF_STREAM;
	pimpl->buffer.AudioBytes = pimpl->sound_data.wav_size;
	//ループするか1回のみか
	pimpl->buffer.LoopCount = (is_loop) ? XAUDIO2_LOOP_INFINITE : 0;

	hr = SoundManager::getinstance()->GetIxaudio()->CreateSourceVoice(&pimpl->source, pimpl->sound_data.pwfex);
	if (FAILED(hr))
	{
		Comment(L"サウンドの作成に失敗",
			L"sound.cpp/Sound::Init");
		return hr;
	}
	hr = pimpl->source->SubmitSourceBuffer(&pimpl->buffer);
	if (FAILED(hr))
	{
		Comment(L"ソースのSubmitに失敗",
			L"sound.cpp/Sound::Init");
		return hr;
	}

	if (is_awake)Play();

	return hr;
}

/**
* @brief 再生
*/
void Sound::Play()
{
	pimpl->source->Start();
}

/**
* @brief 一時停止
*/
void Sound::Pause()
{
	pimpl->source->Stop();
}

/**
* @brief 停止
*/
void Sound::Stop()
{
	pimpl->source->Stop();
	pimpl->source->FlushSourceBuffers();
	pimpl->source->SubmitSourceBuffer(&pimpl->buffer);
}

/**
* @brief 現在再生しているかどうか
* @return 再生中ならtrueを返す
*/
bool Sound::IsPlay()
{
	XAUDIO2_VOICE_STATE xa2scate;
	pimpl->source->GetState(&xa2scate);
	return xa2scate.BuffersQueued != 0;
}

/**
* @brief ボリュームのセッタ
* @param volume ボリューム
*/
void Sound::SetVolume(float volume)
{
	if (volume < 0)volume = 0;
	pimpl->source->SetVolume(volume);
}

/**
* @brief ボリュームのゲッタ
* @return ボリューム
*/
float Sound::GetVolume()const
{
	std::unique_ptr<float> p(new float{});
	pimpl->source->GetVolume(p.get());
	return *p;
}

#pragma endregion