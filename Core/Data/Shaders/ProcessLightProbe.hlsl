struct Pixel
{
	float3 color;
};

int resolution = 256;
float PI = 3.14159265;

StructuredBuffer<float3> BufferIn : register(t0);
RWStructuredBuffer<float3> BufferOut : register(u0);

float3 getPixel(int x, int y, int z)
{
	return BufferIn[(x) + (y * resolution) + (z * resolution * resolution)];
}

float3 setPixel(int x, int y, int z, float3 toSet)
{
	BufferOut[(x)+(y * resolution) + (z * resolution * resolution)] = toSet;
}

float3 importanceSampleGGX(float3 Xin, float roughness, float3 normal)
{
	float alpha = roughness * roughness;
	float phi = 2 * PI * Xin.x;
	float cosTheta = sqrt((1.0 - Xin.y) / (1.0 + (alpha * alpha - 1.0) * Xin.y));
	float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

	float3 Half;
	Half.x = sinTheta * cos(phi);
	Half.y = sinTheta * sin(phi);
	Half.z = cosTheta;

	float3 upVector = abs(normal.z) < 0.999 ? float3(0, 0, 1) : float3(1, 0, 0);
	float3 TangentX = normalize(cross(upVector, normal));
	float3 TangentY = cross(normal, TangentX);
	return TangentX * Half.x + TangentY * Half.y + normal * Half.z;
}

[numthreads(16, 16, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{

}