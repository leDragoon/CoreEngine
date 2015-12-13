
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
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

VS_OUT main(float4 pos : POSITION, float4 norm : NORMAL, float2 tex : TEXCOORD)
{
	VS_OUT output;
	output.pos = mul(pos, world);
	output.position = mul(pos, mul(mul(world, view), projection));
	output.normal = mul(norm, world);
	output.texcoord = tex;
	return output;
}