/**
* @file sound_manager.cpp
* @brief �T�E���h�̃}�l�[�W���[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/12/20
*/
#include "sound_manager.h"
#include "../../common/message_box.h"
#include <unordered_map>

/**
* @brief �T�E���h���Ǘ�����N���X��pimpl�C�f�B�I��
*/
class SoundManager::Impl
{
public:
	//�T�E���h�̊e�f�o�C�X
	IXAudio2* ix_audio2 = nullptr;
	IXAudio2MasteringVoice* mastering_voice = nullptr;
	//�}�b�v
	std::unordered_map <std::wstring, SoundData> sound_list;
};

#pragma region public

/**
* @brief �T�E���h���Ǘ�����N���X�̃R���X�g���N�^
*/
SoundManager::SoundManager() :
	pimpl(new Impl{})
{}

/**
* @brief �T�E���h���Ǘ�����N���X�̃f�X�g���N�^
*/
SoundManager::~SoundManager()
{
	if (pimpl->mastering_voice)
	{
		pimpl->mastering_voice->DestroyVoice();
		pimpl->mastering_voice = 0;
	}
	CoUninitialize();
}

/**
* @brief �T�E���h�}�l�[�W���[�̏�����
* @return ����ɏ������ł������ǂ���
*/
HRESULT SoundManager::Init()
{
	HRESULT hr = S_OK;

	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		Comment(L"CoInitializeEx�Ɏ��s",
			L"sound_manager.cpp/SoundManager::Init");
		return hr;
	}
	hr = XAudio2Create(&pimpl->ix_audio2, 0);
	if (FAILED(hr))
	{
		Comment(L"xaudio�̍쐬�Ɏ��s",
			L"sound_manager.cpp/SoundManager::Init");
		return hr;
	}
	hr = pimpl->ix_audio2->CreateMasteringVoice(&pimpl->mastering_voice);
	if (FAILED(hr))
	{
		Comment(L"MasteringVoice�̍쐬�Ɏ��s",
			L"sound_manager.cpp/SoundManager::Init");
		return hr;
	}

	return hr;
}

/**
* @brief �T�E���h�̓ǂݍ���
* @param path �T�E���h�̃p�X
* @return ����ɓǂݍ��߂����ǂ���
*/
HRESULT SoundManager::LoadSound(const std::wstring& path)
{
	//�L�[�����ƂɒT��
	auto itr = pimpl->sound_list.find(path);
	//������Ȃ�������ǉ�����(�ǂݍ���)
	if (itr != std::end(pimpl->sound_list))return S_OK;
	//�p�X
	WCHAR file_path[256];
	wcscpy_s(file_path, path.c_str());

	//�T�E���h�̃f�[�^
	SoundData sound_data;
	//mmio�n���h��
	HMMIO hMmio = 0;
	//�T�C�Y
	DWORD dw_wav_size = 0;
	//�`�����N���
	MMCKINFO ck_info, riffck_info;
	//PCM�g�`�I�[�f�B�I�f�[�^�̃f�[�^�t�H�[�}�b�g
	PCMWAVEFORMAT pcm_wave_form;
	//�o�b�t�@���J��(���o��&�ǂݎ���p)
	hMmio = mmioOpen(file_path, 0, MMIO_ALLOCBUF | MMIO_READ);
	if (hMmio == 0)
	{
		Comment(L"�����t�@�C���̃p�X���Ⴂ�܂�",
			L"sound_manager.cpp/SoundManager::LoadSound");
		return E_FAIL;
	}
	//��ŊJ�����t�@�C���̃`�����N�ɐi��
	mmioDescend(hMmio, &riffck_info, 0, 0);
	//�`�����N�̎�ޔ���
	ck_info.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hMmio, &ck_info, &riffck_info, MMIO_FINDCHUNK);
	//�ǂݎ��
	mmioRead(hMmio, (HPSTR)(&pcm_wave_form), sizeof(pcmwaveformat_tag));
	//�������m��
	sound_data.pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	//�������R�s�[
	memcpy(sound_data.pwfex, &pcm_wave_form, sizeof(pcm_wave_form));
	sound_data.pwfex->cbSize = 0;
	mmioAscend(hMmio, &ck_info, 0);
	ck_info.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hMmio, &ck_info, &riffck_info, MMIO_FINDCHUNK);
	//�T�C�Y�̎擾
	dw_wav_size = ck_info.cksize;
	sound_data.buffer = new BYTE[dw_wav_size];
	mmioRead(hMmio, (HPSTR)sound_data.buffer, dw_wav_size);
	//�T�C�Y
	sound_data.wav_size = dw_wav_size;
	//map�ɒǉ�
	pimpl->sound_list.insert(std::make_pair(path, sound_data));

	return S_OK;
}

/**
* @brief �T�E���h�̎擾
* @param key �L�[
* @return �T�E���h�ɕK�v�ȃf�[�^
*/
SoundData SoundManager::GetSound(const std::wstring& key)
{
	auto itr = pimpl->sound_list.find(key);
	if (itr == std::end(pimpl->sound_list))throw 0;
	return itr->second;
}

/**
* @brief IXAudio2�̓ǂݍ���
* @return IXAudio2
*/
IXAudio2* SoundManager::GetIxaudio()
{
	return pimpl->ix_audio2;
}

#pragma endregion