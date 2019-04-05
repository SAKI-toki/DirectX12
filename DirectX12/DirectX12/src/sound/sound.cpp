/**
* @file sound.cpp
* @brief �T�E���h�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/12/20
*/
#include "sound.h"
#include "../common/message_box.h"

class Sound::Impl
{
public:
	//����
	IXAudio2SourceVoice* source;
	//�T�E���h�̃f�[�^
	SoundData sound_data;
	//���O(�L�[)
	std::wstring key;
	//�o�b�t�@
	XAUDIO2_BUFFER buffer{};
};

#pragma region public

/**
* @brief �T�E���h�N���X�̃R���X�g���N�^
*/
Sound::Sound() :
	pimpl(new Impl{})
{}

/**
* @brief �T�E���h�N���X�̃f�X�g���N�^
*/
Sound::~Sound()
{
	if (pimpl->source)pimpl->source->DestroyVoice();
}

//���[�u�R���X�g���N�^�A���[�u������Z�q�̃f�t�H���g�w��
Sound::Sound(Sound&&)noexcept = default;
Sound& Sound::operator=(Sound&&)noexcept = default;

/**
* @brief �T�E���h�N���X�̏�����
* @param path �p�X
* @param is_loop ���[�v���邩�ǂ���
* @param is_awake �����Đ����邩�ǂ���
* @return �����������ǂ���
*/
HRESULT Sound::Init(const std::wstring& path, const bool is_loop, const bool is_awake)
{
	HRESULT hr = S_OK;
	pimpl->key = path;
	//���[�h
	hr = SoundManager::getinstance()->LoadSound(path);
	if (FAILED(hr))return hr;
	//�T�E���h�̃f�[�^�̎擾
	pimpl->sound_data = SoundManager::getinstance()->GetSound(path);
	pimpl->buffer.pAudioData = pimpl->sound_data.buffer;
	pimpl->buffer.Flags = XAUDIO2_END_OF_STREAM;
	pimpl->buffer.AudioBytes = pimpl->sound_data.wav_size;
	//���[�v���邩1��݂̂�
	pimpl->buffer.LoopCount = (is_loop) ? XAUDIO2_LOOP_INFINITE : 0;

	hr = SoundManager::getinstance()->GetIxaudio()->CreateSourceVoice(&pimpl->source, pimpl->sound_data.pwfex);
	if (FAILED(hr))
	{
		Comment(L"�T�E���h�̍쐬�Ɏ��s",
			L"sound.cpp/Sound::Init");
		return hr;
	}
	hr = pimpl->source->SubmitSourceBuffer(&pimpl->buffer);
	if (FAILED(hr))
	{
		Comment(L"�\�[�X��Submit�Ɏ��s",
			L"sound.cpp/Sound::Init");
		return hr;
	}

	if (is_awake)Play();

	return hr;
}

/**
* @brief �Đ�
*/
void Sound::Play()
{
	pimpl->source->Start();
}

/**
* @brief �ꎞ��~
*/
void Sound::Pause()
{
	pimpl->source->Stop();
}

/**
* @brief ��~
*/
void Sound::Stop()
{
	pimpl->source->Stop();
	pimpl->source->FlushSourceBuffers();
	pimpl->source->SubmitSourceBuffer(&pimpl->buffer);
}

/**
* @brief ���ݍĐ����Ă��邩�ǂ���
* @return �Đ����Ȃ�true��Ԃ�
*/
bool Sound::IsPlay()
{
	XAUDIO2_VOICE_STATE xa2scate;
	pimpl->source->GetState(&xa2scate);
	return xa2scate.BuffersQueued != 0;
}

/**
* @brief �{�����[���̃Z�b�^
* @param volume �{�����[��
*/
void Sound::SetVolume(float volume)
{
	if (volume < 0)volume = 0;
	pimpl->source->SetVolume(volume);
}

/**
* @brief �{�����[���̃Q�b�^
* @return �{�����[��
*/
float Sound::GetVolume()const
{
	std::unique_ptr<float> p(new float{});
	pimpl->source->GetVolume(p.get());
	return *p;
}

#pragma endregion