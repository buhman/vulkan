struct VSInput
{
  float3 Position : POSITION0;
  float3 Normal : NORMAL0;
  float3 Texture : TEXCOORD0;
};

struct VSSkinnedInput
{
  float3 Position : POSITION0;
  float3 Normal : NORMAL0;
  float3 Texture : TEXCOORD0;
  int4 BlendIndices : BLENDINDICES0;
  float4 BlendWeight : BLENDWEIGHT0;
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

struct Joint
{
  column_major float4x4 Transform;
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
[[vk::binding(2, 0)]] StructuredBuffer<Joint> Joints;

// set 1: constant
[[vk::binding(0, 1)]] StructuredBuffer<MaterialColorImage> MaterialColorImages;
[[vk::binding(1, 1)]] SamplerState LinearSampler;
[[vk::binding(2, 1)]] Texture2DArray ShadowTexture;
[[vk::binding(3, 1)]] Texture2D SceneTexture[];

struct PushConstant {
  int NodeIndex;
  int MaterialIndex;
};

[[vk::push_constant]] PushConstant constants;

float4 getView(float4x4 view, float4 position)
{
  return mul(view, position);
}

float4 getProjection(float4x4 projection, float4 viewPosition)
{
  return mul(projection, viewPosition) * float4(-1, -1, 1, 1);
}

float2 yf(float2 v)
{
  return float2(v.x, 1.0 - v.y);
}

float4x4 getWorld(VSSkinnedInput input)
{
  float4x4 world
    = input.BlendWeight.x * Joints[input.BlendIndices.x].Transform
    + input.BlendWeight.y * Joints[input.BlendIndices.y].Transform
    + input.BlendWeight.z * Joints[input.BlendIndices.z].Transform
    + input.BlendWeight.w * Joints[input.BlendIndices.w].Transform
    ;
  //float4x4 world = Nodes[constants.NodeIndex].World;

  return world;
}

[shader("vertex")]
VSOutput VSMain(VSSkinnedInput input)
{
  float4x4 world = getWorld(input);

  float4 worldPosition = mul(world, float4(input.Position, 1.0));
  float4 viewPosition = getView(Scene.View, worldPosition);
  float4 shadowPosition = getProjection(Scene.ShadowProjection, getView(Scene.ShadowView, worldPosition));

  VSOutput output = (VSOutput)0;
  //output.Position = shadowPosition;
  output.Position = getProjection(Scene.Projection, viewPosition);

  output.ShadowPosition = shadowPosition * float4(0.5, 0.5, 1.0, 1.0) + float4(0.5, 0.5, 0.0, 0.0);
  //output.Normal = mul((float3x3)Scene.View, mul((float3x3)Nodes[constants.NodeIndex].World, input.Normal));
  output.Normal = mul((float3x3)Scene.View, mul((float3x3)world, input.Normal));
  output.Texture = yf(input.Texture.xy);

  output.LightDirection = (Scene.LightPosition - viewPosition).xyz;
  output.ViewDirection = -viewPosition.xyz;

  return output;
}

float Shadow(float3 position, float bias)
{
  float sampledDepth = ShadowTexture.Sample(LinearSampler, float3(position.xy, 0)).x;
  float shadow = (position.z - bias) > sampledDepth ? 0.1 : 1.0;
  return shadow;
}

float ShadowPCF(float3 position, float bias)
{
  float2 dimensions;
  float elements;
  ShadowTexture.GetDimensions(dimensions.x, dimensions.y, elements);
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
    diffuseColor = SceneTexture[MCI.Image.Diffuse].Sample(LinearSampler, input.Texture).rgba;
  } else {
    diffuseColor = MCI.Color.Diffuse;
  }
  if (MCI.Image.Specular >= 0) {
    specularColor = SceneTexture[MCI.Image.Specular].Sample(LinearSampler, input.Texture).rgba;
  } else {
    specularColor = MCI.Color.Specular;
  }
  if (MCI.Image.Emission >= 0) {
    emissionColor = SceneTexture[MCI.Image.Emission].Sample(LinearSampler, input.Texture).rgba;
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
  float shadowBias = max(0.001 * (1.0 - dot(N, L)), 0.0002);

  //float shadowIntensity = Shadow(shadowPosition, shadowBias);
  float shadowIntensity = ShadowPCF(shadowPosition, shadowBias);
  return float4(diffuseSpecular * shadowIntensity + emissionColor.xyz, 1.0);
}

struct VSGeometryOutput
{
  float4 Position : SV_POSITION;
  float3 Normal : Normal;
};

[shader("vertex")]
VSGeometryOutput VSGeometryMain(VSInput input)
{
  VSGeometryOutput output = (VSGeometryOutput)0;
  output.Position = float4(input.Position, 1.0);
  output.Normal = input.Normal;
  return output;
}

struct GSGeometryOutput
{
  float4 Position : SV_POSITION;
  float3 Color : Color;
};

[shader("geometry")]
[maxvertexcount(6)]
void GSGeometryMain(triangle VSGeometryOutput input[3], inout LineStream<GSGeometryOutput> outputStream)
{
  float normalLength = 0.1;

  for (int i = 0; i < 3; i++) {
    float3 position = input[i].Position.xyz;
    float3 normal = input[i].Normal;
    float3 positionNormal = position + normal * normalLength;

    GSGeometryOutput output = (GSGeometryOutput)0;
    output.Position = getProjection(Scene.Projection, getView(Scene.View, float4(position, 1.0)));
    output.Color = float3(1, 0, 0);
    outputStream.Append(output);

    output.Position = getProjection(Scene.Projection, getView(Scene.View, float4(positionNormal, 1.0)));
    output.Color = float3(0, 1, 0);
    outputStream.Append(output);

    outputStream.RestartStrip();
  }
}

[shader("pixel")]
float4 PSGeometryMain(GSGeometryOutput input) : SV_TARGET
{
  return float4(input.Color, 1.0);
}

[shader("vertex")]
VSShadowOutput VSShadowMain(VSSkinnedInput input)
{
  float4x4 world = getWorld(input);

  float4 worldPosition = mul(world, float4(input.Position, 1.0));
  float4 viewPosition = getView(Scene.ShadowView, worldPosition);

  VSShadowOutput output = (VSShadowOutput)0;
  output.Position = getProjection(Scene.ShadowProjection, viewPosition);
  return output;
}

[shader("pixel")]
void PSShadowMain(VSShadowOutput input)
{
}
