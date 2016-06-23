Texture2D inputTexture : register(t0);

SamplerState texSample
{
	Filter = MIN_MAP_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_OUT
{
	float4 pos : POSITION;
	float4 position : SV_POSITION;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

float4 main(VS_OUT input) : SV_TARGET
{
	float2 tCoord = input.texcoord;
	float4 colour = inputTexture.Sample(texSample, tCoord);
	return colour;
}