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

struct Node
{
  column_major float4x4 ModelView;
  //int MaterialIndex;
};

struct Scene
{
  column_major float4x4 Projection;
  float4 LightPosition; // view space
};

struct MaterialColor
{
  float4 Emission;
  float4 Ambient;
  float4 Diffuse;
  float4 Specular;
};

/*
struct Nodes {
  Node n[16];
};

struct MaterialColors {
  MaterialColor mc[16];
};
*/

struct SceneNodes {
  Scene Scene;
};

struct Nodes {
  Node n[11];
};

// set 0: per-frame
[[vk::binding(0, 0)]] ConstantBuffer<Scene> Scene;
[[vk::binding(1, 0)]] ConstantBuffer<Nodes> Nodes;
//[[vk::binding(1, 0)]] cbuffer asdf { Nodes Nodes; }

// set 1: constant
//[[vk::binding(0, 1)]] ConstantBuffer<MaterialColor[]> MaterialColors;

struct PushConstant {
  int NodeIndex;
};

[[vk::push_constant]]
struct PushConstant constants;

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  //[constants.NodeIndex]
  float4x4 modelView = Nodes.n[constants.NodeIndex].ModelView;

  VSOutput output = (VSOutput)0;
  output.Position = mul(Scene.Projection, mul(modelView, float4(input.Position.xyz, 1.0))) * float4(-1, -1, 1, 1);
  output.Normal = mul((float3x3)modelView, input.Normal);
  output.Texture = input.Texture.xy * 1.0;

  float4 viewPosition = mul(modelView, float4(input.Position.xyz, 1.0));
  output.LightDirection = (Scene.LightPosition - viewPosition).xyz;
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
