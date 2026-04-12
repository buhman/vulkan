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
  column_major float4x4 Projection;
  column_major float4x4 ModelView[16];
  float4 LightPosition; // view space
};

[[vk::binding(0, 0)]] ConstantBuffer<ShaderData> data;

struct PushConstant {
  int ModelViewIndex;
};

[[vk::push_constant]]
struct PushConstant constants;

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  float4x4 modelView = data.ModelView[constants.ModelViewIndex];

  VSOutput output = (VSOutput)0;
  output.Position = mul(data.Projection, mul(modelView, float4(input.Position.xyz, 1.0))) * float4(-1, -1, 1, 1);
  output.Normal = mul((float3x3)modelView, input.Normal);
  output.Texture = input.Texture.xy * 1.0;

  float4 viewPosition = mul(modelView, float4(input.Position.xyz, 1.0));
  output.LightDirection = (data.LightPosition - viewPosition).xyz;
  output.ViewDirection = -viewPosition.xyz;

  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  //float3 color = texture.Sample(samplers[0], input.Texture).bgr;

  float3 N = normalize(input.Normal);
  float3 L = normalize(input.LightDirection);
  float3 V = normalize(input.ViewDirection);
  float3 R = reflect(-L, N);

  const float a = 16.0;
  const float specularIntensity = 0.8;
  float3 specular = pow(max(dot(R, V), 0), a) * specularIntensity;
  float3 diffuse = max(dot(N, L), 0.001);

  return float4(diffuse + specular, 1.0);
}
