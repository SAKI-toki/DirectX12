cbuffer cbMatrix : register(b0)
{
	float4x4 WVP;
	float4x4 World;
	float4 Light;
};

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
	float2 UV		: TEXCOORD;
	float4 col2 : COL2;
};


PS_INPUT vs(VS_INPUT input)
{
	PS_INPUT output;

	float4 Pos = float4(input.Position, 1.0f);
	float4 Nrm = float4(input.Normal, 1.0f);
	output.Position = mul(Pos, WVP);
	output.UV = input.UV;
	float3 L = normalize(Light.xyz);
	float3 nor;
	nor = mul(input.Normal, (float3x3)World);
	nor = normalize(nor);
	output.col2 = dot(nor, L);
	output.col2 = output.col2 * 0.5 + 0.5;

	return output;
}


float4 ps(PS_INPUT input) : SV_TARGET
{
	return tex0.Sample(samp0, input.UV) * saturate(input.col2);
}
