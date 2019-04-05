/**
* @file sound_manager.cpp
* @brief サウンドのマネージャークラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/12/20
*/
#include "sound_manager.h"
#include "../../common/message_box.h"
#include <unordered_map>

/**
* @brief サウンドを管理するクラスのpimplイディオム
*/
class SoundManager::Impl
{
public:
	//サウンドの各デバイス
	IXAudio2* ix_audio2 = nullptr;
	IXAudio2MasteringVoice* mastering_voice = nullptr;
	//マップ
	std::unordered_map <std::wstring, SoundData> sound_list;
};

#pragma region public

/**
* @brief サウンドを管理するクラスのコンストラクタ
*/
SoundManager::SoundManager() :
	pimpl(new Impl{})
{}

/**
* @brief サウンドを管理するクラスのデストラクタ
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
* @brief サウンドマネージャーの初期化
* @return 正常に初期化できたかどうか
*/
HRESULT SoundManager::Init()
{
	HRESULT hr = S_OK;

	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		Comment(L"CoInitializeExに失敗",
			L"sound_manager.cpp/SoundManager::Init");
		return hr;
	}
	hr = XAudio2Create(&pimpl->ix_audio2, 0);
	if (FAILED(hr))
	{
		Comment(L"xaudioの作成に失敗",
			L"sound_manager.cpp/SoundManager::Init");
		return hr;
	}
	hr = pimpl->ix_audio2->CreateMasteringVoice(&pimpl->mastering_voice);
	if (FAILED(hr))
	{
		Comment(L"MasteringVoiceの作成に失敗",
			L"sound_manager.cpp/SoundManager::Init");
		return hr;
	}

	return hr;
}

/**
* @brief サウンドの読み込み
* @param path サウンドのパス
* @return 正常に読み込めたかどうか
*/
HRESULT SoundManager::LoadSound(const std::wstring& path)
{
	//キーをもとに探す
	auto itr = pimpl->sound_list.find(path);
	//見つからなかったら追加する(読み込む)
	if (itr != std::end(pimpl->sound_list))return S_OK;
	//パス
	WCHAR file_path[256];
	wcscpy_s(file_path, path.c_str());

	//サウンドのデータ
	SoundData sound_data;
	//mmioハンドラ
	HMMIO hMmio = 0;
	//サイズ
	DWORD dw_wav_size = 0;
	//チャンク情報
	MMCKINFO ck_info, riffck_info;
	//PCM波形オーディオデータのデータフォーマット
	PCMWAVEFORMAT pcm_wave_form;
	//バッファを開く(入出力&読み取り専用)
	hMmio = mmioOpen(file_path, 0, MMIO_ALLOCBUF | MMIO_READ);
	if (hMmio == 0)
	{
		Comment(L"音声ファイルのパスが違います",
			L"sound_manager.cpp/SoundManager::LoadSound");
		return E_FAIL;
	}
	//上で開いたファイルのチャンクに進入
	mmioDescend(hMmio, &riffck_info, 0, 0);
	//チャンクの種類判別
	ck_info.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hMmio, &ck_info, &riffck_info, MMIO_FINDCHUNK);
	//読み取り
	mmioRead(hMmio, (HPSTR)(&pcm_wave_form), sizeof(pcmwaveformat_tag));
	//メモリ確保
	sound_data.pwfex = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	//メモリコピー
	memcpy(sound_data.pwfex, &pcm_wave_form, sizeof(pcm_wave_form));
	sound_data.pwfex->cbSize = 0;
	mmioAscend(hMmio, &ck_info, 0);
	ck_info.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hMmio, &ck_info, &riffck_info, MMIO_FINDCHUNK);
	//サイズの取得
	dw_wav_size = ck_info.cksize;
	sound_data.buffer = new BYTE[dw_wav_size];
	mmioRead(hMmio, (HPSTR)sound_data.buffer, dw_wav_size);
	//サイズ
	sound_data.wav_size = dw_wav_size;
	//mapに追加
	pimpl->sound_list.insert(std::make_pair(path, sound_data));

	return S_OK;
}

/**
* @brief サウンドの取得
* @param key キー
* @return サウンドに必要なデータ
*/
SoundData SoundManager::GetSound(const std::wstring& key)
{
	auto itr = pimpl->sound_list.find(key);
	if (itr == std::end(pimpl->sound_list))throw 0;
	return itr->second;
}

/**
* @brief IXAudio2の読み込み
* @return IXAudio2
*/
IXAudio2* SoundManager::GetIxaudio()
{
	return pimpl->ix_audio2;
}

#pragma endregion