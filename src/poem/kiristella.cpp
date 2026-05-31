#include "poem.h"

namespace poem {
  static char const * const words[] = {
    "La", "lu", "te", "diri", "va",
    "Ki", "estevi", "sa",
    "veri", "son",
    "la", "ser", "vi", "ih", "ta",
    "nu",
    "veri", "eh", "sta",
    "Kiri", "stella",
    "Kiri", "stella",
    "nu",
  };
  static int const words_length = (sizeof (words)) / (sizeof (words[0]));

  static line const lines[] = {
    { 0, 5 },
    { 5, 3 },
    { 8, 2 },
    { 10, 5 },
    { 15, 1 },
    { 16, 3 },
    { 19, 2 },
    { 21, 2 },
    { 23, 1 },
  };
  static int const lines_length = (sizeof (lines)) / (sizeof (lines[0]));

  static timestamp const timestamps[] = {
    { 0.00 , -1 }, // [instrumental]

    { 18.52 , 0 }, // La
    { 19.62 , 1 }, // lu
    { 20.60 , 2 }, // te
    { 21.25 , 3 }, // diri
    { 21.52 , 4 }, // va

    { 22.58 , 5 }, // Ki
    { 23.87 , 6 }, // estevi
    { 25.33 , 7 }, // sa
    { 26.125 , 8 }, // veri
    { 26.38 , 9 }, // son

    { 27.81 , 10 }, // La
    { 28.35 , 11 }, // ser
    { 28.86 , 12 }, // vi
    { 29.02 , 13 }, // ih
    { 29.175 , 14 }, // ta
    { 30.22 , 15 }, // nu

    { 31.65 , 16 }, // veri
    { 31.82 , 17 }, // eh
    { 32.40 , 18 }, // sta

    { 34.22 , 19 }, // Kiri
    { 35.91 , 20 }, // stella
    { 38.16 , 21 }, // Kiri
    { 40.10 , 22 }, // stella
    { 42.26 , 23 }, // nu

    { 51.94 , -1 }, // [instrumental]
  };
  static int const timestamps_length = (sizeof (timestamps)) / (sizeof (timestamps[0]));

  poem const kiristella = {
    .words = words,
    .words_length = words_length,
    .lines = lines,
    .lines_length = lines_length,
    .timestamps = timestamps,
    .timestamps_length = timestamps_length,
  };
}
