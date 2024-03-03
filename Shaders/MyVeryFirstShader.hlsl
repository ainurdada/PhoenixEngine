struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

struct TransformData
{
    float4x4 transformMatrix;
};

cbuffer TransformBuffer : register(b0)
{
    float4x4 transformMatrix;
}

PS_IN VSMain( VS_IN input)
{
	PS_IN output = (PS_IN)0;
	
    output.pos = mul(input.pos, transformMatrix);
    output.pos.x = output.pos.x / output.pos.w;
    output.pos.y = output.pos.y / output.pos.w;
    output.pos.z = output.pos.z / output.pos.w;
	output.col = input.col;
	
	return output;
}

float4 PSMain( PS_IN input ) : SV_Target
{
	float4 col = input.col;
#ifdef TEST
	if (input.pos.x > 400) col = TCOLOR;
#endif
	return col;
}