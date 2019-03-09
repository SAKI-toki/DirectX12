#pragma once
class Shader
{
	std::string key;
public:
	HRESULT LoadTexture(const std::string&, const WCHAR*);
	void SetTexture(ComPtr<ID3D12GraphicsCommandList>&);
	int GetWidth();
	int GetHeight();
	std::string GetKey()const;
};