#include "renpy/language.h"

namespace renpy::script {
using namespace renpy::language;

char const * const strings[] = {
  "Far over the mountains of Almystice", // 0
  "Beyond the tumultuous waters of the Lilac Bay", // 1
  "And across the vast fields of Alysen", // 2
  "Tiny minstrels can be heard amongst the trees", // 3
  "Are we almost there?", // 4
  "Hmmm... Not really", // 5
  "How much further have we to go?", // 6
  "About a day or two of walking", // 7
  "We are still sooo far awayyy", // 8
  "And it will be even further if we dont stop taking breaks", // 9
  "Easy for you to say, all you have to carry is a little memory pipe!", // 10
  "I'm tired ><", // 11
  "Don't start whining now!", // 12
  "You need to remember why we have come all this way", // 13
  "I understand... I suppose it is for an important purpose", // 14
  "We're almost out of the forest, we can take a little break once we clear the tree line", // 15
  "Is that where the flora field is?", // 16
  "Why yes, If I remember correctly, it should be just up ahead", // 17
  "As the minstrel mice girls continue along the path, the forest opens up into a beautiful field of flowers", // 18
  "Look at all the butterflies! They are all so pretty!", // 19
  "This place is like a dream...", // 20
  "There are so many flowers this time of year", // 21
  "I told you it would be worth the journey!", // 22
  "Can we stop for a bit now?", // 23
  "Of course", // 24
  "Ya know, Its a shame we didnt save some of those giant strawberries you found", // 25
  "I told you not to eat them all!", // 26
  "Yah yah", // 27
  "Anyways, shall I recite a tale?", // 28
  "Why dont you sing the story of Eleanor the Hero!", // 29
  "Let us sing of the Hero Eleanor", // 30
  "...", // 31
  "Serves you right for scaring those elephant-dogs", // 32
  "They were asking for it, you know", // 33
  "Rawrrrr", // 34
  "AHHHHHHHHHH!!!!!", // 35
  "Nyanyanyanya", // 36
  "Well, what do we have here? If it isnt 2 little meowse girls, all alone in the flowers", // 37
  "Please dont eat us!!!", // 38
  "Alice dont run, our only chance is through pleading!", // 39
  "Please dont eat us, miss kitty cat!!! ><", // 40
  "I'm not gonna eat you nyanyanya", // 41
  "I just want to know what two little meowses are doing so very far away from home", // 42
  "Also, are you minstrels?", // 43
  "Y-Yes", // 44
  "W-We are on a quest to Castle Alysen...", // 45
  "Shh dont tell her that", // 46
  "The Castle of Alysen you say?!?", // 47
  "Why, that's where I am headed!", // 48
  "You dont say...", // 49
  "Yah I do actually", // 50
  "So... Why might you be traveling to the castle?", // 51
  "nya", // 52
  "Look, your right, the castle is just up ahead!", // 53
};

constexpr int strings_length = (sizeof (strings)) / (sizeof (strings[0]));

const character characters[] = {
  { .characterName = "Alice" }, // 0
  { .characterName = "Cat" }, // 1
  { .characterName = "Eily" }, // 2
  { .characterName = "Mouse Girls" }, // 3
  { .characterName = "Narrator" }, // 4
};

constexpr int characters_length = (sizeof (characters)) / (sizeof (characters[0]));

const audio audio[] = {
  { .path = "sfx/Chime.opus" }, // 0 sfx/Chime.ogg
  { .path = "sfx/MistAmbience.opus" }, // 1 sfx/MistAmbience.ogg
  { .path = "n1test.opus" }, // 2 n1test.mp3
  { .path = "n2test.opus" }, // 3 n2test.mp3
  { .path = "n3test.opus" }, // 4 n3test.mp3
  { .path = "n4test.opus" }, // 5 n4test.mp3
  { .path = "music/TinyForestMinstrels.opus" }, // 6 music/TinyForestMinstrels.ogg
  { .path = "n5test.opus" }, // 7 n5test.ogg
  { .path = "music/PhrygianButterflies.opus" }, // 8 music/PhrygianButterflies.ogg
  { .path = "music/Poem1.opus" }, // 9 music/Poem1.ogg
  { .path = "placeholdermeow.opus" }, // 10 placeholdermeow.mp3
  { .path = "music/ScaredMice.opus" }, // 11 music/ScaredMice.ogg
};

constexpr int audio_length = (sizeof (audio)) / (sizeof (audio[0]));

const image images[] = {
  { .path = "data/renpy/images/bg/white.dds" }, // 0 bg/white.png
  { .path = "data/renpy/images/bg/forest1.dds" }, // 1 bg/forest1.png
  { .path = "data/renpy/images/bg/flowerfield1.dds" }, // 2 bg/flowerfield1.png
  { .path = "data/renpy/images/bg/wheatfield1.dds" }, // 3 bg/wheatfield1.png
  { .path = "data/renpy/images/ch/cat.dds" }, // 4 ch/cat.png
  { .path = "data/renpy/images/ch/catw.dds" }, // 5 ch/catw.png
  { .path = "data/renpy/images/ch/Eily.dds" }, // 6 ch/Eily.png
  { .path = "data/renpy/images/ch/Alice.dds" }, // 7 ch/Alice.png
};

constexpr int images_length = (sizeof (images)) / (sizeof (images[0]));

const option options[] = {
  { .string = "Complain", .statementIndex = 22 }, // 0
  { .string = "Rationalize", .statementIndex = 30 }, // 1
  { .string = "Good idea", .statementIndex = 57 }, // 2
  { .string = "I am too tired", .statementIndex = 64 }, // 3
  { .string = "Beg for mercy", .statementIndex = 80 }, // 4
  { .string = "Run", .statementIndex = 82 }, // 5
};

constexpr int options_length = (sizeof (options)) / (sizeof (options[0]));

const statement statements[] = {
  { .type = type::play, .play = { .audioIndex = 0, /* FIXME channel */ } }, // 0 sfx/Chime.ogg
  { .type = type::play, .play = { .audioIndex = 1, /* FIXME channel */ } }, // 1 sfx/MistAmbience.ogg
  { .type = type::scene, .scene = { .imageIndex = 0 } }, // 2 bgwhite
  { .type = type::voice, .voice = { .audioIndex = 2 } }, // 4 n1test.mp3
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 0 } }, // 5 n "Far over the mountains of Almystice"
  { .type = type::voice, .voice = { .audioIndex = 3 } }, // 6 n2test.mp3
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 1 } }, // 7 n "Beyond the tumultuous waters of the Lilac Bay"
  { .type = type::voice, .voice = { .audioIndex = 4 } }, // 8 n3test.mp3
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 2 } }, // 9 n "And across the vast fields of Alysen"
  { .type = type::voice, .voice = { .audioIndex = 5 } }, // 10 n4test.mp3
  { .type = type::play, .play = { .audioIndex = 6, /* FIXME channel */ } }, // 11 music/TinyForestMinstrels.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 3 } }, // 12 n "Tiny minstrels can be heard amongst the trees"
  { .type = type::scene, .scene = { .imageIndex = 1 } }, // 13 bgforest1
  { .type = type::show, .show = { .imageIndex = 7 } }, // 15 al
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 4 } }, // 16 a "Are we almost there?"
  { .type = type::show, .show = { .imageIndex = 6 } }, // 17 ei
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 5 } }, // 18 e "Hmmm... Not really"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 6 } }, // 19 a "How much further have we to go?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 7 } }, // 20 e "About a day or two of walking"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 0 } }, // 21 "Complain", "Rationalize"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 8 } }, // 22 a "We are still sooo far awayyy"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 9 } }, // 23 e "And it will be even further if we dont stop taking breaks"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 10 } }, // 24 a "Easy for you to say, all you have to carry is a little memory pipe!"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 11 } }, // 25 a "I'm tired ><"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 12 } }, // 26 e "Don't start whining now!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 13 } }, // 27 e "You need to remember why we have come all this way"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 14 } }, // 28 a "I understand... I suppose it is for an important purpose"
  { .type = type::jump, .jump = { .statementIndex = 32 } }, // 29 internal jump (b'__menu_end', 0)
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 14 } }, // 30 a "I understand... I suppose it is for an important purpose"
  { .type = type::jump, .jump = { .statementIndex = 32 } }, // 31 internal jump (b'__menu_end', 0)
  { .type = type::jump, .jump = { .statementIndex = 33 } }, // 32 mainbranch1
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 15 } }, // 33 e "We're almost out of the forest, we can take a little break once we clear the tree line"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 16 } }, // 34 a "Is that where the flora field is?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 17 } }, // 35 e "Why yes, If I remember correctly, it should be just up ahead"
  { .type = type::stop, .stop = { /* FIXME channel */ } }, // 36
  { .type = type::scene, .scene = { .imageIndex = 0 } }, // 37 bgwhite
  { .type = type::voice, .voice = { .audioIndex = 7 } }, // 39 n5test.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 18 } }, // 40 n "As the minstrel mice girls continue along the path, the forest opens up into a beautiful field of flowers"
  { .type = type::play, .play = { .audioIndex = 8, /* FIXME channel */ } }, // 41 music/PhrygianButterflies.ogg
  { .type = type::scene, .scene = { .imageIndex = 2 } }, // 42 bgflower1
  { .type = type::show, .show = { .imageIndex = 6 } }, // 44 ei
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 19 } }, // 45 e "Look at all the butterflies! They are all so pretty!"
  { .type = type::show, .show = { .imageIndex = 7 } }, // 46 al
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 20 } }, // 47 a "This place is like a dream..."
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 21 } }, // 48 e "There are so many flowers this time of year"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 22 } }, // 49 e "I told you it would be worth the journey!"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 23 } }, // 50 a "Can we stop for a bit now?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 24 } }, // 51 e "Of course"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 25 } }, // 52 e "Ya know, Its a shame we didnt save some of those giant strawberries you found"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 26 } }, // 53 a "I told you not to eat them all!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 27 } }, // 54 e "Yah yah"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 28 } }, // 55 e "Anyways, shall I recite a tale?"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 2 } }, // 56 "Good idea", "I am too tired"
  { .type = type::stop, .stop = { /* FIXME channel */ } }, // 57
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 29 } }, // 58 a "Why dont you sing the story of Eleanor the Hero!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 30 } }, // 59 e "Let us sing of the Hero Eleanor"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 31 } }, // 60 a "..."
  { .type = type::play, .play = { .audioIndex = 9, /* FIXME channel */ } }, // 61 music/Poem1.ogg
  { .type = type::pause, .pause = { .duration = 40 } }, // 62
  { .type = type::jump, .jump = { .statementIndex = 67 } }, // 63 internal jump (b'__menu_end', 1)
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 32 } }, // 64 e "Serves you right for scaring those elephant-dogs"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 33 } }, // 65 a "They were asking for it, you know"
  { .type = type::jump, .jump = { .statementIndex = 67 } }, // 66 internal jump (b'__menu_end', 1)
  { .type = type::jump, .jump = { .statementIndex = 68 } }, // 67 mainbranch2
  { .type = type::hide, .hide = { .imageIndex = 6 } }, // 68 ei
  { .type = type::show, .show = { .imageIndex = 5 } }, // 69 catw
  { .type = type::show, .show = { .imageIndex = 6 } }, // 70 ei
  { .type = type::voice, .voice = { .audioIndex = 10 } }, // 71 placeholdermeow.mp3
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 34 } }, // 72 c "Rawrrrr"
  { .type = type::hide, .hide = { .imageIndex = 5 } }, // 73 catw
  { .type = type::show, .show = { .imageIndex = 4 } }, // 74 cat
  { .type = type::play, .play = { .audioIndex = 11, /* FIXME channel */ } }, // 75 music/ScaredMice.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 35 } }, // 76 mg "AHHHHHHHHHH!!!!!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 36 } }, // 77 c "Nyanyanyanya"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 37 } }, // 78 c "Well, what do we have here? If it isnt 2 little meowse girls, all alone in the flowers"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 4 } }, // 79 "Beg for mercy", "Run"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 38 } }, // 80 a "Please dont eat us!!!"
  { .type = type::jump, .jump = { .statementIndex = 85 } }, // 81 internal jump (b'__menu_end', 2)
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 39 } }, // 82 e "Alice dont run, our only chance is through pleading!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 40 } }, // 83 e "Please dont eat us, miss kitty cat!!! ><"
  { .type = type::jump, .jump = { .statementIndex = 85 } }, // 84 internal jump (b'__menu_end', 2)
  { .type = type::jump, .jump = { .statementIndex = 86 } }, // 85 mainbranch3
  { .type = type::stop, .stop = { /* FIXME channel */ } }, // 86
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 41 } }, // 87 c "I'm not gonna eat you nyanyanya"
  { .type = type::play, .play = { .audioIndex = 6, /* FIXME channel */ } }, // 88 music/TinyForestMinstrels.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 42 } }, // 89 c "I just want to know what two little meowses are doing so very far away from home"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 43 } }, // 90 c "Also, are you minstrels?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 44 } }, // 91 e "Y-Yes"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 45 } }, // 92 a "W-We are on a quest to Castle Alysen..."
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 46 } }, // 93 e "Shh dont tell her that"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 47 } }, // 94 c "The Castle of Alysen you say?!?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 48 } }, // 95 c "Why, that's where I am headed!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 49 } }, // 96 e "You dont say..."
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 50 } }, // 97 c "Yah I do actually"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 51 } }, // 98 e "So... Why might you be traveling to the castle?"
  { .type = type::scene, .scene = { .imageIndex = 0 } }, // 99 bgwhite
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 52 } }, // 100 n "nya"
  { .type = type::scene, .scene = { .imageIndex = 3 } }, // 101 bgwheatfield1
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 53 } }, // 102 e "Look, your right, the castle is just up ahead!"
  { .type = type::_return }, // 103
};

constexpr int statements_length = (sizeof (statements)) / (sizeof (statements[0]));

}
