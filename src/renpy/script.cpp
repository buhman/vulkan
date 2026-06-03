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
  "Can we stop for a bit?", // 23
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
  "Then why are you traveling to The Castle Alysen?", // 61
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
  "Hey there... I apologize, I didn't mean to storm off like that", // 74
  "Ha ha, no problem...", // 75
  "So... Why are you traveling to Castle Alysen?", // 76
  "Alice!!!", // 77
  "If you must know, I have been summoned by the queen", // 78
  "I suspect that my poor reputation amongst the locals of Eastern Nidus has come back to haunt me", // 79
  "Though I know not what what she has summoned me for", // 80
  "Ahhhhhh", // 81
  "So then...", // 82
  "Why are YOU traveling to the Castle?", // 83
  "We are delivering a feather!!!", // 84
  "Alice no!", // 85
  "A feather that belonged to the queen herself!!!", // 86
  "Why you little...", // 87
  "A feather you say? One of the queens?", // 88
  "How on the face of Al Mot might you have aquired such a thing?", // 89
  "If it is authentic", // 90
  "Since Alice cannot keep a secret, I shall tell you", // 91
  "Seven moons ago, our town was attacked by three owls and a band of mice from the northern principalities", // 92
  "Eventually word spread to greater nearby settlements, and so", // 93
  "Messengers from the keep in Musia sent for aid from the Ravens", // 94
  "Four moons ago, the request was answered", // 95
  "And a small group of mice accompanied by two ravens a fox, and three squirrels set out to the northern principalities", // 96
  "Anyways, long story short, we drove those barbaric rats out of their home", // 97
  "They arent actual rats you know", // 98
  "Obviously, but you wont catch me speaking kindly of them", // 99
  "And you forgot the most important part", // 100
  "Yah yah, I am getting there", // 101
  "So, essentially, my brother is trained in archery, and...", // 102
  "Speed it up already", // 103
  "You tell it then!", // 104
  "My cousin found this feather in one of the highest towers of a castle far to the north", // 105
  "How do you know it belongs to the queen?", // 106
  "It said so itself above the display on the wall", // 107
  "Supposedly, it was in a room filled with treasures!", // 108
  "That is very nice and all, but what are the two of you doing out here all alone?", // 109
  "Do you expect every bird in Avia to respect your alliance with Castle Alysen?", // 110
  "What do you mean?", // 111
  "I mean, the two of you probably look like walking dinner to most creatures", // 112
  "I could go for some dinner...", // 113
  "Anyways...", // 114
  "To answer your question, upon returning to the village, the feather was taken from my brother by the needle guild", // 115
  "So... Yesterday, after sundown", // 116
  "We stole the feather from the guild hall before vanishing into the night", // 117
  "Can you imagine the look on their stupid faces, when they woke up, and not only is the feather missing", // 118
  "But so are we!", // 119
  "Hahahaha", // 120
  "Are the two of you mad?", // 121
  "I assume you are attempting to return the Queens feather?", // 122
  "Yes, we intend to deliver the feather to its rightful owner", // 123
  "Absolute madness!", // 124
  "I will follow the two of you", // 125
  "To keep you safe, that is", // 126
  "Alright!", // 127
  "Ha ha... Okay...", // 128
  "Great! Follow me, I know a shortcut! :3", // 129
  "Sounds good!", // 130
  "Oh dear!", // 131
  "And so the mice girls follow the noble cat further towards their destination", // 132
  "Nya", // 133
  "Look, your right, the castle is just up ahead!", // 134
  "Wait up", // 135
  "I told you I knew a shortcut!", // 136
  "Most people take the long way around", // 137
  "Yah because those are royal wheatfields!", // 138
  "Who cares?", // 139
  "Are you trying to get us killed?", // 140
  "Its trespassing on royal land!", // 141
  "Calm down, I have done this like a million times", // 142
  "That doesnt make me calm!", // 143
  "How can the rolling fields of wheat not calm your spirit?", // 144
  "You little mice truly are mad!", // 145
  "I like the wheat!", // 146
  "Shut up!", // 147
  "Sounds like someone needs a nap!", // 148
  "Why? because I'm not insane like you?", // 149
  "Yah, your so sane, that you decided to steal from your town and then run off alone to the country of birds", // 150
  "The power of friendship wont protect the two of you from becoming dinner", // 151
  "And that, is why I feel obligated to accompany you!", // 152
  "Hey, we have a good reason!", // 153
  "And what might that be?", // 154
  "My brother found the feather, not the town guild, its a matter of family pride!", // 155
  "Pride has touched the chosen meouse", // 156
  "Flies she towards the Castle", // 157
  "But her ambition burns far too bright, and silly mice dont have any wings to melt", // 158
  "What?", // 159
  "Nyanyanya", // 160
  "Nyevermind", // 161
  "Sing me a song little minstrels!", // 162
  "Very Nyice!", // 163
  "Now tell me little minstrels, what are your names?", // 164
  "My name is Alice", // 165
  "And my name is Eily", // 166
  "What is your name?", // 167
  "My name is Leona!", // 168
  "And so, the odd trio walked through the wheatfields and towards the castle", // 169
  "Upon approaching the gates, the three were escorted to a large room", // 170
  "They were then instructed to wait for an audience with the Queen", // 171
  "You may now present yourselves before her Majesty, Queen Alary of Alysen", // 172
  "Leona Agrepen of Elmindeer", // 173
  "Hail, your Majesty", // 174
  "Eily VeraWheat of the Western Principalities", // 175
  "Alice SeraWheat of the Western Principalities", // 176
  "I'm alright!", // 177
  "H-Hail, your majesty", // 178
  "And what is this?", // 179
  "A cat and two mice in my court?", // 180
  "Is this some kind of joke?", // 181
  "Not a joke Your Majesty, these are my friends", // 182
  "Friends?", // 183
  "Miss Agrepen, your reputation is far from acceptable", // 184
  "And I can imagine, you already know why I have summoned you here today", // 185
  "Uhhmmmm....", // 186
  "Does it have anything to do with Eastern Nidus?", // 187
  "I think you already know the answer to that", // 188
  "Your father would be rather dissapointed if he were still alive", // 189
  "Leona Agrepen, the court has found you guilty of two cases of larceny and seven cases of petty pilfering", // 190
  "Miss Agrepen, you are hereby banned from stepping foot in Eastern Nidus", // 191
  "From here on out, you shall be restricted to the central principalities of Avia", // 192
  "Owww c'mon! There is nothing to do around here!", // 193
  "Silence!", // 194
  "It is here, in the Central city of Alysen that you shall remain, where I can keep a watchful eye on you", // 195
  "Or would you prefer that I permit the request of the lesser courts to have you declawed?", // 196
  "No ><", // 197
  "Take my leniency as a display of gratitude for the services rendered by your father", // 198
  "Yes Your Majesty... Forgive me for speaking out of turn", // 199
  "Now, why have you brought these little mice before me?", // 200
  "Alary, Your Majesty, these are minstrels I met on the road to Alysen", // 201
  "They lay claim to a feather, said to be one of Your Majesty's own", // 202
  "Really?", // 203
  "And what else might the two of you claim? Alice and Eily of the West", // 204
  "I u-uhh...", // 205
  "Your Majesty, this feather was found by my brother in a castle to the north", // 206
  "So very far my cousin and I have journeyed", // 207
  "Over the mountains of Almystice", // 208
  "Beyond the deep blue waters of the Lilac bay", // 209
  "All in hopes that we might return Your Majesty's feather", // 210
  "What splendid and courageous little mice the two of you are", // 211
  "Nyanyanyanyanya", // 212
  "We also wanted to show our profound gratitude for the aid provided by Your Majesty just four moons ago", // 213
  "Please allow us to perform a song for Your Majesty and Your Majesty's court", // 214
  "I appreciate your loyalty to the crown of Corvidae little mice", // 215
  "You are most welcome to proceed with your little song", // 216
  "In the end, Leona managed to stay out of the dungeon", // 217
  "Eily and Alice both stayed in service of the queen for 7 harvests", // 218
  "before returning to their small nameless town, near the Keep of Musia", // 219
};

const int strings_length = (sizeof (strings)) / (sizeof (strings[0]));

const int strings_say_poem_index = 31;

// b'a'
static const uint32_t character_images_0[] = { 16, 18, 19 };

static constexpr uint32_t character_images_0_length = 3;

// b'b'
static const uint32_t character_images_1[] = { 12 };

static constexpr uint32_t character_images_1_length = 1;

// b'c'
static const uint32_t character_images_2[] = { 13, 14 };

static constexpr uint32_t character_images_2_length = 2;

// b'e'
static const uint32_t character_images_3[] = { 15, 17 };

static constexpr uint32_t character_images_3_length = 2;

// b'mg'
static const uint32_t character_images_4[] = { 16, 18, 19, 15, 17 };

static constexpr uint32_t character_images_4_length = 5;

// b'n'
static const uint32_t character_images_5[] = {  };

static constexpr uint32_t character_images_5_length = 0;

// b'l'
static const uint32_t character_images_6[] = { 13, 14 };

static constexpr uint32_t character_images_6_length = 2;

// b'h'
static const uint32_t character_images_7[] = {  };

static constexpr uint32_t character_images_7_length = 0;

const language::character characters[] = {
  { .characterName = "Alice", .color = 0x409b5d, .images = character_images_0, .images_length = character_images_0_length }, // 0
  { .characterName = "Queen Alary", .color = 0x0b1845, .images = character_images_1, .images_length = character_images_1_length }, // 1
  { .characterName = "Cat", .color = 0x590093, .images = character_images_2, .images_length = character_images_2_length }, // 2
  { .characterName = "Eily", .color = 0x0b6092, .images = character_images_3, .images_length = character_images_3_length }, // 3
  { .characterName = "Mouse Girls", .color = 0x000000, .images = character_images_4, .images_length = character_images_4_length }, // 4
  { .characterName = "Narrator", .color = 0x000000, .images = character_images_5, .images_length = character_images_5_length }, // 5
  { .characterName = "Leona", .color = 0x590093, .images = character_images_6, .images_length = character_images_6_length }, // 6
  { .characterName = "Herald", .color = 0x860000, .images = character_images_7, .images_length = character_images_7_length }, // 7
};

const int characters_length = (sizeof (characters)) / (sizeof (characters[0]));

const language::audio audio[] = {
  { .path = "audio/music/MistAmbience.opus.bin", .loop_end = 22.0, .audio_flags = audio::music, .gain = 1.0 }, // 0 music/MistAmbience.ogg
  { .path = "audio/sfx/Chime.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 1 sfx/Chime.ogg
  { .path = "audio/nara/n1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 2 nara/n1.ogg
  { .path = "audio/nara/n2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 3 nara/n2.ogg
  { .path = "audio/nara/n3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 4 nara/n3.ogg
  { .path = "audio/music/TinyForestMinstrels.opus.bin", .loop_end = 44.0, .audio_flags = audio::music, .gain = 0.45 }, // 5 music/TinyForestMinstrels.ogg
  { .path = "audio/nara/n4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 6 nara/n4.ogg
  { .path = "audio/alice/a1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 7 alice/a1.ogg
  { .path = "audio/eily/e1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 8 eily/e1.ogg
  { .path = "audio/alice/a2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 9 alice/a2.ogg
  { .path = "audio/eily/e2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 10 eily/e2.ogg
  { .path = "audio/alice/a3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 11 alice/a3.ogg
  { .path = "audio/eily/e3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 12 eily/e3.ogg
  { .path = "audio/alice/a4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 13 alice/a4.ogg
  { .path = "audio/alice/a5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 14 alice/a5.ogg
  { .path = "audio/eily/e4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 15 eily/e4.ogg
  { .path = "audio/eily/e5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 16 eily/e5.ogg
  { .path = "audio/alice/a6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 17 alice/a6.ogg
  { .path = "audio/eily/e6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 18 eily/e6.ogg
  { .path = "audio/alice/a7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 19 alice/a7.ogg
  { .path = "audio/eily/e7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 20 eily/e7.ogg
  { .path = "audio/nara/n5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 21 nara/n5.ogg
  { .path = "audio/music/PhrygianButterflies.opus.bin", .loop_end = 40.2, .audio_flags = audio::music, .gain = 0.5 }, // 22 music/PhrygianButterflies.ogg
  { .path = "audio/eily/e8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 23 eily/e8.ogg
  { .path = "audio/alice/a8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 24 alice/a8.ogg
  { .path = "audio/eily/e9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 25 eily/e9.ogg
  { .path = "audio/eily/e10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 26 eily/e10.ogg
  { .path = "audio/alice/a9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 27 alice/a9.ogg
  { .path = "audio/eily/e11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 28 eily/e11.ogg
  { .path = "audio/eily/e12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 29 eily/e12.ogg
  { .path = "audio/alice/a10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 30 alice/a10.ogg
  { .path = "audio/eily/e13.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 31 eily/e13.ogg
  { .path = "audio/eily/e14.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 32 eily/e14.ogg
  { .path = "audio/alice/a11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 33 alice/a11.ogg
  { .path = "audio/eily/e15.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 34 eily/e15.ogg
  { .path = "audio/poem/EleanorTheHero.opus.bin", .loop_end = 0.0, .audio_flags = audio::poem, .gain = 1.0 }, // 35 poem/EleanorTheHero.ogg
  { .path = "audio/eily/e16.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 36 eily/e16.ogg
  { .path = "audio/alice/a12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 37 alice/a12.ogg
  { .path = "audio/leona/c1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 38 leona/c1.ogg
  { .path = "audio/music/ScaredMice.opus.bin", .loop_end = 8.0, .audio_flags = audio::music, .gain = 1.0 }, // 39 music/ScaredMice.ogg
  { .path = "audio/mousegirls/mg1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 40 mousegirls/mg1.ogg
  { .path = "audio/leona/c2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 41 leona/c2.ogg
  { .path = "audio/leona/c3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 42 leona/c3.ogg
  { .path = "audio/alice/a14.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 43 alice/a14.ogg
  { .path = "audio/eily/e18.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 44 eily/e18.ogg
  { .path = "audio/eily/e19.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 45 eily/e19.ogg
  { .path = "audio/leona/c4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 46 leona/c4.ogg
  { .path = "audio/leona/c5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 47 leona/c5.ogg
  { .path = "audio/leona/c6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 48 leona/c6.ogg
  { .path = "audio/eily/e20.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 49 eily/e20.ogg
  { .path = "audio/alice/a15.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 50 alice/a15.ogg
  { .path = "audio/eily/e21.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 51 eily/e21.ogg
  { .path = "audio/leona/c7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 52 leona/c7.ogg
  { .path = "audio/leona/c8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 53 leona/c8.ogg
  { .path = "audio/eily/e22.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 54 eily/e22.ogg
  { .path = "audio/leona/c9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 55 leona/c9.ogg
  { .path = "audio/eily/e23.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 56 eily/e23.ogg
  { .path = "audio/leona/c10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 57 leona/c10.ogg
  { .path = "audio/eily/e24.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 58 eily/e24.ogg
  { .path = "audio/leona/c11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 59 leona/c11.ogg
  { .path = "audio/eily/e25.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 60 eily/e25.ogg
  { .path = "audio/leona/c12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 61 leona/c12.ogg
  { .path = "audio/leona/c13.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 62 leona/c13.ogg
  { .path = "audio/eily/e26.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 63 eily/e26.ogg
  { .path = "audio/eily/e27.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 64 eily/e27.ogg
  { .path = "audio/leona/c14.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 65 leona/c14.ogg
  { .path = "audio/alice/a16.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 66 alice/a16.ogg
  { .path = "audio/leona/c15.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 67 leona/c15.ogg
  { .path = "audio/leona/c16.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 68 leona/c16.ogg
  { .path = "audio/leona/c17.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 69 leona/c17.ogg
  { .path = "audio/alice/a17.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 70 alice/a17.ogg
  { .path = "audio/eily/e28.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 71 eily/e28.ogg
  { .path = "audio/alice/a18.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 72 alice/a18.ogg
  { .path = "audio/eily/e29.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 73 eily/e29.ogg
  { .path = "audio/nara/n6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 74 nara/n6.ogg
  { .path = "audio/eily/e30.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 75 eily/e30.ogg
  { .path = "audio/alice/a19.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 76 alice/a19.ogg
  { .path = "audio/eily/e31.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 77 eily/e31.ogg
  { .path = "audio/alice/a20.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 78 alice/a20.ogg
  { .path = "audio/leona/c18.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 79 leona/c18.ogg
  { .path = "audio/eily/e32.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 80 eily/e32.ogg
  { .path = "audio/alice/a21.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 81 alice/a21.ogg
  { .path = "audio/eily/e33.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 82 eily/e33.ogg
  { .path = "audio/leona/c19.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 83 leona/c19.ogg
  { .path = "audio/leona/c20.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 84 leona/c20.ogg
  { .path = "audio/leona/c21.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 85 leona/c21.ogg
  { .path = "audio/alice/a22.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 86 alice/a22.ogg
  { .path = "audio/leona/c22.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 87 leona/c22.ogg
  { .path = "audio/leona/c23.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 88 leona/c23.ogg
  { .path = "audio/alice/a23.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 89 alice/a23.ogg
  { .path = "audio/eily/e34.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 90 eily/e34.ogg
  { .path = "audio/alice/a24.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 91 alice/a24.ogg
  { .path = "audio/eily/e35.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 92 eily/e35.ogg
  { .path = "audio/leona/c24.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 93 leona/c24.ogg
  { .path = "audio/leona/c25.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 94 leona/c25.ogg
  { .path = "audio/leona/c26.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 95 leona/c26.ogg
  { .path = "audio/eily/e36.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 96 eily/e36.ogg
  { .path = "audio/eily/e37.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 97 eily/e37.ogg
  { .path = "audio/eily/e38.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 98 eily/e38.ogg
  { .path = "audio/eily/e39.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 99 eily/e39.ogg
  { .path = "audio/eily/e40.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 100 eily/e40.ogg
  { .path = "audio/eily/e41.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 101 eily/e41.ogg
  { .path = "audio/eily/e42.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 102 eily/e42.ogg
  { .path = "audio/alice/a25.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 103 alice/a25.ogg
  { .path = "audio/eily/e43.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 104 eily/e43.ogg
  { .path = "audio/alice/a26.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 105 alice/a26.ogg
  { .path = "audio/eily/e44.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 106 eily/e44.ogg
  { .path = "audio/eily/e45.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 107 eily/e45.ogg
  { .path = "audio/alice/a27.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 108 alice/a27.ogg
  { .path = "audio/eily/e46.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 109 eily/e46.ogg
  { .path = "audio/alice/a28.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 110 alice/a28.ogg
  { .path = "audio/leona/c27.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 111 leona/c27.ogg
  { .path = "audio/eily/e47.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 112 eily/e47.ogg
  { .path = "audio/alice/a29.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 113 alice/a29.ogg
  { .path = "audio/leona/c28.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 114 leona/c28.ogg
  { .path = "audio/leona/c29.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 115 leona/c29.ogg
  { .path = "audio/eily/e48.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 116 eily/e48.ogg
  { .path = "audio/leona/c30.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 117 leona/c30.ogg
  { .path = "audio/alice/a30.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 118 alice/a30.ogg
  { .path = "audio/eily/e49.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 119 eily/e49.ogg
  { .path = "audio/eily/e50.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 120 eily/e50.ogg
  { .path = "audio/eily/e51.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 121 eily/e51.ogg
  { .path = "audio/eily/e52.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 122 eily/e52.ogg
  { .path = "audio/eily/e53.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 123 eily/e53.ogg
  { .path = "audio/eily/e54.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 124 eily/e54.ogg
  { .path = "audio/alice/a31.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 125 alice/a31.ogg
  { .path = "audio/leona/c31.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 126 leona/c31.ogg
  { .path = "audio/leona/c32.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 127 leona/c32.ogg
  { .path = "audio/alice/a32.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 128 alice/a32.ogg
  { .path = "audio/leona/c33.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 129 leona/c33.ogg
  { .path = "audio/mousegirls/mg2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 130 mousegirls/mg2.ogg
  { .path = "audio/leona/c34.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 131 leona/c34.ogg
  { .path = "audio/leona/c35.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 132 leona/c35.ogg
  { .path = "audio/alice/a33.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 133 alice/a33.ogg
  { .path = "audio/eily/e55.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 134 eily/e55.ogg
  { .path = "audio/leona/c36.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 135 leona/c36.ogg
  { .path = "audio/alice/a34.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 136 alice/a34.ogg
  { .path = "audio/eily/e56.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 137 eily/e56.ogg
  { .path = "audio/nara/n7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 138 nara/n7.ogg
  { .path = "audio/music/WheatFields.opus.bin", .loop_end = 34.0, .audio_flags = audio::music, .gain = 1.0 }, // 139 music/WheatFields.ogg
  { .path = "audio/leona/c37.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 140 leona/c37.ogg
  { .path = "audio/alice/a35.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 141 alice/a35.ogg
  { .path = "audio/eily/e57.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 142 eily/e57.ogg
  { .path = "audio/leona/c38.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 143 leona/c38.ogg
  { .path = "audio/leona/c39.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 144 leona/c39.ogg
  { .path = "audio/eily/e58.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 145 eily/e58.ogg
  { .path = "audio/alice/a36.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 146 alice/a36.ogg
  { .path = "audio/eily/e59.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 147 eily/e59.ogg
  { .path = "audio/eily/e60.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 148 eily/e60.ogg
  { .path = "audio/leona/c40.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 149 leona/c40.ogg
  { .path = "audio/eily/e61.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 150 eily/e61.ogg
  { .path = "audio/leona/c41.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 151 leona/c41.ogg
  { .path = "audio/leona/c42.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 152 leona/c42.ogg
  { .path = "audio/alice/a37.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 153 alice/a37.ogg
  { .path = "audio/eily/e62.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 154 eily/e62.ogg
  { .path = "audio/leona/c43.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 155 leona/c43.ogg
  { .path = "audio/eily/e63.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 156 eily/e63.ogg
  { .path = "audio/leona/c44.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 157 leona/c44.ogg
  { .path = "audio/leona/c45.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 158 leona/c45.ogg
  { .path = "audio/leona/c46.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 159 leona/c46.ogg
  { .path = "audio/eily/e64.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 160 eily/e64.ogg
  { .path = "audio/leona/c47.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 161 leona/c47.ogg
  { .path = "audio/eily/e65.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 162 eily/e65.ogg
  { .path = "audio/leona/c48.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 163 leona/c48.ogg
  { .path = "audio/leona/c49.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 164 leona/c49.ogg
  { .path = "audio/leona/c50.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 165 leona/c50.ogg
  { .path = "audio/mousegirls/mg3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 166 mousegirls/mg3.ogg
  { .path = "audio/leona/c51.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 167 leona/c51.ogg
  { .path = "audio/leona/c52.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 168 leona/c52.ogg
  { .path = "audio/leona/c53.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 169 leona/c53.ogg
  { .path = "audio/poem/KiriStella.opus.bin", .loop_end = 0.0, .audio_flags = audio::poem, .gain = 1.0 }, // 170 poem/KiriStella.ogg
  { .path = "audio/leona/c54.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 171 leona/c54.ogg
  { .path = "audio/leona/c55.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 172 leona/c55.ogg
  { .path = "audio/alice/a39.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 173 alice/a39.ogg
  { .path = "audio/eily/e67.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 174 eily/e67.ogg
  { .path = "audio/eily/e68.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 175 eily/e68.ogg
  { .path = "audio/leona/c56.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 176 leona/c56.ogg
  { .path = "audio/nara/n8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 177 nara/n8.ogg
  { .path = "audio/nara/n9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 178 nara/n9.ogg
  { .path = "audio/nara/n10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 179 nara/n10.ogg
  { .path = "audio/hera/h1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 180 hera/h1.ogg
  { .path = "audio/music/Preludium.opus.bin", .loop_end = 58.2, .audio_flags = audio::music, .gain = 0.45 }, // 181 music/Preludium.ogg
  { .path = "audio/hera/h2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 182 hera/h2.ogg
  { .path = "audio/leona/c57.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 183 leona/c57.ogg
  { .path = "audio/hera/h3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 184 hera/h3.ogg
  { .path = "audio/eily/e69.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 185 eily/e69.ogg
  { .path = "audio/hera/h4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 186 hera/h4.ogg
  { .path = "audio/sfx/Glass.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 187 sfx/Glass.ogg
  { .path = "audio/alice/a40.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 188 alice/a40.ogg
  { .path = "audio/alice/a41.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 189 alice/a41.ogg
  { .path = "audio/leona/c58.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 190 leona/c58.ogg
  { .path = "audio/bird/b1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 191 bird/b1.ogg
  { .path = "audio/bird/b2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 192 bird/b2.ogg
  { .path = "audio/bird/b3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 193 bird/b3.ogg
  { .path = "audio/leona/c59.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 194 leona/c59.ogg
  { .path = "audio/eily/e70.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 195 eily/e70.ogg
  { .path = "audio/bird/b4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 196 bird/b4.ogg
  { .path = "audio/bird/b5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 197 bird/b5.ogg
  { .path = "audio/leona/c60.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 198 leona/c60.ogg
  { .path = "audio/leona/c61.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 199 leona/c61.ogg
  { .path = "audio/bird/b6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 200 bird/b6.ogg
  { .path = "audio/bird/b7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 201 bird/b7.ogg
  { .path = "audio/leona/c0.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 202 leona/c0.ogg
  { .path = "audio/bird/b8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 203 bird/b8.ogg
  { .path = "audio/bird/b9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 204 bird/b9.ogg
  { .path = "audio/bird/b10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 205 bird/b10.ogg
  { .path = "audio/leona/c62.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 206 leona/c62.ogg
  { .path = "audio/bird/b11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 207 bird/b11.ogg
  { .path = "audio/bird/b12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 208 bird/b12.ogg
  { .path = "audio/bird/b13.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 209 bird/b13.ogg
  { .path = "audio/leona/c63.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 210 leona/c63.ogg
  { .path = "audio/bird/b14.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 211 bird/b14.ogg
  { .path = "audio/leona/c64.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 212 leona/c64.ogg
  { .path = "audio/bird/b15.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 213 bird/b15.ogg
  { .path = "audio/leona/c65.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 214 leona/c65.ogg
  { .path = "audio/leona/c66.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 215 leona/c66.ogg
  { .path = "audio/bird/b16.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 216 bird/b16.ogg
  { .path = "audio/bird/b17.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 217 bird/b17.ogg
  { .path = "audio/alice/a42.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 218 alice/a42.ogg
  { .path = "audio/eily/e71.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 219 eily/e71.ogg
  { .path = "audio/eily/e72.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 220 eily/e72.ogg
  { .path = "audio/eily/e73.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 221 eily/e73.ogg
  { .path = "audio/eily/e74.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 222 eily/e74.ogg
  { .path = "audio/eily/e75.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 223 eily/e75.ogg
  { .path = "audio/eily/e76.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 224 eily/e76.ogg
  { .path = "audio/bird/b18.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 225 bird/b18.ogg
  { .path = "audio/leona/c67.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 226 leona/c67.ogg
  { .path = "audio/alice/a43.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 227 alice/a43.ogg
  { .path = "audio/eily/e77.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 228 eily/e77.ogg
  { .path = "audio/bird/b19.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 229 bird/b19.ogg
  { .path = "audio/bird/b20.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 230 bird/b20.ogg
  { .path = "audio/poem/BirdSong.opus.bin", .loop_end = 0.0, .audio_flags = audio::poem, .gain = 1.0 }, // 231 poem/BirdSong.ogg
  { .path = "audio/nara/n11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 232 nara/n11.ogg
  { .path = "audio/nara/n12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 233 nara/n12.ogg
  { .path = "audio/nara/n13.opus.bin", .loop_end = 0.0, .audio_flags = 0, .gain = 1.0 }, // 234 nara/n13.ogg
};

const int audio_length = (sizeof (audio)) / (sizeof (audio[0]));

const language::image images[] = {
  { .path = "data/renpy/images/flowers.dds", .is_character_image = false }, // 0 flowers.png
  { .path = "data/renpy/images/button1.dds", .is_character_image = false }, // 1 button1.png
  { .path = "data/renpy/images/button2.dds", .is_character_image = false }, // 2 button2.png
  { .path = "data/renpy/images/bg/forest1.dds", .is_character_image = false }, // 3 bg/forest1.png
  { .path = "data/renpy/images/bg/forest2.dds", .is_character_image = false }, // 4 bg/forest2.png
  { .path = "data/renpy/images/bg/flowerfield1.dds", .is_character_image = false }, // 5 bg/flowerfield1.png
  { .path = "data/renpy/images/bg/wheatfield1.dds", .is_character_image = false }, // 6 bg/wheatfield1.png
  { .path = "data/renpy/images/bg/castle1.dds", .is_character_image = false }, // 7 bg/castle1.png
  { .path = "data/renpy/images/bg/castle2.dds", .is_character_image = false }, // 8 bg/castle2.png
  { .path = "data/renpy/images/bg/castle3.dds", .is_character_image = false }, // 9 bg/castle3.png
  { .path = "data/renpy/images/bg/castle4.dds", .is_character_image = false }, // 10 bg/castle4.png
  { .path = "data/renpy/images/end.dds", .is_character_image = false }, // 11 end.png
  { .path = "data/renpy/images/ch/ibird/Bird.dds", .is_character_image = true }, // 12 ch/ibird/Bird.png
  { .path = "data/renpy/images/ch/icat/Cat.dds", .is_character_image = true }, // 13 ch/icat/Cat.png
  { .path = "data/renpy/images/ch/icat/Catw.dds", .is_character_image = true }, // 14 ch/icat/Catw.png
  { .path = "data/renpy/images/ch/ieily/Eily.dds", .is_character_image = true }, // 15 ch/ieily/Eily.png
  { .path = "data/renpy/images/ch/ialice/Alice.dds", .is_character_image = true }, // 16 ch/ialice/Alice.png
  { .path = "data/renpy/images/ch/ieily/Seily.dds", .is_character_image = true }, // 17 ch/ieily/Seily.png
  { .path = "data/renpy/images/ch/ialice/Salice.dds", .is_character_image = true }, // 18 ch/ialice/Salice.png
  { .path = "data/renpy/images/ch/ialice/Walice.dds", .is_character_image = true }, // 19 ch/ialice/Walice.png
};

const int images_length = (sizeof (images)) / (sizeof (images[0]));

const language::option options[] = {
  { .string = "Complain", .statementIndex = 28 }, // 0
  { .string = "Rationalize", .statementIndex = 43 }, // 1
  { .string = "Good idea", .statementIndex = 83 }, // 2
  { .string = "I am too tired", .statementIndex = 92 }, // 3
  { .string = "Beg for mercy", .statementIndex = 119 }, // 4
  { .string = "Run", .statementIndex = 122 }, // 5
  { .string = "Sarcasm", .statementIndex = 290 }, // 6
  { .string = "Nod", .statementIndex = 293 }, // 7
  { .string = "Agree", .statementIndex = 325 }, // 8
  { .string = "Stay Silent", .statementIndex = 328 }, // 9
};

const int options_length = (sizeof (options)) / (sizeof (options[0]));

const language::dissolve dissolves[] = {
  { .duration = 3.0, .first_statement = 4, .count = 1 },
  { .duration = 3.0, .first_statement = 15, .count = 2 },
  { .duration = 1.0, .first_statement = 54, .count = 2 },
  { .duration = 1.0, .first_statement = 59, .count = 1 },
  { .duration = 3.0, .first_statement = 193, .count = 2 },
  { .duration = 3.0, .first_statement = 197, .count = 1 },
  { .duration = 2.0, .first_statement = 343, .count = 2 },
  { .duration = 1.3, .first_statement = 347, .count = 3 },
  { .duration = 3.0, .first_statement = 428, .count = 1 },
  { .duration = 2.0, .first_statement = 437, .count = 2 },
  { .duration = 14.0, .first_statement = 548, .count = 1 },
};

const int dissolves_length = (sizeof (dissolves)) / (sizeof (dissolves[0]));

const language::statement statements[] = {
  { .type = type::play, .play = { .audioIndex = 0 } }, // 0 music/MistAmbience.ogg
  { .type = type::scene_color, .scene_color = { .color = 0x000000 } }, // 1 bgblue
  { .type = type::pause, .pause = { .duration = 1.0 } }, // 2
  { .type = type::play, .play = { .audioIndex = 1 } }, // 3 sfx/Chime.ogg
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 4 bgwhite
  { .type = type::voice, .voice = { .audioIndex = 2 } }, // 5 nara/n1.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 0 } }, // 6 n "Far over the mountains of Almystice"
  { .type = type::voice, .voice = { .audioIndex = 3 } }, // 7 nara/n2.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 1 } }, // 8 n "Beyond the tumultuous waters of the Lilac Bay"
  { .type = type::voice, .voice = { .audioIndex = 4 } }, // 9 nara/n3.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 2 } }, // 10 n "And across the vast fields of Alysen"
  { .type = type::stop, .stop = { .audioIndex = 0, .fadeout = 4.2 } }, // 11 MistAmbience
  { .type = type::play, .play = { .audioIndex = 5 } }, // 12 music/TinyForestMinstrels.ogg
  { .type = type::voice, .voice = { .audioIndex = 6 } }, // 13 nara/n4.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 3 } }, // 14 n "Tiny minstrels can be heard amongst the trees"
  { .type = type::scene, .scene = { .imageIndex = 3 } }, // 15 bgforest1
  { .type = type::play, .play = { .audioIndex = 1 } }, // 16 sfx/Chime.ogg
  { .type = type::show, .show = { .imageIndex = 16, .transformIndex = transform::left, } }, // 17 al
  { .type = type::voice, .voice = { .audioIndex = 7 } }, // 18 alice/a1.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 4 } }, // 19 a "Are we almost there?"
  { .type = type::show, .show = { .imageIndex = 15, .transformIndex = transform::right, } }, // 20 ei
  { .type = type::voice, .voice = { .audioIndex = 8 } }, // 21 eily/e1.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 5 } }, // 22 e "Hmmm... Not really"
  { .type = type::voice, .voice = { .audioIndex = 9 } }, // 23 alice/a2.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 6 } }, // 24 a "How much further have we to go?"
  { .type = type::voice, .voice = { .audioIndex = 10 } }, // 25 eily/e2.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 7 } }, // 26 e "About two more moons"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 0 } }, // 27 "Complain", "Rationalize"
  { .type = type::voice, .voice = { .audioIndex = 11 } }, // 28 alice/a3.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 8 } }, // 29 a "We are still sooo far awayyy"
  { .type = type::voice, .voice = { .audioIndex = 12 } }, // 30 eily/e3.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 9 } }, // 31 e "And it will be even further if you dont stop complaining"
  { .type = type::voice, .voice = { .audioIndex = 13 } }, // 32 alice/a4.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 10 } }, // 33 a "Easy for you to say, all you have to carry is a little memory pipe!"
  { .type = type::voice, .voice = { .audioIndex = 14 } }, // 34 alice/a5.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 11 } }, // 35 a "I'm tired ><"
  { .type = type::voice, .voice = { .audioIndex = 15 } }, // 36 eily/e4.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 12 } }, // 37 e "Don't start whining now!"
  { .type = type::voice, .voice = { .audioIndex = 16 } }, // 38 eily/e5.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 13 } }, // 39 e "You need to remember why we have come all this way"
  { .type = type::voice, .voice = { .audioIndex = 17 } }, // 40 alice/a6.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 14 } }, // 41 a "I understand... I suppose it is for an important purpose"
  { .type = type::jump, .jump = { .statementIndex = 46 } }, // 42 internal jump (b'__menu_end', 0)
  { .type = type::voice, .voice = { .audioIndex = 17 } }, // 43 alice/a6.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 14 } }, // 44 a "I understand... I suppose it is for an important purpose"
  { .type = type::jump, .jump = { .statementIndex = 46 } }, // 45 internal jump (b'__menu_end', 0)
  { .type = type::jump, .jump = { .statementIndex = 47 } }, // 46 mainbranch1
  { .type = type::voice, .voice = { .audioIndex = 18 } }, // 47 eily/e6.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 15 } }, // 48 e "We're almost out of the forest, we can take a little break once we clear the tree line"
  { .type = type::voice, .voice = { .audioIndex = 19 } }, // 49 alice/a7.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 16 } }, // 50 a "Is that where the flora field is?"
  { .type = type::voice, .voice = { .audioIndex = 20 } }, // 51 eily/e7.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 17 } }, // 52 e "Why yes, If I remember correctly, it should be just up ahead"
  { .type = type::stop, .stop = { .audioIndex = 5, .fadeout = 5.5 } }, // 53 TinyForestMinstrels
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 54 bgwhite
  { .type = type::play, .play = { .audioIndex = 1 } }, // 55 sfx/Chime.ogg
  { .type = type::voice, .voice = { .audioIndex = 21 } }, // 56 nara/n5.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 18 } }, // 57 n "As the minstrel mice girls continue along the path, the forest opens up into a beautiful field of flowers"
  { .type = type::play, .play = { .audioIndex = 22 } }, // 58 music/PhrygianButterflies.ogg
  { .type = type::scene, .scene = { .imageIndex = 5 } }, // 59 bgflower1
  { .type = type::show, .show = { .imageIndex = 15, .transformIndex = transform::right, } }, // 60 ei
  { .type = type::voice, .voice = { .audioIndex = 23 } }, // 61 eily/e8.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 19 } }, // 62 e "Look at all the butterflies! They are all so pretty!"
  { .type = type::show, .show = { .imageIndex = 16, .transformIndex = transform::left, } }, // 63 al
  { .type = type::voice, .voice = { .audioIndex = 24 } }, // 64 alice/a8.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 20 } }, // 65 a "This place is like a dream..."
  { .type = type::voice, .voice = { .audioIndex = 25 } }, // 66 eily/e9.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 21 } }, // 67 e "There are so many flowers this time of year"
  { .type = type::voice, .voice = { .audioIndex = 26 } }, // 68 eily/e10.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 22 } }, // 69 e "I told you it would be worth the journey!"
  { .type = type::voice, .voice = { .audioIndex = 27 } }, // 70 alice/a9.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 23 } }, // 71 a "Can we stop for a bit?"
  { .type = type::voice, .voice = { .audioIndex = 28 } }, // 72 eily/e11.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 24 } }, // 73 e "Of course"
  { .type = type::voice, .voice = { .audioIndex = 29 } }, // 74 eily/e12.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 25 } }, // 75 e "Ya know, Its a shame we didnt save some of those giant strawberries you found"
  { .type = type::voice, .voice = { .audioIndex = 30 } }, // 76 alice/a10.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 26 } }, // 77 a "I told you not to eat them all!"
  { .type = type::voice, .voice = { .audioIndex = 31 } }, // 78 eily/e13.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 27 } }, // 79 e "Yah yah"
  { .type = type::voice, .voice = { .audioIndex = 32 } }, // 80 eily/e14.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 28 } }, // 81 e "Anyways, shall I recite a tale?"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 2 } }, // 82 "Good idea", "I am too tired"
  { .type = type::stop, .stop = { .audioIndex = 22, .fadeout = 4.2 } }, // 83 PhrygianButterflies
  { .type = type::voice, .voice = { .audioIndex = 33 } }, // 84 alice/a11.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 29 } }, // 85 a "Why dont you sing the story of Eleanor the Hero!"
  { .type = type::voice, .voice = { .audioIndex = 34 } }, // 86 eily/e15.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 30 } }, // 87 e "Sure"
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 31 } }, // 88 e "..."
  { .type = type::play, .play = { .audioIndex = 35 } }, // 89 poem/EleanorTheHero.ogg
  { .type = type::pause, .pause = { .duration = 38.8875 } }, // 90
  { .type = type::jump, .jump = { .statementIndex = 98 } }, // 91 internal jump (b'__menu_end', 1)
  { .type = type::voice, .voice = { .audioIndex = 36 } }, // 92 eily/e16.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 32 } }, // 93 e "Serves you right for scaring those elephant-dogs"
  { .type = type::stop, .stop = { .audioIndex = 22, .fadeout = 4.2 } }, // 94 PhrygianButterflies
  { .type = type::voice, .voice = { .audioIndex = 37 } }, // 95 alice/a12.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 33 } }, // 96 a "They were asking for it, you know"
  { .type = type::jump, .jump = { .statementIndex = 98 } }, // 97 internal jump (b'__menu_end', 1)
  { .type = type::jump, .jump = { .statementIndex = 99 } }, // 98 mainbranch2
  { .type = type::hide, .hide = { .imageIndex = 15 } }, // 99 ei
  { .type = type::show, .show = { .imageIndex = 14, .transformIndex = transform::right, } }, // 100 catw
  { .type = type::show, .show = { .imageIndex = 15, .transformIndex = xflip | transform::centerleft, } }, // 101 ei
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 34 } }, // 102 c "Rawrrrr"
  { .type = type::play, .play = { .audioIndex = 38 } }, // 103 leona/c1.ogg
  { .type = type::pause, .pause = { .duration = 0.7 } }, // 104
  { .type = type::hide, .hide = { .imageIndex = 14 } }, // 105 catw
  { .type = type::show, .show = { .imageIndex = 13, .transformIndex = transform::right, } }, // 106 cat
  { .type = type::play, .play = { .audioIndex = 39 } }, // 107 music/ScaredMice.ogg
  { .type = type::hide, .hide = { .imageIndex = 15 } }, // 108 ei
  { .type = type::hide, .hide = { .imageIndex = 16 } }, // 109 al
  { .type = type::show, .show = { .imageIndex = 17, .transformIndex = xflip | transform::centerleft, } }, // 110 sei
  { .type = type::show, .show = { .imageIndex = 18, .transformIndex = transform::left, } }, // 111 sal
  { .type = type::voice, .voice = { .audioIndex = 40 } }, // 112 mousegirls/mg1.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 35 } }, // 113 mg "AHHHHHHHHHH!!!!!"
  { .type = type::voice, .voice = { .audioIndex = 41 } }, // 114 leona/c2.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 36 } }, // 115 c "Nyanyanyanya"
  { .type = type::voice, .voice = { .audioIndex = 42 } }, // 116 leona/c3.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 37 } }, // 117 c "Well, what do we have here? If it isn't two little meowse girls, all alone amongst the flowers"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 4 } }, // 118 "Beg for mercy", "Run"
  { .type = type::voice, .voice = { .audioIndex = 43 } }, // 119 alice/a14.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 38 } }, // 120 a "Please don't eat us!!!"
  { .type = type::jump, .jump = { .statementIndex = 127 } }, // 121 internal jump (b'__menu_end', 2)
  { .type = type::voice, .voice = { .audioIndex = 44 } }, // 122 eily/e18.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 39 } }, // 123 e "Alice don't run, our only chance is through pleading!"
  { .type = type::voice, .voice = { .audioIndex = 45 } }, // 124 eily/e19.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 40 } }, // 125 e "Please don't eat us, miss kitty cat!!! ><"
  { .type = type::jump, .jump = { .statementIndex = 127 } }, // 126 internal jump (b'__menu_end', 2)
  { .type = type::jump, .jump = { .statementIndex = 128 } }, // 127 mainbranch3
  { .type = type::stop, .stop = { .audioIndex = 39, .fadeout = 2.0 } }, // 128 ScaredMice
  { .type = type::voice, .voice = { .audioIndex = 46 } }, // 129 leona/c4.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 41 } }, // 130 c "I'm not gonna eat you nyanyanya"
  { .type = type::hide, .hide = { .imageIndex = 18 } }, // 131 sal
  { .type = type::show, .show = { .imageIndex = 16, .transformIndex = transform::left, } }, // 132 al
  { .type = type::play, .play = { .audioIndex = 5 } }, // 133 music/TinyForestMinstrels.ogg
  { .type = type::voice, .voice = { .audioIndex = 47 } }, // 134 leona/c5.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 42 } }, // 135 c "I just want to know what two little meowses are doing so very far away from home"
  { .type = type::hide, .hide = { .imageIndex = 17 } }, // 136 sei
  { .type = type::show, .show = { .imageIndex = 15, .transformIndex = xflip | transform::centerleft, } }, // 137 ei
  { .type = type::voice, .voice = { .audioIndex = 48 } }, // 138 leona/c6.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 43 } }, // 139 c "Also, are you minstrels?"
  { .type = type::voice, .voice = { .audioIndex = 49 } }, // 140 eily/e20.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 44 } }, // 141 e "Y-Yes"
  { .type = type::voice, .voice = { .audioIndex = 50 } }, // 142 alice/a15.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 45 } }, // 143 a "W-We are on a quest to Castle Alysen..."
  { .type = type::voice, .voice = { .audioIndex = 51 } }, // 144 eily/e21.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 46 } }, // 145 e "Shh don't tell her that"
  { .type = type::voice, .voice = { .audioIndex = 52 } }, // 146 leona/c7.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 47 } }, // 147 c "The Castle of Alysen you say?!?"
  { .type = type::voice, .voice = { .audioIndex = 53 } }, // 148 leona/c8.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 48 } }, // 149 c "Why, that's where I am headed!"
  { .type = type::voice, .voice = { .audioIndex = 54 } }, // 150 eily/e22.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 49 } }, // 151 e "You don't say..."
  { .type = type::voice, .voice = { .audioIndex = 55 } }, // 152 leona/c9.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 50 } }, // 153 c "Yah, I do actually"
  { .type = type::voice, .voice = { .audioIndex = 56 } }, // 154 eily/e23.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 51 } }, // 155 e "So... Why might you be traveling to the castle?"
  { .type = type::voice, .voice = { .audioIndex = 57 } }, // 156 leona/c10.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 52 } }, // 157 c "I belong to the lineage of Agrepen"
  { .type = type::voice, .voice = { .audioIndex = 58 } }, // 158 eily/e24.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 53 } }, // 159 e "And what might that mean?"
  { .type = type::voice, .voice = { .audioIndex = 59 } }, // 160 leona/c11.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 54 } }, // 161 c "The Agrepens are a long line of felines loyal to the crown of corvidae"
  { .type = type::voice, .voice = { .audioIndex = 60 } }, // 162 eily/e25.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 55 } }, // 163 e "Really? That must mean you are a noble?"
  { .type = type::voice, .voice = { .audioIndex = 61 } }, // 164 leona/c12.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 56 } }, // 165 c "Well, not really..."
  { .type = type::voice, .voice = { .audioIndex = 62 } }, // 166 leona/c13.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 57 } }, // 167 c "My father was one of the queens knights many years ago"
  { .type = type::voice, .voice = { .audioIndex = 63 } }, // 168 eily/e26.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 58 } }, // 169 e "Ah I see"
  { .type = type::voice, .voice = { .audioIndex = 64 } }, // 170 eily/e27.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 59 } }, // 171 e "So do you live at the castle or something?"
  { .type = type::voice, .voice = { .audioIndex = 65 } }, // 172 leona/c14.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 60 } }, // 173 c "Well, no..."
  { .type = type::voice, .voice = { .audioIndex = 66 } }, // 174 alice/a16.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 61 } }, // 175 a "Then why are you traveling to The Castle Alysen?"
  { .type = type::voice, .voice = { .audioIndex = 67 } }, // 176 leona/c15.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 62 } }, // 177 c "uhhh"
  { .type = type::play, .play = { .audioIndex = 0 } }, // 178 music/MistAmbience.ogg
  { .type = type::stop, .stop = { .audioIndex = 5, .fadeout = 2.0 } }, // 179 TinyForestMinstrels
  { .type = type::voice, .voice = { .audioIndex = 68 } }, // 180 leona/c16.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 63 } }, // 181 c "I DONT NEED TO BE PRESSURED BY LITTLE MICE TO SAY ANYTHING!!!!"
  { .type = type::voice, .voice = { .audioIndex = 69 } }, // 182 leona/c17.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 64 } }, // 183 c "GOOD DAY!"
  { .type = type::hide, .hide = { .imageIndex = 13 } }, // 184 cat
  { .type = type::voice, .voice = { .audioIndex = 70 } }, // 185 alice/a17.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 65 } }, // 186 a "Wha..."
  { .type = type::voice, .voice = { .audioIndex = 71 } }, // 187 eily/e28.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 66 } }, // 188 e "Phew, I was scared she was gonna follow us the whole way"
  { .type = type::voice, .voice = { .audioIndex = 72 } }, // 189 alice/a18.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 67 } }, // 190 a "She didn't seem so bad"
  { .type = type::voice, .voice = { .audioIndex = 73 } }, // 191 eily/e29.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 68 } }, // 192 e "Are you kidding? She's a crazy kitty!"
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 193 bgwhite
  { .type = type::play, .play = { .audioIndex = 1 } }, // 194 sfx/Chime.ogg
  { .type = type::voice, .voice = { .audioIndex = 74 } }, // 195 nara/n6.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 69 } }, // 196 n "After their encounter with the weird cat, the mice scurry out of the flower field and into the nearby meadow"
  { .type = type::scene, .scene = { .imageIndex = 4 } }, // 197 bgforest2
  { .type = type::show, .show = { .imageIndex = 15, .transformIndex = transform::right, } }, // 198 ei
  { .type = type::voice, .voice = { .audioIndex = 75 } }, // 199 eily/e30.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 70 } }, // 200 e "I think this is the right way..."
  { .type = type::show, .show = { .imageIndex = 16, .transformIndex = transform::left, } }, // 201 al
  { .type = type::voice, .voice = { .audioIndex = 76 } }, // 202 alice/a19.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 71 } }, // 203 a "Then where did the path go?"
  { .type = type::voice, .voice = { .audioIndex = 77 } }, // 204 eily/e31.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 72 } }, // 205 e "How am I supposed to know?"
  { .type = type::voice, .voice = { .audioIndex = 78 } }, // 206 alice/a20.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 73 } }, // 207 a "Did you hear that?!?!"
  { .type = type::show, .show = { .imageIndex = 15, .transformIndex = xflip | transform::centerleft, } }, // 208 ei
  { .type = type::show, .show = { .imageIndex = 13, .transformIndex = transform::right, } }, // 209 cat
  { .type = type::play, .play = { .audioIndex = 22 } }, // 210 music/PhrygianButterflies.ogg
  { .type = type::voice, .voice = { .audioIndex = 79 } }, // 211 leona/c18.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 74 } }, // 212 c "Hey there... I apologize, I didn't mean to storm off like that"
  { .type = type::voice, .voice = { .audioIndex = 80 } }, // 213 eily/e32.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 75 } }, // 214 e "Ha ha, no problem..."
  { .type = type::voice, .voice = { .audioIndex = 81 } }, // 215 alice/a21.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 76 } }, // 216 a "So... Why are you traveling to Castle Alysen?"
  { .type = type::voice, .voice = { .audioIndex = 82 } }, // 217 eily/e33.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 77 } }, // 218 e "Alice!!!"
  { .type = type::voice, .voice = { .audioIndex = 83 } }, // 219 leona/c19.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 78 } }, // 220 c "If you must know, I have been summoned by the queen"
  { .type = type::voice, .voice = { .audioIndex = 84 } }, // 221 leona/c20.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 79 } }, // 222 c "I suspect that my poor reputation amongst the locals of Eastern Nidus has come back to haunt me"
  { .type = type::voice, .voice = { .audioIndex = 85 } }, // 223 leona/c21.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 80 } }, // 224 c "Though I know not what what she has summoned me for"
  { .type = type::voice, .voice = { .audioIndex = 86 } }, // 225 alice/a22.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 81 } }, // 226 a "Ahhhhhh"
  { .type = type::voice, .voice = { .audioIndex = 87 } }, // 227 leona/c22.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 82 } }, // 228 c "So then..."
  { .type = type::voice, .voice = { .audioIndex = 88 } }, // 229 leona/c23.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 83 } }, // 230 c "Why are YOU traveling to the Castle?"
  { .type = type::voice, .voice = { .audioIndex = 89 } }, // 231 alice/a23.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 84 } }, // 232 a "We are delivering a feather!!!"
  { .type = type::voice, .voice = { .audioIndex = 90 } }, // 233 eily/e34.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 85 } }, // 234 e "Alice no!"
  { .type = type::voice, .voice = { .audioIndex = 91 } }, // 235 alice/a24.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 86 } }, // 236 a "A feather that belonged to the queen herself!!!"
  { .type = type::voice, .voice = { .audioIndex = 92 } }, // 237 eily/e35.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 87 } }, // 238 e "Why you little..."
  { .type = type::voice, .voice = { .audioIndex = 93 } }, // 239 leona/c24.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 88 } }, // 240 c "A feather you say? One of the queens?"
  { .type = type::voice, .voice = { .audioIndex = 94 } }, // 241 leona/c25.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 89 } }, // 242 c "How on the face of Al Mot might you have aquired such a thing?"
  { .type = type::voice, .voice = { .audioIndex = 95 } }, // 243 leona/c26.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 90 } }, // 244 c "If it is authentic"
  { .type = type::voice, .voice = { .audioIndex = 96 } }, // 245 eily/e36.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 91 } }, // 246 e "Since Alice cannot keep a secret, I shall tell you"
  { .type = type::voice, .voice = { .audioIndex = 97 } }, // 247 eily/e37.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 92 } }, // 248 e "Seven moons ago, our town was attacked by three owls and a band of mice from the northern principalities"
  { .type = type::voice, .voice = { .audioIndex = 98 } }, // 249 eily/e38.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 93 } }, // 250 e "Eventually word spread to greater nearby settlements, and so"
  { .type = type::voice, .voice = { .audioIndex = 99 } }, // 251 eily/e39.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 94 } }, // 252 e "Messengers from the keep in Musia sent for aid from the Ravens"
  { .type = type::voice, .voice = { .audioIndex = 100 } }, // 253 eily/e40.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 95 } }, // 254 e "Four moons ago, the request was answered"
  { .type = type::voice, .voice = { .audioIndex = 101 } }, // 255 eily/e41.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 96 } }, // 256 e "And a small group of mice accompanied by two ravens a fox, and three squirrels set out to the northern principalities"
  { .type = type::voice, .voice = { .audioIndex = 102 } }, // 257 eily/e42.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 97 } }, // 258 e "Anyways, long story short, we drove those barbaric rats out of their home"
  { .type = type::voice, .voice = { .audioIndex = 103 } }, // 259 alice/a25.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 98 } }, // 260 a "They arent actual rats you know"
  { .type = type::voice, .voice = { .audioIndex = 104 } }, // 261 eily/e43.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 99 } }, // 262 e "Obviously, but you wont catch me speaking kindly of them"
  { .type = type::voice, .voice = { .audioIndex = 105 } }, // 263 alice/a26.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 100 } }, // 264 a "And you forgot the most important part"
  { .type = type::voice, .voice = { .audioIndex = 106 } }, // 265 eily/e44.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 101 } }, // 266 e "Yah yah, I am getting there"
  { .type = type::voice, .voice = { .audioIndex = 107 } }, // 267 eily/e45.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 102 } }, // 268 e "So, essentially, my brother is trained in archery, and..."
  { .type = type::voice, .voice = { .audioIndex = 108 } }, // 269 alice/a27.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 103 } }, // 270 a "Speed it up already"
  { .type = type::voice, .voice = { .audioIndex = 109 } }, // 271 eily/e46.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 104 } }, // 272 e "You tell it then!"
  { .type = type::voice, .voice = { .audioIndex = 110 } }, // 273 alice/a28.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 105 } }, // 274 a "My cousin found this feather in one of the highest towers of a castle far to the north"
  { .type = type::voice, .voice = { .audioIndex = 111 } }, // 275 leona/c27.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 106 } }, // 276 c "How do you know it belongs to the queen?"
  { .type = type::voice, .voice = { .audioIndex = 112 } }, // 277 eily/e47.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 107 } }, // 278 e "It said so itself above the display on the wall"
  { .type = type::voice, .voice = { .audioIndex = 113 } }, // 279 alice/a29.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 108 } }, // 280 a "Supposedly, it was in a room filled with treasures!"
  { .type = type::voice, .voice = { .audioIndex = 114 } }, // 281 leona/c28.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 109 } }, // 282 c "That is very nice and all, but what are the two of you doing out here all alone?"
  { .type = type::voice, .voice = { .audioIndex = 115 } }, // 283 leona/c29.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 110 } }, // 284 c "Do you expect every bird in Avia to respect your alliance with Castle Alysen?"
  { .type = type::voice, .voice = { .audioIndex = 116 } }, // 285 eily/e48.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 111 } }, // 286 e "What do you mean?"
  { .type = type::voice, .voice = { .audioIndex = 117 } }, // 287 leona/c30.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 112 } }, // 288 c "I mean, the two of you probably look like walking dinner to most creatures"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 6 } }, // 289 "Sarcasm", "Nod"
  { .type = type::voice, .voice = { .audioIndex = 118 } }, // 290 alice/a30.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 113 } }, // 291 a "I could go for some dinner..."
  { .type = type::jump, .jump = { .statementIndex = 295 } }, // 292 internal jump (b'__menu_end', 3)
  { .type = type::jump, .jump = { .statementIndex = 296 } }, // 293 mainbranch4
  { .type = type::jump, .jump = { .statementIndex = 295 } }, // 294 internal jump (b'__menu_end', 3)
  { .type = type::jump, .jump = { .statementIndex = 296 } }, // 295 mainbranch4
  { .type = type::voice, .voice = { .audioIndex = 119 } }, // 296 eily/e49.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 114 } }, // 297 e "Anyways..."
  { .type = type::voice, .voice = { .audioIndex = 120 } }, // 298 eily/e50.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 115 } }, // 299 e "To answer your question, upon returning to the village, the feather was taken from my brother by the needle guild"
  { .type = type::voice, .voice = { .audioIndex = 121 } }, // 300 eily/e51.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 116 } }, // 301 e "So... Yesterday, after sundown"
  { .type = type::voice, .voice = { .audioIndex = 122 } }, // 302 eily/e52.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 117 } }, // 303 e "We stole the feather from the guild hall before vanishing into the night"
  { .type = type::voice, .voice = { .audioIndex = 123 } }, // 304 eily/e53.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 118 } }, // 305 e "Can you imagine the look on their stupid faces, when they woke up, and not only is the feather missing"
  { .type = type::voice, .voice = { .audioIndex = 124 } }, // 306 eily/e54.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 119 } }, // 307 e "But so are we!"
  { .type = type::voice, .voice = { .audioIndex = 125 } }, // 308 alice/a31.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 120 } }, // 309 a "Hahahaha"
  { .type = type::voice, .voice = { .audioIndex = 126 } }, // 310 leona/c31.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 121 } }, // 311 c "Are the two of you mad?"
  { .type = type::voice, .voice = { .audioIndex = 127 } }, // 312 leona/c32.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 122 } }, // 313 c "I assume you are attempting to return the Queens feather?"
  { .type = type::voice, .voice = { .audioIndex = 128 } }, // 314 alice/a32.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 123 } }, // 315 a "Yes, we intend to deliver the feather to its rightful owner"
  { .type = type::voice, .voice = { .audioIndex = 129 } }, // 316 leona/c33.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 124 } }, // 317 c "Absolute madness!"
  { .type = type::voice, .voice = { .audioIndex = 130 } }, // 318 mousegirls/mg2.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 31 } }, // 319 mg "..."
  { .type = type::voice, .voice = { .audioIndex = 131 } }, // 320 leona/c34.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 125 } }, // 321 c "I will follow the two of you"
  { .type = type::voice, .voice = { .audioIndex = 132 } }, // 322 leona/c35.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 126 } }, // 323 c "To keep you safe, that is"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 8 } }, // 324 "Agree", "Stay Silent"
  { .type = type::voice, .voice = { .audioIndex = 133 } }, // 325 alice/a33.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 127 } }, // 326 a "Alright!"
  { .type = type::jump, .jump = { .statementIndex = 330 } }, // 327 internal jump (b'__menu_end', 4)
  { .type = type::jump, .jump = { .statementIndex = 331 } }, // 328 mainbranch5
  { .type = type::jump, .jump = { .statementIndex = 330 } }, // 329 internal jump (b'__menu_end', 4)
  { .type = type::jump, .jump = { .statementIndex = 331 } }, // 330 mainbranch5
  { .type = type::voice, .voice = { .audioIndex = 134 } }, // 331 eily/e55.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 128 } }, // 332 e "Ha ha... Okay..."
  { .type = type::voice, .voice = { .audioIndex = 135 } }, // 333 leona/c36.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 129 } }, // 334 c "Great! Follow me, I know a shortcut! :3"
  { .type = type::hide, .hide = { .imageIndex = 13 } }, // 335 cat
  { .type = type::voice, .voice = { .audioIndex = 136 } }, // 336 alice/a34.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 130 } }, // 337 a "Sounds good!"
  { .type = type::hide, .hide = { .imageIndex = 16 } }, // 338 al
  { .type = type::stop, .stop = { .audioIndex = 22, .fadeout = 2.0 } }, // 339 PhrygianButterflies
  { .type = type::voice, .voice = { .audioIndex = 137 } }, // 340 eily/e56.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 131 } }, // 341 e "Oh dear!"
  { .type = type::hide, .hide = { .imageIndex = 15 } }, // 342 ei
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 343 bgwhite
  { .type = type::play, .play = { .audioIndex = 1 } }, // 344 sfx/Chime.ogg
  { .type = type::voice, .voice = { .audioIndex = 138 } }, // 345 nara/n7.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 132 } }, // 346 n "And so the mice girls follow the noble cat further towards their destination"
  { .type = type::scene, .scene = { .imageIndex = 6 } }, // 347 bgwheatfield1
  { .type = type::play, .play = { .audioIndex = 139 } }, // 348 music/WheatFields.ogg
  { .type = type::show, .show = { .imageIndex = 13, .transformIndex = transform::right, } }, // 349 cat
  { .type = type::voice, .voice = { .audioIndex = 140 } }, // 350 leona/c37.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 133 } }, // 351 c "Nya"
  { .type = type::show, .show = { .imageIndex = 19, .transformIndex = transform::left, } }, // 352 wal
  { .type = type::voice, .voice = { .audioIndex = 141 } }, // 353 alice/a35.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 134 } }, // 354 a "Look, your right, the castle is just up ahead!"
  { .type = type::show, .show = { .imageIndex = 15, .transformIndex = xflip | transform::centerleft, } }, // 355 ei
  { .type = type::voice, .voice = { .audioIndex = 142 } }, // 356 eily/e57.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 135 } }, // 357 e "Wait up"
  { .type = type::voice, .voice = { .audioIndex = 143 } }, // 358 leona/c38.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 136 } }, // 359 c "I told you I knew a shortcut!"
  { .type = type::voice, .voice = { .audioIndex = 144 } }, // 360 leona/c39.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 137 } }, // 361 c "Most people take the long way around"
  { .type = type::voice, .voice = { .audioIndex = 145 } }, // 362 eily/e58.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 138 } }, // 363 e "Yah because those are royal wheatfields!"
  { .type = type::voice, .voice = { .audioIndex = 146 } }, // 364 alice/a36.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 139 } }, // 365 a "Who cares?"
  { .type = type::voice, .voice = { .audioIndex = 147 } }, // 366 eily/e59.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 140 } }, // 367 e "Are you trying to get us killed?"
  { .type = type::voice, .voice = { .audioIndex = 148 } }, // 368 eily/e60.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 141 } }, // 369 e "Its trespassing on royal land!"
  { .type = type::voice, .voice = { .audioIndex = 149 } }, // 370 leona/c40.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 142 } }, // 371 c "Calm down, I have done this like a million times"
  { .type = type::voice, .voice = { .audioIndex = 150 } }, // 372 eily/e61.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 143 } }, // 373 e "That doesnt make me calm!"
  { .type = type::voice, .voice = { .audioIndex = 151 } }, // 374 leona/c41.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 144 } }, // 375 c "How can the rolling fields of wheat not calm your spirit?"
  { .type = type::voice, .voice = { .audioIndex = 152 } }, // 376 leona/c42.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 145 } }, // 377 c "You little mice truly are mad!"
  { .type = type::voice, .voice = { .audioIndex = 153 } }, // 378 alice/a37.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 146 } }, // 379 a "I like the wheat!"
  { .type = type::voice, .voice = { .audioIndex = 154 } }, // 380 eily/e62.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 147 } }, // 381 e "Shut up!"
  { .type = type::voice, .voice = { .audioIndex = 155 } }, // 382 leona/c43.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 148 } }, // 383 c "Sounds like someone needs a nap!"
  { .type = type::voice, .voice = { .audioIndex = 156 } }, // 384 eily/e63.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 149 } }, // 385 e "Why? because I'm not insane like you?"
  { .type = type::voice, .voice = { .audioIndex = 157 } }, // 386 leona/c44.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 150 } }, // 387 c "Yah, your so sane, that you decided to steal from your town and then run off alone to the country of birds"
  { .type = type::voice, .voice = { .audioIndex = 158 } }, // 388 leona/c45.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 151 } }, // 389 c "The power of friendship wont protect the two of you from becoming dinner"
  { .type = type::voice, .voice = { .audioIndex = 159 } }, // 390 leona/c46.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 152 } }, // 391 c "And that, is why I feel obligated to accompany you!"
  { .type = type::voice, .voice = { .audioIndex = 160 } }, // 392 eily/e64.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 153 } }, // 393 e "Hey, we have a good reason!"
  { .type = type::voice, .voice = { .audioIndex = 161 } }, // 394 leona/c47.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 154 } }, // 395 c "And what might that be?"
  { .type = type::voice, .voice = { .audioIndex = 162 } }, // 396 eily/e65.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 155 } }, // 397 e "My brother found the feather, not the town guild, its a matter of family pride!"
  { .type = type::voice, .voice = { .audioIndex = 163 } }, // 398 leona/c48.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 156 } }, // 399 c "Pride has touched the chosen meouse"
  { .type = type::voice, .voice = { .audioIndex = 164 } }, // 400 leona/c49.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 157 } }, // 401 c "Flies she towards the Castle"
  { .type = type::voice, .voice = { .audioIndex = 165 } }, // 402 leona/c50.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 158 } }, // 403 c "But her ambition burns far too bright, and silly mice dont have any wings to melt"
  { .type = type::voice, .voice = { .audioIndex = 166 } }, // 404 mousegirls/mg3.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 159 } }, // 405 mg "What?"
  { .type = type::voice, .voice = { .audioIndex = 167 } }, // 406 leona/c51.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 160 } }, // 407 c "Nyanyanya"
  { .type = type::voice, .voice = { .audioIndex = 168 } }, // 408 leona/c52.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 161 } }, // 409 c "Nyevermind"
  { .type = type::stop, .stop = { .audioIndex = 139, .fadeout = 3.0 } }, // 410 WheatFields
  { .type = type::voice, .voice = { .audioIndex = 169 } }, // 411 leona/c53.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 162 } }, // 412 c "Sing me a song little minstrels!"
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 31 } }, // 413 e "..."
  { .type = type::play, .play = { .audioIndex = 170 } }, // 414 poem/KiriStella.ogg
  { .type = type::pause, .pause = { .duration = 67 } }, // 415
  { .type = type::voice, .voice = { .audioIndex = 171 } }, // 416 leona/c54.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 163 } }, // 417 c "Very Nyice!"
  { .type = type::voice, .voice = { .audioIndex = 172 } }, // 418 leona/c55.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 164 } }, // 419 c "Now tell me little minstrels, what are your names?"
  { .type = type::voice, .voice = { .audioIndex = 173 } }, // 420 alice/a39.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 165 } }, // 421 a "My name is Alice"
  { .type = type::voice, .voice = { .audioIndex = 174 } }, // 422 eily/e67.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 166 } }, // 423 e "And my name is Eily"
  { .type = type::voice, .voice = { .audioIndex = 175 } }, // 424 eily/e68.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 167 } }, // 425 e "What is your name?"
  { .type = type::voice, .voice = { .audioIndex = 176 } }, // 426 leona/c56.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 168 } }, // 427 l "My name is Leona!"
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 428 bgwhite
  { .type = type::voice, .voice = { .audioIndex = 177 } }, // 429 nara/n8.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 169 } }, // 430 n "And so, the odd trio walked through the wheatfields and towards the castle"
  { .type = type::voice, .voice = { .audioIndex = 178 } }, // 431 nara/n9.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 170 } }, // 432 n "Upon approaching the gates, the three were escorted to a large room"
  { .type = type::voice, .voice = { .audioIndex = 179 } }, // 433 nara/n10.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 171 } }, // 434 n "They were then instructed to wait for an audience with the Queen"
  { .type = type::voice, .voice = { .audioIndex = 180 } }, // 435 hera/h1.ogg
  { .type = type::say, .say = { .characterIndex = 7, .stringIndex = 172 } }, // 436 h "You may now present yourselves before her Majesty, Queen Alary of Alysen"
  { .type = type::scene, .scene = { .imageIndex = 7 } }, // 437 bgcastle1
  { .type = type::play, .play = { .audioIndex = 181 } }, // 438 music/Preludium.ogg
  { .type = type::show, .show = { .imageIndex = 12, .transformIndex = transform::right, } }, // 439 bi
  { .type = type::pause, .pause = { .duration = 1.0 } }, // 440
  { .type = type::voice, .voice = { .audioIndex = 182 } }, // 441 hera/h2.ogg
  { .type = type::say, .say = { .characterIndex = 7, .stringIndex = 173 } }, // 442 h "Leona Agrepen of Elmindeer"
  { .type = type::show, .show = { .imageIndex = 13, .transformIndex = xflip | transform::center, } }, // 443 cat
  { .type = type::voice, .voice = { .audioIndex = 183 } }, // 444 leona/c57.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 174 } }, // 445 l "Hail, your Majesty"
  { .type = type::voice, .voice = { .audioIndex = 184 } }, // 446 hera/h3.ogg
  { .type = type::say, .say = { .characterIndex = 7, .stringIndex = 175 } }, // 447 h "Eily VeraWheat of the Western Principalities"
  { .type = type::show, .show = { .imageIndex = 15, .transformIndex = transform::centerleft, } }, // 448 ei
  { .type = type::voice, .voice = { .audioIndex = 185 } }, // 449 eily/e69.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 174 } }, // 450 e "Hail, your Majesty"
  { .type = type::voice, .voice = { .audioIndex = 186 } }, // 451 hera/h4.ogg
  { .type = type::say, .say = { .characterIndex = 7, .stringIndex = 176 } }, // 452 h "Alice SeraWheat of the Western Principalities"
  { .type = type::play, .play = { .audioIndex = 187 } }, // 453 sfx/Glass.ogg
  { .type = type::pause, .pause = { .duration = 1.0 } }, // 454
  { .type = type::voice, .voice = { .audioIndex = 188 } }, // 455 alice/a40.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 177 } }, // 456 a "I'm alright!"
  { .type = type::show, .show = { .imageIndex = 19, .transformIndex = transform::left, } }, // 457 wal
  { .type = type::voice, .voice = { .audioIndex = 189 } }, // 458 alice/a41.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 178 } }, // 459 a "H-Hail, your majesty"
  { .type = type::voice, .voice = { .audioIndex = 190 } }, // 460 leona/c58.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 160 } }, // 461 l "Nyanyanya"
  { .type = type::voice, .voice = { .audioIndex = 191 } }, // 462 bird/b1.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 179 } }, // 463 b "And what is this?"
  { .type = type::voice, .voice = { .audioIndex = 192 } }, // 464 bird/b2.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 180 } }, // 465 b "A cat and two mice in my court?"
  { .type = type::voice, .voice = { .audioIndex = 193 } }, // 466 bird/b3.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 181 } }, // 467 b "Is this some kind of joke?"
  { .type = type::voice, .voice = { .audioIndex = 194 } }, // 468 leona/c59.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 182 } }, // 469 l "Not a joke Your Majesty, these are my friends"
  { .type = type::voice, .voice = { .audioIndex = 195 } }, // 470 eily/e70.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 183 } }, // 471 e "Friends?"
  { .type = type::voice, .voice = { .audioIndex = 196 } }, // 472 bird/b4.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 184 } }, // 473 b "Miss Agrepen, your reputation is far from acceptable"
  { .type = type::voice, .voice = { .audioIndex = 197 } }, // 474 bird/b5.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 185 } }, // 475 b "And I can imagine, you already know why I have summoned you here today"
  { .type = type::voice, .voice = { .audioIndex = 198 } }, // 476 leona/c60.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 186 } }, // 477 l "Uhhmmmm...."
  { .type = type::voice, .voice = { .audioIndex = 199 } }, // 478 leona/c61.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 187 } }, // 479 l "Does it have anything to do with Eastern Nidus?"
  { .type = type::voice, .voice = { .audioIndex = 200 } }, // 480 bird/b6.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 188 } }, // 481 b "I think you already know the answer to that"
  { .type = type::voice, .voice = { .audioIndex = 201 } }, // 482 bird/b7.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 189 } }, // 483 b "Your father would be rather dissapointed if he were still alive"
  { .type = type::voice, .voice = { .audioIndex = 202 } }, // 484 leona/c0.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 31 } }, // 485 l "..."
  { .type = type::voice, .voice = { .audioIndex = 203 } }, // 486 bird/b8.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 190 } }, // 487 b "Leona Agrepen, the court has found you guilty of two cases of larceny and seven cases of petty pilfering"
  { .type = type::voice, .voice = { .audioIndex = 204 } }, // 488 bird/b9.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 191 } }, // 489 b "Miss Agrepen, you are hereby banned from stepping foot in Eastern Nidus"
  { .type = type::voice, .voice = { .audioIndex = 205 } }, // 490 bird/b10.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 192 } }, // 491 b "From here on out, you shall be restricted to the central principalities of Avia"
  { .type = type::voice, .voice = { .audioIndex = 206 } }, // 492 leona/c62.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 193 } }, // 493 l "Owww c'mon! There is nothing to do around here!"
  { .type = type::voice, .voice = { .audioIndex = 207 } }, // 494 bird/b11.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 194 } }, // 495 b "Silence!"
  { .type = type::voice, .voice = { .audioIndex = 208 } }, // 496 bird/b12.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 195 } }, // 497 b "It is here, in the Central city of Alysen that you shall remain, where I can keep a watchful eye on you"
  { .type = type::voice, .voice = { .audioIndex = 209 } }, // 498 bird/b13.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 196 } }, // 499 b "Or would you prefer that I permit the request of the lesser courts to have you declawed?"
  { .type = type::voice, .voice = { .audioIndex = 210 } }, // 500 leona/c63.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 197 } }, // 501 l "No ><"
  { .type = type::voice, .voice = { .audioIndex = 211 } }, // 502 bird/b14.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 198 } }, // 503 b "Take my leniency as a display of gratitude for the services rendered by your father"
  { .type = type::voice, .voice = { .audioIndex = 212 } }, // 504 leona/c64.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 199 } }, // 505 l "Yes Your Majesty... Forgive me for speaking out of turn"
  { .type = type::voice, .voice = { .audioIndex = 213 } }, // 506 bird/b15.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 200 } }, // 507 b "Now, why have you brought these little mice before me?"
  { .type = type::voice, .voice = { .audioIndex = 214 } }, // 508 leona/c65.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 201 } }, // 509 l "Alary, Your Majesty, these are minstrels I met on the road to Alysen"
  { .type = type::voice, .voice = { .audioIndex = 215 } }, // 510 leona/c66.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 202 } }, // 511 l "They lay claim to a feather, said to be one of Your Majesty's own"
  { .type = type::voice, .voice = { .audioIndex = 216 } }, // 512 bird/b16.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 203 } }, // 513 b "Really?"
  { .type = type::voice, .voice = { .audioIndex = 217 } }, // 514 bird/b17.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 204 } }, // 515 b "And what else might the two of you claim? Alice and Eily of the West"
  { .type = type::voice, .voice = { .audioIndex = 218 } }, // 516 alice/a42.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 205 } }, // 517 a "I u-uhh..."
  { .type = type::voice, .voice = { .audioIndex = 219 } }, // 518 eily/e71.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 206 } }, // 519 e "Your Majesty, this feather was found by my brother in a castle to the north"
  { .type = type::voice, .voice = { .audioIndex = 220 } }, // 520 eily/e72.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 207 } }, // 521 e "So very far my cousin and I have journeyed"
  { .type = type::voice, .voice = { .audioIndex = 221 } }, // 522 eily/e73.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 208 } }, // 523 e "Over the mountains of Almystice"
  { .type = type::voice, .voice = { .audioIndex = 222 } }, // 524 eily/e74.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 209 } }, // 525 e "Beyond the deep blue waters of the Lilac bay"
  { .type = type::voice, .voice = { .audioIndex = 223 } }, // 526 eily/e75.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 2 } }, // 527 e "And across the vast fields of Alysen"
  { .type = type::voice, .voice = { .audioIndex = 224 } }, // 528 eily/e76.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 210 } }, // 529 e "All in hopes that we might return Your Majesty's feather"
  { .type = type::voice, .voice = { .audioIndex = 225 } }, // 530 bird/b18.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 211 } }, // 531 b "What splendid and courageous little mice the two of you are"
  { .type = type::voice, .voice = { .audioIndex = 226 } }, // 532 leona/c67.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 212 } }, // 533 l "Nyanyanyanyanya"
  { .type = type::voice, .voice = { .audioIndex = 227 } }, // 534 alice/a43.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 213 } }, // 535 a "We also wanted to show our profound gratitude for the aid provided by Your Majesty just four moons ago"
  { .type = type::voice, .voice = { .audioIndex = 228 } }, // 536 eily/e77.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 214 } }, // 537 e "Please allow us to perform a song for Your Majesty and Your Majesty's court"
  { .type = type::stop, .stop = { .audioIndex = 181, .fadeout = 4.2 } }, // 538 Preludium
  { .type = type::voice, .voice = { .audioIndex = 229 } }, // 539 bird/b19.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 215 } }, // 540 b "I appreciate your loyalty to the crown of Corvidae little mice"
  { .type = type::stop, .stop = { .audioIndex = 0, .fadeout = 4.2 } }, // 541 MistAmbience
  { .type = type::voice, .voice = { .audioIndex = 230 } }, // 542 bird/b20.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 216 } }, // 543 b "You are most welcome to proceed with your little song"
  { .type = type::play, .play = { .audioIndex = 231 } }, // 544 poem/BirdSong.ogg
  { .type = type::scene, .scene = { .imageIndex = 7 } }, // 545 bgcastle1
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 31 } }, // 546 e "..."
  { .type = type::pause, .pause = { .duration = 73.5 } }, // 547
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 548 bgwhite
  { .type = type::voice, .voice = { .audioIndex = 232 } }, // 549 nara/n11.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 217 } }, // 550 n "In the end, Leona managed to stay out of the dungeon"
  { .type = type::voice, .voice = { .audioIndex = 233 } }, // 551 nara/n12.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 218 } }, // 552 n "Eily and Alice both stayed in service of the queen for 7 harvests"
  { .type = type::voice, .voice = { .audioIndex = 234 } }, // 553 nara/n13.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 219 } }, // 554 n "before returning to their small nameless town, near the Keep of Musia"
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 555 bgwhite
  { .type = type::show, .show = { .imageIndex = 11, .transformIndex = transform::center, } }, // 556 bgend
  { .type = type::pause, .pause = { .duration = 1.0 } }, // 557
  { .type = type::jump, .jump = { .statementIndex = 557 } }, // 558 end
  { .type = type::_return }, // 559
};

const int statements_length = (sizeof (statements)) / (sizeof (statements[0]));

}
