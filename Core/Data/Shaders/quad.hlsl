
cbuffer perObjectVertexData : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 projection;
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

VS_OUT main(float4 pos : POSITION, float4 tan : TANGENT, float4 norm : NORMAL, float2 tex : TEXCOORD)
{
	VS_OUT output;
	output.pos = pos;
	output.position = mul(pos, world);
	output.tangent = tan;
	output.bitangent = tan;
	output.normal = norm;
	output.texcoord = tex;
	return output;
}