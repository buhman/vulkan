struct VSInput
{
  float3 Position : POSITION0;
  float3 Normal : NORMAL0;
  float3 Texture : TEXCOORD0;
};

struct VSOutput
{
  float4 Position : SV_POSITION;
  float3 Normal : NORMAL0;
  float2 Texture : TEXCOORD0;
};

struct ShaderData
{
  float4x4 Projection;
  float4x4 View;
  float4x4 Model;
  float4 lightPosition;
  uint32_t selected;
};

struct PushConstant {
  vk::BufferPointer<ShaderData> data;
};

[[vk::push_constant]]
struct PushConstant constants;

[[vk::binding(0)]] SamplerState samplers[];
[[vk::binding(0)]] Texture2D textures[];

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  VSOutput output = (VSOutput)0;
  output.Position = mul(constants.data.Get().Projection, mul(constants.data.Get().View, mul(constants.data.Get().Model, float4(input.Position.xyz, 1.0))));
  //output.Normal = mul((float3x3)constants.data.Get().Model, input.Normal);
  output.Normal = input.Normal * 0.5 + 0.5;
  output.Texture = input.Texture.xy;
  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  float3 color = textures[0].Sample(samplers[0], input.Texture).bgr;

  return float4(color, 1.0);
}

struct VSOutlineOutput
{
  float4 Position : SV_POSITION;
  float3 Normal : NORMAL0;
};

[shader("vertex")]
VSOutlineOutput VSOutlineMain(VSInput input)
{
  VSOutlineOutput output = (VSOutlineOutput)0;
  float3 position = input.Position.xyz + input.Normal.xyz * 0.01;
  output.Position = mul(constants.data.Get().Projection, mul(constants.data.Get().View, mul(constants.data.Get().Model, float4(position, 1.0))));
  output.Normal = input.Normal;
  return output;
}

[shader("pixel")]
float4 PSOutlineMain(VSOutlineOutput input) : SV_TARGET
{
  return float4(1.0, 1.0, 1.0, 1.0);
}
