cbuffer cbWindowAspect
{
	float aspect;
};

struct VS_INPUT
{
	float3 Position : POSITION;
	float2 UV		: TEXCOORD;
};

struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float2 UV		: TEXCOORD;
};

PS_INPUT vs(const VS_INPUT input)
{
	PS_INPUT output;
	float4 Pos = float4(input.Position, 1.0f);
	output.Position = Pos;
	output.UV = input.UV;
	output.UV.x = output.UV.x * aspect;
	return output;
}

float4 ps(const PS_INPUT input) : SV_TARGET
{
	float dist = distance(input.UV, float2(0.5f * aspect, 0.5f));
	return float4(0.0f,0.0f,0.0f, dist);
}