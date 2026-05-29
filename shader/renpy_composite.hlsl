[[vk::binding(0, 0)]] SamplerState ClosestSampler;
[[vk::binding(1, 0)]] Texture2D Texture[];

struct PushConstant {
  float DissolveLerp;
  float TextLerp;
};

[[vk::push_constant]] PushConstant PushConstant;

struct VSInput
{
  float2 Position : POSITION0;
  float2 Texture : TEXCOORD0;
};

struct VSOutput
{
  float4 Position : SV_POSITION;
  float2 Texture : NORMAL0;
  float DissolveLerp : DissolveLerp;
  float TextLerp : TextLerp;
};

float4 mix(float4 x, float4 y, float a)
{
  return x * (1 - a) + y * a;
}

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  VSOutput output = (VSOutput)0;
  output.Position = float4(input.Position, 0, 1);
  output.Texture = input.Texture;
  output.DissolveLerp = PushConstant.DissolveLerp;
  output.TextLerp = PushConstant.TextLerp;

  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  float4 color0 = Texture[0].Sample(ClosestSampler, input.Texture);

  float4 color = float4(0, 0, 0, 0);
  if (input.DissolveLerp >= 0) {
    float4 color1 = Texture[1].Sample(ClosestSampler, input.Texture);
    float4 color01 = mix(color0, color1, input.TextLerp);

    float4 color2 = Texture[2].Sample(ClosestSampler, input.Texture);
    color = mix(color01, color2, input.DissolveLerp);
  } else {
    color = color0;
  }

  return float4(color.xyzw);
}
