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

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  VSOutput output = (VSOutput)0;
  output.Position = mul(constants.data.Get().Projection, mul(constants.data.Get().View, mul(constants.data.Get().Model, float4(input.Position.xyz, 1.0))));
  //output.Normal = mul((float3x3)constants.data.Get().Model, input.Normal);
  output.Normal = input.Normal * 0.5 + 0.5;
  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  return float4(input.Normal, 1.0);
}
