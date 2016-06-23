TextureCube skyCubeMap : register(t4);

cbuffer perObjectPixelData : register(b1)
{
	float4x4 view;
	float4 cameraPosition;
	float4 viewDirection;
};

struct VS_OUT
{
	float4 pos : POSITION;
	float4 position : SV_POSITION;
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

SamplerState texSampleCUBE
{
	Filter = MIN_MAP_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

float4 main(VS_OUT input) : SV_TARGET
{
	float3 vDir = normalize(cameraPosition.xyz - input.pos.xyz);
	return skyCubeMap.Sample(texSampleCUBE, vDir);
}