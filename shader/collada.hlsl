struct VSInput
{
  float3 Position : POSITION0;
  float3 Normal : NORMAL0;
  float3 Texture : TEXCOORD0;
};

struct VSOutput
{
  float4 Position : SV_POSITION;
  float4 ShadowPosition : ShadowPosition;
  float3 Normal : NORMAL0;
  float2 Texture : TEXCOORD0;
  float3 LightDirection : NORMAL1;
  float3 ViewDirection : NORMAL2;
  nointerpolation int MaterialIndex : MaterialIndex;
};

struct VSShadowOutput
{
  float4 Position : SV_POSITION;
};

struct Node
{
  column_major float4x4 World;
};

struct Scene
{
  column_major float4x4 Projection;
  column_major float4x4 View;
  column_major float4x4 ShadowProjection;
  column_major float4x4 ShadowView;
  float4 LightPosition; // view space
};

struct MaterialImage {
  int Emission;
  int Ambient;
  int Diffuse;
  int Specular;
};

struct MaterialColor {
  float4 Emission;
  float4 Ambient;
  float4 Diffuse;
  float4 Specular;
};

struct MaterialColorImage
{
  MaterialColor Color;
  MaterialImage Image;
};

// set 0: per-frame
[[vk::binding(0, 0)]] ConstantBuffer<Scene> Scene;
[[vk::binding(1, 0)]] StructuredBuffer<Node> Nodes;

// set 1: constant
[[vk::binding(0, 1)]] StructuredBuffer<MaterialColorImage> MaterialColorImages;
[[vk::binding(1, 1)]] SamplerState LinearSampler;
[[vk::binding(2, 1)]] Texture2D ShadowTexture;
[[vk::binding(3, 1)]] Texture2D SceneTexture[];

struct PushConstant {
  int NodeIndex;
  int MaterialIndex;
};

[[vk::push_constant]] PushConstant constants;

float4 getView(float4x4 view, float3 position)
{
  float4x4 world = Nodes[constants.NodeIndex].World;
  return mul(view, mul(world, float4(position.xyz, 1.0)));
}

float4 getProjection(float4x4 projection, float4 viewPosition)
{
  return mul(projection, viewPosition) * float4(-1, -1, 1, 1);
}

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  float4 viewPosition = getView(Scene.View, input.Position);
  float4 shadowPosition = getProjection(Scene.ShadowProjection, getView(Scene.ShadowView, input.Position));

  VSOutput output = (VSOutput)0;
  output.Position = getProjection(Scene.Projection, viewPosition);
  output.ShadowPosition = shadowPosition * float4(0.5, 0.5, 1.0, 1.0) + float4(0.5, 0.5, 0.0, 0.0);
  output.Normal = mul((float3x3)Scene.View, mul((float3x3)Nodes[constants.NodeIndex].World, input.Normal));
  output.Texture = input.Texture.xy * 1.0;

  output.LightDirection = (Scene.LightPosition - viewPosition).xyz;
  output.ViewDirection = -viewPosition.xyz;

  return output;
}

float Shadow(float3 position, float bias)
{
  float sampledDepth = ShadowTexture.Sample(LinearSampler, position.xy).x;
  float shadow = (position.z - bias) > sampledDepth ? 0.1 : 1.0;
  return shadow;
}

float ShadowPCF(float3 position, float bias)
{
  float2 dimensions;
  ShadowTexture.GetDimensions(dimensions.x, dimensions.y);
  float2 texelSize = 1.0 / dimensions;

  float shadow = 0.0;

  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      float2 offset = texelSize * float2(x, y);
      shadow += Shadow(position + float3(offset, 0), bias);
    }
  }

  return shadow / 9.0;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  MaterialColorImage MCI = MaterialColorImages[constants.MaterialIndex];
  float4 diffuseColor;
  float4 specularColor;
  float4 emissionColor;
  if (MCI.Image.Diffuse >= 0) {
    diffuseColor = SceneTexture[MCI.Image.Diffuse].Sample(LinearSampler, input.Texture).bgra;
  } else {
    diffuseColor = MCI.Color.Diffuse;
  }
  if (MCI.Image.Specular >= 0) {
    specularColor = SceneTexture[MCI.Image.Specular].Sample(LinearSampler, input.Texture).bgra;
  } else {
    specularColor = MCI.Color.Specular;
  }
  if (MCI.Image.Emission >= 0) {
    emissionColor = SceneTexture[MCI.Image.Emission].Sample(LinearSampler, input.Texture).bgra;
  } else {
    emissionColor = MCI.Color.Emission;
  }

  float3 N = normalize(input.Normal);
  float3 L = normalize(input.LightDirection);
  float3 V = normalize(input.ViewDirection);
  float3 R = reflect(-L, N);

  const float a = 16.0;
  const float specularIntensity = 0.8;
  float3 specular = pow(max(dot(R, V), 0), a) * specularIntensity;
  float3 diffuse = max(dot(N, L), 0.001);

  float3 diffuseSpecular = diffuse * diffuseColor.xyz + specular * specularColor.xyz;

  float3 shadowPosition = input.ShadowPosition.xyz / input.ShadowPosition.w;
  float shadowBias = max(0.01 * (1.0 - dot(N, L)), 0.002);

  //float shadowIntensity = Shadow(shadowPosition, shadowBias);
  float shadowIntensity = ShadowPCF(shadowPosition, shadowBias);
  return float4(diffuseSpecular * shadowIntensity + emissionColor.xyz, 1.0);
}

[shader("vertex")]
VSShadowOutput VSShadowMain(VSInput input)
{
  float4 viewPosition = getView(Scene.ShadowView, input.Position);

  VSShadowOutput output = (VSShadowOutput)0;
  output.Position = getProjection(Scene.ShadowProjection, viewPosition);
  return output;
}

[shader("pixel")]
void PSShadowMain(VSShadowOutput input)
{
}
