
cbuffer perObjectData
{
	float4x4 worldViewProjection;
};

struct VS_OUT
{
	float4 outPos : SV_POSITION;
};

VS_OUT main(float4 pos : POSITION)
{
	VS_OUT output;
	output.outPos = mul(pos, worldViewProjection);
	return output;
}