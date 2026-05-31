#include "poem.h"

namespace poem {
  static char const * const words[] = {
    "La", "drevo", "se", "la", // 4
    "la", "se", "esmiral", // 3
    "as", "dra", "verisal", // 3
    "very", "fior", // 2

    "La", "dro", // 2
    "Se", "la", "Tagi", "de", "sma", "ve", "la", // 7
    "ve", "la", "lu", "de", // 4

    "Varose", // 1
    "Eleison", // 1
    "Eleison", // 1

    "La", "la", "lu", "ser", "per", "dio", // 6
  };
  static int const words_length = (sizeof (words)) / (sizeof (words[0]));

  static line const lines[] = {
    { 0, 4 },
    { 4, 3 },
    { 7, 3 },
    { 10, 2 },
    { 12, 2 },
    { 14, 7 },
    { 21, 4 },
    { 25, 1 },
    { 26, 1 },
    { 27, 1 },
    { 28, 6 },
  };
  static int const lines_length = (sizeof (lines)) / (sizeof (lines[0]));

  static timestamp const timestamps[] = {
    { 0.0, -1 }, // [instrumental]

    { 9.65, 0 }, // La
    { 10.59, 1 }, // drevo
    { 11.675, 2 }, // se
    { 12.000, 3 }, // la
    { 12.85, 4 }, // la
    { 13.125, 5 }, // se
    { 13.955, 6 }, // esmiral
    { 14.795, 7 }, // as
    { 15.28, 8 }, // dra
    { 16.015, 9 }, // verisal
    { 17.025, 10 }, // very
    { 17.46, 11 }, // fior

    { 18.99, 12 }, // La
    { 20.03, 13 }, // dro
    { 21.18, 14 }, // Se
    { 21.86, 15 }, // la
    { 22.15, 16 }, // Tagi
    { 22.94, 17 }, // de
    { 23.31, 18 }, // sma
    { 24.075, 19 }, // ve
    { 24.30, 20 }, // la
    { 25.05, 21 }, // ve
    { 25.63, 22 }, // la
    { 26.175, 23 }, // lu
    { 26.755, 24 }, // de

    { 27.975, -1 }, // [instrumental]

    { 46.155, 25 }, // Varose
    { 48.41, 26 }, // Eleison
    { 50.88, 27 }, // Eleison

    { 58.50, -1 }, // [instrumental]

    { 59.63, 28 }, // La
    { 61.87, 29 }, // la
    { 62.82, 30 }, // lu
    { 62.94, 31 }, // ser
    { 63.76, 32 }, // per
    { 64.24, 33 }, // dio

    { 72.92, -1 }, // [instrumental]
  };
  static int const timestamps_length = (sizeof (timestamps)) / (sizeof (timestamps[0]));

  poem const birdsong = {
    .words = words,
    .words_length = words_length,
    .lines = lines,
    .lines_length = lines_length,
    .timestamps = timestamps,
    .timestamps_length = timestamps_length,
  };
}
