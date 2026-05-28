#include "renpy/language.h"
#include "renpy/script.h"

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
  "About two more moons", // 7
  "We are still sooo far awayyy", // 8
  "And it will be even further if you dont stop complaining", // 9
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
  "Sure", // 30
  "...", // 31
  "Serves you right for scaring those elephant-dogs", // 32
  "They were asking for it, you know", // 33
  "Rawrrrr", // 34
  "AHHHHHHHHHH!!!!!", // 35
  "Nyanyanyanya", // 36
  "Well, what do we have here? If it isn't two little meowse girls, all alone amongst the flowers", // 37
  "Please don't eat us!!!", // 38
  "Alice don't run, our only chance is through pleading!", // 39
  "Please don't eat us, miss kitty cat!!! ><", // 40
  "I'm not gonna eat you nyanyanya", // 41
  "I just want to know what two little meowses are doing so very far away from home", // 42
  "Also, are you minstrels?", // 43
  "Y-Yes", // 44
  "W-We are on a quest to Castle Alysen...", // 45
  "Shh don't tell her that", // 46
  "The Castle of Alysen you say?!?", // 47
  "Why, that's where I am headed!", // 48
  "You don't say...", // 49
  "Yah, I do actually", // 50
  "So... Why might you be traveling to the castle?", // 51
  "I belong to the lineage of Agrepen", // 52
  "And what might that mean?", // 53
  "The Agrepens are a long line of felines loyal to the crown of corvidae", // 54
  "Really? That must mean you are a noble?", // 55
  "Well, not really...", // 56
  "My father was one of the queens knights many years ago", // 57
  "Ah I see", // 58
  "So do you live at the castle or something?", // 59
  "Well, no...", // 60
  "Then why are you traveling to Castle Alysen?", // 61
  "uhhh", // 62
  "I DONT NEED TO BE PRESSURED BY LITTLE MICE TO SAY ANYTHING!!!!", // 63
  "GOOD DAY!", // 64
  "Wha...", // 65
  "Phew, I was scared she was gonna follow us the whole way", // 66
  "She didn't seem so bad", // 67
  "Are you kidding? She's a crazy kitty!", // 68
  "After their encounter with the weird cat, the mice scurry out of the flower field and into the nearby meadow", // 69
  "I think this is the right way...", // 70
  "Then where did the path go?", // 71
  "How am I supposed to know?", // 72
  "Did you hear that?!?!", // 73
  "Hey there...", // 74
  "I apologize", // 75
  "I didn't mean to storm off like that", // 76
  "Ha ha, no problem...", // 77
  "So... Why are you traveling to Castle Alysen?", // 78
  "Alice!!!", // 79
  "If you must know, I have been summoned by the queen", // 80
  "I suspect that my poor reputation amongst the locals of Eastern Nidus has come back to haunt me", // 81
  "Though I know not what what she has summoned me for", // 82
  "Ahhhhhh", // 83
  "So then...", // 84
  "Why are YOU traveling to the Castle?", // 85
  "We are delivering a feather!!!", // 86
  "Alice no!", // 87
  "A feather that belonged to the queen herself!!!", // 88
  "Why you little...", // 89
  "A feather you say? One of the queens?", // 90
  "How on the face of Al Mot might you have aquired such a thing?", // 91
  "If it is authentic, that is...", // 92
  "Since Alice cannot keep a secret, I shall tell you", // 93
  "Seven moons ago, our town was attacked by three owls and a band of mice from the northern principalities", // 94
  "Eventually word spread to greater nearby settlements, and so", // 95
  "Messengers from the keep in Musia sent for aid from the Ravens", // 96
  "Four moons ago, the request was answered", // 97
  "And a small group of mice accompanied by two ravens a fox, and three squirrels set out to the northern principalities", // 98
  "Anyways, long story short, we drove those barbaric rats out of their home", // 99
  "They arent actual rats you know", // 100
  "Obviously, but you wont catch me speaking kindly of them", // 101
  "And you forgot the most important part", // 102
  "Yah yah, I am getting there", // 103
  "So, essentially, my brother is trained in archery, and...", // 104
  "Speed it up already", // 105
  "You tell it then!", // 106
  "My cousin found this feather in one of the highest towers of a castle far to the north", // 107
  "How do you know it belongs to the queen?", // 108
  "It said so itself above the display on the wall", // 109
  "Supposedly, it was in a room filled with treasures!", // 110
  "That is very nice and all, but what are the two of you doing out here all alone?", // 111
  "Do you expect every bird in Avia to respect your alliance with Castle Alysen?", // 112
  "What do you mean?", // 113
  "I mean, the two of you probably look like walking dinner to most creatures", // 114
  "I could go for some dinner...", // 115
  "Anyways...", // 116
  "To answer your question, upon returning to the village, the feather was taken from my brother by the needle guild", // 117
  "So... Yesterday, after sundown", // 118
  "We stole the feather from the guild hall before vanishing into the night", // 119
  "Can you imagine the look on their stupid faces, when they woke up, and not only is the feather missing", // 120
  "But so are we!", // 121
  "Hahahaha", // 122
  "Are the two of you mad?", // 123
  "I assume you are attempting to return the Queens feather?", // 124
  "Yes, we intend to deliver the feather to its rightful owner", // 125
  "Absolute madness!", // 126
  "I will follow the two of you", // 127
  "To keep you safe, that is", // 128
  "Alright!", // 129
  "Ha ha... Okay...", // 130
  "Great! Follow me, I know a shortcut! :3", // 131
  "Sounds good!", // 132
  "Oh dear!", // 133
  "And so the mice girls follow the noble cat further towards their destination", // 134
  "Nya", // 135
  "Look, your right, the castle is just up ahead!", // 136
  "Wait up", // 137
  "I told you I knew a shortcut!", // 138
  "Most people take the long way around", // 139
  "Yah because these are royal wheatfields!", // 140
  "Who cares?", // 141
  "Are you trying to get us killed?", // 142
  "Its trespassing on royal land!", // 143
  "Calm down, I have done this a million times", // 144
  "That doesnt make me calm!", // 145
  "How can the rolling fields of wheat not calm your spirit?", // 146
  "You little mice truly are mad!", // 147
  "I like the wheat!", // 148
  "Shut up!", // 149
  "Sounds like someone needs a nap!", // 150
  "Why? because I'm not insane like you?", // 151
  "Yah, your so sane, that you decided to steal from your town and then run off alone to the country of birds", // 152
  "The power of friendship wont protect the two of you from becoming dinner", // 153
  "And that, is why I feel obligated to accompany you!", // 154
  "Hey, we have a good reason!", // 155
  "And what might that be?", // 156
  "My brother found the feather, not the town guild, its a matter of family pride!", // 157
  "Pride has touched the chosen meouse", // 158
  "Flies she towards the Castle", // 159
  "But her ambition burns far too bright, and silly myice dont have any wings to myelt", // 160
  "What?", // 161
  "Nyanyanya", // 162
  "Nyevermind", // 163
  "Sing me a song little minstrels!", // 164
  "Very Nyice!", // 165
  "Now tell me little minstrels, what are your names?", // 166
  "My name is Alice", // 167
  "And my name is Eily", // 168
  "What is your name?", // 169
  "My name is Leona!", // 170
  "And so, the odd trio walked through the wheatfields and towards the castle walls", // 171
  "Upon approaching the castle walls", // 172
};

const int strings_length = (sizeof (strings)) / (sizeof (strings[0]));

const language::character characters[] = {
  { .characterName = "Alice", .color = 0x00765e }, // 0
  { .characterName = "Cat", .color = 0x590093 }, // 1
  { .characterName = "Eily", .color = 0x0b6092 }, // 2
  { .characterName = "Mouse Girls", .color = 0x000000 }, // 3
  { .characterName = "Narrator", .color = 0x000000 }, // 4
  { .characterName = "Leona", .color = 0x590093 }, // 5
};

const int characters_length = (sizeof (characters)) / (sizeof (characters[0]));

const language::audio audio[] = {
  { .path = "audio/sfx/Chime.opus.bin", .loop_end = 0.0 }, // 0 sfx/Chime.ogg
  { .path = "audio/sfx/MistAmbience.opus.bin", .loop_end = 22.0 }, // 1 sfx/MistAmbience.ogg
  { .path = "audio/music/TinyForestMinstrels.opus.bin", .loop_end = 44.0 }, // 2 music/TinyForestMinstrels.ogg
  { .path = "audio/music/PhrygianButterflies.opus.bin", .loop_end = 40.125 }, // 3 music/PhrygianButterflies.ogg
  { .path = "audio/music/Poem1.opus.bin", .loop_end = 0.0 }, // 4 music/Poem1.ogg
  { .path = "audio/placeholdermeow.opus.bin", .loop_end = 0.0 }, // 5 placeholdermeow.mp3
  { .path = "audio/music/ScaredMice.opus.bin", .loop_end = 8.0 }, // 6 music/ScaredMice.ogg
  { .path = "audio/music/WheatFields.opus.bin", .loop_end = 34.0 }, // 7 music/WheatFields.ogg
};

const int audio_length = (sizeof (audio)) / (sizeof (audio[0]));

const language::image images[] = {
  { .path = "data/renpy/images/flowers.dds" }, // 0 flowers.png
  { .path = "data/renpy/images/bg/forest1.dds" }, // 1 bg/forest1.png
  { .path = "data/renpy/images/bg/forest2.dds" }, // 2 bg/forest2.png
  { .path = "data/renpy/images/bg/flowerfield1.dds" }, // 3 bg/flowerfield1.png
  { .path = "data/renpy/images/bg/wheatfield1.dds" }, // 4 bg/wheatfield1.png
  { .path = "data/renpy/images/ch/cat.dds" }, // 5 ch/cat.png
  { .path = "data/renpy/images/ch/catw.dds" }, // 6 ch/catw.png
  { .path = "data/renpy/images/ch/Eily.dds" }, // 7 ch/Eily.png
  { .path = "data/renpy/images/ch/Alice.dds" }, // 8 ch/Alice.png
};

const int images_length = (sizeof (images)) / (sizeof (images[0]));

const language::option options[] = {
  { .string = "Complain", .statementIndex = 19 }, // 0
  { .string = "Rationalize", .statementIndex = 27 }, // 1
  { .string = "Good idea", .statementIndex = 54 }, // 2
  { .string = "I am too tired", .statementIndex = 61 }, // 3
  { .string = "Beg for mercy", .statementIndex = 78 }, // 4
  { .string = "Run", .statementIndex = 80 }, // 5
};

const int options_length = (sizeof (options)) / (sizeof (options[0]));

const language::statement statements[] = {
  { .type = type::play, .play = { .audioIndex = 0 } }, // 0 sfx/Chime.ogg
  { .type = type::play, .play = { .audioIndex = 1 } }, // 1 sfx/MistAmbience.ogg
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 2 bgwhite
  { .type = type::dissolve, .dissolve = { .duration = 3.0 } }, // 3
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 0 } }, // 4 n "Far over the mountains of Almystice"
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 1 } }, // 5 n "Beyond the tumultuous waters of the Lilac Bay"
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 2 } }, // 6 n "And across the vast fields of Alysen"
  { .type = type::play, .play = { .audioIndex = 2 } }, // 7 music/TinyForestMinstrels.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 3 } }, // 8 n "Tiny minstrels can be heard amongst the trees"
  { .type = type::stop, .stop = { .audioIndex = 2, .fadeout = 5.5 } }, // 9 TinyForestMinstrels
  { .type = type::scene, .scene = { .imageIndex = 1 } }, // 10 bgforest1
  { .type = type::dissolve, .dissolve = { .duration = 3.0 } }, // 11
  { .type = type::show, .show = { .imageIndex = 8, .transformIndex = transform::left } }, // 12 al
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 4 } }, // 13 a "Are we almost there?"
  { .type = type::show, .show = { .imageIndex = 7, .transformIndex = transform::right } }, // 14 ei
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 5 } }, // 15 e "Hmmm... Not really"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 6 } }, // 16 a "How much further have we to go?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 7 } }, // 17 e "About two more moons"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 0 } }, // 18 "Complain", "Rationalize"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 8 } }, // 19 a "We are still sooo far awayyy"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 9 } }, // 20 e "And it will be even further if you dont stop complaining"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 10 } }, // 21 a "Easy for you to say, all you have to carry is a little memory pipe!"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 11 } }, // 22 a "I'm tired ><"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 12 } }, // 23 e "Don't start whining now!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 13 } }, // 24 e "You need to remember why we have come all this way"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 14 } }, // 25 a "I understand... I suppose it is for an important purpose"
  { .type = type::jump, .jump = { .statementIndex = 29 } }, // 26 internal jump (b'__menu_end', 0)
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 14 } }, // 27 a "I understand... I suppose it is for an important purpose"
  { .type = type::jump, .jump = { .statementIndex = 29 } }, // 28 internal jump (b'__menu_end', 0)
  { .type = type::jump, .jump = { .statementIndex = 30 } }, // 29 mainbranch1
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 15 } }, // 30 e "We're almost out of the forest, we can take a little break once we clear the tree line"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 16 } }, // 31 a "Is that where the flora field is?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 17 } }, // 32 e "Why yes, If I remember correctly, it should be just up ahead"
  { .type = type::stop, .stop = { .audioIndex = 2, .fadeout = 5.5 } }, // 33 TinyForestMinstrels
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 34 bgwhite
  { .type = type::play, .play = { .audioIndex = 0 } }, // 35 sfx/Chime.ogg
  { .type = type::dissolve, .dissolve = { .duration = 1.0 } }, // 36
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 18 } }, // 37 n "As the minstrel mice girls continue along the path, the forest opens up into a beautiful field of flowers"
  { .type = type::play, .play = { .audioIndex = 3 } }, // 38 music/PhrygianButterflies.ogg
  { .type = type::scene, .scene = { .imageIndex = 3 } }, // 39 bgflower1
  { .type = type::dissolve, .dissolve = { .duration = 1.0 } }, // 40
  { .type = type::show, .show = { .imageIndex = 7, .transformIndex = transform::right } }, // 41 ei
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 19 } }, // 42 e "Look at all the butterflies! They are all so pretty!"
  { .type = type::show, .show = { .imageIndex = 8, .transformIndex = transform::left } }, // 43 al
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 20 } }, // 44 a "This place is like a dream..."
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 21 } }, // 45 e "There are so many flowers this time of year"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 22 } }, // 46 e "I told you it would be worth the journey!"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 23 } }, // 47 a "Can we stop for a bit now?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 24 } }, // 48 e "Of course"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 25 } }, // 49 e "Ya know, Its a shame we didnt save some of those giant strawberries you found"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 26 } }, // 50 a "I told you not to eat them all!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 27 } }, // 51 e "Yah yah"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 28 } }, // 52 e "Anyways, shall I recite a tale?"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 2 } }, // 53 "Good idea", "I am too tired"
  { .type = type::stop, .stop = { .audioIndex = 3, .fadeout = 4.2 } }, // 54 PhrygianButterflies
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 29 } }, // 55 a "Why dont you sing the story of Eleanor the Hero!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 30 } }, // 56 e "Sure"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 31 } }, // 57 a "..."
  { .type = type::play, .play = { .audioIndex = 4 } }, // 58 music/Poem1.ogg
  { .type = type::pause, .pause = { .duration = 40 } }, // 59
  { .type = type::jump, .jump = { .statementIndex = 65 } }, // 60 internal jump (b'__menu_end', 1)
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 32 } }, // 61 e "Serves you right for scaring those elephant-dogs"
  { .type = type::stop, .stop = { .audioIndex = 3, .fadeout = 4.2 } }, // 62 PhrygianButterflies
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 33 } }, // 63 a "They were asking for it, you know"
  { .type = type::jump, .jump = { .statementIndex = 65 } }, // 64 internal jump (b'__menu_end', 1)
  { .type = type::jump, .jump = { .statementIndex = 66 } }, // 65 mainbranch2
  { .type = type::hide, .hide = { .imageIndex = 7 } }, // 66 ei
  { .type = type::show, .show = { .imageIndex = 6, .transformIndex = transform::right } }, // 67 catw
  { .type = type::show, .show = { .imageIndex = 7, .transformIndex = transform::centerleft } }, // 68 ei
  { .type = type::voice, .voice = { .audioIndex = 5 } }, // 69 placeholdermeow.mp3
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 34 } }, // 70 c "Rawrrrr"
  { .type = type::hide, .hide = { .imageIndex = 6 } }, // 71 catw
  { .type = type::show, .show = { .imageIndex = 5, .transformIndex = transform::right } }, // 72 cat
  { .type = type::play, .play = { .audioIndex = 6 } }, // 73 music/ScaredMice.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 35 } }, // 74 mg "AHHHHHHHHHH!!!!!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 36 } }, // 75 c "Nyanyanyanya"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 37 } }, // 76 c "Well, what do we have here? If it isn't two little meowse girls, all alone amongst the flowers"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 4 } }, // 77 "Beg for mercy", "Run"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 38 } }, // 78 a "Please don't eat us!!!"
  { .type = type::jump, .jump = { .statementIndex = 83 } }, // 79 internal jump (b'__menu_end', 2)
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 39 } }, // 80 e "Alice don't run, our only chance is through pleading!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 40 } }, // 81 e "Please don't eat us, miss kitty cat!!! ><"
  { .type = type::jump, .jump = { .statementIndex = 83 } }, // 82 internal jump (b'__menu_end', 2)
  { .type = type::jump, .jump = { .statementIndex = 84 } }, // 83 mainbranch3
  { .type = type::stop, .stop = { .audioIndex = 6, .fadeout = 2.0 } }, // 84 ScaredMice
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 41 } }, // 85 c "I'm not gonna eat you nyanyanya"
  { .type = type::play, .play = { .audioIndex = 2 } }, // 86 music/TinyForestMinstrels.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 42 } }, // 87 c "I just want to know what two little meowses are doing so very far away from home"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 43 } }, // 88 c "Also, are you minstrels?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 44 } }, // 89 e "Y-Yes"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 45 } }, // 90 a "W-We are on a quest to Castle Alysen..."
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 46 } }, // 91 e "Shh don't tell her that"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 47 } }, // 92 c "The Castle of Alysen you say?!?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 48 } }, // 93 c "Why, that's where I am headed!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 49 } }, // 94 e "You don't say..."
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 50 } }, // 95 c "Yah, I do actually"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 51 } }, // 96 e "So... Why might you be traveling to the castle?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 52 } }, // 97 c "I belong to the lineage of Agrepen"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 53 } }, // 98 e "And what might that mean?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 54 } }, // 99 c "The Agrepens are a long line of felines loyal to the crown of corvidae"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 55 } }, // 100 e "Really? That must mean you are a noble?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 56 } }, // 101 c "Well, not really..."
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 57 } }, // 102 c "My father was one of the queens knights many years ago"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 58 } }, // 103 e "Ah I see"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 59 } }, // 104 e "So do you live at the castle or something?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 60 } }, // 105 c "Well, no..."
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 61 } }, // 106 a "Then why are you traveling to Castle Alysen?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 62 } }, // 107 c "uhhh"
  { .type = type::play, .play = { .audioIndex = 1 } }, // 108 sfx/MistAmbience.ogg
  { .type = type::stop, .stop = { .audioIndex = 2, .fadeout = 2.0 } }, // 109 TinyForestMinstrels
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 63 } }, // 110 c "I DONT NEED TO BE PRESSURED BY LITTLE MICE TO SAY ANYTHING!!!!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 64 } }, // 111 c "GOOD DAY!"
  { .type = type::hide, .hide = { .imageIndex = 5 } }, // 112 cat
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 65 } }, // 113 a "Wha..."
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 66 } }, // 114 e "Phew, I was scared she was gonna follow us the whole way"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 67 } }, // 115 a "She didn't seem so bad"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 68 } }, // 116 e "Are you kidding? She's a crazy kitty!"
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 117 bgwhite
  { .type = type::play, .play = { .audioIndex = 0 } }, // 118 sfx/Chime.ogg
  { .type = type::dissolve, .dissolve = { .duration = 3.0 } }, // 119
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 69 } }, // 120 n "After their encounter with the weird cat, the mice scurry out of the flower field and into the nearby meadow"
  { .type = type::scene, .scene = { .imageIndex = 2 } }, // 121 bgforest2
  { .type = type::dissolve, .dissolve = { .duration = 3.0 } }, // 122
  { .type = type::show, .show = { .imageIndex = 7, .transformIndex = transform::right } }, // 123 ei
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 70 } }, // 124 e "I think this is the right way..."
  { .type = type::show, .show = { .imageIndex = 8, .transformIndex = transform::left } }, // 125 al
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 71 } }, // 126 a "Then where did the path go?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 72 } }, // 127 e "How am I supposed to know?"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 73 } }, // 128 a "Did you hear that?!?!"
  { .type = type::show, .show = { .imageIndex = 7, .transformIndex = transform::centerleft } }, // 129 ei
  { .type = type::show, .show = { .imageIndex = 5, .transformIndex = transform::right } }, // 130 cat
  { .type = type::play, .play = { .audioIndex = 3 } }, // 131 music/PhrygianButterflies.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 74 } }, // 132 c "Hey there..."
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 75 } }, // 133 c "I apologize"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 76 } }, // 134 c "I didn't mean to storm off like that"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 77 } }, // 135 e "Ha ha, no problem..."
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 78 } }, // 136 a "So... Why are you traveling to Castle Alysen?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 79 } }, // 137 e "Alice!!!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 80 } }, // 138 c "If you must know, I have been summoned by the queen"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 81 } }, // 139 c "I suspect that my poor reputation amongst the locals of Eastern Nidus has come back to haunt me"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 82 } }, // 140 c "Though I know not what what she has summoned me for"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 83 } }, // 141 a "Ahhhhhh"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 84 } }, // 142 c "So then..."
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 85 } }, // 143 c "Why are YOU traveling to the Castle?"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 86 } }, // 144 a "We are delivering a feather!!!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 87 } }, // 145 e "Alice no!"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 88 } }, // 146 a "A feather that belonged to the queen herself!!!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 89 } }, // 147 e "Why you little..."
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 90 } }, // 148 c "A feather you say? One of the queens?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 91 } }, // 149 c "How on the face of Al Mot might you have aquired such a thing?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 92 } }, // 150 c "If it is authentic, that is..."
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 93 } }, // 151 e "Since Alice cannot keep a secret, I shall tell you"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 94 } }, // 152 e "Seven moons ago, our town was attacked by three owls and a band of mice from the northern principalities"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 95 } }, // 153 e "Eventually word spread to greater nearby settlements, and so"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 96 } }, // 154 e "Messengers from the keep in Musia sent for aid from the Ravens"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 97 } }, // 155 e "Four moons ago, the request was answered"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 98 } }, // 156 e "And a small group of mice accompanied by two ravens a fox, and three squirrels set out to the northern principalities"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 99 } }, // 157 e "Anyways, long story short, we drove those barbaric rats out of their home"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 100 } }, // 158 a "They arent actual rats you know"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 101 } }, // 159 e "Obviously, but you wont catch me speaking kindly of them"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 102 } }, // 160 a "And you forgot the most important part"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 103 } }, // 161 e "Yah yah, I am getting there"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 104 } }, // 162 e "So, essentially, my brother is trained in archery, and..."
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 105 } }, // 163 a "Speed it up already"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 106 } }, // 164 e "You tell it then!"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 107 } }, // 165 a "My cousin found this feather in one of the highest towers of a castle far to the north"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 108 } }, // 166 c "How do you know it belongs to the queen?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 109 } }, // 167 e "It said so itself above the display on the wall"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 110 } }, // 168 a "Supposedly, it was in a room filled with treasures!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 111 } }, // 169 c "That is very nice and all, but what are the two of you doing out here all alone?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 112 } }, // 170 c "Do you expect every bird in Avia to respect your alliance with Castle Alysen?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 113 } }, // 171 e "What do you mean?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 114 } }, // 172 c "I mean, the two of you probably look like walking dinner to most creatures"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 115 } }, // 173 a "I could go for some dinner..."
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 116 } }, // 174 e "Anyways..."
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 117 } }, // 175 e "To answer your question, upon returning to the village, the feather was taken from my brother by the needle guild"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 118 } }, // 176 e "So... Yesterday, after sundown"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 119 } }, // 177 e "We stole the feather from the guild hall before vanishing into the night"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 120 } }, // 178 e "Can you imagine the look on their stupid faces, when they woke up, and not only is the feather missing"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 121 } }, // 179 e "But so are we!"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 122 } }, // 180 a "Hahahaha"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 123 } }, // 181 c "Are the two of you mad?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 124 } }, // 182 c "I assume you are attempting to return the Queens feather?"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 125 } }, // 183 a "Yes, we intend to deliver the feather to its rightful owner"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 126 } }, // 184 c "Absolute madness!"
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 31 } }, // 185 mg "..."
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 127 } }, // 186 c "I will follow the two of you"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 128 } }, // 187 c "To keep you safe, that is"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 129 } }, // 188 a "Alright!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 130 } }, // 189 e "Ha ha... Okay..."
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 131 } }, // 190 c "Great! Follow me, I know a shortcut! :3"
  { .type = type::hide, .hide = { .imageIndex = 5 } }, // 191 cat
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 132 } }, // 192 a "Sounds good!"
  { .type = type::hide, .hide = { .imageIndex = 8 } }, // 193 al
  { .type = type::stop, .stop = { .audioIndex = 3, .fadeout = 2.0 } }, // 194 PhrygianButterflies
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 133 } }, // 195 e "Oh dear!"
  { .type = type::hide, .hide = { .imageIndex = 7 } }, // 196 ei
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 197 bgwhite
  { .type = type::play, .play = { .audioIndex = 0 } }, // 198 sfx/Chime.ogg
  { .type = type::dissolve, .dissolve = { .duration = 2.0 } }, // 199
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 134 } }, // 200 n "And so the mice girls follow the noble cat further towards their destination"
  { .type = type::scene, .scene = { .imageIndex = 4 } }, // 201 bgwheatfield1
  { .type = type::play, .play = { .audioIndex = 7 } }, // 202 music/WheatFields.ogg
  { .type = type::show, .show = { .imageIndex = 5, .transformIndex = transform::right } }, // 203 cat
  { .type = type::dissolve, .dissolve = { .duration = 1.3 } }, // 204
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 135 } }, // 205 c "Nya"
  { .type = type::show, .show = { .imageIndex = 8, .transformIndex = transform::left } }, // 206 al
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 136 } }, // 207 a "Look, your right, the castle is just up ahead!"
  { .type = type::show, .show = { .imageIndex = 7, .transformIndex = transform::centerleft } }, // 208 ei
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 137 } }, // 209 e "Wait up"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 138 } }, // 210 c "I told you I knew a shortcut!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 139 } }, // 211 c "Most people take the long way around"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 140 } }, // 212 e "Yah because these are royal wheatfields!"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 141 } }, // 213 a "Who cares?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 142 } }, // 214 e "Are you trying to get us killed?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 143 } }, // 215 e "Its trespassing on royal land!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 144 } }, // 216 c "Calm down, I have done this a million times"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 145 } }, // 217 e "That doesnt make me calm!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 146 } }, // 218 c "How can the rolling fields of wheat not calm your spirit?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 147 } }, // 219 c "You little mice truly are mad!"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 148 } }, // 220 a "I like the wheat!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 149 } }, // 221 e "Shut up!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 150 } }, // 222 c "Sounds like someone needs a nap!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 151 } }, // 223 e "Why? because I'm not insane like you?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 152 } }, // 224 c "Yah, your so sane, that you decided to steal from your town and then run off alone to the country of birds"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 153 } }, // 225 c "The power of friendship wont protect the two of you from becoming dinner"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 154 } }, // 226 c "And that, is why I feel obligated to accompany you!"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 155 } }, // 227 e "Hey, we have a good reason!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 156 } }, // 228 c "And what might that be?"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 157 } }, // 229 e "My brother found the feather, not the town guild, its a matter of family pride!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 158 } }, // 230 c "Pride has touched the chosen meouse"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 159 } }, // 231 c "Flies she towards the Castle"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 160 } }, // 232 c "But her ambition burns far too bright, and silly myice dont have any wings to myelt"
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 161 } }, // 233 mg "What?"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 162 } }, // 234 c "Nyanyanya"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 163 } }, // 235 c "Nyevermind"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 164 } }, // 236 c "Sing me a song little minstrels!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 165 } }, // 237 c "Very Nyice!"
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 166 } }, // 238 c "Now tell me little minstrels, what are your names?"
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 167 } }, // 239 a "My name is Alice"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 168 } }, // 240 e "And my name is Eily"
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 169 } }, // 241 e "What is your name?"
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 170 } }, // 242 l "My name is Leona!"
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 243 bgwhite
  { .type = type::dissolve, .dissolve = { .duration = 3.0 } }, // 244
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 171 } }, // 245 n "And so, the odd trio walked through the wheatfields and towards the castle walls"
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 172 } }, // 246 n "Upon approaching the castle walls"
  { .type = type::_return }, // 247
};

const int statements_length = (sizeof (statements)) / (sizeof (statements[0]));

}
