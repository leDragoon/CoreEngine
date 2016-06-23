Texture2D albedoTexture : register(t0);
Texture2D roughnessTexture : register(t1);
Texture2D metalnessTexture : register(t2);
Texture2D normalTexture : register(t3);
TextureCube radianceTexture : register(t4);
TextureCube irradianceTexture : register(t5);

cbuffer perObjectPixelData : register(b1)
{
	float4x4 view;
	float4 cameraPosition;
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
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

SamplerState texSample
{
	Filter = MIN_MAP_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

float4 main(VS_OUT input) : SV_TARGET
{
	const float PI = 3.14159265f;
	float3 lDir = -normalize(lightDirection.xyz);
	float3 vDir = -normalize(cameraPosition.xyz + input.pos.xyz);
	float3 lCol = lightColor.xyz;
	float4 albedo = albedoTexture.Sample(texSample, input.texcoord);
	float roughness = max(roughnessTexture.Sample(texSample, input.texcoord).x, 0.0001);
	roughness = 0.1;
	float roughness2 = roughness * roughness;
	float metalness = metalnessTexture.Sample(texSample, input.texcoord).x;
	float ior = 1.0;
	float F0 = ((1.0f - ior) * (1.0f - ior)) / ((1.0f + ior) * (1.0f + ior));

	float3 mappedNormal = normalTexture.Sample(texSample, input.texcoord).xyz * 2.0f - 1.0f;
	float3 normal = input.normal.xyz;

	if (mappedNormal.x > 0.0f)
	{
		float3 dp1 = (ddx(input.position.xyz));
		float3 dp2 = (ddy(input.position.xyz));
		float2 duv1 = (ddx(input.texcoord));
		float2 duv2 = (ddy(input.texcoord));
		float3 dp2perp = (cross(dp2, (input.normal.xyz)));
		float3 dp1perp = (cross((input.normal.xyz), dp1));
		float3 t = normalize(dp2perp * duv1.x + dp1perp * duv2.x);
		float3 b = normalize(dp2perp * duv1.y + dp1perp * duv2.y);
		float invmax = rsqrt(max((dot(t, t)), (dot(b, b))));
		float3x3 TBN = float3x3((t * invmax), (b * invmax), (input.normal.xyz));
		normal = normalize(mul(mappedNormal, TBN));
	}

	if (lightType == 0)
	{
		lDir = normalize(lightPosition.xyz - input.pos.xyz);
	}

	float3 H = normalize(vDir + lDir);
	float NDOTL = saturate(dot(normal, lDir));
	float NDOTH = saturate(dot(normal, H));
	float LDOTH = saturate(dot(lDir, H));
	float NDOTV = (dot(normal, vDir));
	float VDOTH = saturate(dot(vDir, H));

	
	float4 specular = pow(saturate(NDOTH), 4) * 4;
	float4 diffuse = NDOTL * albedo;

	float4 finalColor = saturate(diffuse * roughness) + saturate((specular * (1.0f - roughness)));
	finalColor = NDOTL;

	return pow(abs(finalColor), 1.0);
}