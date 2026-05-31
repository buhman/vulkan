#include "poem.h"

namespace poem {
  static char const * const words[] = {
    "Windless", "misty", "nights",
    "I've", "seen", "along", "my", "way",
    "Long", "ago",
    "With", "my", "sword", "in", "hand", "I", "traveled",
    "Through", "the", "wastes",
    "Clad", "in", "cloud", "and", "rain",
    "Through", "the", "night", "and", "the", "day",
  };
  static int const words_length = (sizeof (words)) / (sizeof (words[0]));

  static line const lines[] = {
    { 0, 3 },
    { 3, 5 },
    { 8, 2 },
    { 10, 7 },
    { 17, 3 },
    { 20, 5 },
    { 25, 6 }
  };
  static int const lines_length = (sizeof (lines)) / (sizeof (lines[0]));

  static timestamp const timestamps[] = {
    { 0.0, -1 }, // [instrumental]

    { 4.985, 0 }, // windless
    { 6.24, 1 }, // misty
    { 7.43, 2 }, // nights

    { 9.42, 3 }, // I've
    { 9.875, 4 }, // seen
    { 10.665, 5 }, // along
    { 11.64, 6 }, // my
    { 12.31, 7 }, // way

    { 14.275, 8 }, // Long
    { 14.60, 9 }, // ago

    { 16.65, 10 }, // with
    { 17.00, 11 }, // my
    { 17.12, 12 }, // sword
    { 17.58, 13 }, // in
    { 17.725, 14 }, // hand
    { 18.18, 15 }, // I
    { 18.36, 16 }, // traveled

    { 19.255, 17 }, // through
    { 19.41, 18 }, // the
    { 19.54, 19 }, // wastes

    { 22.62, -1 }, // [instrumental]

    { 24.80, 20 }, // clad
    { 25.35, 21 }, // in
    { 25.80, 22 }, // cloud
    { 26.65, 23 }, // and
    { 27.00, 24 }, // rain

    { 28.025, 25 }, // through
    { 28.225, 26 }, // the
    { 28.28, 27 }, // night
    { 28.835, 28 }, // and
    { 29.15, 29 }, // the
    { 29.65, 30 }, // day

    { 33.00, -1 }, // [instrumental]
  };
  static int const timestamps_length = (sizeof (timestamps)) / (sizeof (timestamps[0]));

  poem const eleanorthehero = {
    .words = words,
    .words_length = words_length,
    .lines = lines,
    .lines_length = lines_length,
    .timestamps = timestamps,
    .timestamps_length = timestamps_length,
  };
}
