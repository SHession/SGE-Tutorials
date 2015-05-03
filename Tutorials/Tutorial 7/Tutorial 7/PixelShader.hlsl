

Texture2D    tex : register( t0 );  //Texture to be drawn
SamplerState samLinear : register( s0 ); //Sample state of the texture

cbuffer cbLighting : register(b0) //Constant buffer for world view projection
{
	float4 lightDirection;
};


struct VS_OUTPUT //THe output of the vertex into the pixel shader
{
	float4 Pos : SV_POSITION;
    float4 Normal : NORMAL;
	float2 Tex : TEXCOORD0;
};


float4 PS( VS_OUTPUT input) : SV_TARGET
{

	return tex.Sample(samLinear, input.Tex) ; //sample the texture based on the uvs
}

float4 PS2( VS_OUTPUT input) : SV_TARGET
{
	float lighting =  dot( lightDirection, input.Normal );


	if(lighting < 0.2)
		lighting = 0.2;

	return tex.Sample(samLinear, input.Tex) * lighting; //sample the texture based on the uvs
}