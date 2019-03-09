cbuffer cbMatrix : register(b0)
{
	float4x4 WVP;
	float4 Color;
};

struct VS_INPUT
{
	float3 Position : POSITION;
	float3 Normal	: NORMAL;
};

struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float4 Normal	: NORMAL;
};


PS_INPUT vs(VS_INPUT input)
{
	PS_INPUT output;

	float4 Pos = float4(input.Position, 1.0f);
	float4 Nrm = float4(input.Normal, 1.0f);
	output.Position = mul(Pos, WVP);
	output.Normal = mul(Nrm, WVP);

	return output;
}


float4 ps(PS_INPUT input) : SV_TARGET
{
	return Color;
}
