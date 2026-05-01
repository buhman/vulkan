#include "directxmath/directxmath.h"

#include "view.h"

constexpr float at_distance = 10.0;

void view::applyTransform(float delta_forward, float delta_strafe, float delta_elevation,
                          float delta_yaw, float delta_pitch)
{
  pitch = clampPitch(delta_pitch);

  forward = XMVector3Transform(forward, XMMatrixRotationZ(delta_yaw));
  normal = getNormal(); // on forward change
  direction = getDirection(); // on forward/normal/pitch change

  eye += forward * delta_forward + normal * delta_strafe + up * delta_elevation;
  at = eye + direction * at_distance;
}
