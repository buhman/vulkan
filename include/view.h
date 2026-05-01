#pragma once

#include "directxmath/directxmath.h"

struct view {
  // positions
  XMVECTOR eye;
  XMVECTOR at;

  // vectors
  XMVECTOR up;
  XMVECTOR forward;
  XMVECTOR normal; // cross(forward, up)
  XMVECTOR direction; // rotationaxis(forward, pitch)

  // angles
  float pitch;

  void applyTransform(float delta_forward, float delta_strafe, float delta_elevation,
                      float delta_yaw, float delta_pitch);

  inline XMMATRIX getView()
  {
    return XMMatrixLookAtLH(eye, at, up);
  }

  inline float clampPitch(float delta_pitch)
  {
    float newPitch = pitch + delta_pitch;
    if (newPitch > 1.57f) newPitch = 1.57f;
    if (newPitch < -1.57f) newPitch = -1.57f;
    return newPitch;
  }

  inline XMVECTOR getNormal()
  {
    return XMVector3Normalize(XMVector3Cross(forward, up));
  }

  inline XMVECTOR getDirection()
  {
    XMMATRIX mrn = XMMatrixRotationAxis(normal, pitch);
    return XMVector3Transform(forward, mrn);
  }
};
