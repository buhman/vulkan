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
  float3 LightDirection : NORMAL1;
  float3 ViewDirection : NORMAL2;
};

struct ShaderData
{
  float4x4 Transform;
  float4x4 ModelView;
  float4 LightPosition; // view space
  uint32_t Selected;
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
  output.Position = mul(constants.data.Get().Transform, float4(input.Position.xyz, 1.0));
  output.Normal = mul((float3x3)constants.data.Get().ModelView, input.Normal);
  output.Texture = input.Texture.xy;

  float4 viewPosition = mul(constants.data.Get().ModelView, float4(input.Position.xyz, 1.0));
  output.LightDirection = (constants.data.Get().LightPosition - viewPosition).xyz;
  output.ViewDirection = -viewPosition.xyz;

  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  float3 color = textures[0].Sample(samplers[0], input.Texture).bgr;

  float3 N = normalize(input.Normal);
  float3 L = normalize(input.LightDirection);
  float3 V = normalize(input.ViewDirection);
  float3 R = reflect(-L, N);

  const float a = 16.0;
  const float specularIntensity = 0.8;
  float3 specular = pow(max(dot(R, V), 0), a) * specularIntensity;
  float3 diffuse = max(dot(N, L), 0.001);

  return float4(diffuse * color + specular, 1.0);
}

struct VSOutlineOutput
{
  float4 Position : SV_POSITION;
};

[shader("vertex")]
VSOutlineOutput VSOutlineMain(VSInput input)
{
  VSOutlineOutput output = (VSOutlineOutput)0;
  float3 position = input.Position.xyz + input.Normal.xyz * 0.01;
  output.Position = mul(constants.data.Get().Transform, float4(position, 1.0));
  return output;
}

[shader("pixel")]
float4 PSOutlineMain(VSOutlineOutput input) : SV_TARGET
{
  return float4(1.0, 1.0, 1.0, 1.0);
}
