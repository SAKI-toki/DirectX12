/**
* @file texture_manager.h
* @brief �e�N�X�`�����Ǘ�����N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/02/08
*/
#include "texture_manager.h"
#include "../../device/device.h"
#include "../../common/message_box.h"
#include <fstream>
#include <unordered_map>

/**
* @brief �e�N�X�`�����Ǘ�����N���X��pimpl�C�f�B�I��
*/
class TextureManager::Impl
{
public:
	/**
	* @brief �e�N�X�`���̏��\����
	*/
	struct TextureData
	{
		int width{}, height{};
		ComPtr<ID3D12Resource> texture;
		ComPtr<ID3D12DescriptorHeap> dh_texture;
	};
	std::unordered_map<std::wstring, TextureData> texture_data_map;
};

#pragma region public

/**
* @brief �e�N�X�`�����Ǘ�����N���X�̃R���X�g���N�^
*/
TextureManager::TextureManager() :
	pimpl(new Impl{})
{}

//�f�X�g���N�^�̃f�t�H���g�w��
TextureManager::~TextureManager()noexcept = default;

/**
* @brief �e�N�X�`���̓ǂݍ���
* @param path �e�N�X�`���̃p�X
* @return �����������ǂ���
*/
HRESULT TextureManager::LoadTexture(const std::wstring& path)
{
	HRESULT hr = S_OK;

	auto itr = pimpl->texture_data_map.find(path);
	//���ɓǂݍ���ł���ꍇ
	if (itr != std::end(pimpl->texture_data_map)) { return hr; }
	TextureManager::Impl::TextureData texture_data;
	std::vector<byte> img;
	//�Ǝ��t�@�C���̓ǂݍ���
	{
		std::ifstream ifs(path,  std::ios_base::binary);
		if (ifs.fail())
		{
			Comment(L"�e�N�X�`���̃p�X���Ⴂ�܂�", 
				L"texture_manager.cpp/TextureManager::LoadTexture");
			return E_FAIL;
		}
		ifs.read(reinterpret_cast<char*>(&texture_data.width), sizeof(texture_data.width));
		ifs.read(reinterpret_cast<char*>(&texture_data.height), sizeof(texture_data.height));
		img.resize(static_cast<size_t>(texture_data.width) * static_cast<size_t>(texture_data.height) * static_cast<size_t>(4));
		ifs.read(reinterpret_cast<char*>(&img[0]), img.size());
		ifs.close();
	}


	D3D12_HEAP_PROPERTIES heap_properties{};
	heap_properties.Type = D3D12_HEAP_TYPE_CUSTOM;
	heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	heap_properties.CreationNodeMask = 0;
	heap_properties.VisibleNodeMask = 0;

	D3D12_RESOURCE_DESC resource_desc{};
	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resource_desc.Width = texture_data.width;
	resource_desc.Height = texture_data.height;
	resource_desc.DepthOrArraySize = 1;
	resource_desc.MipLevels = 1;
	resource_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;

	hr = Device::getinstance()->GetDevice()->CreateCommittedResource
	(&heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_COMMON,
		nullptr, IID_PPV_ARGS(&texture_data.texture));
	if (FAILED(hr))
	{
		Comment(L"�e�N�X�`���p�̃��\�[�X�ƃq�[�v�̍쐬�Ɏ��s", 
			L"texture_manager.cpp/TextureManager::LoadTexture");
		return hr;
	}

	D3D12_DESCRIPTOR_HEAP_DESC descriptor_heap_desc{};
	descriptor_heap_desc.NumDescriptors = 2;
	descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descriptor_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descriptor_heap_desc.NodeMask = 0;
	hr = Device::getinstance()->GetDevice()->CreateDescriptorHeap
	(&descriptor_heap_desc, IID_PPV_ARGS(&texture_data.dh_texture));
	if (FAILED(hr))
	{
		Comment(L"�e�N�X�`���p�̃f�X�N���v�^�q�[�v�̍쐬�Ɏ��s",
			L"texture_manager.cpp/TextureManager::LoadTexture");
		return hr;
	}
	D3D12_CPU_DESCRIPTOR_HANDLE handle_srv{};
	D3D12_SHADER_RESOURCE_VIEW_DESC resource_view_desc{};
	resource_view_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	resource_view_desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	resource_view_desc.Texture2D.MipLevels = 1;
	resource_view_desc.Texture2D.MostDetailedMip = 0;
	resource_view_desc.Texture2D.PlaneSlice = 0;
	resource_view_desc.Texture2D.ResourceMinLODClamp = 0.0f;
	resource_view_desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	handle_srv = texture_data.dh_texture->GetCPUDescriptorHandleForHeapStart();
	Device::getinstance()->GetDevice()->CreateShaderResourceView(texture_data.texture.Get(), &resource_view_desc, handle_srv);

	D3D12_BOX box{ 0,0,0,static_cast<UINT>(texture_data.width),static_cast<UINT>(texture_data.height),1 };
	hr = texture_data.texture->WriteToSubresource(
		0, &box, &img[0], static_cast<UINT>(4 * texture_data.width), static_cast<UINT>(4 * texture_data.width * texture_data.height));
	if (FAILED(hr))
	{
		Comment(L"�T�u���\�[�X�ւ̏������݂Ɏ��s", 
			L"texture_manager.cpp/TextureManager::LoadTexture");
		return E_FAIL;
	}
	pimpl->texture_data_map.insert(std::make_pair(path, texture_data));
	return hr;
}

/**
* @brief �e�N�X�`���̃Z�b�g
* @param key �L�[
* @param command_list �Z�b�g����R�}���h���X�g
*/
void TextureManager::SetTexture(const std::wstring& key, 
	ComPtr<ID3D12GraphicsCommandList>& command_list)
{
	auto itr = pimpl->texture_data_map.find(key);
	if (itr == pimpl->texture_data_map.end())throw 0;

	Device::getinstance()->SetResourceBarrier(
		D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_GENERIC_READ, 
		itr->second.texture.Get(),command_list);
	
	ID3D12DescriptorHeap* ppHeaps[] = { itr->second.dh_texture.Get() };
	command_list->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	command_list->SetGraphicsRootDescriptorTable(1, 
		itr->second.dh_texture->GetGPUDescriptorHandleForHeapStart());

	Device::getinstance()->SetResourceBarrier(
		D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_COMMON, 
		itr->second.texture.Get(), command_list);
}

/**
* @brief �e�N�X�`���̕����擾
* @param key �L�[
* @param �e�N�X�`���̕�
*/
int TextureManager::GetWidth(const std::wstring& key)
{
	auto itr = pimpl->texture_data_map.find(key);
	if (itr == pimpl->texture_data_map.end())throw 0;

	return itr->second.width;
}

/**
* @brief �e�N�X�`���̍������擾
* @param key �L�[
* @param �e�N�X�`���̍���
*/
int TextureManager::GetHeight(const std::wstring& key)
{
	auto itr = pimpl->texture_data_map.find(key);
	if (itr == pimpl->texture_data_map.end())throw 0;

	return itr->second.height;
}

#pragma endregion