
Texture2D albedoTexture : register(t0);

cbuffer perObjectPixelData : register(b1)
{
	float4 view;
};

cbuffer perLightData : register(b2)
{
	float4 lightPosition;
	float4 lightDirection;
	float4 lightColor;
	int lightType;
};

struct VS_OUT
{
	float4 pos : POSITION;
	float4 position : SV_POSITION;
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

SamplerState texSample2D
{
	Filter = MIN_MAP_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

float4 main(VS_OUT input) : SV_TARGET
{
	float4 lDir = lightDirection;
	float4 normal = normalize(input.normal);

	if (lightType == 0)
	{
		lDir = float4(normalize(lightPosition.xyz - input.pos.xyz), 1.0f);
	}

	float4 lambertDiffuse = (max(dot(lDir.xyz, normal.xyz), 0.0f) * pow(albedoTexture.Sample(texSample2D, input.texcoord), 2.2)) * pow(lightColor, 2.2);
	return pow(lambertDiffuse, 1.0 / 2.2);
}