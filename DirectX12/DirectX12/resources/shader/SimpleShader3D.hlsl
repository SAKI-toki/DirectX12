#include "constant_buffer/Light.hlsl"
#include "constant_buffer/Matrix.hlsl"

Texture2D<float4> tex0 : register(t0);
SamplerState samp0 : register(s0);

struct VS_INPUT
{
	float3 Position : POSITION;
	float3 Normal	: NORMAL;
	float2 UV		: TEXCOORD;
};

struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float4 Normal : NORMAL;
	float2 UV		: TEXCOORD;
	float4 col2 : COL2;
};

PS_INPUT vs(VS_INPUT input)
{
	PS_INPUT output;

	float4 Pos = float4(input.Position, 1.0f);
	float4 Nrm = float4(input.Normal, 1.0f);
	output.Position = mul(Pos, WVP);
	output.Normal = Nrm;
	output.UV = input.UV;
	float3 L = normalize(Light.xyz);
	float3 nor;
	nor = mul(input.Normal, (float3x3)World);
	nor = normalize(nor);
	output.col2 = saturate(dot(nor, L));
	output.col2 = output.col2 * 0.9 + 0.1;
	
	return output;
}

float4 ps(PS_INPUT input) : SV_TARGET
{
	return tex0.Sample(samp0, input.UV) * saturate(input.col2);
}