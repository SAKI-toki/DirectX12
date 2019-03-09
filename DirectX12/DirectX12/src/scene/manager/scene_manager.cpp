#include "scene_manager.h"
#include "../main/title/title_scene.h"

HRESULT SceneManager::Init()
{
	HRESULT hr = S_OK;

	scene_ptr = std::make_shared<TitleScene>();
	hr = scene_ptr->Init();
	if (FAILED(hr))return hr;

	return hr;
}

HRESULT SceneManager::Update()
{
	HRESULT hr = S_OK;

	auto next_scene_ptr = scene_ptr->Update(scene_ptr, hr);
	if (FAILED(hr))return hr;

	if (next_scene_ptr != scene_ptr)
	{
		hr = scene_ptr->Destroy();
		if (FAILED(hr))return hr;
		scene_ptr = next_scene_ptr;
		hr = scene_ptr->Init();
		if (FAILED(hr))return hr;
	}

	return hr;
}

HRESULT SceneManager::Render()
{
	HRESULT hr = S_OK;

	hr = scene_ptr->Render();
	if (FAILED(hr))return hr;

	return hr;
}

HRESULT SceneManager::Destroy()
{
	HRESULT hr = S_OK;

	hr = scene_ptr->Destroy();
	if (FAILED(hr))return hr;

	return hr;
}