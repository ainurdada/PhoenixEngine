
struct PS_IN
{
    float4 Position : SV_Position;
    float2 TexCoord : TEXCOORD;
};

PS_IN VSMain(uint id : SV_VertexID)
{
    PS_IN output = (PS_IN)0;
    output.TexCoord = float2(id & 1, (id & 2) >> 1);
    output.Position = float4(output.TexCoord * float2(2, -2) + float2(-1, 1), 0, 1);
    return output;
}