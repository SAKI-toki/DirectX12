cbuffer cbTansMatrix : register(b0)
{
	float4x4 WVP;
	float4 Color;
};

Texture2D<float4> tex0 : register(t0);
SamplerState samp0 : register(s0);

struct VS_INPUT
{
	float3 Position : POSITION;
};

struct PS_INPUT
{
	float4 Position : SV_POSITION;
};


PS_INPUT vs(VS_INPUT input)
{
	PS_INPUT output;

	float4 Pos = float4(input.Position, 1.0f);
	output.Position = mul(Pos, WVP);

	return output;
}


float4 ps(PS_INPUT input) : SV_TARGET
{
	return Color;
}
