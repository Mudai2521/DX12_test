
SamplerState ColorSmp : register(s0);
 
Texture2D ColorMap : register(t0);


cbuffer Transform : register(b0)
{
    float4x4 World; // ���[���h�s��
    float4x4 View; // �r���[�s��
    float4x4 Proj; // ���e�s��
}

struct VSInput
{
    float4 position : POSITION;
    float3 normal : NORMAL; // �@��
    float2 uv : TEXCOORD; // UV
    float3 tangent : TANGENT; // �ڋ��
    float4 color : COLOR;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD; 
};

PSInput VSMain(VSInput input)
{
    PSInput result;

    result.position = input.position;
    result.position = mul(Proj, mul(View, mul(World, result.position)));
    result.color = input.color;
    result.uv = input.uv;

    return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
    float4 result;
    
    result = ColorMap.Sample(ColorSmp, input.uv);
    
    return result;
    //return float4(1.0f, 1.0f, 1.0f, 1.0f);
}
