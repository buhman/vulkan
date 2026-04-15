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
  0.7333334,
  1.0,
  1.3,
  1.666667,
  1.9,
  2.333333,
  2.666667,
  2.966667,
  3.333333,
};

float const array_node_camera001_target_translation_x_output_array[] = {
  10.26849,
  45.83029,
  44.00047,
  6.904039,
  45.62367,
  -23.78957,
  -18.07641,
  48.39803,
  -41.5632,
  30.36242,
  10.26849,
};

float const array_node_camera001_target_translation_x_intangent_array[] = {
  -0.3329306, 10.26849,
  0.2223333, 45.83029,
  0.6001334, 45.82846,
  0.9112, 6.904039,
  1.2001, 45.62367,
  1.544567, -23.78957,
  1.8223, -23.78386,
  2.189033, 48.39803,
  2.555667, -41.5632,
  2.866767, 30.36242,
  3.211233, 10.26849,
};

float const array_node_camera001_target_translation_x_outtangent_array[] = {
  0.111, 10.26849,
  0.4665333, 45.83029,
  0.8221334, 42.7818,
  1.0999, 6.904039,
  1.4221, 45.62367,
  1.744367, -23.78957,
  2.0443, -7.476865,
  2.444333, 48.39803,
  2.766567, -41.5632,
  3.088767, 30.36242,
  3.666264, 10.26849,
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
  0.7333334,
  1.0,
  1.3,
  1.666667,
  1.9,
  2.333333,
  2.666667,
  2.966667,
  3.333333,
};

float const array_node_camera001_target_translation_y_output_array[] = {
  7.983534,
  32.69148,
  4.197104,
  27.66198,
  39.99716,
  -51.44068,
  33.49808,
  -14.75031,
  -0.2895107,
  43.32291,
  7.983534,
};

float const array_node_camera001_target_translation_y_intangent_array[] = {
  -0.3329306, 7.983534,
  0.2223333, 32.69148,
  0.6001334, 4.197104,
  0.9112, 22.0519,
  1.2001, 39.99716,
  1.544567, -51.44068,
  1.8223, 33.49808,
  2.189033, -14.75031,
  2.555667, -10.4676,
  2.866767, 43.32291,
  3.211233, 7.983534,
};

float const array_node_camera001_target_translation_y_outtangent_array[] = {
  0.111, 7.983534,
  0.4665333, 32.69148,
  0.8221334, 4.197104,
  1.0999, 33.97332,
  1.4221, 39.99716,
  1.744367, -51.44068,
  2.0443, 33.49808,
  2.444333, -14.75031,
  2.766567, 8.870774,
  3.088767, 43.32291,
  3.666264, 7.983534,
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
  0.7333334,
  1.0,
  1.3,
  1.9,
  2.333333,
  2.666667,
  2.966667,
  3.333333,
};

float const array_node_camera001_target_translation_z_output_array[] = {
  43.74428,
  43.74428,
  43.74428,
  43.74428,
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
  0.6001334, 43.74428,
  0.9112, 43.74428,
  1.2001, 43.74428,
  1.7002, 43.74428,
  2.189033, 43.74428,
  2.555667, 43.74428,
  2.866767, 43.74428,
  3.211233, 43.74428,
};

float const array_node_camera001_target_translation_z_outtangent_array[] = {
  0.111, 43.74428,
  0.4665333, 43.74428,
  0.8221334, 43.74428,
  1.0999, 43.74428,
  1.4998, 43.74428,
  2.0443, 43.74428,
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
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
  100.0,
};

float const array_node_lighthelper_translation_z_intangent_array[] = {
  -0.3329306, 100.0,
  0.1556333, 100.0,
  0.3667333, 100.0,
  0.5667334, 100.0,
  0.7667333, 100.0,
  0.9889667, 100.0,
  1.200067, 100.0,
  1.400067, 100.0,
  1.600067, 100.0,
  1.8223, 100.0,
  2.0334, 100.0,
  2.2334, 100.0,
  2.4334, 100.0,
  2.655633, 100.0,
  2.866733, 100.0,
  3.066733, 100.0,
  3.266733, 100.0,
};

float const array_node_lighthelper_translation_z_outtangent_array[] = {
  0.0777, 100.0,
  0.2999333, 100.0,
  0.4999333, 100.0,
  0.6999334, 100.0,
  0.9110333, 100.0,
  1.133267, 100.0,
  1.333267, 100.0,
  1.533267, 100.0,
  1.744367, 100.0,
  1.9666, 100.0,
  2.1666, 100.0,
  2.3666, 100.0,
  2.5777, 100.0,
  2.799933, 100.0,
  2.999933, 100.0,
  3.199933, 100.0,
  3.666264, 100.0,
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
  0.692005, 0.6241241, -0.3627647, -4.146301, -0.7218927, 0.5982842, -0.3477455, -3.974632, 0.0, 0.5025188, 0.8645663, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6247931, 0.6877698, -0.3696029, -4.146301, -0.7807903, 0.5503575, -0.2957584, -3.974632, 0.0, 0.4733701, 0.8808636, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.3647357, 0.8488983, -0.3825435, -4.146301, -0.9311111, 0.3325312, -0.1498503, -3.974632, 0.0, 0.4108462, 0.9117047, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.1645458, 0.9076589, -0.3861088, -4.146301, -0.9863694, -0.1514154, 0.0644105, -3.974632, 0.0, 0.3914444, 0.9202018, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.6127588, 0.6979875, -0.3705943, -4.146301, -0.79027, -0.5412048, 0.2873511, -3.974632, 0.0, 0.4689465, 0.8832266, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8001266, 0.4915125, -0.3438209, -4.146301, -0.5998311, -0.6556383, 0.4586295, -3.974632, 0.0, 0.5731962, 0.8194182, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.867311, 0.3805892, -0.3208169, -4.146301, -0.4977666, -0.6631404, 0.558993, -3.974632, 0.0, 0.6445127, 0.7645936, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8849987, 0.3458669, -0.3116943, -4.146301, -0.4655935, -0.6574229, 0.5924676, -3.974632, 0.0, 0.6694558, 0.7428519, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9131027, 0.3070821, -0.2682238, -4.146301, -0.4077296, -0.6877046, 0.6006821, -3.974632, 0.0, 0.6578472, 0.7531514, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9713711, 0.1836072, -0.1507533, -4.146301, -0.2375672, -0.7507381, 0.6164042, -3.974632, 0.0, 0.6345713, 0.7728644, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.999695, -0.01930654, 0.01540279, -4.146301, 0.02469789, -0.781468, 0.6234564, -3.974632, 0.0, 0.6236466, 0.7817065, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9561786, -0.2248371, 0.1875389, -4.146301, 0.2927841, -0.7342762, 0.6124671, -3.974632, 0.0, 0.6405364, 0.7679278, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.878125, -0.3541585, 0.3216649, -4.146301, 0.4784314, -0.6500314, 0.5903919, -3.974632, 0.0, 0.6723325, 0.7402493, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8248081, -0.4064652, 0.3930365, -4.146301, 0.5654128, -0.5929399, 0.5733504, -3.974632, 0.0, 0.6951319, 0.7188822, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.7561108, -0.4838564, 0.4406579, -4.146301, 0.6544436, -0.5590231, 0.5091137, -3.974632, 0.0, 0.6733321, 0.7393402, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.5518118, -0.6658029, 0.5022054, -4.146301, 0.8339687, -0.4405416, 0.3322941, -3.974632, 0.0, 0.6021874, 0.7983548, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.09527927, -0.8338454, 0.5437129, -4.146301, 0.9954506, -0.07981127, 0.05204129, -3.974632, 0.0, 0.5461977, 0.8376563, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.4048784, -0.7416463, 0.5348218, -4.146301, 0.9143705, 0.328397, -0.2368162, -3.974634, 0.0, 0.584907, 0.8111004, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6480864, -0.5743325, 0.5001262, -4.146301, 0.7615668, 0.4887517, -0.4256029, -3.974632, 0.0, 0.6567069, 0.7541459, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7121619, -0.5101218, 0.4822875, -4.146301, 0.7020152, 0.5174949, -0.4892583, -3.974632, 0.0, 0.6870043, 0.7266533, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7536112, -0.4915915, 0.4363577, -4.146301, 0.6573205, 0.5636045, -0.5002796, -3.974632, 0.0, 0.6638432, 0.7478718, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8627668, -0.4030795, 0.3052218, -4.146301, 0.5056021, 0.6878208, -0.520835, -3.974632, 0.0, 0.6036799, 0.7972268, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9813205, -0.1624428, 0.1030651, -4.146301, 0.1923801, 0.828612, -0.52573, -3.974632, 0.0, 0.5357373, 0.8443847, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9719243, 0.2026844, -0.1195081, -4.146301, -0.2352938, 0.8372253, -0.4936503, -3.974632, 0.0, 0.5079103, 0.86141, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8278828, 0.4799063, -0.2903447, -4.146301, -0.5609012, 0.7083354, -0.428545, -3.974632, 0.0, 0.5176398, 0.8555987, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.692005, 0.6241241, -0.3627647, -4.146301, -0.7218927, 0.5982842, -0.3477455, -3.974632, 0.0, 0.5025188, 0.8645663, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.515815, 0.7693762, -0.3768224, -4.146301, -0.8567, 0.4632378, -0.2268829, -3.974632, 0.0, 0.4398533, 0.8980696, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.1157832, 0.9149847, -0.3865193, -4.146301, -0.9932745, 0.1066572, -0.04505544, -3.974632, 0.0, 0.3891364, 0.9211801, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.3957774, 0.8352898, -0.3816429, -4.146301, -0.9183465, -0.3599826, 0.1644756, -3.974632, 0.0, 0.4155762, 0.9095584, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.6975451, 0.6183276, -0.3620798, -4.146301, -0.7165409, -0.6019355, 0.352481, -3.974632, 0.0, 0.5053164, 0.8629342, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8221068, 0.4583134, -0.3377711, -4.146301, -0.5693334, -0.661796, 0.4877352, -3.974632, 0.0, 0.5932748, 0.805, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8712977, 0.373005, -0.3189163, -4.146301, -0.4907549, -0.6622418, 0.5662114, -3.974632, 0.0, 0.6498484, 0.7600638, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8849987, 0.3458669, -0.3116943, -4.146301, -0.4655935, -0.6574229, 0.5924676, -3.974632, 0.0, 0.6694558, 0.7428519, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9131027, 0.3070821, -0.2682238, -4.146301, -0.4077296, -0.6877046, 0.6006821, -3.974632, 0.0, 0.6578472, 0.7531514, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9713711, 0.1836072, -0.1507533, -4.146301, -0.2375672, -0.7507381, 0.6164042, -3.974632, 0.0, 0.6345713, 0.7728644, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.999695, -0.01930654, 0.01540279, -4.146301, 0.02469789, -0.781468, 0.6234564, -3.974632, 0.0, 0.6236466, 0.7817065, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9561786, -0.2248371, 0.1875389, -4.146301, 0.2927841, -0.7342762, 0.6124671, -3.974632, 0.0, 0.6405364, 0.7679278, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.878125, -0.3541585, 0.3216649, -4.146301, 0.4784314, -0.6500314, 0.5903919, -3.974632, 0.0, 0.6723325, 0.7402493, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8248081, -0.4064652, 0.3930365, -4.146301, 0.5654128, -0.5929399, 0.5733504, -3.974632, 0.0, 0.6951319, 0.7188822, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.7561108, -0.4838564, 0.4406579, -4.146301, 0.6544436, -0.5590231, 0.5091137, -3.974632, 0.0, 0.6733321, 0.7393402, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.5518118, -0.6658029, 0.5022054, -4.146301, 0.8339687, -0.4405416, 0.3322941, -3.974632, 0.0, 0.6021874, 0.7983548, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.09527927, -0.8338454, 0.5437129, -4.146301, 0.9954506, -0.07981127, 0.05204129, -3.974632, 0.0, 0.5461977, 0.8376563, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.4048784, -0.7416463, 0.5348218, -4.146301, 0.9143705, 0.328397, -0.2368162, -3.974634, 0.0, 0.584907, 0.8111004, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6480864, -0.5743325, 0.5001262, -4.146301, 0.7615668, 0.4887517, -0.4256029, -3.974632, 0.0, 0.6567069, 0.7541459, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7121619, -0.5101218, 0.4822875, -4.146301, 0.7020152, 0.5174949, -0.4892583, -3.974632, 0.0, 0.6870043, 0.7266533, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7536112, -0.4915915, 0.4363577, -4.146301, 0.6573205, 0.5636045, -0.5002796, -3.974632, 0.0, 0.6638432, 0.7478718, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8627668, -0.4030795, 0.3052218, -4.146301, 0.5056021, 0.6878208, -0.520835, -3.974632, 0.0, 0.6036799, 0.7972268, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9813205, -0.1624428, 0.1030651, -4.146301, 0.1923801, 0.828612, -0.52573, -3.974632, 0.0, 0.5357373, 0.8443847, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9719243, 0.2026844, -0.1195081, -4.146301, -0.2352938, 0.8372253, -0.4936503, -3.974632, 0.0, 0.5079103, 0.86141, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8278828, 0.4799063, -0.2903447, -4.146301, -0.5609012, 0.7083354, -0.428545, -3.974632, 0.0, 0.5176398, 0.8555987, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.692005, 0.6241241, -0.3627647, -4.146301, -0.7218927, 0.5982842, -0.3477455, -3.974632, 0.0, 0.5025188, 0.8645663, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.5158147, 0.7693764, -0.3768224, -4.146301, -0.8567002, 0.4632375, -0.2268828, -3.974632, 0.0, 0.4398533, 0.8980696, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.1157825, 0.9149848, -0.3865193, -4.146301, -0.9932746, 0.1066566, -0.04505521, -3.974632, 0.0, 0.3891364, 0.9211801, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.3957779, 0.8352895, -0.3816429, -4.146301, -0.9183463, -0.359983, 0.1644759, -3.974632, 0.0, 0.4155763, 0.9095584, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.6975454, 0.6183274, -0.3620798, -4.146301, -0.7165406, -0.6019357, 0.3524811, -3.974632, 0.0, 0.5053165, 0.8629341, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8221068, 0.4583133, -0.3377711, -4.146301, -0.5693333, -0.661796, 0.4877353, -3.974632, 0.0, 0.5932748, 0.805, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8712977, 0.373005, -0.3189163, -4.146301, -0.4907549, -0.6622418, 0.5662114, -3.974632, 0.0, 0.6498484, 0.7600638, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8849987, 0.3458669, -0.3116943, -4.146301, -0.4655935, -0.6574229, 0.5924676, -3.974632, 0.0, 0.6694558, 0.7428519, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9131027, 0.3070821, -0.2682238, -4.146301, -0.4077296, -0.6877046, 0.6006821, -3.974632, 0.0, 0.6578472, 0.7531514, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9713711, 0.1836072, -0.1507533, -4.146301, -0.2375672, -0.7507381, 0.6164042, -3.974632, 0.0, 0.6345713, 0.7728644, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.999695, -0.01930654, 0.01540279, -4.146301, 0.02469789, -0.781468, 0.6234564, -3.974632, 0.0, 0.6236466, 0.7817065, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9561786, -0.2248371, 0.1875389, -4.146301, 0.2927841, -0.7342762, 0.6124671, -3.974632, 0.0, 0.6405364, 0.7679278, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.878125, -0.3541585, 0.3216649, -4.146301, 0.4784314, -0.6500314, 0.5903919, -3.974632, 0.0, 0.6723325, 0.7402493, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8248081, -0.4064652, 0.3930365, -4.146301, 0.5654128, -0.5929399, 0.5733504, -3.974632, 0.0, 0.6951319, 0.7188822, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.7561108, -0.4838564, 0.4406579, -4.146301, 0.6544436, -0.5590231, 0.5091137, -3.974632, 0.0, 0.6733321, 0.7393402, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.5518118, -0.6658029, 0.5022054, -4.146301, 0.8339687, -0.4405416, 0.3322941, -3.974632, 0.0, 0.6021874, 0.7983548, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.09527927, -0.8338454, 0.5437129, -4.146301, 0.9954506, -0.07981127, 0.05204129, -3.974632, 0.0, 0.5461977, 0.8376563, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.4048784, -0.7416463, 0.5348218, -4.146301, 0.9143705, 0.328397, -0.2368162, -3.974634, 0.0, 0.584907, 0.8111004, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6480864, -0.5743325, 0.5001262, -4.146301, 0.7615668, 0.4887517, -0.4256029, -3.974632, 0.0, 0.6567069, 0.7541459, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7121619, -0.5101218, 0.4822875, -4.146301, 0.7020152, 0.5174949, -0.4892583, -3.974632, 0.0, 0.6870043, 0.7266533, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7536112, -0.4915915, 0.4363577, -4.146301, 0.6573205, 0.5636045, -0.5002796, -3.974632, 0.0, 0.6638432, 0.7478718, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8627668, -0.4030795, 0.3052218, -4.146301, 0.5056021, 0.6878208, -0.520835, -3.974632, 0.0, 0.6036799, 0.7972268, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9813205, -0.1624428, 0.1030651, -4.146301, 0.1923801, 0.828612, -0.52573, -3.974632, 0.0, 0.5357373, 0.8443847, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9719243, 0.2026844, -0.1195081, -4.146301, -0.2352938, 0.8372253, -0.4936503, -3.974632, 0.0, 0.5079103, 0.86141, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8278828, 0.4799063, -0.2903447, -4.146301, -0.5609012, 0.7083354, -0.428545, -3.974632, 0.0, 0.5176398, 0.8555987, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.692005, 0.6241241, -0.3627647, -4.146301, -0.7218927, 0.5982842, -0.3477455, -3.974632, 0.0, 0.5025188, 0.8645663, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.5158147, 0.7693764, -0.3768224, -4.146301, -0.8567002, 0.4632375, -0.2268828, -3.974632, 0.0, 0.4398533, 0.8980696, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.1157825, 0.9149848, -0.3865193, -4.146301, -0.9932746, 0.1066566, -0.04505521, -3.974632, 0.0, 0.3891364, 0.9211801, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.3957779, 0.8352895, -0.3816429, -4.146301, -0.9183463, -0.359983, 0.1644759, -3.974632, 0.0, 0.4155763, 0.9095584, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.6975454, 0.6183274, -0.3620798, -4.146301, -0.7165406, -0.6019357, 0.3524811, -3.974632, 0.0, 0.5053165, 0.8629341, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8221068, 0.4583133, -0.3377711, -4.146301, -0.5693333, -0.661796, 0.4877353, -3.974632, 0.0, 0.5932748, 0.805, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8712977, 0.373005, -0.3189163, -4.146301, -0.4907549, -0.6622418, 0.5662114, -3.974632, 0.0, 0.6498484, 0.7600638, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8849987, 0.3458669, -0.3116943, -4.146301, -0.4655935, -0.6574229, 0.5924676, -3.974632, 0.0, 0.6694558, 0.7428519, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9131027, 0.3070821, -0.2682238, -4.146301, -0.4077296, -0.6877046, 0.6006821, -3.974632, 0.0, 0.6578472, 0.7531514, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9713711, 0.1836072, -0.1507533, -4.146301, -0.2375672, -0.7507381, 0.6164042, -3.974632, 0.0, 0.6345713, 0.7728644, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.999695, -0.01930654, 0.01540279, -4.146301, 0.02469789, -0.781468, 0.6234564, -3.974632, 0.0, 0.6236466, 0.7817065, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.9561786, -0.2248371, 0.1875389, -4.146301, 0.2927841, -0.7342762, 0.6124671, -3.974632, 0.0, 0.6405364, 0.7679278, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.878125, -0.3541585, 0.3216649, -4.146301, 0.4784314, -0.6500314, 0.5903919, -3.974632, 0.0, 0.6723325, 0.7402493, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.8248081, -0.4064652, 0.3930365, -4.146301, 0.5654128, -0.5929399, 0.5733504, -3.974632, 0.0, 0.6951319, 0.7188822, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.7561108, -0.4838564, 0.4406579, -4.146301, 0.6544436, -0.5590231, 0.5091137, -3.974632, 0.0, 0.6733321, 0.7393402, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.5518118, -0.6658029, 0.5022054, -4.146301, 0.8339687, -0.4405416, 0.3322941, -3.974632, 0.0, 0.6021874, 0.7983548, 10.48219, 0.0, 0.0, 0.0, 1.0,
  -0.09527927, -0.8338454, 0.5437129, -4.146301, 0.9954506, -0.07981127, 0.05204129, -3.974632, 0.0, 0.5461977, 0.8376563, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.4048784, -0.7416463, 0.5348218, -4.146301, 0.9143705, 0.328397, -0.2368162, -3.974634, 0.0, 0.584907, 0.8111004, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.6480864, -0.5743325, 0.5001262, -4.146301, 0.7615668, 0.4887517, -0.4256029, -3.974632, 0.0, 0.6567069, 0.7541459, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7121619, -0.5101218, 0.4822875, -4.146301, 0.7020152, 0.5174949, -0.4892583, -3.974632, 0.0, 0.6870043, 0.7266533, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7458067, -0.5011244, 0.4389154, -4.146301, 0.6661624, 0.5610372, -0.4913908, -3.974632, 0.0, 0.6588715, 0.7522555, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.8442236, -0.4361525, 0.3115404, -4.146301, 0.5359911, 0.6869708, -0.490698, -3.974632, 0.0, 0.5812419, 0.8137309, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9751951, -0.1938297, 0.1068854, -4.146301, 0.2213469, 0.8539617, -0.4709086, -3.974632, 0.0, 0.4828866, 0.8756829, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.9594948, 0.2527427, -0.1244624, -4.146301, -0.2817265, 0.8607829, -0.4238902, -3.974632, 0.0, 0.4417848, 0.897121, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.7795101, 0.5507601, -0.2983745, -4.146301, -0.6263897, 0.6853929, -0.3713119, -3.974632, 0.0, 0.4763401, 0.8792611, 10.48219, 0.0, 0.0, 0.0, 1.0,
  0.692005, 0.6241241, -0.3627647, -4.146301, -0.7218927, 0.5982842, -0.3477455, -3.974632, 0.0, 0.5025188, 0.8645663, 10.48219, 0.0, 0.0, 0.0, 1.0,
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
  -0.9161802, 0.3124457, -0.2509807, -3.604237, -0.4006261, -0.7305838, 0.5529431, 4.948456, -0.0105977, 0.6071451, 0.7945203, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9119079, 0.3204501, -0.2563896, -3.604237, -0.4102582, -0.7279188, 0.5493836, 4.948456, -0.01058077, 0.6061733, 0.7952622, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8993864, 0.3427151, -0.2713862, -3.604237, -0.4370275, -0.7198479, 0.5392829, 4.948456, -0.01053631, 0.603627, 0.7971973, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8784992, 0.3764929, -0.2940955, -3.604237, -0.4776287, -0.7056486, 0.5233843, 4.948456, -0.01047754, 0.6002611, 0.7997355, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8489218, 0.418663, -0.3225724, -3.604233, -0.5284156, -0.6843712, 0.5024072, 4.948456, -0.0104199, 0.5969567, 0.8022058, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8107447, 0.4656336, -0.3547934, -3.60424, -0.5853078, -0.6555184, 0.4771901, 4.948456, -0.01037776, 0.5945428, 0.803997, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.7649714, 0.5135495, -0.3886975, -3.604233, -0.6439808, -0.6195859, 0.4487784, 4.948456, -0.01036161, 0.5936165, 0.8046815, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.7137414, 0.5588009, -0.4222734, -3.604233, -0.7003324, -0.5783058, 0.4184459, 4.948456, -0.01037514, 0.594394, 0.804107, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.6601804, 0.5986251, -0.4536626, -3.60424, -0.7510347, -0.5344815, 0.3876549, 4.948456, -0.01041436, 0.5966386, 0.8024424, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.607953, 0.631506, -0.4812415, -3.60424, -0.7939039, -0.4914994, 0.3579733, 4.948456, -0.01046758, 0.5996906, 0.8001636, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.5607551, 0.6571883, -0.5036441, -3.604233, -0.8279148, -0.4527755, 0.3309853, 4.948456, -0.01051795, 0.6025761, 0.7979921, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.5181024, 0.676968, -0.5227659, -3.604233, -0.8552531, -0.4175962, 0.3068475, 4.948456, -0.01057904, 0.6060757, 0.7953367, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.4774761, 0.6921888, -0.5411942, -3.60424, -0.8785798, -0.3836042, 0.2845085, 4.948456, -0.01067072, 0.6113284, 0.791305, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.4390698, 0.7035406, -0.5587918, -3.60424, -0.8983881, -0.3512571, 0.263661, 4.948456, -0.01078331, 0.6177776, 0.7862789, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.4027898, 0.7117743, -0.5754458, -3.60424, -0.9152274, -0.3206986, 0.2439489, 4.948456, -0.01090806, 0.624924, 0.7806094, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.3683196, 0.717624, -0.5910639, -3.60424, -0.9296336, -0.2918294, 0.2249817, 4.948456, -0.01103746, 0.6323381, 0.7746139, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.3351812, 0.7217615, -0.605569, -3.604233, -0.9420874, -0.2643736, 0.2063438, 4.948456, -0.01116532, 0.6396616, 0.7685756, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.302785, 0.7247701, -0.6188939, -3.604233, -0.9529919, -0.2379322, 0.1876019, 4.948456, -0.01128649, 0.6466041, 0.7627423, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.2704617, 0.7271335, -0.6309733, -3.604233, -0.9626631, -0.2120195, 0.1683069, 4.948456, -0.011397, 0.6529356, 0.7573276, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.2374812, 0.7292309, -0.6417359, -3.604233, -0.971324, -0.1860832, 0.1479949, 4.948456, -0.0114938, 0.6584796, 0.7525107, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.2030581, 0.7313307, -0.6510935, -3.604233, -0.9790982, -0.1595119, 0.1261844, 4.948456, -0.01157456, 0.6631074, 0.7484347, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.1663501, 0.733579, -0.6589305, -3.604233, -0.985998, -0.1316335, 0.102374, 4.948456, -0.01163786, 0.6667342, 0.7452047, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.1264517, 0.7359793, -0.6650898, -3.604233, -0.9919039, -0.101709, 0.07603824, 4.948456, -0.01168298, 0.6693204, 0.7428821, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.08218365, 0.7407522, -0.6667324, -3.604233, -0.9965488, -0.06890982, 0.04627776, 4.948456, -0.01166403, 0.6682348, 0.7438589, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.03261369, 0.7489376, -0.6618375, -3.604233, -0.9994011, -0.03209125, 0.01293343, 4.948456, -0.01155281, 0.6618631, 0.7495357, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.02252811, 0.7585098, -0.6512722, -3.604233, -0.9996814, 0.009679973, -0.02330601, 4.948456, -0.01137351, 0.6515899, 0.7584862, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.08605819, 0.7669948, -0.6358561, -3.604233, -0.9962276, 0.05910354, -0.06353867, 4.948456, -0.01115244, 0.6389254, 0.7691878, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.1598325, 0.7708566, -0.616631, -3.604233, -0.9870836, 0.1178904, -0.108479, 4.948456, -0.0109269, 0.6260049, 0.7797425, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.2406767, 0.7667248, -0.5951538, -3.604233, -0.9705458, 0.1833253, -0.1563088, 4.948456, -0.01073908, 0.615244, 0.7882637, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.3230913, 0.7527348, -0.5735872, -3.604233, -0.946308, 0.2501612, -0.2047446, 4.948456, -0.01062905, 0.6089414, 0.793144, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.3998981, 0.7296865, -0.5546522, -3.604233, -0.9164979, 0.3113273, -0.2512106, 4.948456, -0.01062655, 0.6087964, 0.7932554, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.4678032, 0.6998164, -0.5398306, -3.604233, -0.8837673, 0.3629567, -0.2953264, 4.948456, -0.01073902, 0.6152393, 0.7882672, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.5276291, 0.6655545, -0.527868, -3.604233, -0.8494043, 0.4053558, -0.3379333, 4.948456, -0.01093864, 0.626677, 0.7792024, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.5793417, 0.6296618, -0.5175802, -3.604233, -0.8150079, 0.4387877, -0.3784539, 4.948456, -0.01119017, 0.6410861, 0.7673873, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.6240454, 0.5939434, -0.5077386, -3.604233, -0.7813038, 0.4647623, -0.4166056, 4.948456, -0.01146233, 0.6566791, 0.754083, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.6633595, 0.5593, -0.4971293, -3.604233, -0.7482088, 0.4853376, -0.4523617, 4.948456, -0.01173037, 0.6720351, 0.7404264, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.6990041, 0.5259217, -0.4845614, -3.604233, -0.7150173, 0.5026513, -0.4858928, 4.948456, -0.01197606, 0.686111, 0.7273984, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.7325901, 0.4934588, -0.4688392, -3.60424, -0.680561, 0.5186813, -0.5175003, 4.948456, -0.01218688, 0.6981893, 0.7158095, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.7655337, 0.461111, -0.4487033, -3.60424, -0.643277, 0.5351524, -0.547546, 4.948456, -0.01235473, 0.7078055, 0.7062993, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.7990155, 0.427617, -0.4227504, -3.60424, -0.6011809, 0.5535055, -0.5763792, 4.948456, -0.01247483, 0.7146856, 0.6993347, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8315851, 0.3949224, -0.3905156, -3.60424, -0.5552564, 0.5753316, -0.6005695, 4.948456, -0.01250237, 0.7162612, 0.6977204, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8621544, 0.3637292, -0.3526906, -3.604233, -0.5064933, 0.6017152, -0.6175785, 4.948456, -0.01241195, 0.7110836, 0.7029979, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8915472, 0.3308041, -0.3093737, -3.604237, -0.4527626, 0.6324842, -0.6284662, 4.948456, -0.01222515, 0.7003802, 0.7136653, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9197963, 0.2931916, -0.2607935, -3.604237, -0.3922135, 0.6666776, -0.6338055, 4.948456, -0.01196122, 0.6852589, 0.7282014, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.946171, 0.2483506, -0.2075626, -3.604237, -0.3234574, 0.7024635, -0.6339719, 4.948456, -0.01164221, 0.6669836, 0.7449814, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9691941, 0.194659, -0.1508991, -3.604237, -0.2460387, 0.7370873, -0.6294183, 4.948456, -0.01129609, 0.6471555, 0.7622743, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9868657, 0.1322504, -0.09276747, -3.604237, -0.1611704, 0.7671081, -0.6209423, 4.948456, -0.01095718, 0.6277382, 0.7783474, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9973116, 0.06389546, -0.03587043, -3.604237, -0.07249569, 0.7891541, -0.6099019, 4.948456, -0.01066261, 0.6108629, 0.7916647, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9998521, -0.004690825, 0.01654154, -3.604237, 0.01365691, 0.8011546, -0.5983017, 4.948456, -0.01044577, 0.5984392, 0.8011001, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9959732, -0.06570088, 0.06099665, -3.604237, 0.08905339, 0.8034353, -0.5886946, 4.948456, -0.01032912, 0.5917561, 0.806051, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9893406, -0.1110978, 0.09413933, -3.604237, 0.1452528, 0.7987277, -0.5838972, 4.948456, -0.01032197, 0.5913473, 0.806351, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9824119, -0.142403, 0.1207817, -3.604237, 0.1864292, 0.7845152, -0.591422, 4.948456, -0.01053476, 0.6035373, 0.7972651, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9753356, -0.1646995, 0.1469501, -3.604237, 0.2204537, 0.7599678, -0.611432, 4.948456, -0.01097476, 0.6287471, 0.7775323, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9686361, -0.1794595, 0.171867, -3.604237, 0.2482173, 0.7308164, -0.6358425, 4.948456, -0.01149517, 0.6585604, 0.75244, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9620499, -0.1903357, 0.1955304, -3.604237, 0.2726101, 0.7018686, -0.6580762, 4.948456, -0.01198124, 0.6864057, 0.7271201, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9547756, -0.2014623, 0.2186694, -3.604237, 0.2970702, 0.6769416, -0.6734237, 4.948456, -0.01235693, 0.7079288, 0.7061758, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9455171, -0.2171095, 0.242612, -3.604237, 0.3253291, 0.6588298, -0.6783098, 4.948456, -0.01257252, 0.7202825, 0.6935669, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.932067, -0.2424501, 0.2692005, -3.604233, 0.3620671, 0.6491954, -0.6689192, 4.948456, -0.01258414, 0.7209462, 0.6928768, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.9142426, -0.2758653, 0.2967467, -3.604233, 0.4049757, 0.6446804, -0.6483685, 4.948456, -0.01244437, 0.7129414, 0.7011132, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8937162, -0.3119277, 0.3224474, -3.604233, 0.4484654, 0.6407734, -0.6231279, 4.948456, -0.01224482, 0.701506, 0.7125583, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.869557, -0.3516302, 0.3467371, -3.604233, 0.4936867, 0.6360273, -0.5930789, 4.948456, -0.01198977, 0.6868956, 0.7266573, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8405691, -0.3957399, 0.3699099, -3.60424, 0.5415781, 0.6286622, -0.5581012, 4.948456, -0.01168537, 0.6694579, 0.7427581, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.8052793, -0.4446921, 0.3921403, -3.604233, 0.592787, 0.6165282, -0.5181666, 4.948456, -0.01134097, 0.6497246, 0.7600852, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.7619869, -0.4983866, 0.4135054, -3.604233, 0.6474995, 0.5971573, -0.4734422, 4.948456, -0.01097047, 0.6285014, 0.7777311, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.7089508, -0.5558956, 0.4340149, -3.604233, 0.7051783, 0.5679876, -0.424398, 4.948456, -0.01059406, 0.6069352, 0.7946807, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.6448128, -0.6151556, 0.453652, -3.604233, 0.7642719, 0.5268606, -0.3718956, 4.948456, -0.01023763, 0.5865166, 0.8098725, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.5693041, -0.6728338, 0.4724273, -3.604233, 0.8220669, 0.4728298, -0.3172347, 4.948456, -0.009931385, 0.5689699, 0.8222983, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.4840977, -0.7246547, 0.4904335, -3.604233, 0.87496, 0.407104, -0.2621281, 4.948456, -0.009705066, 0.5560054, 0.8311221, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.3933539, -0.7663686, 0.5078896, -3.604233, 0.919337, 0.3336259, -0.2085976, 4.948456, -0.00958234, 0.5489745, 0.8357841, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.3033766, -0.7950932, 0.5251565, -3.604233, 0.9528225, 0.2586686, -0.1588069, 4.948456, -0.009575128, 0.5485593, 0.8360568, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.2212487, -0.8102531, 0.5427145, -3.604233, 0.9751693, 0.1893387, -0.1148719, 4.948456, -0.009681463, 0.5546538, 0.8320249, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.146956, -0.8119571, 0.5649155, -3.604233, 0.989093, 0.1263689, -0.07566976, 4.948456, -0.00994718, 0.5698743, 0.8216717, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.08091598, -0.8011724, 0.5929381, -3.604233, 0.9966669, 0.07122761, -0.03976935, 4.948456, -0.01037138, 0.5941798, 0.8042654, 0.0, 0.0, 0.0, 0.0, 1.0,
  0.02694064, -0.7818443, 0.6228915, -3.604233, 0.9995778, 0.02784669, -0.00827986, 4.948456, -0.01087188, 0.6228516, 0.7822644, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.01473271, -0.758354, 0.6516764, -3.604233, 0.9998266, -0.00375688, 0.01823163, 4.948456, -0.01137775, 0.6518321, 0.7582779, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.04566806, -0.7344506, 0.6771239, -3.604233, 0.9988864, -0.0255413, 0.03966546, 4.948456, -0.01183766, 0.6781815, 0.7347991, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.07085967, -0.7136773, 0.6968814, -3.604233, 0.9974116, -0.04214644, 0.05825567, 4.948456, -0.01220464, 0.6992056, 0.7148165, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.09480351, -0.6982647, 0.7095342, -3.604233, 0.995418, -0.05757516, 0.07634085, 4.948456, -0.0124545, 0.7135207, 0.7005235, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.1188374, -0.6891729, 0.7147855, -3.604233, 0.9928339, -0.07335454, 0.09433865, 4.948456, -0.01258289, 0.7208744, 0.6929516, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.1445087, -0.6872667, 0.711886, -3.604233, 0.9894234, -0.09121561, 0.1127862, 4.948456, -0.01257908, 0.7206555, 0.6931793, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.1738897, -0.6933736, 0.6992822, -3.604233, 0.9846867, -0.1134696, 0.1323501, 4.948456, -0.01242077, 0.7115883, 0.7024869, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.2067981, -0.7082352, 0.6750092, -3.604233, 0.978309, -0.1411721, 0.1515972, 4.948456, -0.01207393, 0.6917178, 0.722067, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.2438289, -0.7302294, 0.6382102, -3.604233, 0.9697498, -0.1757596, 0.1693927, 4.948456, -0.0115239, 0.6602073, 0.750995, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.2896261, -0.7554419, 0.587728, -3.604233, 0.9570793, -0.2216742, 0.1867073, 4.948452, -0.01076239, 0.6165777, 0.7872204, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.3505112, -0.777211, 0.5225754, -3.604233, 0.9365072, -0.285025, 0.2042419, 4.948456, -0.00979197, 0.5609849, 0.8277682, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.4351676, -0.783798, 0.4430462, -3.60424, 0.9003078, -0.3740881, 0.2224946, 4.948456, -0.008652448, 0.4957005, 0.8684505, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.5532059, -0.7550135, 0.3520199, -3.604233, 0.8330111, -0.497586, 0.2418687, 4.948456, -0.007453978, 0.4270398, 0.9042022, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.7052652, -0.6611884, 0.2557946, -3.60424, 0.7089146, -0.6544731, 0.2628782, 4.948456, -0.00640136, 0.3667355, 0.9303032, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.8600573, -0.4832669, 0.1635679, -3.60424, 0.5101648, -0.8109909, 0.2864012, 4.948456, -0.00575608, 0.329768, 0.9440445, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9603514, -0.265361, 0.08549082, -3.604237, 0.2787344, -0.9076519, 0.3138075, 4.948456, -0.005676269, 0.3251947, 0.94563, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9970927, -0.07335954, 0.02060073, -3.604237, 0.07595819, -0.9355515, 0.3449259, 4.948456, -0.006030499, 0.345488, 0.9384039, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9965335, 0.0742411, -0.03753906, -3.604237, -0.08292853, -0.9223841, 0.3772671, 4.948456, -0.006616711, 0.3790724, 0.9253434, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9807798, 0.1740847, -0.08812129, -3.604237, -0.1949806, -0.891353, 0.409234, 4.948456, -0.0073058, 0.4185505, 0.9081641, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9626802, 0.2368741, -0.1309093, -3.604237, -0.2705226, -0.8565071, 0.4395602, 4.948456, -0.008004307, 0.4585699, 0.8886222, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9471744, 0.2743482, -0.1661131, -3.604237, -0.3206019, -0.8239123, 0.4673148, 4.948456, -0.008655667, 0.4958849, 0.8683451, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9353998, 0.2954651, -0.1942359, -3.604235, -0.3534713, -0.7957015, 0.4918509, 4.948456, -0.009229063, 0.5287341, 0.8487374, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9270946, 0.3063819, -0.2159291, -3.604237, -0.3747012, -0.7724714, 0.512725, 4.948456, -0.009709417, 0.5562537, 0.8309558, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9216192, 0.3112089, -0.2318764, -3.604237, -0.3879637, -0.75432, 0.5296089, 4.948456, -0.01008999, 0.5780575, 0.8159337, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9183235, 0.3126878, -0.24271, -3.604237, -0.3956947, -0.7412443, 0.5422018, 4.948456, -0.01036751, 0.5939559, 0.8044309, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9166561, 0.3126718, -0.2489534, -3.604237, -0.3995376, -0.733286, 0.5501467, 4.948456, -0.01053869, 0.6037617, 0.7970952, 0.0, 0.0, 0.0, 0.0, 1.0,
  -0.9161802, 0.3124457, -0.2509807, -3.604237, -0.4006261, -0.7305838, 0.5529431, 4.948456, -0.0105977, 0.6071451, 0.7945203, 0.0, 0.0, 0.0, 0.0, 1.0,
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
    .translate = {10.26849f, 7.983534f, 43.74428f},
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
  &node_channel_node_camera001_target_translation_y,
  &node_channel_node_camera001_target_translation_z,
  &node_channel_node_camera001_target_translation_x,
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
    .translate = {-42.21109f, -40.46347f, 100.0f},
  },
};

instance_geometry const instance_geometries_node_lighthelper[] = {
};

instance_controller const instance_controllers_node_lighthelper[] = {
};

instance_light const instance_lights_node_lighthelper[] = {
};

channel const * const node_channels_node_lighthelper[] = {
  &node_channel_node_lighthelper_translation_y,
  &node_channel_node_lighthelper_translation_x,
  &node_channel_node_lighthelper_translation_z,
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
    .matrix = {0.692005f, 0.6241241f, -0.3627647f, -4.146301f, -0.7218927f, 0.5982842f, -0.3477455f, -3.974632f, 0.0f, 0.5025188f, 0.8645663f, 10.48219f, 0.0f, 0.0f, 0.0f, 1.0f},
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
  &node_channel_node_camerahelper_translation_z,
  &node_channel_node_camerahelper_translation_y,
  &node_channel_node_camerahelper_translation_x,
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
    .matrix = {-0.9161802f, 0.3124457f, -0.2509807f, -3.604237f, -0.4006261f, -0.7305838f, 0.5529431f, 4.948456f, -0.01059775f, 0.6071451f, 0.7945203f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
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
