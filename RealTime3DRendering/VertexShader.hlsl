struct VSOUT
{
    float3 color : Color;
    float4 pos: SV_POSITION;
};

cbuffer CBuf
{
    // col major
    matrix transformation;
};
VSOUT main(float2 pos : Position, float3 color : Color)
{
    VSOUT vso;
    vso.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f), transformation);
    vso.color = color;
    return vso;
}