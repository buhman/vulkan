#include "collada/types.h"

#include "scenes/shadow_test/shadow_test.h"

namespace shadow_test {

using namespace collada::types;

camera const camera_camera001_camera = {
  .xfov = 45.0f,
  .yfov = 0.0f,
  .znear = 1.0f,
  .zfar = 1000.0f,
  .aspect_ratio = 0.0f,
};

light const light_environmentambientlight = {
  .type = light_type::AMBIENT,
  .color = {0.0f, 0.0f, 0.0f},
};

light const light_directlight_light = {
  .type = light_type::DIRECTIONAL,
  .color = {1.0f, 1.0f, 1.0f},
};

float const array_node_camera001_target_translation_x_input_array[] = {
  0.0,
  0.3333333,
  0.6666667,
  1.0,
  1.3,
  1.666667,
  2.0,
  2.333333,
  2.666667,
  2.966667,
  3.333333,
};

float const array_node_camera001_target_translation_x_output_array[] = {
  18.7608,
  19.90498,
  81.34351,
  41.12402,
  79.84364,
  10.4304,
  16.14357,
  5.871902,
  -84.83231,
  64.5824,
  18.7608,
};

float const array_node_camera001_target_translation_x_intangent_array[] = {
  -0.3329306, 18.7608,
  0.2223333, 18.76195,
  0.5556667, 81.34351,
  0.889, 41.12402,
  1.2001, 79.84364,
  1.544567, 10.4304,
  1.889, 16.14357,
  2.222333, 16.13329,
  2.555667, -84.83231,
  2.866767, 64.5824,
  3.211233, 18.7608,
};

float const array_node_camera001_target_translation_x_outtangent_array[] = {
  0.111, 18.7608,
  0.4443333, 21.04802,
  0.7776667, 81.34351,
  1.0999, 41.12402,
  1.4221, 79.84364,
  1.777667, 10.4304,
  2.111, 16.14357,
  2.444333, -4.389489,
  2.766567, -84.83231,
  3.088767, 64.5824,
  3.666264, 18.7608,
};

enum interpolation const array_node_camera001_target_translation_x_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_camera001_target_translation_x_sampler = {
  // node_camera001_target_translation_x_input
  .input = {
    .float_array = array_node_camera001_target_translation_x_input_array,
    .count = 11,
    .stride = 1,
  },
  // node_camera001_target_translation_x_output
  .output = {
    .float_array = array_node_camera001_target_translation_x_output_array,
    .count = 11,
    .stride = 1,
  },
  // node_camera001_target_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_camera001_target_translation_x_intangent_array,
    .count = 11,
    .stride = 2,
  },
  // node_camera001_target_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_camera001_target_translation_x_outtangent_array,
    .count = 11,
    .stride = 2,
  },
  // node_camera001_target_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_camera001_target_translation_x_interpolation_array,
    .count = 11,
    .stride = 1,
  },
};

float const array_node_camera001_target_translation_y_input_array[] = {
  0.0,
  0.3333333,
  0.6666667,
  1.0,
  1.3,
  1.666667,
  2.0,
  2.333333,
  2.666667,
  2.966667,
  3.333333,
};

float const array_node_camera001_target_translation_y_output_array[] = {
  -49.36783,
  1.856133,
  -27.52136,
  67.89663,
  80.23181,
  -11.20603,
  119.8653,
  -32.92146,
  39.94514,
  83.55756,
  -49.36783,
};

float const array_node_camera001_target_translation_y_intangent_array[] = {
  -0.3329306, -49.36783,
  0.2223333, 1.856133,
  0.5556667, -27.52136,
  0.889, 54.20458,
  1.2001, 80.23181,
  1.544567, -11.20603,
  1.889, 119.8653,
  2.222333, -32.92146,
  2.555667, 19.53066,
  2.866767, 83.55756,
  3.211233, -49.36783,
};

float const array_node_camera001_target_translation_y_outtangent_array[] = {
  0.111, -49.36783,
  0.4443333, 1.856133,
  0.7776667, -27.52136,
  1.0999, 80.21947,
  1.4221, 80.23181,
  1.777667, -11.20603,
  2.111, 119.8653,
  2.444333, -32.92146,
  2.766567, 58.31817,
  3.088767, 83.55756,
  3.666264, -49.36783,
};

enum interpolation const array_node_camera001_target_translation_y_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_camera001_target_translation_y_sampler = {
  // node_camera001_target_translation_y_input
  .input = {
    .float_array = array_node_camera001_target_translation_y_input_array,
    .count = 11,
    .stride = 1,
  },
  // node_camera001_target_translation_y_output
  .output = {
    .float_array = array_node_camera001_target_translation_y_output_array,
    .count = 11,
    .stride = 1,
  },
  // node_camera001_target_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_camera001_target_translation_y_intangent_array,
    .count = 11,
    .stride = 2,
  },
  // node_camera001_target_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_camera001_target_translation_y_outtangent_array,
    .count = 11,
    .stride = 2,
  },
  // node_camera001_target_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_camera001_target_translation_y_interpolation_array,
    .count = 11,
    .stride = 1,
  },
};

float const array_node_camera001_target_translation_z_input_array[] = {
  0.0,
  0.3333333,
  0.6666667,
  1.0,
  1.3,
  2.0,
  2.333333,
  2.666667,
  2.966667,
  3.333333,
};

float const array_node_camera001_target_translation_z_output_array[] = {
  43.74428,
  43.74428,
  65.51973,
  13.07175,
  43.74428,
  43.74428,
  43.74428,
  43.74428,
  43.74428,
  43.74428,
};

float const array_node_camera001_target_translation_z_intangent_array[] = {
  -0.3329306, 43.74428,
  0.2223333, 43.74428,
  0.5556667, 65.51973,
  0.889, 13.07175,
  1.2001, 43.74428,
  1.7669, 43.74428,
  2.222333, 43.74428,
  2.555667, 43.74428,
  2.866767, 43.74428,
  3.211233, 43.74428,
};

float const array_node_camera001_target_translation_z_outtangent_array[] = {
  0.111, 43.74428,
  0.4443333, 43.74428,
  0.7776667, 65.51973,
  1.0999, 13.07175,
  1.5331, 43.74428,
  2.111, 43.74428,
  2.444333, 43.74428,
  2.766567, 43.74428,
  3.088767, 43.74428,
  3.666264, 43.74428,
};

enum interpolation const array_node_camera001_target_translation_z_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_camera001_target_translation_z_sampler = {
  // node_camera001_target_translation_z_input
  .input = {
    .float_array = array_node_camera001_target_translation_z_input_array,
    .count = 10,
    .stride = 1,
  },
  // node_camera001_target_translation_z_output
  .output = {
    .float_array = array_node_camera001_target_translation_z_output_array,
    .count = 10,
    .stride = 1,
  },
  // node_camera001_target_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_camera001_target_translation_z_intangent_array,
    .count = 10,
    .stride = 2,
  },
  // node_camera001_target_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_camera001_target_translation_z_outtangent_array,
    .count = 10,
    .stride = 2,
  },
  // node_camera001_target_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_camera001_target_translation_z_interpolation_array,
    .count = 10,
    .stride = 1,
  },
};

float const array_node_torus_knot_rotationz_angle_input_array[] = {
  0.0,
  1.666667,
  3.333333,
};

float const array_node_torus_knot_rotationz_angle_output_array[] = {
  0.0,
  -180.0,
  -360.0,
};

float const array_node_torus_knot_rotationz_angle_intangent_array[] = {
  -0.3332639, -120.0,
  1.111111, -120.0,
  2.777778, -300.0,
};

float const array_node_torus_knot_rotationz_angle_outtangent_array[] = {
  0.5555556, -60.0,
  2.222222, -240.0,
  3.666597, -240.0,
};

enum interpolation const array_node_torus_knot_rotationz_angle_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_torus_knot_rotationz_angle_sampler = {
  // node_torus_knot_rotationz_angle_input
  .input = {
    .float_array = array_node_torus_knot_rotationz_angle_input_array,
    .count = 3,
    .stride = 1,
  },
  // node_torus_knot_rotationz_angle_output
  .output = {
    .float_array = array_node_torus_knot_rotationz_angle_output_array,
    .count = 3,
    .stride = 1,
  },
  // node_torus_knot_rotationz_angle_intangent
  .in_tangent = {
    .float_array = array_node_torus_knot_rotationz_angle_intangent_array,
    .count = 3,
    .stride = 2,
  },
  // node_torus_knot_rotationz_angle_outtangent
  .out_tangent = {
    .float_array = array_node_torus_knot_rotationz_angle_outtangent_array,
    .count = 3,
    .stride = 2,
  },
  // node_torus_knot_rotationz_angle_interpolation
  .interpolation = {
    .interpolation_array = array_node_torus_knot_rotationz_angle_interpolation_array,
    .count = 3,
    .stride = 1,
  },
};

float const array_node_lighthelper_translation_x_input_array[] = {
  0.0,
  0.2333333,
  0.4333333,
  0.6333333,
  0.8333334,
  1.066667,
  1.266667,
  1.466667,
  1.666667,
  1.9,
  2.1,
  2.3,
  2.5,
  2.733333,
  2.933333,
  3.133333,
  3.333333,
};

float const array_node_lighthelper_translation_x_output_array[] = {
  -42.21109,
  -42.21108,
  64.55054,
  77.47449,
  -42.21109,
  -42.21108,
  64.55054,
  77.47449,
  -42.21109,
  -42.21108,
  64.55054,
  77.47449,
  -42.21109,
  -42.21108,
  64.55054,
  77.47449,
  -42.21109,
};

float const array_node_lighthelper_translation_x_intangent_array[] = {
  -0.3329306, -42.21109,
  0.1556333, -42.21109,
  0.3667333, 51.6395,
  0.5667334, 77.47449,
  0.7667333, -42.21109,
  0.9889667, -42.21109,
  1.200067, 51.6395,
  1.400067, 77.47449,
  1.600067, -42.21109,
  1.8223, -42.21109,
  2.0334, 51.6395,
  2.2334, 77.47449,
  2.4334, -42.21109,
  2.655633, -42.21109,
  2.866733, 51.6395,
  3.066733, 77.47449,
  3.266733, -42.21109,
};

float const array_node_lighthelper_translation_x_outtangent_array[] = {
  0.0777, -42.21109,
  0.2999333, -42.21107,
  0.4999333, 77.46157,
  0.6999334, 77.47449,
  0.9110333, -42.21109,
  1.133267, -42.21107,
  1.333267, 77.46157,
  1.533267, 77.47449,
  1.744367, -42.21109,
  1.9666, -42.21107,
  2.1666, 77.46157,
  2.3666, 77.47449,
  2.5777, -42.21109,
  2.799933, -42.21107,
  2.999933, 77.46157,
  3.199933, 77.47449,
  3.666264, -42.21109,
};

enum interpolation const array_node_lighthelper_translation_x_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_lighthelper_translation_x_sampler = {
  // node_lighthelper_translation_x_input
  .input = {
    .float_array = array_node_lighthelper_translation_x_input_array,
    .count = 17,
    .stride = 1,
  },
  // node_lighthelper_translation_x_output
  .output = {
    .float_array = array_node_lighthelper_translation_x_output_array,
    .count = 17,
    .stride = 1,
  },
  // node_lighthelper_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_lighthelper_translation_x_intangent_array,
    .count = 17,
    .stride = 2,
  },
  // node_lighthelper_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_lighthelper_translation_x_outtangent_array,
    .count = 17,
    .stride = 2,
  },
  // node_lighthelper_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_lighthelper_translation_x_interpolation_array,
    .count = 17,
    .stride = 1,
  },
};

float const array_node_lighthelper_translation_y_input_array[] = {
  0.0,
  0.2333333,
  0.4333333,
  0.6333333,
  0.8333334,
  1.066667,
  1.266667,
  1.466667,
  1.666667,
  1.9,
  2.1,
  2.3,
  2.5,
  2.733333,
  2.933333,
  3.133333,
  3.333333,
};

float const array_node_lighthelper_translation_y_output_array[] = {
  -40.46347,
  92.09061,
  92.09061,
  -70.41342,
  -40.46347,
  92.09061,
  92.09061,
  -70.41342,
  -40.46347,
  92.09061,
  92.09061,
  -70.41342,
  -40.46347,
  92.09061,
  92.09061,
  -70.41342,
  -40.46347,
};

float const array_node_lighthelper_translation_y_intangent_array[] = {
  -0.3329306, -40.46347,
  0.1556333, 92.09061,
  0.3667333, 92.09061,
  0.5667334, -70.41342,
  0.7667333, -65.43909,
  0.9889667, 92.09061,
  1.200067, 92.09061,
  1.400067, -70.41342,
  1.600067, -65.43909,
  1.8223, 92.09061,
  2.0334, 92.09061,
  2.2334, -70.41342,
  2.4334, -65.43909,
  2.655633, 92.09061,
  2.866733, 92.09061,
  3.066733, -70.41342,
  3.266733, -40.46347,
};

float const array_node_lighthelper_translation_y_outtangent_array[] = {
  0.0777, -40.46347,
  0.2999333, 92.09061,
  0.4999333, 92.09061,
  0.6999334, -70.41342,
  0.9110333, -11.32525,
  1.133267, 92.09061,
  1.333267, 92.09061,
  1.533267, -70.41342,
  1.744367, -11.32525,
  1.9666, 92.09061,
  2.1666, 92.09061,
  2.3666, -70.41342,
  2.5777, -11.32525,
  2.799933, 92.09061,
  2.999933, 92.09061,
  3.199933, -70.41342,
  3.666264, -40.46347,
};

enum interpolation const array_node_lighthelper_translation_y_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_lighthelper_translation_y_sampler = {
  // node_lighthelper_translation_y_input
  .input = {
    .float_array = array_node_lighthelper_translation_y_input_array,
    .count = 17,
    .stride = 1,
  },
  // node_lighthelper_translation_y_output
  .output = {
    .float_array = array_node_lighthelper_translation_y_output_array,
    .count = 17,
    .stride = 1,
  },
  // node_lighthelper_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_lighthelper_translation_y_intangent_array,
    .count = 17,
    .stride = 2,
  },
  // node_lighthelper_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_lighthelper_translation_y_outtangent_array,
    .count = 17,
    .stride = 2,
  },
  // node_lighthelper_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_lighthelper_translation_y_interpolation_array,
    .count = 17,
    .stride = 1,
  },
};

float const array_node_lighthelper_translation_z_input_array[] = {
  0.0,
  0.2333333,
  0.4333333,
  0.6333333,
  0.8333334,
  1.066667,
  1.266667,
  1.466667,
  1.666667,
  1.9,
  2.1,
  2.3,
  2.5,
  2.733333,
  2.933333,
  3.133333,
  3.333333,
};

float const array_node_lighthelper_translation_z_output_array[] = {
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
  150.0,
};

float const array_node_lighthelper_translation_z_intangent_array[] = {
  -0.3329306, 150.0,
  0.1556333, 150.0,
  0.3667333, 150.0,
  0.5667334, 150.0,
  0.7667333, 150.0,
  0.9889667, 150.0,
  1.200067, 150.0,
  1.400067, 150.0,
  1.600067, 150.0,
  1.8223, 150.0,
  2.0334, 150.0,
  2.2334, 150.0,
  2.4334, 150.0,
  2.655633, 150.0,
  2.866733, 150.0,
  3.066733, 150.0,
  3.266733, 150.0,
};

float const array_node_lighthelper_translation_z_outtangent_array[] = {
  0.0777, 150.0,
  0.2999333, 150.0,
  0.4999333, 150.0,
  0.6999334, 150.0,
  0.9110333, 150.0,
  1.133267, 150.0,
  1.333267, 150.0,
  1.533267, 150.0,
  1.744367, 150.0,
  1.9666, 150.0,
  2.1666, 150.0,
  2.3666, 150.0,
  2.5777, 150.0,
  2.799933, 150.0,
  2.999933, 150.0,
  3.199933, 150.0,
  3.666264, 150.0,
};

enum interpolation const array_node_lighthelper_translation_z_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_lighthelper_translation_z_sampler = {
  // node_lighthelper_translation_z_input
  .input = {
    .float_array = array_node_lighthelper_translation_z_input_array,
    .count = 17,
    .stride = 1,
  },
  // node_lighthelper_translation_z_output
  .output = {
    .float_array = array_node_lighthelper_translation_z_output_array,
    .count = 17,
    .stride = 1,
  },
  // node_lighthelper_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_lighthelper_translation_z_intangent_array,
    .count = 17,
    .stride = 2,
  },
  // node_lighthelper_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_lighthelper_translation_z_outtangent_array,
    .count = 17,
    .stride = 2,
  },
  // node_lighthelper_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_lighthelper_translation_z_interpolation_array,
    .count = 17,
    .stride = 1,
  },
};

float const array_node_directlight_matrix_input_array[] = {
  0.0,
  0.03333333,
  0.06666667,
  0.1,
  0.1333333,
  0.1666667,
  0.2,
  0.2333333,
  0.2666667,
  0.3,
  0.3333333,
  0.3666667,
  0.4,
  0.4333333,
  0.4666667,
  0.5,
  0.5333333,
  0.5666667,
  0.6,
  0.6333333,
  0.6666667,
  0.7,
  0.7333333,
  0.7666667,
  0.8,
  0.8333333,
  0.8666667,
  0.9,
  0.9333333,
  0.9666667,
  1.0,
  1.033333,
  1.066667,
  1.1,
  1.133333,
  1.166667,
  1.2,
  1.233333,
  1.266667,
  1.3,
  1.333333,
  1.366667,
  1.4,
  1.433333,
  1.466667,
  1.5,
  1.533333,
  1.566667,
  1.6,
  1.633333,
  1.666667,
  1.7,
  1.733333,
  1.766667,
  1.8,
  1.833333,
  1.866667,
  1.9,
  1.933333,
  1.966667,
  2.0,
  2.033333,
  2.066667,
  2.1,
  2.133333,
  2.166667,
  2.2,
  2.233333,
  2.266667,
  2.3,
  2.333333,
  2.366667,
  2.4,
  2.433333,
  2.466667,
  2.5,
  2.533333,
  2.566667,
  2.6,
  2.633333,
  2.666667,
  2.7,
  2.733333,
  2.766667,
  2.8,
  2.833333,
  2.866667,
  2.9,
  2.933333,
  2.966667,
  3.0,
  3.033333,
  3.066667,
  3.1,
  3.133333,
  3.166667,
  3.2,
  3.233333,
  3.266667,
  3.3,
  3.333333,
};

float const array_node_directlight_matrix_output_array[] = {
  0.692005, 0.6702266, -0.2681891, -4.146301, -0.7218927, 0.6424779, -0.2570856, -3.974632, 0.0, 0.3715083, 0.9284297, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6247931, 0.7322824, -0.270917, -4.146301, -0.7807903, 0.5859768, -0.2167894, -3.974632, 0.0, 0.3469779, 0.9378733, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.3647357, 0.8892985, -0.2758914, -4.146301, -0.9311111, 0.3483569, -0.1080724, -3.974632, 0.0, 0.2963034, 0.9550939, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.1645458, 0.9466118, -0.2772199, -4.146301, -0.9863694, -0.1579135, 0.04624569, -3.974632, 0.0, 0.2810508, 0.9596929, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.6127588, 0.7422394, -0.2713068, -4.146301, -0.79027, -0.5755168, 0.2103655, -3.974632, 0.0, 0.3433089, 0.9392225, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8001267, 0.5404293, -0.2602567, -4.146301, -0.5998311, -0.7208894, 0.3471616, -3.974632, 0.0, 0.4338833, 0.9009691, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.867311, 0.4305242, -0.249841, -4.146301, -0.4977666, -0.7501474, 0.4353243, -3.974632, 0.0, 0.5019241, 0.8649117, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8849987, 0.3956348, -0.2454594, -4.146301, -0.4655935, -0.7520216, 0.4665685, -3.974632, 0.0, 0.5271969, 0.8497432, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9131027, 0.3494211, -0.2101151, -4.146301, -0.4077296, -0.7825219, 0.4705488, -3.974632, 0.0, 0.5153295, 0.8569921, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9713711, 0.206814, -0.1169022, -4.146301, -0.2375672, -0.8456268, 0.4779928, -3.974632, 0.0, 0.4920805, 0.8705497, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.999695, -0.02164769, 0.01188969, -4.146301, 0.02469789, -0.8762305, 0.4812588, -3.974632, 0.0, 0.4814056, 0.8764979, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9561786, -0.2539004, 0.1457982, -4.146301, 0.2927841, -0.8291916, 0.4761499, -3.974632, 0.0, 0.4979717, 0.8671933, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.878125, -0.4056587, 0.2536485, -4.146301, 0.4784314, -0.7445562, 0.4655528, -3.974632, 0.0, 0.530167, 0.8478932, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8248081, -0.470663, 0.3133177, -4.146301, 0.5654128, -0.6865897, 0.4570589, -3.974632, 0.0, 0.5541397, 0.8324236, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.7561108, -0.5544743, 0.3476417, -4.146301, 0.6544436, -0.6406113, 0.4016475, -3.974632, 0.0, 0.5312018, 0.8472453, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.5518118, -0.7401292, 0.3843339, -4.146301, 0.8339687, -0.489721, 0.2543021, -3.974632, 0.0, 0.4608493, 0.8874784, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.09527927, -0.9081463, 0.4076668, -4.146301, 0.9954506, -0.08692294, 0.0390197, -3.974632, 0.0, 0.4095299, 0.9122967, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.4048784, -0.8189967, 0.4065929, -4.146301, 0.9143705, 0.3626474, -0.1800372, -3.974634, 0.0, 0.4446697, 0.8956946, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6480864, -0.6531851, 0.3915777, -4.146301, 0.7615668, 0.5558546, -0.3332291, -3.974632, 0.0, 0.5141739, 0.857686, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7121619, -0.5883649, 0.382952, -4.146301, 0.7020153, 0.5968688, -0.388487, -3.974632, 0.0, 0.5455038, 0.8381084, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7536112, -0.5608854, 0.3427503, -4.146301, 0.6573205, 0.6430493, -0.3929597, -3.974632, 0.0, 0.5214356, 0.8532906, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8627668, -0.4483393, 0.2337206, -4.146301, 0.5056021, 0.7650527, -0.3988243, -3.974632, 0.0, 0.462262, 0.8867434, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9813205, -0.1762961, 0.07700508, -4.146301, 0.1923801, 0.8992769, -0.392799, -3.974632, 0.0, 0.400276, 0.9163947, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9719243, 0.2180167, -0.08849775, -4.146301, -0.2352938, 0.9005584, -0.3655564, -3.974632, 0.0, 0.3761161, 0.9265726, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8278828, 0.5177841, -0.215661, -4.146301, -0.5609012, 0.7642427, -0.3183129, -3.974632, 0.0, 0.3844903, 0.923129, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.692005, 0.6702266, -0.2681891, -4.146301, -0.7218927, 0.6424779, -0.2570856, -3.974632, 0.0, 0.3715083, 0.9284297, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.515815, 0.8117951, -0.273722, -4.146301, -0.8567, 0.4887779, -0.1648067, -3.974632, 0.0, 0.3195074, 0.9475838, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.1157832, 0.9537606, -0.2773717, -4.146301, -0.9932745, 0.1111772, -0.03233242, -3.974632, 0.0, 0.2792498, 0.9602185, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.3957773, 0.8760313, -0.275553, -4.146301, -0.9183465, -0.3775408, 0.1187543, -3.974632, 0.0, 0.3000534, 0.9539224, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.6975451, 0.6645705, -0.267912, -4.146301, -0.7165409, -0.6469525, 0.2608096, -3.974632, 0.0, 0.3738964, 0.9274705, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8221068, 0.5077216, -0.2576031, -4.146301, -0.5693334, -0.7331404, 0.371974, -3.974632, 0.0, 0.4524643, 0.8917825, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8712977, 0.4229292, -0.2489402, -4.146301, -0.4907549, -0.7508783, 0.4419743, -3.974632, 0.0, 0.5072599, 0.8617932, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8849987, 0.3956348, -0.2454594, -4.146301, -0.4655935, -0.7520216, 0.4665685, -3.974632, 0.0, 0.5271969, 0.8497432, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9131027, 0.3494211, -0.2101151, -4.146301, -0.4077296, -0.7825219, 0.4705488, -3.974632, 0.0, 0.5153295, 0.8569921, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9713711, 0.206814, -0.1169022, -4.146301, -0.2375672, -0.8456268, 0.4779928, -3.974632, 0.0, 0.4920805, 0.8705497, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.999695, -0.02164769, 0.01188969, -4.146301, 0.02469789, -0.8762305, 0.4812588, -3.974632, 0.0, 0.4814056, 0.8764979, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9561786, -0.2539004, 0.1457982, -4.146301, 0.2927841, -0.8291916, 0.4761499, -3.974632, 0.0, 0.4979717, 0.8671933, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.878125, -0.4056587, 0.2536485, -4.146301, 0.4784314, -0.7445562, 0.4655528, -3.974632, 0.0, 0.530167, 0.8478932, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8248081, -0.470663, 0.3133177, -4.146301, 0.5654128, -0.6865897, 0.4570589, -3.974632, 0.0, 0.5541397, 0.8324236, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.7561108, -0.5544743, 0.3476417, -4.146301, 0.6544436, -0.6406113, 0.4016475, -3.974632, 0.0, 0.5312018, 0.8472453, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.5518118, -0.7401292, 0.3843339, -4.146301, 0.8339687, -0.489721, 0.2543021, -3.974632, 0.0, 0.4608493, 0.8874784, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.09527927, -0.9081463, 0.4076668, -4.146301, 0.9954506, -0.08692294, 0.0390197, -3.974632, 0.0, 0.4095299, 0.9122967, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.4048784, -0.8189967, 0.4065929, -4.146301, 0.9143705, 0.3626474, -0.1800372, -3.974634, 0.0, 0.4446697, 0.8956946, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6480864, -0.6531851, 0.3915777, -4.146301, 0.7615668, 0.5558546, -0.3332291, -3.974632, 0.0, 0.5141739, 0.857686, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7121619, -0.5883649, 0.382952, -4.146301, 0.7020153, 0.5968688, -0.388487, -3.974632, 0.0, 0.5455038, 0.8381084, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7536112, -0.5608854, 0.3427503, -4.146301, 0.6573205, 0.6430493, -0.3929597, -3.974632, 0.0, 0.5214356, 0.8532906, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8627668, -0.4483393, 0.2337206, -4.146301, 0.5056021, 0.7650527, -0.3988243, -3.974632, 0.0, 0.462262, 0.8867434, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9813205, -0.1762961, 0.07700508, -4.146301, 0.1923801, 0.8992769, -0.392799, -3.974632, 0.0, 0.400276, 0.9163947, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9719243, 0.2180167, -0.08849775, -4.146301, -0.2352938, 0.9005584, -0.3655564, -3.974632, 0.0, 0.3761161, 0.9265726, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8278828, 0.5177841, -0.215661, -4.146301, -0.5609012, 0.7642427, -0.3183129, -3.974632, 0.0, 0.3844903, 0.923129, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.692005, 0.6702266, -0.2681891, -4.146301, -0.7218927, 0.6424779, -0.2570856, -3.974632, 0.0, 0.3715083, 0.9284297, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.5158147, 0.8117952, -0.273722, -4.146301, -0.8567002, 0.4887776, -0.1648066, -3.974632, 0.0, 0.3195074, 0.9475838, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.1157826, 0.9537606, -0.2773717, -4.146301, -0.9932746, 0.1111766, -0.03233224, -3.974632, 0.0, 0.2792497, 0.9602185, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.3957779, 0.8760311, -0.275553, -4.146301, -0.9183463, -0.3775414, 0.1187545, -3.974632, 0.0, 0.3000535, 0.9539224, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.6975454, 0.6645703, -0.267912, -4.146301, -0.7165406, -0.6469527, 0.2608097, -3.974632, 0.0, 0.3738964, 0.9274705, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8221068, 0.5077215, -0.2576031, -4.146301, -0.5693333, -0.7331404, 0.3719741, -3.974632, 0.0, 0.4524644, 0.8917825, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8712977, 0.4229292, -0.2489402, -4.146301, -0.4907549, -0.7508783, 0.4419743, -3.974632, 0.0, 0.5072599, 0.8617932, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8849987, 0.3956348, -0.2454594, -4.146301, -0.4655935, -0.7520216, 0.4665685, -3.974632, 0.0, 0.5271969, 0.8497432, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9131027, 0.3494211, -0.2101151, -4.146301, -0.4077296, -0.7825219, 0.4705488, -3.974632, 0.0, 0.5153295, 0.8569921, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9713711, 0.206814, -0.1169022, -4.146301, -0.2375672, -0.8456268, 0.4779928, -3.974632, 0.0, 0.4920805, 0.8705497, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.999695, -0.02164769, 0.01188969, -4.146301, 0.02469789, -0.8762305, 0.4812588, -3.974632, 0.0, 0.4814056, 0.8764979, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9561786, -0.2539004, 0.1457982, -4.146301, 0.2927841, -0.8291916, 0.4761499, -3.974632, 0.0, 0.4979717, 0.8671933, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.878125, -0.4056587, 0.2536485, -4.146301, 0.4784314, -0.7445562, 0.4655528, -3.974632, 0.0, 0.530167, 0.8478932, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8248081, -0.470663, 0.3133177, -4.146301, 0.5654128, -0.6865897, 0.4570589, -3.974632, 0.0, 0.5541397, 0.8324236, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.7561108, -0.5544743, 0.3476417, -4.146301, 0.6544436, -0.6406113, 0.4016475, -3.974632, 0.0, 0.5312018, 0.8472453, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.5518118, -0.7401292, 0.3843339, -4.146301, 0.8339687, -0.489721, 0.2543021, -3.974632, 0.0, 0.4608493, 0.8874784, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.09527927, -0.9081463, 0.4076668, -4.146301, 0.9954506, -0.08692294, 0.0390197, -3.974632, 0.0, 0.4095299, 0.9122967, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.4048784, -0.8189967, 0.4065929, -4.146301, 0.9143705, 0.3626474, -0.1800372, -3.974634, 0.0, 0.4446697, 0.8956946, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6480864, -0.6531851, 0.3915777, -4.146301, 0.7615668, 0.5558546, -0.3332291, -3.974632, 0.0, 0.5141739, 0.857686, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7121619, -0.5883649, 0.382952, -4.146301, 0.7020153, 0.5968688, -0.388487, -3.974632, 0.0, 0.5455038, 0.8381084, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7536112, -0.5608854, 0.3427503, -4.146301, 0.6573205, 0.6430493, -0.3929597, -3.974632, 0.0, 0.5214356, 0.8532906, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8627668, -0.4483393, 0.2337206, -4.146301, 0.5056021, 0.7650527, -0.3988243, -3.974632, 0.0, 0.462262, 0.8867434, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9813205, -0.1762961, 0.07700508, -4.146301, 0.1923801, 0.8992769, -0.392799, -3.974632, 0.0, 0.400276, 0.9163947, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9719243, 0.2180167, -0.08849775, -4.146301, -0.2352938, 0.9005584, -0.3655564, -3.974632, 0.0, 0.3761161, 0.9265726, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8278828, 0.5177841, -0.215661, -4.146301, -0.5609012, 0.7642427, -0.3183129, -3.974632, 0.0, 0.3844903, 0.923129, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.692005, 0.6702266, -0.2681891, -4.146301, -0.7218927, 0.6424779, -0.2570856, -3.974632, 0.0, 0.3715083, 0.9284297, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.5158147, 0.8117952, -0.273722, -4.146301, -0.8567002, 0.4887776, -0.1648066, -3.974632, 0.0, 0.3195074, 0.9475838, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.1157826, 0.9537606, -0.2773717, -4.146301, -0.9932746, 0.1111766, -0.03233224, -3.974632, 0.0, 0.2792497, 0.9602185, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.3957779, 0.8760311, -0.275553, -4.146301, -0.9183463, -0.3775414, 0.1187545, -3.974632, 0.0, 0.3000535, 0.9539224, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.6975454, 0.6645703, -0.267912, -4.146301, -0.7165406, -0.6469527, 0.2608097, -3.974632, 0.0, 0.3738964, 0.9274705, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8221068, 0.5077215, -0.2576031, -4.146301, -0.5693333, -0.7331404, 0.3719741, -3.974632, 0.0, 0.4524644, 0.8917825, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8712977, 0.4229292, -0.2489402, -4.146301, -0.4907549, -0.7508783, 0.4419743, -3.974632, 0.0, 0.5072599, 0.8617932, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8849987, 0.3956348, -0.2454594, -4.146301, -0.4655935, -0.7520216, 0.4665685, -3.974632, 0.0, 0.5271969, 0.8497432, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9131027, 0.3494211, -0.2101151, -4.146301, -0.4077296, -0.7825219, 0.4705488, -3.974632, 0.0, 0.5153295, 0.8569921, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9713711, 0.206814, -0.1169022, -4.146301, -0.2375672, -0.8456268, 0.4779928, -3.974632, 0.0, 0.4920805, 0.8705497, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.999695, -0.02164769, 0.01188969, -4.146301, 0.02469789, -0.8762305, 0.4812588, -3.974632, 0.0, 0.4814056, 0.8764979, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9561786, -0.2539004, 0.1457982, -4.146301, 0.2927841, -0.8291916, 0.4761499, -3.974632, 0.0, 0.4979717, 0.8671933, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.878125, -0.4056587, 0.2536485, -4.146301, 0.4784314, -0.7445562, 0.4655528, -3.974632, 0.0, 0.530167, 0.8478932, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8248081, -0.470663, 0.3133177, -4.146301, 0.5654128, -0.6865897, 0.4570589, -3.974632, 0.0, 0.5541397, 0.8324236, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.7561108, -0.5544743, 0.3476417, -4.146301, 0.6544436, -0.6406113, 0.4016475, -3.974632, 0.0, 0.5312018, 0.8472453, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.5518118, -0.7401292, 0.3843339, -4.146301, 0.8339687, -0.489721, 0.2543021, -3.974632, 0.0, 0.4608493, 0.8874784, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.09527927, -0.9081463, 0.4076668, -4.146301, 0.9954506, -0.08692294, 0.0390197, -3.974632, 0.0, 0.4095299, 0.9122967, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.4048784, -0.8189967, 0.4065929, -4.146301, 0.9143705, 0.3626474, -0.1800372, -3.974634, 0.0, 0.4446697, 0.8956946, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6480864, -0.6531851, 0.3915777, -4.146301, 0.7615668, 0.5558546, -0.3332291, -3.974632, 0.0, 0.5141739, 0.857686, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7121619, -0.5883649, 0.382952, -4.146301, 0.7020153, 0.5968688, -0.388487, -3.974632, 0.0, 0.5455038, 0.8381084, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7458067, -0.5704789, 0.3439857, -4.146301, 0.6661624, 0.6386836, -0.3851116, -3.974632, 0.0, 0.5163691, 0.8563661, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8442236, -0.4809824, 0.2365215, -4.146301, 0.5359911, 0.757581, -0.372538, -3.974632, 0.0, 0.4412788, 0.8973701, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9751951, -0.2069366, 0.07855993, -4.146301, 0.2213469, 0.9117075, -0.346114, -3.974632, 0.0, 0.3549177, 0.9348976, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9594948, 0.2668105, -0.09045404, -4.146301, -0.2817265, 0.9086946, -0.3080655, -3.974632, 0.0, 0.3210706, 0.9470553, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7795101, 0.5868992, -0.2188912, -4.146301, -0.6263897, 0.7303662, -0.2723989, -3.974632, 0.0, 0.3494489, 0.9369555, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.692005, 0.6702266, -0.2681891, -4.146301, -0.7218927, 0.6424779, -0.2570856, -3.974632, 0.0, 0.3715083, 0.9284297, 10.48219, 0.0, 0.0, 0.0, 1.0,
};

enum interpolation const array_node_directlight_matrix_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_directlight_matrix_sampler = {
  // node_directlight_matrix_input
  .input = {
    .float_array = array_node_directlight_matrix_input_array,
    .count = 101,
    .stride = 1,
  },
  // node_directlight_matrix_output
  .output = {
    .float_array = array_node_directlight_matrix_output_array,
    .count = 101,
    .stride = 16,
  },
  // node_directlight_matrix_interpolation
  .interpolation = {
    .interpolation_array = array_node_directlight_matrix_interpolation_array,
    .count = 101,
    .stride = 1,
  },
};

float const array_node_camerahelper_translation_x_input_array[] = {
  0.0,
  0.8333334,
  1.666667,
  2.5,
  3.333333,
};

float const array_node_camerahelper_translation_x_output_array[] = {
  -57.36452,
  -158.3051,
  6.142715,
  214.8339,
  -57.36452,
};

float const array_node_camerahelper_translation_x_intangent_array[] = {
  -0.3329306, -57.36452,
  0.5558333, -158.3051,
  1.389167, -55.98494,
  2.2225, 214.8339,
  3.055833, -57.36452,
};

float const array_node_camerahelper_translation_x_outtangent_array[] = {
  0.2775, -57.36452,
  1.110833, -158.3051,
  1.944167, 68.27037,
  2.7775, 214.8339,
  3.666264, -57.36452,
};

enum interpolation const array_node_camerahelper_translation_x_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_camerahelper_translation_x_sampler = {
  // node_camerahelper_translation_x_input
  .input = {
    .float_array = array_node_camerahelper_translation_x_input_array,
    .count = 5,
    .stride = 1,
  },
  // node_camerahelper_translation_x_output
  .output = {
    .float_array = array_node_camerahelper_translation_x_output_array,
    .count = 5,
    .stride = 1,
  },
  // node_camerahelper_translation_x_intangent
  .in_tangent = {
    .float_array = array_node_camerahelper_translation_x_intangent_array,
    .count = 5,
    .stride = 2,
  },
  // node_camerahelper_translation_x_outtangent
  .out_tangent = {
    .float_array = array_node_camerahelper_translation_x_outtangent_array,
    .count = 5,
    .stride = 2,
  },
  // node_camerahelper_translation_x_interpolation
  .interpolation = {
    .interpolation_array = array_node_camerahelper_translation_x_interpolation_array,
    .count = 5,
    .stride = 1,
  },
};

float const array_node_camerahelper_translation_y_input_array[] = {
  0.0,
  0.8333334,
  1.666667,
  2.5,
  3.333333,
};

float const array_node_camerahelper_translation_y_output_array[] = {
  159.98,
  -1.736969,
  -219.6883,
  -4.115463,
  159.98,
};

float const array_node_camerahelper_translation_y_intangent_array[] = {
  -0.3329306, 159.98,
  0.5558333, 61.4778,
  1.389167, -219.6883,
  2.2225, -67.33023,
  3.055833, 159.98,
};

float const array_node_camerahelper_translation_y_outtangent_array[] = {
  0.2775, 159.98,
  1.110833, -64.95174,
  1.944167, -219.6883,
  2.7775, 59.0993,
  3.666264, 159.98,
};

enum interpolation const array_node_camerahelper_translation_y_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_camerahelper_translation_y_sampler = {
  // node_camerahelper_translation_y_input
  .input = {
    .float_array = array_node_camerahelper_translation_y_input_array,
    .count = 5,
    .stride = 1,
  },
  // node_camerahelper_translation_y_output
  .output = {
    .float_array = array_node_camerahelper_translation_y_output_array,
    .count = 5,
    .stride = 1,
  },
  // node_camerahelper_translation_y_intangent
  .in_tangent = {
    .float_array = array_node_camerahelper_translation_y_intangent_array,
    .count = 5,
    .stride = 2,
  },
  // node_camerahelper_translation_y_outtangent
  .out_tangent = {
    .float_array = array_node_camerahelper_translation_y_outtangent_array,
    .count = 5,
    .stride = 2,
  },
  // node_camerahelper_translation_y_interpolation
  .interpolation = {
    .interpolation_array = array_node_camerahelper_translation_y_interpolation_array,
    .count = 5,
    .stride = 1,
  },
};

float const array_node_camerahelper_translation_z_input_array[] = {
  0.0,
  0.8333334,
  1.666667,
  2.5,
  3.333333,
};

float const array_node_camerahelper_translation_z_output_array[] = {
  269.2574,
  269.2574,
  269.2574,
  269.2574,
  269.2574,
};

float const array_node_camerahelper_translation_z_intangent_array[] = {
  -0.3329306, 269.2574,
  0.5558333, 269.2574,
  1.389167, 269.2574,
  2.2225, 269.2574,
  3.055833, 269.2574,
};

float const array_node_camerahelper_translation_z_outtangent_array[] = {
  0.2775, 269.2574,
  1.110833, 269.2574,
  1.944167, 269.2574,
  2.7775, 269.2574,
  3.666264, 269.2574,
};

enum interpolation const array_node_camerahelper_translation_z_interpolation_array[] = {
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
  interpolation::BEZIER,
};

sampler const sampler_node_camerahelper_translation_z_sampler = {
  // node_camerahelper_translation_z_input
  .input = {
    .float_array = array_node_camerahelper_translation_z_input_array,
    .count = 5,
    .stride = 1,
  },
  // node_camerahelper_translation_z_output
  .output = {
    .float_array = array_node_camerahelper_translation_z_output_array,
    .count = 5,
    .stride = 1,
  },
  // node_camerahelper_translation_z_intangent
  .in_tangent = {
    .float_array = array_node_camerahelper_translation_z_intangent_array,
    .count = 5,
    .stride = 2,
  },
  // node_camerahelper_translation_z_outtangent
  .out_tangent = {
    .float_array = array_node_camerahelper_translation_z_outtangent_array,
    .count = 5,
    .stride = 2,
  },
  // node_camerahelper_translation_z_interpolation
  .interpolation = {
    .interpolation_array = array_node_camerahelper_translation_z_interpolation_array,
    .count = 5,
    .stride = 1,
  },
};

float const array_node_camera001_matrix_input_array[] = {
  0.0,
  0.03333333,
  0.06666667,
  0.1,
  0.1333333,
  0.1666667,
  0.2,
  0.2333333,
  0.2666667,
  0.3,
  0.3333333,
  0.3666667,
  0.4,
  0.4333333,
  0.4666667,
  0.5,
  0.5333333,
  0.5666667,
  0.6,
  0.6333333,
  0.6666667,
  0.7,
  0.7333333,
  0.7666667,
  0.8,
  0.8333333,
  0.8666667,
  0.9,
  0.9333333,
  0.9666667,
  1.0,
  1.033333,
  1.066667,
  1.1,
  1.133333,
  1.166667,
  1.2,
  1.233333,
  1.266667,
  1.3,
  1.333333,
  1.366667,
  1.4,
  1.433333,
  1.466667,
  1.5,
  1.533333,
  1.566667,
  1.6,
  1.633333,
  1.666667,
  1.7,
  1.733333,
  1.766667,
  1.8,
  1.833333,
  1.866667,
  1.9,
  1.933333,
  1.966667,
  2.0,
  2.033333,
  2.066667,
  2.1,
  2.133333,
  2.166667,
  2.2,
  2.233333,
  2.266667,
  2.3,
  2.333333,
  2.366667,
  2.4,
  2.433333,
  2.466667,
  2.5,
  2.533333,
  2.566667,
  2.6,
  2.633333,
  2.666667,
  2.7,
  2.733333,
  2.766667,
  2.8,
  2.833333,
  2.866667,
  2.9,
  2.933333,
  2.966667,
  3.0,
  3.033333,
  3.066667,
  3.1,
  3.133333,
  3.166667,
  3.2,
  3.233333,
  3.266667,
  3.3,
  3.333333,
};

float const array_node_camera001_matrix_output_array[] = {
  -0.9413647, 0.2284669, -0.2482645, -3.604237, -0.3371616, -0.6641206, 0.6672826, 4.948456, -0.01242554, 0.7118617, 0.7022099, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9397281, 0.2325841, -0.2506304, -3.604237, -0.3416982, -0.6653518, 0.663739, 4.948456, -0.01238214, 0.7093742, 0.7047234, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9348633, 0.2444722, -0.2574173, -3.604237, -0.3547956, -0.6684431, 0.6536849, 4.948456, -0.01226103, 0.7024366, 0.7116407, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9265543, 0.2637478, -0.2682052, -3.604237, -0.3759669, -0.6722135, 0.6377913, 4.948456, -0.01207512, 0.6917847, 0.7220028, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9142916, 0.2902016, -0.2825838, -3.604233, -0.4048832, -0.6751512, 0.6166363, 4.948456, -0.01183795, 0.6781989, 0.7347829, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8973854, 0.323486, -0.3000935, -3.60424, -0.4410958, -0.6754896, 0.5908877, 4.948456, -0.0115661, 0.6626242, 0.7488627, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8751454, 0.3627716, -0.3201831, -3.604233, -0.4837284, -0.6713846, 0.5614709, 4.948456, -0.01128029, 0.6462505, 0.7630421, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8471938, 0.406409, -0.3421904, -3.604233, -0.5311698, -0.6612697, 0.529699, 4.948456, -0.01100569, 0.630519, 0.7760958, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8139214, 0.4517161, -0.3653551, -3.60424, -0.580875, -0.6443848, 0.4973455, 4.948456, -0.0107702, 0.617026, 0.7868691, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.7769756, 0.4950734, -0.3888586, -3.60424, -0.6294413, -0.6213417, 0.4666243, 4.948456, -0.01060074, 0.6073194, 0.7943871, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.7395098, 0.5324315, -0.4118761, -3.604233, -0.6730635, -0.5944132, 0.4400664, 4.948456, -0.01051932, 0.6026523, 0.7979346, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.6987548, 0.5644106, -0.4395252, -3.604233, -0.7152829, -0.560336, 0.417605, 4.948456, -0.01058101, 0.6061885, 0.7952506, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.6514075, 0.5913878, -0.4753194, -3.60424, -0.7586508, -0.5166096, 0.3969423, 4.948456, -0.01080769, 0.6191729, 0.7851803, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.6010755, 0.6103275, -0.5159542, -3.60424, -0.7991144, -0.4679967, 0.377353, 4.948456, -0.0111559, 0.639124, 0.7690227, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.5509208, 0.6203532, -0.5582546, -3.60424, -0.8344771, -0.418756, 0.3581777, 4.948456, -0.01157581, 0.6631783, 0.7483718, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.5030627, 0.6225541, -0.5994618, -3.60424, -0.8641663, -0.3719866, 0.3388841, 4.948456, -0.01201802, 0.6885148, 0.7251228, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.4584817, 0.6192697, -0.6374164, -3.604233, -0.8886166, -0.3294896, 0.3190563, 4.948456, -0.0124402, 0.7127004, 0.7013582, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.4172369, 0.6133617, -0.6705973, -3.604233, -0.9087074, -0.2919723, 0.2983335, 4.948456, -0.01280939, 0.7338526, 0.679188, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.3787481, 0.607721, -0.698015, -3.604233, -0.9254069, -0.2593535, 0.2763288, 4.948456, -0.01310187, 0.750607, 0.660619, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.3419999, 0.6050392, -0.7190018, -3.604233, -0.9396058, -0.2310087, 0.2525388, 4.948456, -0.01329982, 0.7619466, 0.6475034, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.3056142, 0.607781, -0.7329409, -3.604233, -0.9520612, -0.2058836, 0.2262547, 4.948456, -0.01338714, 0.7669514, 0.6415656, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.2617462, 0.6201251, -0.7395498, -3.604233, -0.9650445, -0.1787485, 0.1916711, 4.948456, -0.01333332, 0.7638679, 0.6452351, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.204065, 0.641952, -0.7390907, -3.604233, -0.978869, -0.1439417, 0.145245, 4.948456, -0.01314556, 0.7531125, 0.6577604, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.1332688, 0.6687178, -0.7314753, -3.604233, -0.9909964, -0.09949171, 0.08959579, 4.948456, -0.01286137, 0.7368298, 0.675956, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.0508098, 0.695389, -0.7168351, -3.604233, -0.9986298, -0.04437339, 0.02773779, 4.948456, -0.01251983, 0.7172623, 0.6966909, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.04046291, 0.7169858, -0.6959125, -3.604233, -0.999107, 0.02055507, -0.03691422, 4.948456, -0.01216238, 0.6967848, 0.7171772, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.1387001, 0.7291706, -0.6701287, -3.604233, -0.9902637, 0.09403151, -0.102644, 4.948456, -0.0118317, 0.677841, 0.7351134, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.2402089, 0.7285494, -0.6414948, -3.604233, -0.9706521, 0.1723919, -0.167676, 4.948456, -0.0115717, 0.6629456, 0.7485781, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.3373253, 0.7147521, -0.6126508, -3.604233, -0.9413188, 0.2482066, -0.2287184, 4.948456, -0.01141297, 0.6538524, 0.7565361, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.4228232, 0.6907985, -0.5865305, -3.604233, -0.9061408, 0.3141708, -0.2832056, 4.948456, -0.01136714, 0.6512252, 0.7587994, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.4914149, 0.6618691, -0.5660749, -3.604233, -0.8708505, 0.3648938, -0.3293507, 4.948456, -0.01142978, 0.6548146, 0.7557032, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.5454156, 0.6303769, -0.5524008, -3.604233, -0.8380853, 0.4010402, -0.3698372, 4.948456, -0.01160192, 0.6646742, 0.7470432, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.5902758, 0.5967821, -0.5435307, -3.604233, -0.8071143, 0.42646, -0.4082868, 4.948456, -0.01186406, 0.6796933, 0.7334005, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.627662, 0.5629917, -0.5376623, -3.604233, -0.7783907, 0.4430582, -0.4447553, 4.948456, -0.01217782, 0.6976674, 0.7163183, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.6594679, 0.5300824, -0.5330241, -3.604233, -0.7516285, 0.4531579, -0.4792729, 4.948456, -0.01251006, 0.7167012, 0.6972681, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.6875205, 0.4986201, -0.5279144, -3.604233, -0.7260515, 0.4591633, -0.5118772, 4.948456, -0.01283323, 0.7352192, 0.677708, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.7134559, 0.4688696, -0.5207127, -3.604233, -0.7005771, 0.4634015, -0.5426332, 4.948456, -0.01312518, 0.7519444, 0.6590959, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.7386922, 0.4408773, -0.5098636, -3.60424, -0.6739102, 0.4680662, -0.5716283, 4.948456, -0.01336807, 0.7658599, 0.6428686, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.764436, 0.4144411, -0.4938381, -3.60424, -0.6445572, 0.4752077, -0.5989355, 4.948456, -0.01354777, 0.7761549, 0.6303968, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.7916854, 0.3889929, -0.4710825, -3.60424, -0.6107763, 0.4867268, -0.6245391, 4.948456, -0.01365268, 0.7821647, 0.6229221, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8188909, 0.3656388, -0.4424091, -3.60424, -0.5737863, 0.5031774, -0.6462057, 4.948456, -0.01366764, 0.7830204, 0.6218459, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.844683, 0.3444911, -0.4096783, -3.604233, -0.535094, 0.5240111, -0.6626362, 4.948456, -0.01359629, 0.7789341, 0.6269583, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8697346, 0.3233566, -0.3728297, -3.604237, -0.4933361, 0.5490505, -0.6746577, 4.948456, -0.01345264, 0.7707037, 0.6370517, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8942465, 0.3002681, -0.3319067, -3.604237, -0.4473783, 0.5777171, -0.6827119, 4.948456, -0.01324838, 0.7590008, 0.650955, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9179849, 0.2734984, -0.2872318, -3.604237, -0.396402, 0.6089547, -0.6870514, 4.948456, -0.01299637, 0.7445623, 0.6674265, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9402917, 0.2417698, -0.2395803, -3.604237, -0.3401319, 0.6411473, -0.6879249, 4.948456, -0.01271319, 0.7283391, 0.685099, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9601519, 0.2046561, -0.1903259, -3.604237, -0.2792021, 0.6721395, -0.6857658, 4.948456, -0.01242059, 0.7115789, 0.7024965, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9764097, 0.163092, -0.1415091, -3.604237, -0.2155837, 0.699468, -0.6813722, 4.948456, -0.01214528, 0.6958057, 0.7181273, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9881719, 0.1197582, -0.09578114, -3.604237, -0.1528857, 0.7208451, -0.6760239, 4.948456, -0.01191604, 0.6826716, 0.7306282, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9952873, 0.07901698, -0.056207, -3.604237, -0.09625285, 0.7347498, -0.6714746, 4.948456, -0.01175981, 0.6737204, 0.7388928, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.998595, 0.04618811, -0.02597033, -3.604237, -0.05168128, 0.7407603, -0.6697784, 4.948456, -0.011698, 0.6701797, 0.7421067, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9998347, 0.01816374, -0.000651438, -3.604237, -0.01383614, 0.7374025, -0.6753119, 4.948456, -0.0117858, 0.6752095, 0.7375319, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9996305, -0.009374737, 0.0255109, -3.604237, 0.02437233, 0.7245985, -0.6887403, 4.948456, -0.01202839, 0.6891077, 0.7245591, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9980828, -0.03407585, 0.05166608, -3.604237, 0.06064432, 0.7051817, -0.7064285, 4.948456, -0.01236176, 0.7082075, 0.7058961, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9954788, -0.05518156, 0.07730919, -3.604237, 0.09412622, 0.6821792, -0.7251014, 4.948456, -0.01272642, 0.7291, 0.6842889, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9920604, -0.07313573, 0.1023095, -3.604237, 0.1250804, 0.6583815, -0.7422188, 4.948456, -0.01307594, 0.7491229, 0.662302, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9879096, -0.08906954, 0.1268901, -3.604237, 0.1544522, 0.6360969, -0.7559928, 4.948456, -0.01337844, 0.7664512, 0.6421632, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9829092, -0.1044578, 0.1515849, -3.604233, 0.1835867, 0.6170937, -0.765174, 4.948456, -0.01361364, 0.7799258, 0.6257241, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9767052, -0.1210147, 0.1772066, -3.604233, 0.2141429, 0.6026605, -0.7687281, 4.948456, -0.01376795, 0.7887685, 0.6145362, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9686104, -0.1408172, 0.2048517, -3.604233, 0.2481984, 0.5936926, -0.7654585, 4.948456, -0.01382917, 0.792275, 0.6100074, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9573636, -0.1666724, 0.2359557, -3.604233, 0.2885565, 0.5906853, -0.7535424, 4.948456, -0.01378077, 0.7895008, 0.613595, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9407217, -0.2026321, 0.2719976, -3.60424, 0.3389066, 0.5936928, -0.7298432, 4.948456, -0.01359331, 0.7787613, 0.6271731, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9154402, -0.2522891, 0.3135592, -3.604233, 0.4022353, 0.5992313, -0.6921913, 4.948456, -0.01326203, 0.7597844, 0.6500399, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8766, -0.3187492, 0.3605151, -3.604233, 0.4810491, 0.6003664, -0.6388677, 4.948456, -0.01280248, 0.7334571, 0.6796152, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8170524, -0.40368, 0.4116645, -3.604233, 0.5764331, 0.5870966, -0.5683682, 4.948456, -0.01224792, 0.7016838, 0.7123833, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.7283205, -0.5038918, 0.4643731, -3.604233, 0.6851372, 0.5470356, -0.4809772, 4.948456, -0.01166808, 0.668465, 0.7436522, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.6051674, -0.6072691, 0.5147783, -3.604233, 0.7960197, 0.4706553, -0.3805733, 4.948456, -0.01117271, 0.6400845, 0.7682234, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.4542592, -0.6937054, 0.5589466, -3.604233, 0.890803, 0.3613572, -0.2754828, 4.948456, -0.0108754, 0.6230521, 0.7821047, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.2985804, -0.7465601, 0.5945568, -3.604233, 0.9543229, 0.2406147, -0.1771216, 4.948456, -0.01082706, 0.6202844, 0.7843024, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.1674054, -0.7650468, 0.6218351, -3.604233, 0.9858269, 0.136925, -0.09693682, 4.948456, -0.01098358, 0.6292496, 0.7771257, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.08151036, -0.761555, 0.6429542, -3.604233, 0.9966089, 0.06955778, -0.04395633, 4.948456, -0.01124727, 0.644357, 0.7646421, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.03281348, -0.7473465, 0.6636238, -3.604233, 0.9993942, 0.03223037, -0.01311939, 4.948456, -0.01158404, 0.6636525, 0.7479515, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.003627419, -0.7273052, 0.6863047, -3.604233, 0.9999216, 0.01085883, 0.006222486, 4.948456, -0.01197814, 0.6862284, 0.7272875, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.01020056, -0.7051325, 0.7090023, -3.604233, 0.9998713, 0.001583516, 0.01596033, 4.948456, -0.0123769, 0.7090739, 0.7050256, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.01290297, -0.6832106, 0.7301074, -3.604233, 0.9998354, 0.000492046, 0.01813024, 4.948456, -0.01274603, 0.7302213, 0.6830918, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.008003592, -0.6631503, 0.7484435, -3.604233, 0.9998825, 0.004471421, 0.01465427, 4.948456, -0.01306462, 0.748473, 0.6630367, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.000481115, -0.6469606, 0.7625234, -3.604233, 0.9999112, 0.009836971, 0.008977055, 4.948456, -0.01330876, 0.7624601, 0.6468984, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.005708754, -0.6362069, 0.7714974, -3.604233, 0.999893, 0.01401996, 0.004162609, 4.948456, -0.01346462, 0.7713913, 0.6362187, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.009305119, -0.6315634, 0.7752683, -3.604233, 0.9998651, 0.01636701, 0.001332342, 4.948456, -0.01353031, 0.7751516, 0.6316304, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.008942782, -0.6338679, 0.7733895, -3.604233, 0.9998688, 0.01610791, 0.001640379, 4.948456, -0.01349753, 0.7732736, 0.6339289, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.002830982, -0.6442094, 0.7648439, -3.604233, 0.9999068, 0.0120334, 0.006434381, 4.948456, -0.01334881, 0.7647545, 0.6441834, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.006968617, -0.6677442, 0.7443582, -3.604233, 0.9998912, 0.005018949, 0.01386332, 4.948456, -0.01299303, 0.7443739, 0.6676366, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.01834195, -0.7076274, 0.7063477, -3.604233, 0.9997556, -0.004265904, 0.02168726, 4.948456, -0.01233321, 0.7065729, 0.7075327, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.0344395, -0.7616603, 0.6470606, -3.604233, 0.9993427, -0.01892095, 0.03091752, 4.948452, -0.01130563, 0.6477003, 0.7618113, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.06113547, -0.8250542, 0.5617367, -3.604233, 0.9980809, -0.04498857, 0.04254686, 4.948456, -0.009831726, 0.5632599, 0.8262213, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.1116969, -0.887184, 0.4476924, -3.60424, 0.993711, -0.09614551, 0.05739605, 4.948456, -0.00787723, 0.4512879, 0.8923436, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.2217518, -0.9246425, 0.3096169, -3.604233, 0.9750872, -0.2084614, 0.07581996, 4.948456, -0.005563199, 0.3187167, 0.9478337, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.4978073, -0.851731, 0.1635304, -3.60424, 0.8672811, -0.4881519, 0.09762656, 4.948456, -0.003323853, 0.1904261, 0.9816959, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9609214, -0.2748429, 0.0330342, -3.60424, 0.2768122, -0.953069, 0.1226159, 4.948456, -0.002216219, 0.1269685, 0.9919043, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9348061, 0.3499648, -0.06051588, -3.604237, -0.355147, -0.9224715, 0.1513835, 4.948456, -0.002845227, 0.1630062, 0.986621, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8519998, 0.5087125, -0.1237242, -3.604237, -0.5235264, -0.8296546, 0.19389, 4.948456, -0.004014074, 0.2299671, 0.9731901, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8350076, 0.522161, -0.1735223, -3.604237, -0.550212, -0.7954391, 0.254054, 4.948456, -0.005369365, 0.3076111, 0.951497, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8474479, 0.4874653, -0.2102606, -3.604237, -0.5308356, -0.7831129, 0.3239564, 4.948456, -0.006740212, 0.38615, 0.9224113, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8678036, 0.4378176, -0.2350162, -3.604237, -0.4968422, -0.7721598, 0.3961276, 4.948456, -0.00803852, 0.460527, 0.8876093, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8877711, 0.386736, -0.2495947, -3.604237, -0.4601929, -0.7566071, 0.4645086, 4.948456, -0.009202957, 0.5272392, 0.8496671, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9047119, 0.3403055, -0.2562975, -3.604235, -0.4259016, -0.7368705, 0.5250046, 4.948456, -0.01019608, 0.5841355, 0.8115921, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9181376, 0.3011444, -0.2575563, -3.604237, -0.3961086, -0.7155295, 0.5754265, 4.948456, -0.0110026, 0.630341, 0.7762405, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9282615, 0.2701628, -0.2556218, -3.604237, -0.3717463, -0.695424, 0.6149718, 4.948456, -0.01162296, 0.6658812, 0.7459672, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9354168, 0.247555, -0.2524117, -3.604237, -0.3533406, -0.6789649, 0.6435504, 4.948456, -0.01206445, 0.6911754, 0.7225864, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9398102, 0.2334554, -0.2495101, -3.604237, -0.3414741, -0.668038, 0.661151, 4.948456, -0.01233297, 0.7065578, 0.7075479, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9413647, 0.2284669, -0.2482645, -3.604237, -0.3371616, -0.6641206, 0.6672826, 4.948456, -0.01242554, 0.7118617, 0.7022099, 0.0, 0.0, 0.0, 0.0, 1.0,
};

enum interpolation const array_node_camera001_matrix_interpolation_array[] = {
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
  interpolation::LINEAR,
};

sampler const sampler_node_camera001_matrix_sampler = {
  // node_camera001_matrix_input
  .input = {
    .float_array = array_node_camera001_matrix_input_array,
    .count = 101,
    .stride = 1,
  },
  // node_camera001_matrix_output
  .output = {
    .float_array = array_node_camera001_matrix_output_array,
    .count = 101,
    .stride = 16,
  },
  // node_camera001_matrix_interpolation
  .interpolation = {
    .interpolation_array = array_node_camera001_matrix_interpolation_array,
    .count = 101,
    .stride = 1,
  },
};

channel const node_channel_node_camera001_target_translation_x = {
  .source_sampler = &sampler_node_camera001_target_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_camera001_target_translation_y = {
  .source_sampler = &sampler_node_camera001_target_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_camera001_target_translation_z = {
  .source_sampler = &sampler_node_camera001_target_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_torus_knot_rotationz_angle = {
  .source_sampler = &sampler_node_torus_knot_rotationz_angle_sampler,
  .target_transform_index = 1,
  .target_attribute = target_attribute::ANGLE,
};

channel const node_channel_node_lighthelper_translation_x = {
  .source_sampler = &sampler_node_lighthelper_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_lighthelper_translation_y = {
  .source_sampler = &sampler_node_lighthelper_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_lighthelper_translation_z = {
  .source_sampler = &sampler_node_lighthelper_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_directlight_matrix = {
  .source_sampler = &sampler_node_directlight_matrix_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::ALL,
};

channel const node_channel_node_camerahelper_translation_x = {
  .source_sampler = &sampler_node_camerahelper_translation_x_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::X,
};

channel const node_channel_node_camerahelper_translation_y = {
  .source_sampler = &sampler_node_camerahelper_translation_y_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Y,
};

channel const node_channel_node_camerahelper_translation_z = {
  .source_sampler = &sampler_node_camerahelper_translation_z_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::Z,
};

channel const node_channel_node_camera001_matrix = {
  .source_sampler = &sampler_node_camera001_matrix_sampler,
  .target_transform_index = 0,
  .target_attribute = target_attribute::ALL,
};

image const * const images[] = {
};

effect const effect_planematerial = {
  .type = effect_type::BLINN,
  .blinn = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.6627451f, 0.5882353f, 0.6196079f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.6627451f, 0.5882353f, 0.6196079f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .shininess = 10.0f,
    .reflective = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .reflectivity = 0.0f,
    .transparent = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .transparency = 1.0f,
    .index_of_refraction = 0.0f,
  }
};

effect const effect_coloreffectr5g54b179 = {
  .type = effect_type::PHONG,
  .phong = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 0.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.01960784f, 0.2117647f, 0.7019608f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.01960784f, 0.2117647f, 0.7019608f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .shininess = 10.0f,
    .reflective = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .reflectivity = 0.0f,
    .transparent = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .transparency = 1.0f,
    .index_of_refraction = 0.0f,
  }
};

effect const effect_torusmaterial = {
  .type = effect_type::BLINN,
  .blinn = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.5254902f, 0.4313726f, 0.03137255f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.5254902f, 0.4313726f, 0.03137255f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {0.666f, 0.666f, 0.666f, 1.0f},
    },
    .shininess = 10.0f,
    .reflective = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .reflectivity = 0.0f,
    .transparent = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .transparency = 1.0f,
    .index_of_refraction = 0.0f,
  }
};

effect const effect_coloreffectr255g229b0 = {
  .type = effect_type::PHONG,
  .phong = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 0.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 0.8980392f, 0.0f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 0.8980392f, 0.0f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .shininess = 10.0f,
    .reflective = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .reflectivity = 0.0f,
    .transparent = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .transparency = 1.0f,
    .index_of_refraction = 0.0f,
  }
};

effect const effect_conematerial = {
  .type = effect_type::BLINN,
  .blinn = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.02352941f, 0.5254902f, 0.02352941f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.02352941f, 0.5254902f, 0.02352941f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {0.666f, 0.666f, 0.666f, 1.0f},
    },
    .shininess = 10.0f,
    .reflective = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .reflectivity = 0.0f,
    .transparent = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .transparency = 1.0f,
    .index_of_refraction = 0.0f,
  }
};

effect const effect_boxmaterial = {
  .type = effect_type::BLINN,
  .blinn = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.345098f, 0.345098f, 0.882353f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.345098f, 0.345098f, 0.882353f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {0.666f, 0.666f, 0.666f, 1.0f},
    },
    .shininess = 10.0f,
    .reflective = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .reflectivity = 0.0f,
    .transparent = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .transparency = 1.0f,
    .index_of_refraction = 0.0f,
  }
};

effect const effect_lightmaterial = {
  .type = effect_type::BLINN,
  .blinn = {
    .emission = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .ambient = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .diffuse = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .specular = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .shininess = 10.0f,
    .reflective = {
      .type = color_or_texture_type::COLOR,
      .color = {0.0f, 0.0f, 0.0f, 1.0f},
    },
    .reflectivity = 0.0f,
    .transparent = {
      .type = color_or_texture_type::COLOR,
      .color = {1.0f, 1.0f, 1.0f, 1.0f},
    },
    .transparency = 1.0f,
    .index_of_refraction = 0.0f,
  }
};

material const material_coloreffectr5g54b179_material = {
  .effect = &effect_coloreffectr5g54b179,
};

material const material_coloreffectr255g229b0_material = {
  .effect = &effect_coloreffectr255g229b0,
};

material const material_planematerial_material = {
  .effect = &effect_planematerial,
};

material const material_torusmaterial_material = {
  .effect = &effect_torusmaterial,
};

material const material_conematerial_material = {
  .effect = &effect_conematerial,
};

material const material_boxmaterial_material = {
  .effect = &effect_boxmaterial,
};

material const material_lightmaterial_material = {
  .effect = &effect_lightmaterial,
};

material const * const materials[] = {
  &material_coloreffectr5g54b179_material,
  &material_coloreffectr255g229b0_material,
  &material_planematerial_material,
  &material_torusmaterial_material,
  &material_conematerial_material,
  &material_boxmaterial_material,
  &material_lightmaterial_material,
};

input_element const input_elements_position_0_3_normal_0_3_texcoord_0_3[] = {
  {
    .semantic = "POSITION",
    .semantic_index = 0,
    .format = input_format::FLOAT3,
  },
  {
    .semantic = "NORMAL",
    .semantic_index = 0,
    .format = input_format::FLOAT3,
  },
  {
    .semantic = "TEXCOORD",
    .semantic_index = 0,
    .format = input_format::FLOAT3,
  },
};

triangles const triangles_geom_plane[] = {
  {
    .count = 20000, // triangles
    .index_offset = 0, // indices
    .inputs_index = 0, // index into inputs_list
  },
};

geometry const geometry_geom_plane = {
  .mesh = {
    .triangles = triangles_geom_plane,
    .triangles_count = 1,

    .vertex_buffer_offset = 0,
    .vertex_buffer_size = 367236,

    .index_buffer_offset = 0,
    .index_buffer_size = 240000,
  }
};

triangles const triangles_geom_torus_knot[] = {
  {
    .count = 2880, // triangles
    .index_offset = 0, // indices
    .inputs_index = 0, // index into inputs_list
  },
};

geometry const geometry_geom_torus_knot = {
  .mesh = {
    .triangles = triangles_geom_torus_knot,
    .triangles_count = 1,

    .vertex_buffer_offset = 367236,
    .vertex_buffer_size = 56628,

    .index_buffer_offset = 240000,
    .index_buffer_size = 34560,
  }
};

triangles const triangles_geom_cone[] = {
  {
    .count = 288, // triangles
    .index_offset = 0, // indices
    .inputs_index = 0, // index into inputs_list
  },
};

geometry const geometry_geom_cone = {
  .mesh = {
    .triangles = triangles_geom_cone,
    .triangles_count = 1,

    .vertex_buffer_offset = 423864,
    .vertex_buffer_size = 7488,

    .index_buffer_offset = 274560,
    .index_buffer_size = 3456,
  }
};

triangles const triangles_geom_boxwithhole[] = {
  {
    .count = 32, // triangles
    .index_offset = 0, // indices
    .inputs_index = 0, // index into inputs_list
  },
};

geometry const geometry_geom_boxwithhole = {
  .mesh = {
    .triangles = triangles_geom_boxwithhole,
    .triangles_count = 1,

    .vertex_buffer_offset = 431352,
    .vertex_buffer_size = 2880,

    .index_buffer_offset = 278016,
    .index_buffer_size = 384,
  }
};

triangles const triangles_geom_lightindicator[] = {
  {
    .count = 12, // triangles
    .index_offset = 0, // indices
    .inputs_index = 0, // index into inputs_list
  },
};

geometry const geometry_geom_lightindicator = {
  .mesh = {
    .triangles = triangles_geom_lightindicator,
    .triangles_count = 1,

    .vertex_buffer_offset = 434232,
    .vertex_buffer_size = 864,

    .index_buffer_offset = 278400,
    .index_buffer_size = 144,
  }
};

geometry const * const geometries[] = {
  &geometry_geom_plane,
  &geometry_geom_torus_knot,
  &geometry_geom_cone,
  &geometry_geom_boxwithhole,
  &geometry_geom_lightindicator,
};

transform const transforms_node_environmentambientlight[] = {
};

instance_geometry const instance_geometries_node_environmentambientlight[] = {
};

instance_controller const instance_controllers_node_environmentambientlight[] = {
};

instance_light const instance_lights_node_environmentambientlight[] = {
  {
    .light = &light_environmentambientlight,
  }
};

channel const * const node_channels_node_environmentambientlight[] = {
};

node const node_node_environmentambientlight = {
  .name = "EnvironmentAmbientLight",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_environmentambientlight,
  .transforms_count = 0,

  .instance_geometries = instance_geometries_node_environmentambientlight,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_environmentambientlight,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_environmentambientlight,
  .instance_lights_count = 1,

  .channels = node_channels_node_environmentambientlight,
  .channels_count = 0,
};

transform const transforms_node_plane[] = {
};

instance_material const instance_geometry_instance_materials_node_plane_0[] = {
  {
    .element_index = 0, // an index into mesh.triangles
    .material_index = 2, // an index into materials

    .emission = { .input_set = -1 },
    .ambient = { .input_set = -1 },
    .diffuse = { .input_set = -1 },
    .specular = { .input_set = -1 },
  },
};

instance_geometry const instance_geometries_node_plane[] = {
  {
    .geometry = &geometry_geom_plane,

    .instance_materials = instance_geometry_instance_materials_node_plane_0,
    .instance_materials_count = 1,
  },
};

instance_controller const instance_controllers_node_plane[] = {
};

instance_light const instance_lights_node_plane[] = {
};

channel const * const node_channels_node_plane[] = {
};

node const node_node_plane = {
  .name = "Plane",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_plane,
  .transforms_count = 0,

  .instance_geometries = instance_geometries_node_plane,
  .instance_geometries_count = 1,

  .instance_controllers = instance_controllers_node_plane,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_plane,
  .instance_lights_count = 0,

  .channels = node_channels_node_plane,
  .channels_count = 0,
};

transform const transforms_node_camera001_target[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {18.7608f, -49.36783f, 43.74428f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {-0.7700763f, 0.318976f, 0.5524825f, -73.7201f},
  },
};

instance_geometry const instance_geometries_node_camera001_target[] = {
};

instance_controller const instance_controllers_node_camera001_target[] = {
};

instance_light const instance_lights_node_camera001_target[] = {
};

channel const * const node_channels_node_camera001_target[] = {
  &node_channel_node_camera001_target_translation_x,
  &node_channel_node_camera001_target_translation_z,
  &node_channel_node_camera001_target_translation_y,
};

node const node_node_camera001_target = {
  .name = "Camera001.Target",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_camera001_target,
  .transforms_count = 2,

  .instance_geometries = instance_geometries_node_camera001_target,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_camera001_target,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_camera001_target,
  .instance_lights_count = 0,

  .channels = node_channels_node_camera001_target,
  .channels_count = 3,
};

transform const transforms_node_torus_knot[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-6.954298f, 40.46052f, 74.58796f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 0.0f, 1.0f, -5.08889e-14f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {0.0f, 1.0f, 0.0f, 1.70755e-06f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, 90.0f},
  },
};

instance_material const instance_geometry_instance_materials_node_torus_knot_0[] = {
  {
    .element_index = 0, // an index into mesh.triangles
    .material_index = 3, // an index into materials

    .emission = { .input_set = -1 },
    .ambient = { .input_set = -1 },
    .diffuse = { .input_set = -1 },
    .specular = { .input_set = -1 },
  },
};

instance_geometry const instance_geometries_node_torus_knot[] = {
  {
    .geometry = &geometry_geom_torus_knot,

    .instance_materials = instance_geometry_instance_materials_node_torus_knot_0,
    .instance_materials_count = 1,
  },
};

instance_controller const instance_controllers_node_torus_knot[] = {
};

instance_light const instance_lights_node_torus_knot[] = {
};

channel const * const node_channels_node_torus_knot[] = {
  &node_channel_node_torus_knot_rotationz_angle,
};

node const node_node_torus_knot = {
  .name = "Torus_Knot",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_torus_knot,
  .transforms_count = 4,

  .instance_geometries = instance_geometries_node_torus_knot,
  .instance_geometries_count = 1,

  .instance_controllers = instance_controllers_node_torus_knot,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_torus_knot,
  .instance_lights_count = 0,

  .channels = node_channels_node_torus_knot,
  .channels_count = 1,
};

transform const transforms_node_directlight_target[] = {
  {
    .type = transform_type::ROTATE,
    .rotate = {-0.5773502f, 0.5773503f, 0.5773503f, -120.0f},
  },
};

instance_geometry const instance_geometries_node_directlight_target[] = {
};

instance_controller const instance_controllers_node_directlight_target[] = {
};

instance_light const instance_lights_node_directlight_target[] = {
};

channel const * const node_channels_node_directlight_target[] = {
};

node const node_node_directlight_target = {
  .name = "DirectLight.Target",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_directlight_target,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_directlight_target,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_directlight_target,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_directlight_target,
  .instance_lights_count = 0,

  .channels = node_channels_node_directlight_target,
  .channels_count = 0,
};

transform const transforms_node_cone[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-70.49181f, -17.80504f, 52.78688f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {1.0f, 0.0f, 0.0f, -89.7081f},
  },
};

instance_material const instance_geometry_instance_materials_node_cone_0[] = {
  {
    .element_index = 0, // an index into mesh.triangles
    .material_index = 4, // an index into materials

    .emission = { .input_set = -1 },
    .ambient = { .input_set = -1 },
    .diffuse = { .input_set = -1 },
    .specular = { .input_set = -1 },
  },
};

instance_geometry const instance_geometries_node_cone[] = {
  {
    .geometry = &geometry_geom_cone,

    .instance_materials = instance_geometry_instance_materials_node_cone_0,
    .instance_materials_count = 1,
  },
};

instance_controller const instance_controllers_node_cone[] = {
};

instance_light const instance_lights_node_cone[] = {
};

channel const * const node_channels_node_cone[] = {
};

node const node_node_cone = {
  .name = "Cone",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_cone,
  .transforms_count = 2,

  .instance_geometries = instance_geometries_node_cone,
  .instance_geometries_count = 1,

  .instance_controllers = instance_controllers_node_cone,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_cone,
  .instance_lights_count = 0,

  .channels = node_channels_node_cone,
  .channels_count = 0,
};

transform const transforms_node_boxwithhole[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {72.78688f, -2.19274e-06f, 50.16393f},
  },
  {
    .type = transform_type::ROTATE,
    .rotate = {-1.0f, 0.0f, 0.0f, -90.0f},
  },
};

instance_material const instance_geometry_instance_materials_node_boxwithhole_0[] = {
  {
    .element_index = 0, // an index into mesh.triangles
    .material_index = 5, // an index into materials

    .emission = { .input_set = -1 },
    .ambient = { .input_set = -1 },
    .diffuse = { .input_set = -1 },
    .specular = { .input_set = -1 },
  },
};

instance_geometry const instance_geometries_node_boxwithhole[] = {
  {
    .geometry = &geometry_geom_boxwithhole,

    .instance_materials = instance_geometry_instance_materials_node_boxwithhole_0,
    .instance_materials_count = 1,
  },
};

instance_controller const instance_controllers_node_boxwithhole[] = {
};

instance_light const instance_lights_node_boxwithhole[] = {
};

channel const * const node_channels_node_boxwithhole[] = {
};

node const node_node_boxwithhole = {
  .name = "BoxWithHole",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_boxwithhole,
  .transforms_count = 2,

  .instance_geometries = instance_geometries_node_boxwithhole,
  .instance_geometries_count = 1,

  .instance_controllers = instance_controllers_node_boxwithhole,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_boxwithhole,
  .instance_lights_count = 0,

  .channels = node_channels_node_boxwithhole,
  .channels_count = 0,
};

transform const transforms_node_lighthelper[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-42.21109f, -40.46347f, 150.0f},
  },
};

instance_geometry const instance_geometries_node_lighthelper[] = {
};

instance_controller const instance_controllers_node_lighthelper[] = {
};

instance_light const instance_lights_node_lighthelper[] = {
};

channel const * const node_channels_node_lighthelper[] = {
  &node_channel_node_lighthelper_translation_x,
  &node_channel_node_lighthelper_translation_z,
  &node_channel_node_lighthelper_translation_y,
};

node const node_node_lighthelper = {
  .name = "LightHelper",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_lighthelper,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_lighthelper,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_lighthelper,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_lighthelper,
  .instance_lights_count = 0,

  .channels = node_channels_node_lighthelper,
  .channels_count = 3,
};

transform const transforms_node_directlight[] = {
  {
    .type = transform_type::MATRIX,
    .matrix = {0.692005f, 0.6702266f, -0.2681891f, -4.146301f, -0.7218927f, 0.6424779f, -0.2570856f, -3.974632f, 0.0f, 0.3715082f, 0.9284297f, 10.48219f, 0.0f, 0.0f, 0.0f, 1.0f},
  },
};

instance_geometry const instance_geometries_node_directlight[] = {
};

instance_controller const instance_controllers_node_directlight[] = {
};

instance_light const instance_lights_node_directlight[] = {
  {
    .light = &light_directlight_light,
  }
};

channel const * const node_channels_node_directlight[] = {
  &node_channel_node_directlight_matrix,
};

node const node_node_directlight = {
  .name = "DirectLight",

  .parent_index = 7,

  .type = node_type::NODE,

  .transforms = transforms_node_directlight,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_directlight,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_directlight,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_directlight,
  .instance_lights_count = 1,

  .channels = node_channels_node_directlight,
  .channels_count = 1,
};

transform const transforms_node_lightindicator[] = {
};

instance_geometry const instance_geometries_node_lightindicator[] = {
};

instance_controller const instance_controllers_node_lightindicator[] = {
};

instance_light const instance_lights_node_lightindicator[] = {
};

channel const * const node_channels_node_lightindicator[] = {
};

node const node_node_lightindicator = {
  .name = "LightIndicator",

  .parent_index = 8,

  .type = node_type::NODE,

  .transforms = transforms_node_lightindicator,
  .transforms_count = 0,

  .instance_geometries = instance_geometries_node_lightindicator,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_lightindicator,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_lightindicator,
  .instance_lights_count = 0,

  .channels = node_channels_node_lightindicator,
  .channels_count = 0,
};

transform const transforms_node_lightindicator_10[] = {
  {
    .type = transform_type::MATRIX,
    .matrix = {1.0f, 0.0f, 0.0f, -8.14603e-07f, 0.0f, 1.0f, 0.0f, -2.18557e-07f, 0.0f, 0.0f, 1.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f},
  },
};

instance_material const instance_geometry_instance_materials_node_lightindicator_10_0[] = {
  {
    .element_index = 0, // an index into mesh.triangles
    .material_index = 6, // an index into materials

    .emission = { .input_set = -1 },
    .ambient = { .input_set = -1 },
    .diffuse = { .input_set = -1 },
    .specular = { .input_set = -1 },
  },
};

instance_geometry const instance_geometries_node_lightindicator_10[] = {
  {
    .geometry = &geometry_geom_lightindicator,

    .instance_materials = instance_geometry_instance_materials_node_lightindicator_10_0,
    .instance_materials_count = 1,
  },
};

instance_controller const instance_controllers_node_lightindicator_10[] = {
};

instance_light const instance_lights_node_lightindicator_10[] = {
};

channel const * const node_channels_node_lightindicator_10[] = {
};

node const node_node_lightindicator_10 = {
  .name = "node-LightIndicator-10",

  .parent_index = 9,

  .type = node_type::NODE,

  .transforms = transforms_node_lightindicator_10,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_lightindicator_10,
  .instance_geometries_count = 1,

  .instance_controllers = instance_controllers_node_lightindicator_10,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_lightindicator_10,
  .instance_lights_count = 0,

  .channels = node_channels_node_lightindicator_10,
  .channels_count = 0,
};

transform const transforms_node_camerahelper[] = {
  {
    .type = transform_type::TRANSLATE,
    .translate = {-57.36452f, 159.98f, 269.2574f},
  },
};

instance_geometry const instance_geometries_node_camerahelper[] = {
};

instance_controller const instance_controllers_node_camerahelper[] = {
};

instance_light const instance_lights_node_camerahelper[] = {
};

channel const * const node_channels_node_camerahelper[] = {
  &node_channel_node_camerahelper_translation_y,
  &node_channel_node_camerahelper_translation_x,
  &node_channel_node_camerahelper_translation_z,
};

node const node_node_camerahelper = {
  .name = "CameraHelper",

  .parent_index = -1,

  .type = node_type::NODE,

  .transforms = transforms_node_camerahelper,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_camerahelper,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_camerahelper,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_camerahelper,
  .instance_lights_count = 0,

  .channels = node_channels_node_camerahelper,
  .channels_count = 3,
};

transform const transforms_node_camera001[] = {
  {
    .type = transform_type::MATRIX,
    .matrix = {-0.9413646f, 0.2284669f, -0.2482645f, -3.604237f, -0.3371616f, -0.6641206f, 0.6672826f, 4.948456f, -0.01242558f, 0.7118617f, 0.7022099f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
  },
};

instance_geometry const instance_geometries_node_camera001[] = {
};

instance_controller const instance_controllers_node_camera001[] = {
};

instance_light const instance_lights_node_camera001[] = {
};

channel const * const node_channels_node_camera001[] = {
  &node_channel_node_camera001_matrix,
};

node const node_node_camera001 = {
  .name = "Camera001",

  .parent_index = 11,

  .type = node_type::NODE,

  .transforms = transforms_node_camera001,
  .transforms_count = 1,

  .instance_geometries = instance_geometries_node_camera001,
  .instance_geometries_count = 0,

  .instance_controllers = instance_controllers_node_camera001,
  .instance_controllers_count = 0,

  .instance_lights = instance_lights_node_camera001,
  .instance_lights_count = 0,

  .channels = node_channels_node_camera001,
  .channels_count = 1,
};

node const * const nodes[] = {
  &node_node_environmentambientlight, // 0
  &node_node_plane, // 1
  &node_node_camera001_target, // 2
  &node_node_torus_knot, // 3
  &node_node_directlight_target, // 4
  &node_node_cone, // 5
  &node_node_boxwithhole, // 6
  &node_node_lighthelper, // 7
  &node_node_directlight, // 8
  &node_node_lightindicator, // 9
  &node_node_lightindicator_10, // 10
  &node_node_camerahelper, // 11
  &node_node_camera001, // 12
};

inputs const inputs_list[] = {
  {
    .elements = input_elements_position_0_3_normal_0_3_texcoord_0_3,
    .elements_count = 3,
  },
};

extern collada::types::descriptor const descriptor;

collada::types::descriptor const descriptor = {
  .nodes = nodes,
  .nodes_count = (sizeof (nodes)) / (sizeof (nodes[0])),

  .inputs_list = inputs_list,
  .inputs_list_count = (sizeof (inputs_list)) / (sizeof (inputs_list[0])),

  .images = images,
  .images_count = (sizeof (images)) / (sizeof (images[0])),

  .materials = materials,
  .materials_count = (sizeof (materials)) / (sizeof (materials[0])),

  .position_normal_texture_buffer = "data/scenes/shadow_test/shadow_test.vtx",
  .joint_weight_buffer = "data/scenes/shadow_test/shadow_test.vjw",
  .index_buffer = "data/scenes/shadow_test/shadow_test.idx",
};

}
