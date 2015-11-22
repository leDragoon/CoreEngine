
struct VS_IN
{
	float3 worldPosition : POSITION;
	float3 worldNormal : NORMAL;
	float2 uvCoords : UV;
};

struct VS_OUT
{
	float4 worldPosition : POSITION;
};

VS_OUT main(VS_IN input)
{
	VS_OUT output;
	output.worldPosition = float4(input.worldPosition, 1.0f);
	return output;
}