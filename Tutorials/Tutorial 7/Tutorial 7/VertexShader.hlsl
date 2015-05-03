
cbuffer cbPerObject : register(b0) //Constant buffer for world view projection
{
	float4x4 rotation;                  // World matrix for object
	float4x4 worldViewProj; 
};


struct VS_OUTPUT //Output of the vertex shader
{
	float4 Pos : SV_POSITION;
    float4 Normal : NORMAL;
	float2 Tex : TEXCOORD0;
};

VS_OUTPUT VS( float4 pos : POSITION , float4 norm : NORMAL, float2  tex : TEXCOORD0)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;

	output.Pos = mul(pos, worldViewProj);
	output.Normal = normalize(mul(norm, rotation)); 
	output.Tex = tex; 

	return output;
}