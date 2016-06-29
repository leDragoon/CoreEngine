cbuffer perObjectVertexData : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 projection;
};

cbuffer perTextData : register(b3)
{
	float4 positionScale;
};

struct VS_OUT
{
	float4 pos : POSITION;
	float4 position : SV_POSITION;
	float4 tangent : TANGENT;
	float4 bitangent : BITANGENT;
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD;
	float2 texcoord2 : TEXCOORD2;
};

VS_OUT main(float4 pos : POSITION, float4 tan : TANGENT, float4 norm : NORMAL, float2 tex : TEXCOORD)
{
	VS_OUT output;
	output.pos = pos;
	output.position = mul(pos, world);
	output.tangent = tan;
	output.bitangent = tan;
	output.normal = norm;
	output.texcoord = tex;

	float tCoordX, tCoordY;
	if (tex.x == 0.0f)
	{
		tCoordX = positionScale.x / 256;
	}

	else if (tex.x == 1.0f)
	{
		tCoordX = (positionScale.x + positionScale.z) / 256;
	}

	if (tex.y == 0.0f)
	{
		tCoordY = positionScale.y / 256;
	}

	else if (tex.y == 1.0f)
	{
		tCoordY = (positionScale.y + positionScale.w) / 256;
	}
	output.texcoord2 = float2(tCoordX, tCoordY);
	return output;
}