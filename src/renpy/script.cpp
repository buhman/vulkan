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

// b'a'
static const uint32_t character_images_0[] = { 13, 15, 16 };

static constexpr uint32_t character_images_0_length = 3;

// b'b'
static const uint32_t character_images_1[] = { 9 };

static constexpr uint32_t character_images_1_length = 1;

// b'c'
static const uint32_t character_images_2[] = { 10, 11 };

static constexpr uint32_t character_images_2_length = 2;

// b'e'
static const uint32_t character_images_3[] = { 12, 14 };

static constexpr uint32_t character_images_3_length = 2;

// b'mg'
static const uint32_t character_images_4[] = { 13, 15, 16, 12, 14 };

static constexpr uint32_t character_images_4_length = 5;

// b'n'
static const uint32_t character_images_5[] = {  };

static constexpr uint32_t character_images_5_length = 0;

// b'l'
static const uint32_t character_images_6[] = { 10, 11 };

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
  { .path = "audio/music/MistAmbience.opus.bin", .loop_end = 22.0, .audio_flags = audio::music, .attenuation = 1.0 }, // 0 music/MistAmbience.ogg
  { .path = "audio/sfx/Chime.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 1 sfx/Chime.ogg
  { .path = "audio/nara/n1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 2 nara/n1.ogg
  { .path = "audio/nara/n2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 3 nara/n2.ogg
  { .path = "audio/nara/n3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 4 nara/n3.ogg
  { .path = "audio/music/TinyForestMinstrels.opus.bin", .loop_end = 44.0, .audio_flags = audio::music, .attenuation = 0.45 }, // 5 music/TinyForestMinstrels.ogg
  { .path = "audio/nara/n4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 6 nara/n4.ogg
  { .path = "audio/alice/a1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 7 alice/a1.ogg
  { .path = "audio/eily/e1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 8 eily/e1.ogg
  { .path = "audio/alice/a2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 9 alice/a2.ogg
  { .path = "audio/eily/e2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 10 eily/e2.ogg
  { .path = "audio/alice/a3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 11 alice/a3.ogg
  { .path = "audio/eily/e3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 12 eily/e3.ogg
  { .path = "audio/alice/a4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 13 alice/a4.ogg
  { .path = "audio/alice/a5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 14 alice/a5.ogg
  { .path = "audio/eily/e4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 15 eily/e4.ogg
  { .path = "audio/eily/e5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 16 eily/e5.ogg
  { .path = "audio/alice/a6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 17 alice/a6.ogg
  { .path = "audio/eily/e6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 18 eily/e6.ogg
  { .path = "audio/alice/a7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 19 alice/a7.ogg
  { .path = "audio/eily/e7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 20 eily/e7.ogg
  { .path = "audio/nara/n5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 21 nara/n5.ogg
  { .path = "audio/music/PhrygianButterflies.opus.bin", .loop_end = 40.2, .audio_flags = audio::music, .attenuation = 0.5 }, // 22 music/PhrygianButterflies.ogg
  { .path = "audio/eily/e8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 23 eily/e8.ogg
  { .path = "audio/alice/a8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 24 alice/a8.ogg
  { .path = "audio/eily/e9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 25 eily/e9.ogg
  { .path = "audio/eily/e10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 26 eily/e10.ogg
  { .path = "audio/alice/a9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 27 alice/a9.ogg
  { .path = "audio/eily/e11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 28 eily/e11.ogg
  { .path = "audio/eily/e12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 29 eily/e12.ogg
  { .path = "audio/alice/a10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 30 alice/a10.ogg
  { .path = "audio/eily/e13.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 31 eily/e13.ogg
  { .path = "audio/eily/e14.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 32 eily/e14.ogg
  { .path = "audio/alice/a11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 33 alice/a11.ogg
  { .path = "audio/eily/e15.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 34 eily/e15.ogg
  { .path = "audio/poem/Poem1.opus.bin", .loop_end = 0.0, .audio_flags = audio::poem, .attenuation = 1.0 }, // 35 poem/Poem1.ogg
  { .path = "audio/eily/e16.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 36 eily/e16.ogg
  { .path = "audio/alice/a12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 37 alice/a12.ogg
  { .path = "audio/leona/c1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 38 leona/c1.ogg
  { .path = "audio/music/ScaredMice.opus.bin", .loop_end = 8.0, .audio_flags = audio::music, .attenuation = 1.0 }, // 39 music/ScaredMice.ogg
  { .path = "audio/mousegirls/mg1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 40 mousegirls/mg1.ogg
  { .path = "audio/leona/c2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 41 leona/c2.ogg
  { .path = "audio/leona/c3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 42 leona/c3.ogg
  { .path = "audio/alice/a14.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 43 alice/a14.ogg
  { .path = "audio/eily/e18.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 44 eily/e18.ogg
  { .path = "audio/eily/e19.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 45 eily/e19.ogg
  { .path = "audio/leona/c4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 46 leona/c4.ogg
  { .path = "audio/leona/c5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 47 leona/c5.ogg
  { .path = "audio/leona/c6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 48 leona/c6.ogg
  { .path = "audio/eily/e20.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 49 eily/e20.ogg
  { .path = "audio/alice/a15.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 50 alice/a15.ogg
  { .path = "audio/eily/e21.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 51 eily/e21.ogg
  { .path = "audio/leona/c7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 52 leona/c7.ogg
  { .path = "audio/leona/c8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 53 leona/c8.ogg
  { .path = "audio/eily/e22.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 54 eily/e22.ogg
  { .path = "audio/leona/c9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 55 leona/c9.ogg
  { .path = "audio/eily/e23.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 56 eily/e23.ogg
  { .path = "audio/leona/c10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 57 leona/c10.ogg
  { .path = "audio/eily/e24.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 58 eily/e24.ogg
  { .path = "audio/leona/c11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 59 leona/c11.ogg
  { .path = "audio/eily/e25.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 60 eily/e25.ogg
  { .path = "audio/leona/c12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 61 leona/c12.ogg
  { .path = "audio/leona/c13.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 62 leona/c13.ogg
  { .path = "audio/eily/e26.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 63 eily/e26.ogg
  { .path = "audio/eily/e27.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 64 eily/e27.ogg
  { .path = "audio/leona/c14.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 65 leona/c14.ogg
  { .path = "audio/alice/a16.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 66 alice/a16.ogg
  { .path = "audio/leona/c15.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 67 leona/c15.ogg
  { .path = "audio/leona/c16.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 68 leona/c16.ogg
  { .path = "audio/leona/c17.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 69 leona/c17.ogg
  { .path = "audio/alice/a17.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 70 alice/a17.ogg
  { .path = "audio/eily/e28.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 71 eily/e28.ogg
  { .path = "audio/alice/a18.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 72 alice/a18.ogg
  { .path = "audio/eily/e29.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 73 eily/e29.ogg
  { .path = "audio/nara/n6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 74 nara/n6.ogg
  { .path = "audio/eily/e30.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 75 eily/e30.ogg
  { .path = "audio/alice/a19.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 76 alice/a19.ogg
  { .path = "audio/eily/e31.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 77 eily/e31.ogg
  { .path = "audio/alice/a20.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 78 alice/a20.ogg
  { .path = "audio/leona/c18.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 79 leona/c18.ogg
  { .path = "audio/eily/e32.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 80 eily/e32.ogg
  { .path = "audio/alice/a21.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 81 alice/a21.ogg
  { .path = "audio/eily/e33.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 82 eily/e33.ogg
  { .path = "audio/leona/c19.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 83 leona/c19.ogg
  { .path = "audio/leona/c20.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 84 leona/c20.ogg
  { .path = "audio/leona/c21.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 85 leona/c21.ogg
  { .path = "audio/alice/a22.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 86 alice/a22.ogg
  { .path = "audio/leona/c22.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 87 leona/c22.ogg
  { .path = "audio/leona/c23.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 88 leona/c23.ogg
  { .path = "audio/alice/a23.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 89 alice/a23.ogg
  { .path = "audio/eily/e34.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 90 eily/e34.ogg
  { .path = "audio/alice/a24.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 91 alice/a24.ogg
  { .path = "audio/eily/e35.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 92 eily/e35.ogg
  { .path = "audio/leona/c24.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 93 leona/c24.ogg
  { .path = "audio/leona/c25.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 94 leona/c25.ogg
  { .path = "audio/leona/c26.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 95 leona/c26.ogg
  { .path = "audio/eily/e36.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 96 eily/e36.ogg
  { .path = "audio/eily/e37.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 97 eily/e37.ogg
  { .path = "audio/eily/e38.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 98 eily/e38.ogg
  { .path = "audio/eily/e39.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 99 eily/e39.ogg
  { .path = "audio/eily/e40.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 100 eily/e40.ogg
  { .path = "audio/eily/e41.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 101 eily/e41.ogg
  { .path = "audio/eily/e42.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 102 eily/e42.ogg
  { .path = "audio/alice/a25.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 103 alice/a25.ogg
  { .path = "audio/eily/e43.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 104 eily/e43.ogg
  { .path = "audio/alice/a26.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 105 alice/a26.ogg
  { .path = "audio/eily/e44.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 106 eily/e44.ogg
  { .path = "audio/eily/e45.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 107 eily/e45.ogg
  { .path = "audio/alice/a27.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 108 alice/a27.ogg
  { .path = "audio/eily/e46.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 109 eily/e46.ogg
  { .path = "audio/alice/a28.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 110 alice/a28.ogg
  { .path = "audio/leona/c27.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 111 leona/c27.ogg
  { .path = "audio/eily/e47.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 112 eily/e47.ogg
  { .path = "audio/alice/a29.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 113 alice/a29.ogg
  { .path = "audio/leona/c28.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 114 leona/c28.ogg
  { .path = "audio/leona/c29.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 115 leona/c29.ogg
  { .path = "audio/eily/e48.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 116 eily/e48.ogg
  { .path = "audio/leona/c30.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 117 leona/c30.ogg
  { .path = "audio/alice/a30.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 118 alice/a30.ogg
  { .path = "audio/eily/e49.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 119 eily/e49.ogg
  { .path = "audio/eily/e50.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 120 eily/e50.ogg
  { .path = "audio/eily/e51.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 121 eily/e51.ogg
  { .path = "audio/eily/e52.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 122 eily/e52.ogg
  { .path = "audio/eily/e53.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 123 eily/e53.ogg
  { .path = "audio/eily/e54.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 124 eily/e54.ogg
  { .path = "audio/alice/a31.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 125 alice/a31.ogg
  { .path = "audio/leona/c31.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 126 leona/c31.ogg
  { .path = "audio/leona/c32.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 127 leona/c32.ogg
  { .path = "audio/alice/a32.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 128 alice/a32.ogg
  { .path = "audio/leona/c33.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 129 leona/c33.ogg
  { .path = "audio/mousegirls/mg2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 130 mousegirls/mg2.ogg
  { .path = "audio/leona/c34.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 131 leona/c34.ogg
  { .path = "audio/leona/c35.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 132 leona/c35.ogg
  { .path = "audio/alice/a33.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 133 alice/a33.ogg
  { .path = "audio/eily/e55.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 134 eily/e55.ogg
  { .path = "audio/leona/c36.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 135 leona/c36.ogg
  { .path = "audio/alice/a34.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 136 alice/a34.ogg
  { .path = "audio/eily/e56.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 137 eily/e56.ogg
  { .path = "audio/nara/n7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 138 nara/n7.ogg
  { .path = "audio/music/WheatFields.opus.bin", .loop_end = 34.0, .audio_flags = audio::music, .attenuation = 1.0 }, // 139 music/WheatFields.ogg
  { .path = "audio/leona/c37.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 140 leona/c37.ogg
  { .path = "audio/alice/a35.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 141 alice/a35.ogg
  { .path = "audio/eily/e57.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 142 eily/e57.ogg
  { .path = "audio/leona/c38.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 143 leona/c38.ogg
  { .path = "audio/leona/c39.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 144 leona/c39.ogg
  { .path = "audio/eily/e58.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 145 eily/e58.ogg
  { .path = "audio/alice/a36.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 146 alice/a36.ogg
  { .path = "audio/eily/e59.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 147 eily/e59.ogg
  { .path = "audio/eily/e60.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 148 eily/e60.ogg
  { .path = "audio/leona/c40.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 149 leona/c40.ogg
  { .path = "audio/eily/e61.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 150 eily/e61.ogg
  { .path = "audio/leona/c41.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 151 leona/c41.ogg
  { .path = "audio/leona/c42.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 152 leona/c42.ogg
  { .path = "audio/alice/a37.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 153 alice/a37.ogg
  { .path = "audio/eily/e62.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 154 eily/e62.ogg
  { .path = "audio/leona/c43.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 155 leona/c43.ogg
  { .path = "audio/eily/e63.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 156 eily/e63.ogg
  { .path = "audio/leona/c44.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 157 leona/c44.ogg
  { .path = "audio/leona/c45.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 158 leona/c45.ogg
  { .path = "audio/leona/c46.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 159 leona/c46.ogg
  { .path = "audio/eily/e64.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 160 eily/e64.ogg
  { .path = "audio/leona/c47.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 161 leona/c47.ogg
  { .path = "audio/eily/e65.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 162 eily/e65.ogg
  { .path = "audio/leona/c48.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 163 leona/c48.ogg
  { .path = "audio/leona/c49.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 164 leona/c49.ogg
  { .path = "audio/leona/c50.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 165 leona/c50.ogg
  { .path = "audio/mousegirls/mg3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 166 mousegirls/mg3.ogg
  { .path = "audio/leona/c51.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 167 leona/c51.ogg
  { .path = "audio/leona/c52.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 168 leona/c52.ogg
  { .path = "audio/leona/c53.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 169 leona/c53.ogg
  { .path = "audio/leona/c54.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 170 leona/c54.ogg
  { .path = "audio/leona/c55.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 171 leona/c55.ogg
  { .path = "audio/alice/a39.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 172 alice/a39.ogg
  { .path = "audio/eily/e67.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 173 eily/e67.ogg
  { .path = "audio/eily/e68.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 174 eily/e68.ogg
  { .path = "audio/leona/c56.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 175 leona/c56.ogg
  { .path = "audio/nara/n8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 176 nara/n8.ogg
  { .path = "audio/nara/n9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 177 nara/n9.ogg
  { .path = "audio/nara/n10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 178 nara/n10.ogg
  { .path = "audio/hera/h1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 179 hera/h1.ogg
  { .path = "audio/music/Preludium.opus.bin", .loop_end = 58.2, .audio_flags = audio::music, .attenuation = 1.0 }, // 180 music/Preludium.ogg
  { .path = "audio/hera/h2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 181 hera/h2.ogg
  { .path = "audio/leona/c57.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 182 leona/c57.ogg
  { .path = "audio/hera/h3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 183 hera/h3.ogg
  { .path = "audio/eily/e69.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 184 eily/e69.ogg
  { .path = "audio/hera/h4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 185 hera/h4.ogg
  { .path = "audio/sfx/Glass.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 186 sfx/Glass.ogg
  { .path = "audio/alice/a40.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 187 alice/a40.ogg
  { .path = "audio/alice/a41.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 188 alice/a41.ogg
  { .path = "audio/leona/c58.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 189 leona/c58.ogg
  { .path = "audio/bird/b1.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 190 bird/b1.ogg
  { .path = "audio/bird/b2.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 191 bird/b2.ogg
  { .path = "audio/bird/b3.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 192 bird/b3.ogg
  { .path = "audio/leona/c59.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 193 leona/c59.ogg
  { .path = "audio/eily/e70.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 194 eily/e70.ogg
  { .path = "audio/bird/b4.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 195 bird/b4.ogg
  { .path = "audio/bird/b5.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 196 bird/b5.ogg
  { .path = "audio/leona/c60.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 197 leona/c60.ogg
  { .path = "audio/leona/c61.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 198 leona/c61.ogg
  { .path = "audio/bird/b6.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 199 bird/b6.ogg
  { .path = "audio/bird/b7.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 200 bird/b7.ogg
  { .path = "audio/leona/c0.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 201 leona/c0.ogg
  { .path = "audio/bird/b8.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 202 bird/b8.ogg
  { .path = "audio/bird/b9.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 203 bird/b9.ogg
  { .path = "audio/bird/b10.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 204 bird/b10.ogg
  { .path = "audio/leona/c62.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 205 leona/c62.ogg
  { .path = "audio/bird/b11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 206 bird/b11.ogg
  { .path = "audio/bird/b12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 207 bird/b12.ogg
  { .path = "audio/bird/b13.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 208 bird/b13.ogg
  { .path = "audio/leona/c63.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 209 leona/c63.ogg
  { .path = "audio/bird/b14.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 210 bird/b14.ogg
  { .path = "audio/leona/c64.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 211 leona/c64.ogg
  { .path = "audio/bird/b15.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 212 bird/b15.ogg
  { .path = "audio/leona/c65.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 213 leona/c65.ogg
  { .path = "audio/leona/c66.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 214 leona/c66.ogg
  { .path = "audio/bird/b16.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 215 bird/b16.ogg
  { .path = "audio/bird/b17.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 216 bird/b17.ogg
  { .path = "audio/alice/a42.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 217 alice/a42.ogg
  { .path = "audio/eily/e71.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 218 eily/e71.ogg
  { .path = "audio/eily/e72.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 219 eily/e72.ogg
  { .path = "audio/eily/e73.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 220 eily/e73.ogg
  { .path = "audio/eily/e74.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 221 eily/e74.ogg
  { .path = "audio/eily/e75.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 222 eily/e75.ogg
  { .path = "audio/eily/e76.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 223 eily/e76.ogg
  { .path = "audio/bird/b18.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 224 bird/b18.ogg
  { .path = "audio/leona/c67.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 225 leona/c67.ogg
  { .path = "audio/alice/a43.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 226 alice/a43.ogg
  { .path = "audio/eily/e77.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 227 eily/e77.ogg
  { .path = "audio/bird/b19.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 228 bird/b19.ogg
  { .path = "audio/bird/b20.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 229 bird/b20.ogg
  { .path = "audio/poem/Poem3.opus.bin", .loop_end = 0.0, .audio_flags = audio::poem, .attenuation = 1.0 }, // 230 poem/Poem3.ogg
  { .path = "audio/nara/n11.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 231 nara/n11.ogg
  { .path = "audio/nara/n12.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 232 nara/n12.ogg
  { .path = "audio/nara/n13.opus.bin", .loop_end = 0.0, .audio_flags = 0, .attenuation = 1.0 }, // 233 nara/n13.ogg
};

const int audio_length = (sizeof (audio)) / (sizeof (audio[0]));

const language::image images[] = {
  { .path = "data/renpy/images/flowers.dds", .is_character_image = false }, // 0 flowers.png
  { .path = "data/renpy/images/bg/forest1.dds", .is_character_image = false }, // 1 bg/forest1.png
  { .path = "data/renpy/images/bg/forest2.dds", .is_character_image = false }, // 2 bg/forest2.png
  { .path = "data/renpy/images/bg/flowerfield1.dds", .is_character_image = false }, // 3 bg/flowerfield1.png
  { .path = "data/renpy/images/bg/wheatfield1.dds", .is_character_image = false }, // 4 bg/wheatfield1.png
  { .path = "data/renpy/images/bg/castle1.dds", .is_character_image = false }, // 5 bg/castle1.png
  { .path = "data/renpy/images/bg/castle2.dds", .is_character_image = false }, // 6 bg/castle2.png
  { .path = "data/renpy/images/bg/castle3.dds", .is_character_image = false }, // 7 bg/castle3.png
  { .path = "data/renpy/images/bg/castle4.dds", .is_character_image = false }, // 8 bg/castle4.png
  { .path = "data/renpy/images/ch/ibird/Bird.dds", .is_character_image = true }, // 9 ch/ibird/Bird.png
  { .path = "data/renpy/images/ch/icat/Cat.dds", .is_character_image = true }, // 10 ch/icat/Cat.png
  { .path = "data/renpy/images/ch/icat/Catw.dds", .is_character_image = true }, // 11 ch/icat/Catw.png
  { .path = "data/renpy/images/ch/ieily/Eily.dds", .is_character_image = true }, // 12 ch/ieily/Eily.png
  { .path = "data/renpy/images/ch/ialice/Alice.dds", .is_character_image = true }, // 13 ch/ialice/Alice.png
  { .path = "data/renpy/images/ch/ieily/Seily.dds", .is_character_image = true }, // 14 ch/ieily/Seily.png
  { .path = "data/renpy/images/ch/ialice/Salice.dds", .is_character_image = true }, // 15 ch/ialice/Salice.png
  { .path = "data/renpy/images/ch/ialice/Walice.dds", .is_character_image = true }, // 16 ch/ialice/Walice.png
};

const int images_length = (sizeof (images)) / (sizeof (images[0]));

const language::option options[] = {
  { .string = "Complain", .statementIndex = 28 }, // 0
  { .string = "Rationalize", .statementIndex = 43 }, // 1
  { .string = "Good idea", .statementIndex = 83 }, // 2
  { .string = "I am too tired", .statementIndex = 92 }, // 3
  { .string = "Beg for mercy", .statementIndex = 118 }, // 4
  { .string = "Run", .statementIndex = 121 }, // 5
};

const int options_length = (sizeof (options)) / (sizeof (options[0]));

const language::dissolve dissolves[] = {
  { .duration = 3.0, .first_statement = 4, .count = 1 },
  { .duration = 3.0, .first_statement = 15, .count = 2 },
  { .duration = 1.0, .first_statement = 54, .count = 2 },
  { .duration = 1.0, .first_statement = 59, .count = 1 },
  { .duration = 3.0, .first_statement = 192, .count = 2 },
  { .duration = 3.0, .first_statement = 196, .count = 1 },
  { .duration = 2.0, .first_statement = 332, .count = 2 },
  { .duration = 1.3, .first_statement = 336, .count = 3 },
  { .duration = 3.0, .first_statement = 418, .count = 1 },
  { .duration = 2.0, .first_statement = 427, .count = 2 },
  { .duration = 7.0, .first_statement = 535, .count = 1 },
  { .duration = 7.0, .first_statement = 536, .count = 1 },
  { .duration = 7.0, .first_statement = 537, .count = 1 },
  { .duration = 7.0, .first_statement = 538, .count = 1 },
  { .duration = 7.0, .first_statement = 539, .count = 1 },
  { .duration = 7.0, .first_statement = 540, .count = 1 },
  { .duration = 7.0, .first_statement = 541, .count = 1 },
  { .duration = 10.0, .first_statement = 542, .count = 1 },
  { .duration = 13.0, .first_statement = 544, .count = 1 },
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
  { .type = type::scene, .scene = { .imageIndex = 1 } }, // 15 bgforest1
  { .type = type::play, .play = { .audioIndex = 1 } }, // 16 sfx/Chime.ogg
  { .type = type::show, .show = { .imageIndex = 13, .transformIndex = transform::left, } }, // 17 al
  { .type = type::voice, .voice = { .audioIndex = 7 } }, // 18 alice/a1.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 4 } }, // 19 a "Are we almost there?"
  { .type = type::show, .show = { .imageIndex = 12, .transformIndex = transform::right, } }, // 20 ei
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
  { .type = type::scene, .scene = { .imageIndex = 3 } }, // 59 bgflower1
  { .type = type::show, .show = { .imageIndex = 12, .transformIndex = transform::right, } }, // 60 ei
  { .type = type::voice, .voice = { .audioIndex = 23 } }, // 61 eily/e8.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 19 } }, // 62 e "Look at all the butterflies! They are all so pretty!"
  { .type = type::show, .show = { .imageIndex = 13, .transformIndex = transform::left, } }, // 63 al
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
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 31 } }, // 88 a "..."
  { .type = type::play, .play = { .audioIndex = 35 } }, // 89 poem/Poem1.ogg
  { .type = type::pause, .pause = { .duration = 40 } }, // 90
  { .type = type::jump, .jump = { .statementIndex = 98 } }, // 91 internal jump (b'__menu_end', 1)
  { .type = type::voice, .voice = { .audioIndex = 36 } }, // 92 eily/e16.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 32 } }, // 93 e "Serves you right for scaring those elephant-dogs"
  { .type = type::stop, .stop = { .audioIndex = 22, .fadeout = 4.2 } }, // 94 PhrygianButterflies
  { .type = type::voice, .voice = { .audioIndex = 37 } }, // 95 alice/a12.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 33 } }, // 96 a "They were asking for it, you know"
  { .type = type::jump, .jump = { .statementIndex = 98 } }, // 97 internal jump (b'__menu_end', 1)
  { .type = type::jump, .jump = { .statementIndex = 99 } }, // 98 mainbranch2
  { .type = type::hide, .hide = { .imageIndex = 12 } }, // 99 ei
  { .type = type::show, .show = { .imageIndex = 11, .transformIndex = transform::right, } }, // 100 catw
  { .type = type::show, .show = { .imageIndex = 12, .transformIndex = xflip | transform::centerleft, } }, // 101 ei
  { .type = type::voice, .voice = { .audioIndex = 38 } }, // 102 leona/c1.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 34 } }, // 103 c "Rawrrrr"
  { .type = type::hide, .hide = { .imageIndex = 11 } }, // 104 catw
  { .type = type::show, .show = { .imageIndex = 10, .transformIndex = transform::right, } }, // 105 cat
  { .type = type::play, .play = { .audioIndex = 39 } }, // 106 music/ScaredMice.ogg
  { .type = type::hide, .hide = { .imageIndex = 12 } }, // 107 ei
  { .type = type::hide, .hide = { .imageIndex = 13 } }, // 108 al
  { .type = type::show, .show = { .imageIndex = 14, .transformIndex = xflip | transform::centerleft, } }, // 109 sei
  { .type = type::show, .show = { .imageIndex = 15, .transformIndex = transform::left, } }, // 110 sal
  { .type = type::voice, .voice = { .audioIndex = 40 } }, // 111 mousegirls/mg1.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 35 } }, // 112 mg "AHHHHHHHHHH!!!!!"
  { .type = type::voice, .voice = { .audioIndex = 41 } }, // 113 leona/c2.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 36 } }, // 114 c "Nyanyanyanya"
  { .type = type::voice, .voice = { .audioIndex = 42 } }, // 115 leona/c3.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 37 } }, // 116 c "Well, what do we have here? If it isn't two little meowse girls, all alone amongst the flowers"
  { .type = type::menu, .menu = { .count = 2, .optionIndex = 4 } }, // 117 "Beg for mercy", "Run"
  { .type = type::voice, .voice = { .audioIndex = 43 } }, // 118 alice/a14.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 38 } }, // 119 a "Please don't eat us!!!"
  { .type = type::jump, .jump = { .statementIndex = 126 } }, // 120 internal jump (b'__menu_end', 2)
  { .type = type::voice, .voice = { .audioIndex = 44 } }, // 121 eily/e18.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 39 } }, // 122 e "Alice don't run, our only chance is through pleading!"
  { .type = type::voice, .voice = { .audioIndex = 45 } }, // 123 eily/e19.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 40 } }, // 124 e "Please don't eat us, miss kitty cat!!! ><"
  { .type = type::jump, .jump = { .statementIndex = 126 } }, // 125 internal jump (b'__menu_end', 2)
  { .type = type::jump, .jump = { .statementIndex = 127 } }, // 126 mainbranch3
  { .type = type::stop, .stop = { .audioIndex = 39, .fadeout = 2.0 } }, // 127 ScaredMice
  { .type = type::voice, .voice = { .audioIndex = 46 } }, // 128 leona/c4.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 41 } }, // 129 c "I'm not gonna eat you nyanyanya"
  { .type = type::hide, .hide = { .imageIndex = 15 } }, // 130 sal
  { .type = type::show, .show = { .imageIndex = 13, .transformIndex = transform::left, } }, // 131 al
  { .type = type::play, .play = { .audioIndex = 5 } }, // 132 music/TinyForestMinstrels.ogg
  { .type = type::voice, .voice = { .audioIndex = 47 } }, // 133 leona/c5.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 42 } }, // 134 c "I just want to know what two little meowses are doing so very far away from home"
  { .type = type::hide, .hide = { .imageIndex = 14 } }, // 135 sei
  { .type = type::show, .show = { .imageIndex = 12, .transformIndex = xflip | transform::centerleft, } }, // 136 ei
  { .type = type::voice, .voice = { .audioIndex = 48 } }, // 137 leona/c6.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 43 } }, // 138 c "Also, are you minstrels?"
  { .type = type::voice, .voice = { .audioIndex = 49 } }, // 139 eily/e20.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 44 } }, // 140 e "Y-Yes"
  { .type = type::voice, .voice = { .audioIndex = 50 } }, // 141 alice/a15.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 45 } }, // 142 a "W-We are on a quest to Castle Alysen..."
  { .type = type::voice, .voice = { .audioIndex = 51 } }, // 143 eily/e21.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 46 } }, // 144 e "Shh don't tell her that"
  { .type = type::voice, .voice = { .audioIndex = 52 } }, // 145 leona/c7.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 47 } }, // 146 c "The Castle of Alysen you say?!?"
  { .type = type::voice, .voice = { .audioIndex = 53 } }, // 147 leona/c8.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 48 } }, // 148 c "Why, that's where I am headed!"
  { .type = type::voice, .voice = { .audioIndex = 54 } }, // 149 eily/e22.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 49 } }, // 150 e "You don't say..."
  { .type = type::voice, .voice = { .audioIndex = 55 } }, // 151 leona/c9.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 50 } }, // 152 c "Yah, I do actually"
  { .type = type::voice, .voice = { .audioIndex = 56 } }, // 153 eily/e23.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 51 } }, // 154 e "So... Why might you be traveling to the castle?"
  { .type = type::voice, .voice = { .audioIndex = 57 } }, // 155 leona/c10.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 52 } }, // 156 c "I belong to the lineage of Agrepen"
  { .type = type::voice, .voice = { .audioIndex = 58 } }, // 157 eily/e24.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 53 } }, // 158 e "And what might that mean?"
  { .type = type::voice, .voice = { .audioIndex = 59 } }, // 159 leona/c11.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 54 } }, // 160 c "The Agrepens are a long line of felines loyal to the crown of corvidae"
  { .type = type::voice, .voice = { .audioIndex = 60 } }, // 161 eily/e25.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 55 } }, // 162 e "Really? That must mean you are a noble?"
  { .type = type::voice, .voice = { .audioIndex = 61 } }, // 163 leona/c12.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 56 } }, // 164 c "Well, not really..."
  { .type = type::voice, .voice = { .audioIndex = 62 } }, // 165 leona/c13.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 57 } }, // 166 c "My father was one of the queens knights many years ago"
  { .type = type::voice, .voice = { .audioIndex = 63 } }, // 167 eily/e26.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 58 } }, // 168 e "Ah I see"
  { .type = type::voice, .voice = { .audioIndex = 64 } }, // 169 eily/e27.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 59 } }, // 170 e "So do you live at the castle or something?"
  { .type = type::voice, .voice = { .audioIndex = 65 } }, // 171 leona/c14.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 60 } }, // 172 c "Well, no..."
  { .type = type::voice, .voice = { .audioIndex = 66 } }, // 173 alice/a16.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 61 } }, // 174 a "Then why are you traveling to The Castle Alysen?"
  { .type = type::voice, .voice = { .audioIndex = 67 } }, // 175 leona/c15.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 62 } }, // 176 c "uhhh"
  { .type = type::play, .play = { .audioIndex = 0 } }, // 177 music/MistAmbience.ogg
  { .type = type::stop, .stop = { .audioIndex = 5, .fadeout = 2.0 } }, // 178 TinyForestMinstrels
  { .type = type::voice, .voice = { .audioIndex = 68 } }, // 179 leona/c16.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 63 } }, // 180 c "I DONT NEED TO BE PRESSURED BY LITTLE MICE TO SAY ANYTHING!!!!"
  { .type = type::voice, .voice = { .audioIndex = 69 } }, // 181 leona/c17.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 64 } }, // 182 c "GOOD DAY!"
  { .type = type::hide, .hide = { .imageIndex = 10 } }, // 183 cat
  { .type = type::voice, .voice = { .audioIndex = 70 } }, // 184 alice/a17.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 65 } }, // 185 a "Wha..."
  { .type = type::voice, .voice = { .audioIndex = 71 } }, // 186 eily/e28.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 66 } }, // 187 e "Phew, I was scared she was gonna follow us the whole way"
  { .type = type::voice, .voice = { .audioIndex = 72 } }, // 188 alice/a18.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 67 } }, // 189 a "She didn't seem so bad"
  { .type = type::voice, .voice = { .audioIndex = 73 } }, // 190 eily/e29.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 68 } }, // 191 e "Are you kidding? She's a crazy kitty!"
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 192 bgwhite
  { .type = type::play, .play = { .audioIndex = 1 } }, // 193 sfx/Chime.ogg
  { .type = type::voice, .voice = { .audioIndex = 74 } }, // 194 nara/n6.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 69 } }, // 195 n "After their encounter with the weird cat, the mice scurry out of the flower field and into the nearby meadow"
  { .type = type::scene, .scene = { .imageIndex = 2 } }, // 196 bgforest2
  { .type = type::show, .show = { .imageIndex = 12, .transformIndex = transform::right, } }, // 197 ei
  { .type = type::voice, .voice = { .audioIndex = 75 } }, // 198 eily/e30.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 70 } }, // 199 e "I think this is the right way..."
  { .type = type::show, .show = { .imageIndex = 13, .transformIndex = transform::left, } }, // 200 al
  { .type = type::voice, .voice = { .audioIndex = 76 } }, // 201 alice/a19.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 71 } }, // 202 a "Then where did the path go?"
  { .type = type::voice, .voice = { .audioIndex = 77 } }, // 203 eily/e31.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 72 } }, // 204 e "How am I supposed to know?"
  { .type = type::voice, .voice = { .audioIndex = 78 } }, // 205 alice/a20.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 73 } }, // 206 a "Did you hear that?!?!"
  { .type = type::show, .show = { .imageIndex = 12, .transformIndex = xflip | transform::centerleft, } }, // 207 ei
  { .type = type::show, .show = { .imageIndex = 10, .transformIndex = transform::right, } }, // 208 cat
  { .type = type::play, .play = { .audioIndex = 22 } }, // 209 music/PhrygianButterflies.ogg
  { .type = type::voice, .voice = { .audioIndex = 79 } }, // 210 leona/c18.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 74 } }, // 211 c "Hey there... I apologize, I didn't mean to storm off like that"
  { .type = type::voice, .voice = { .audioIndex = 80 } }, // 212 eily/e32.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 75 } }, // 213 e "Ha ha, no problem..."
  { .type = type::voice, .voice = { .audioIndex = 81 } }, // 214 alice/a21.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 76 } }, // 215 a "So... Why are you traveling to Castle Alysen?"
  { .type = type::voice, .voice = { .audioIndex = 82 } }, // 216 eily/e33.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 77 } }, // 217 e "Alice!!!"
  { .type = type::voice, .voice = { .audioIndex = 83 } }, // 218 leona/c19.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 78 } }, // 219 c "If you must know, I have been summoned by the queen"
  { .type = type::voice, .voice = { .audioIndex = 84 } }, // 220 leona/c20.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 79 } }, // 221 c "I suspect that my poor reputation amongst the locals of Eastern Nidus has come back to haunt me"
  { .type = type::voice, .voice = { .audioIndex = 85 } }, // 222 leona/c21.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 80 } }, // 223 c "Though I know not what what she has summoned me for"
  { .type = type::voice, .voice = { .audioIndex = 86 } }, // 224 alice/a22.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 81 } }, // 225 a "Ahhhhhh"
  { .type = type::voice, .voice = { .audioIndex = 87 } }, // 226 leona/c22.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 82 } }, // 227 c "So then..."
  { .type = type::voice, .voice = { .audioIndex = 88 } }, // 228 leona/c23.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 83 } }, // 229 c "Why are YOU traveling to the Castle?"
  { .type = type::voice, .voice = { .audioIndex = 89 } }, // 230 alice/a23.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 84 } }, // 231 a "We are delivering a feather!!!"
  { .type = type::voice, .voice = { .audioIndex = 90 } }, // 232 eily/e34.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 85 } }, // 233 e "Alice no!"
  { .type = type::voice, .voice = { .audioIndex = 91 } }, // 234 alice/a24.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 86 } }, // 235 a "A feather that belonged to the queen herself!!!"
  { .type = type::voice, .voice = { .audioIndex = 92 } }, // 236 eily/e35.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 87 } }, // 237 e "Why you little..."
  { .type = type::voice, .voice = { .audioIndex = 93 } }, // 238 leona/c24.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 88 } }, // 239 c "A feather you say? One of the queens?"
  { .type = type::voice, .voice = { .audioIndex = 94 } }, // 240 leona/c25.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 89 } }, // 241 c "How on the face of Al Mot might you have aquired such a thing?"
  { .type = type::voice, .voice = { .audioIndex = 95 } }, // 242 leona/c26.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 90 } }, // 243 c "If it is authentic"
  { .type = type::voice, .voice = { .audioIndex = 96 } }, // 244 eily/e36.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 91 } }, // 245 e "Since Alice cannot keep a secret, I shall tell you"
  { .type = type::voice, .voice = { .audioIndex = 97 } }, // 246 eily/e37.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 92 } }, // 247 e "Seven moons ago, our town was attacked by three owls and a band of mice from the northern principalities"
  { .type = type::voice, .voice = { .audioIndex = 98 } }, // 248 eily/e38.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 93 } }, // 249 e "Eventually word spread to greater nearby settlements, and so"
  { .type = type::voice, .voice = { .audioIndex = 99 } }, // 250 eily/e39.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 94 } }, // 251 e "Messengers from the keep in Musia sent for aid from the Ravens"
  { .type = type::voice, .voice = { .audioIndex = 100 } }, // 252 eily/e40.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 95 } }, // 253 e "Four moons ago, the request was answered"
  { .type = type::voice, .voice = { .audioIndex = 101 } }, // 254 eily/e41.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 96 } }, // 255 e "And a small group of mice accompanied by two ravens a fox, and three squirrels set out to the northern principalities"
  { .type = type::voice, .voice = { .audioIndex = 102 } }, // 256 eily/e42.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 97 } }, // 257 e "Anyways, long story short, we drove those barbaric rats out of their home"
  { .type = type::voice, .voice = { .audioIndex = 103 } }, // 258 alice/a25.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 98 } }, // 259 a "They arent actual rats you know"
  { .type = type::voice, .voice = { .audioIndex = 104 } }, // 260 eily/e43.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 99 } }, // 261 e "Obviously, but you wont catch me speaking kindly of them"
  { .type = type::voice, .voice = { .audioIndex = 105 } }, // 262 alice/a26.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 100 } }, // 263 a "And you forgot the most important part"
  { .type = type::voice, .voice = { .audioIndex = 106 } }, // 264 eily/e44.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 101 } }, // 265 e "Yah yah, I am getting there"
  { .type = type::voice, .voice = { .audioIndex = 107 } }, // 266 eily/e45.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 102 } }, // 267 e "So, essentially, my brother is trained in archery, and..."
  { .type = type::voice, .voice = { .audioIndex = 108 } }, // 268 alice/a27.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 103 } }, // 269 a "Speed it up already"
  { .type = type::voice, .voice = { .audioIndex = 109 } }, // 270 eily/e46.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 104 } }, // 271 e "You tell it then!"
  { .type = type::voice, .voice = { .audioIndex = 110 } }, // 272 alice/a28.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 105 } }, // 273 a "My cousin found this feather in one of the highest towers of a castle far to the north"
  { .type = type::voice, .voice = { .audioIndex = 111 } }, // 274 leona/c27.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 106 } }, // 275 c "How do you know it belongs to the queen?"
  { .type = type::voice, .voice = { .audioIndex = 112 } }, // 276 eily/e47.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 107 } }, // 277 e "It said so itself above the display on the wall"
  { .type = type::voice, .voice = { .audioIndex = 113 } }, // 278 alice/a29.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 108 } }, // 279 a "Supposedly, it was in a room filled with treasures!"
  { .type = type::voice, .voice = { .audioIndex = 114 } }, // 280 leona/c28.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 109 } }, // 281 c "That is very nice and all, but what are the two of you doing out here all alone?"
  { .type = type::voice, .voice = { .audioIndex = 115 } }, // 282 leona/c29.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 110 } }, // 283 c "Do you expect every bird in Avia to respect your alliance with Castle Alysen?"
  { .type = type::voice, .voice = { .audioIndex = 116 } }, // 284 eily/e48.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 111 } }, // 285 e "What do you mean?"
  { .type = type::voice, .voice = { .audioIndex = 117 } }, // 286 leona/c30.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 112 } }, // 287 c "I mean, the two of you probably look like walking dinner to most creatures"
  { .type = type::voice, .voice = { .audioIndex = 118 } }, // 288 alice/a30.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 113 } }, // 289 a "I could go for some dinner..."
  { .type = type::voice, .voice = { .audioIndex = 119 } }, // 290 eily/e49.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 114 } }, // 291 e "Anyways..."
  { .type = type::voice, .voice = { .audioIndex = 120 } }, // 292 eily/e50.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 115 } }, // 293 e "To answer your question, upon returning to the village, the feather was taken from my brother by the needle guild"
  { .type = type::voice, .voice = { .audioIndex = 121 } }, // 294 eily/e51.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 116 } }, // 295 e "So... Yesterday, after sundown"
  { .type = type::voice, .voice = { .audioIndex = 122 } }, // 296 eily/e52.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 117 } }, // 297 e "We stole the feather from the guild hall before vanishing into the night"
  { .type = type::voice, .voice = { .audioIndex = 123 } }, // 298 eily/e53.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 118 } }, // 299 e "Can you imagine the look on their stupid faces, when they woke up, and not only is the feather missing"
  { .type = type::voice, .voice = { .audioIndex = 124 } }, // 300 eily/e54.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 119 } }, // 301 e "But so are we!"
  { .type = type::voice, .voice = { .audioIndex = 125 } }, // 302 alice/a31.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 120 } }, // 303 a "Hahahaha"
  { .type = type::voice, .voice = { .audioIndex = 126 } }, // 304 leona/c31.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 121 } }, // 305 c "Are the two of you mad?"
  { .type = type::voice, .voice = { .audioIndex = 127 } }, // 306 leona/c32.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 122 } }, // 307 c "I assume you are attempting to return the Queens feather?"
  { .type = type::voice, .voice = { .audioIndex = 128 } }, // 308 alice/a32.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 123 } }, // 309 a "Yes, we intend to deliver the feather to its rightful owner"
  { .type = type::voice, .voice = { .audioIndex = 129 } }, // 310 leona/c33.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 124 } }, // 311 c "Absolute madness!"
  { .type = type::voice, .voice = { .audioIndex = 130 } }, // 312 mousegirls/mg2.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 31 } }, // 313 mg "..."
  { .type = type::voice, .voice = { .audioIndex = 131 } }, // 314 leona/c34.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 125 } }, // 315 c "I will follow the two of you"
  { .type = type::voice, .voice = { .audioIndex = 132 } }, // 316 leona/c35.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 126 } }, // 317 c "To keep you safe, that is"
  { .type = type::voice, .voice = { .audioIndex = 133 } }, // 318 alice/a33.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 127 } }, // 319 a "Alright!"
  { .type = type::voice, .voice = { .audioIndex = 134 } }, // 320 eily/e55.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 128 } }, // 321 e "Ha ha... Okay..."
  { .type = type::voice, .voice = { .audioIndex = 135 } }, // 322 leona/c36.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 129 } }, // 323 c "Great! Follow me, I know a shortcut! :3"
  { .type = type::hide, .hide = { .imageIndex = 10 } }, // 324 cat
  { .type = type::voice, .voice = { .audioIndex = 136 } }, // 325 alice/a34.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 130 } }, // 326 a "Sounds good!"
  { .type = type::hide, .hide = { .imageIndex = 13 } }, // 327 al
  { .type = type::stop, .stop = { .audioIndex = 22, .fadeout = 2.0 } }, // 328 PhrygianButterflies
  { .type = type::voice, .voice = { .audioIndex = 137 } }, // 329 eily/e56.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 131 } }, // 330 e "Oh dear!"
  { .type = type::hide, .hide = { .imageIndex = 12 } }, // 331 ei
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 332 bgwhite
  { .type = type::play, .play = { .audioIndex = 1 } }, // 333 sfx/Chime.ogg
  { .type = type::voice, .voice = { .audioIndex = 138 } }, // 334 nara/n7.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 132 } }, // 335 n "And so the mice girls follow the noble cat further towards their destination"
  { .type = type::scene, .scene = { .imageIndex = 4 } }, // 336 bgwheatfield1
  { .type = type::play, .play = { .audioIndex = 139 } }, // 337 music/WheatFields.ogg
  { .type = type::show, .show = { .imageIndex = 10, .transformIndex = transform::right, } }, // 338 cat
  { .type = type::voice, .voice = { .audioIndex = 140 } }, // 339 leona/c37.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 133 } }, // 340 c "Nya"
  { .type = type::show, .show = { .imageIndex = 16, .transformIndex = transform::left, } }, // 341 wal
  { .type = type::voice, .voice = { .audioIndex = 141 } }, // 342 alice/a35.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 134 } }, // 343 a "Look, your right, the castle is just up ahead!"
  { .type = type::show, .show = { .imageIndex = 12, .transformIndex = xflip | transform::centerleft, } }, // 344 ei
  { .type = type::voice, .voice = { .audioIndex = 142 } }, // 345 eily/e57.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 135 } }, // 346 e "Wait up"
  { .type = type::voice, .voice = { .audioIndex = 143 } }, // 347 leona/c38.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 136 } }, // 348 c "I told you I knew a shortcut!"
  { .type = type::voice, .voice = { .audioIndex = 144 } }, // 349 leona/c39.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 137 } }, // 350 c "Most people take the long way around"
  { .type = type::voice, .voice = { .audioIndex = 145 } }, // 351 eily/e58.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 138 } }, // 352 e "Yah because those are royal wheatfields!"
  { .type = type::voice, .voice = { .audioIndex = 146 } }, // 353 alice/a36.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 139 } }, // 354 a "Who cares?"
  { .type = type::voice, .voice = { .audioIndex = 147 } }, // 355 eily/e59.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 140 } }, // 356 e "Are you trying to get us killed?"
  { .type = type::voice, .voice = { .audioIndex = 148 } }, // 357 eily/e60.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 141 } }, // 358 e "Its trespassing on royal land!"
  { .type = type::voice, .voice = { .audioIndex = 149 } }, // 359 leona/c40.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 142 } }, // 360 c "Calm down, I have done this like a million times"
  { .type = type::voice, .voice = { .audioIndex = 150 } }, // 361 eily/e61.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 143 } }, // 362 e "That doesnt make me calm!"
  { .type = type::voice, .voice = { .audioIndex = 151 } }, // 363 leona/c41.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 144 } }, // 364 c "How can the rolling fields of wheat not calm your spirit?"
  { .type = type::voice, .voice = { .audioIndex = 152 } }, // 365 leona/c42.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 145 } }, // 366 c "You little mice truly are mad!"
  { .type = type::voice, .voice = { .audioIndex = 153 } }, // 367 alice/a37.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 146 } }, // 368 a "I like the wheat!"
  { .type = type::voice, .voice = { .audioIndex = 154 } }, // 369 eily/e62.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 147 } }, // 370 e "Shut up!"
  { .type = type::voice, .voice = { .audioIndex = 155 } }, // 371 leona/c43.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 148 } }, // 372 c "Sounds like someone needs a nap!"
  { .type = type::voice, .voice = { .audioIndex = 156 } }, // 373 eily/e63.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 149 } }, // 374 e "Why? because I'm not insane like you?"
  { .type = type::voice, .voice = { .audioIndex = 157 } }, // 375 leona/c44.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 150 } }, // 376 c "Yah, your so sane, that you decided to steal from your town and then run off alone to the country of birds"
  { .type = type::voice, .voice = { .audioIndex = 158 } }, // 377 leona/c45.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 151 } }, // 378 c "The power of friendship wont protect the two of you from becoming dinner"
  { .type = type::voice, .voice = { .audioIndex = 159 } }, // 379 leona/c46.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 152 } }, // 380 c "And that, is why I feel obligated to accompany you!"
  { .type = type::voice, .voice = { .audioIndex = 160 } }, // 381 eily/e64.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 153 } }, // 382 e "Hey, we have a good reason!"
  { .type = type::voice, .voice = { .audioIndex = 161 } }, // 383 leona/c47.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 154 } }, // 384 c "And what might that be?"
  { .type = type::voice, .voice = { .audioIndex = 162 } }, // 385 eily/e65.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 155 } }, // 386 e "My brother found the feather, not the town guild, its a matter of family pride!"
  { .type = type::voice, .voice = { .audioIndex = 163 } }, // 387 leona/c48.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 156 } }, // 388 c "Pride has touched the chosen meouse"
  { .type = type::voice, .voice = { .audioIndex = 164 } }, // 389 leona/c49.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 157 } }, // 390 c "Flies she towards the Castle"
  { .type = type::voice, .voice = { .audioIndex = 165 } }, // 391 leona/c50.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 158 } }, // 392 c "But her ambition burns far too bright, and silly mice dont have any wings to melt"
  { .type = type::voice, .voice = { .audioIndex = 166 } }, // 393 mousegirls/mg3.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 159 } }, // 394 mg "What?"
  { .type = type::voice, .voice = { .audioIndex = 167 } }, // 395 leona/c51.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 160 } }, // 396 c "Nyanyanya"
  { .type = type::voice, .voice = { .audioIndex = 168 } }, // 397 leona/c52.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 161 } }, // 398 c "Nyevermind"
  { .type = type::stop, .stop = { .audioIndex = 139, .fadeout = 3.0 } }, // 399 WheatFields
  { .type = type::voice, .voice = { .audioIndex = 169 } }, // 400 leona/c53.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 162 } }, // 401 c "Sing me a song little minstrels!"
  { .type = type::voice, .voice = { .audioIndex = 130 } }, // 402 mousegirls/mg2.ogg
  { .type = type::say, .say = { .characterIndex = 4, .stringIndex = 31 } }, // 403 mg "..."
  { .type = type::play, .play = { .audioIndex = 35 } }, // 404 poem/Poem1.ogg
  { .type = type::pause, .pause = { .duration = 40 } }, // 405
  { .type = type::voice, .voice = { .audioIndex = 170 } }, // 406 leona/c54.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 163 } }, // 407 c "Very Nyice!"
  { .type = type::voice, .voice = { .audioIndex = 171 } }, // 408 leona/c55.ogg
  { .type = type::say, .say = { .characterIndex = 2, .stringIndex = 164 } }, // 409 c "Now tell me little minstrels, what are your names?"
  { .type = type::voice, .voice = { .audioIndex = 172 } }, // 410 alice/a39.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 165 } }, // 411 a "My name is Alice"
  { .type = type::voice, .voice = { .audioIndex = 173 } }, // 412 eily/e67.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 166 } }, // 413 e "And my name is Eily"
  { .type = type::voice, .voice = { .audioIndex = 174 } }, // 414 eily/e68.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 167 } }, // 415 e "What is your name?"
  { .type = type::voice, .voice = { .audioIndex = 175 } }, // 416 leona/c56.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 168 } }, // 417 l "My name is Leona!"
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 418 bgwhite
  { .type = type::voice, .voice = { .audioIndex = 176 } }, // 419 nara/n8.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 169 } }, // 420 n "And so, the odd trio walked through the wheatfields and towards the castle"
  { .type = type::voice, .voice = { .audioIndex = 177 } }, // 421 nara/n9.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 170 } }, // 422 n "Upon approaching the gates, the three were escorted to a large room"
  { .type = type::voice, .voice = { .audioIndex = 178 } }, // 423 nara/n10.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 171 } }, // 424 n "They were then instructed to wait for an audience with the Queen"
  { .type = type::voice, .voice = { .audioIndex = 179 } }, // 425 hera/h1.ogg
  { .type = type::say, .say = { .characterIndex = 7, .stringIndex = 172 } }, // 426 h "You may now present yourselves before her Majesty, Queen Alary of Alysen"
  { .type = type::scene, .scene = { .imageIndex = 5 } }, // 427 bgcastle1
  { .type = type::play, .play = { .audioIndex = 180 } }, // 428 music/Preludium.ogg
  { .type = type::show, .show = { .imageIndex = 9, .transformIndex = transform::right, } }, // 429 bi
  { .type = type::pause, .pause = { .duration = 1.0 } }, // 430
  { .type = type::voice, .voice = { .audioIndex = 181 } }, // 431 hera/h2.ogg
  { .type = type::say, .say = { .characterIndex = 7, .stringIndex = 173 } }, // 432 h "Leona Agrepen of Elmindeer"
  { .type = type::show, .show = { .imageIndex = 10, .transformIndex = xflip | transform::center, } }, // 433 cat
  { .type = type::voice, .voice = { .audioIndex = 182 } }, // 434 leona/c57.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 174 } }, // 435 l "Hail, your Majesty"
  { .type = type::voice, .voice = { .audioIndex = 183 } }, // 436 hera/h3.ogg
  { .type = type::say, .say = { .characterIndex = 7, .stringIndex = 175 } }, // 437 h "Eily VeraWheat of the Western Principalities"
  { .type = type::show, .show = { .imageIndex = 12, .transformIndex = transform::centerleft, } }, // 438 ei
  { .type = type::voice, .voice = { .audioIndex = 184 } }, // 439 eily/e69.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 174 } }, // 440 e "Hail, your Majesty"
  { .type = type::voice, .voice = { .audioIndex = 185 } }, // 441 hera/h4.ogg
  { .type = type::say, .say = { .characterIndex = 7, .stringIndex = 176 } }, // 442 h "Alice SeraWheat of the Western Principalities"
  { .type = type::play, .play = { .audioIndex = 186 } }, // 443 sfx/Glass.ogg
  { .type = type::pause, .pause = { .duration = 1.0 } }, // 444
  { .type = type::voice, .voice = { .audioIndex = 187 } }, // 445 alice/a40.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 177 } }, // 446 a "I'm alright!"
  { .type = type::show, .show = { .imageIndex = 16, .transformIndex = transform::left, } }, // 447 wal
  { .type = type::voice, .voice = { .audioIndex = 188 } }, // 448 alice/a41.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 178 } }, // 449 a "H-Hail, your majesty"
  { .type = type::voice, .voice = { .audioIndex = 189 } }, // 450 leona/c58.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 160 } }, // 451 l "Nyanyanya"
  { .type = type::voice, .voice = { .audioIndex = 190 } }, // 452 bird/b1.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 179 } }, // 453 b "And what is this?"
  { .type = type::voice, .voice = { .audioIndex = 191 } }, // 454 bird/b2.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 180 } }, // 455 b "A cat and two mice in my court?"
  { .type = type::voice, .voice = { .audioIndex = 192 } }, // 456 bird/b3.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 181 } }, // 457 b "Is this some kind of joke?"
  { .type = type::voice, .voice = { .audioIndex = 193 } }, // 458 leona/c59.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 182 } }, // 459 l "Not a joke Your Majesty, these are my friends"
  { .type = type::voice, .voice = { .audioIndex = 194 } }, // 460 eily/e70.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 183 } }, // 461 e "Friends?"
  { .type = type::voice, .voice = { .audioIndex = 195 } }, // 462 bird/b4.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 184 } }, // 463 b "Miss Agrepen, your reputation is far from acceptable"
  { .type = type::voice, .voice = { .audioIndex = 196 } }, // 464 bird/b5.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 185 } }, // 465 b "And I can imagine, you already know why I have summoned you here today"
  { .type = type::voice, .voice = { .audioIndex = 197 } }, // 466 leona/c60.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 186 } }, // 467 l "Uhhmmmm...."
  { .type = type::voice, .voice = { .audioIndex = 198 } }, // 468 leona/c61.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 187 } }, // 469 l "Does it have anything to do with Eastern Nidus?"
  { .type = type::voice, .voice = { .audioIndex = 199 } }, // 470 bird/b6.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 188 } }, // 471 b "I think you already know the answer to that"
  { .type = type::voice, .voice = { .audioIndex = 200 } }, // 472 bird/b7.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 189 } }, // 473 b "Your father would be rather dissapointed if he were still alive"
  { .type = type::voice, .voice = { .audioIndex = 201 } }, // 474 leona/c0.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 31 } }, // 475 l "..."
  { .type = type::voice, .voice = { .audioIndex = 202 } }, // 476 bird/b8.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 190 } }, // 477 b "Leona Agrepen, the court has found you guilty of two cases of larceny and seven cases of petty pilfering"
  { .type = type::voice, .voice = { .audioIndex = 203 } }, // 478 bird/b9.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 191 } }, // 479 b "Miss Agrepen, you are hereby banned from stepping foot in Eastern Nidus"
  { .type = type::voice, .voice = { .audioIndex = 204 } }, // 480 bird/b10.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 192 } }, // 481 b "From here on out, you shall be restricted to the central principalities of Avia"
  { .type = type::voice, .voice = { .audioIndex = 205 } }, // 482 leona/c62.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 193 } }, // 483 l "Owww c'mon! There is nothing to do around here!"
  { .type = type::voice, .voice = { .audioIndex = 206 } }, // 484 bird/b11.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 194 } }, // 485 b "Silence!"
  { .type = type::voice, .voice = { .audioIndex = 207 } }, // 486 bird/b12.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 195 } }, // 487 b "It is here, in the Central city of Alysen that you shall remain, where I can keep a watchful eye on you"
  { .type = type::voice, .voice = { .audioIndex = 208 } }, // 488 bird/b13.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 196 } }, // 489 b "Or would you prefer that I permit the request of the lesser courts to have you declawed?"
  { .type = type::voice, .voice = { .audioIndex = 209 } }, // 490 leona/c63.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 197 } }, // 491 l "No ><"
  { .type = type::voice, .voice = { .audioIndex = 210 } }, // 492 bird/b14.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 198 } }, // 493 b "Take my leniency as a display of gratitude for the services rendered by your father"
  { .type = type::voice, .voice = { .audioIndex = 211 } }, // 494 leona/c64.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 199 } }, // 495 l "Yes Your Majesty... Forgive me for speaking out of turn"
  { .type = type::voice, .voice = { .audioIndex = 212 } }, // 496 bird/b15.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 200 } }, // 497 b "Now, why have you brought these little mice before me?"
  { .type = type::voice, .voice = { .audioIndex = 213 } }, // 498 leona/c65.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 201 } }, // 499 l "Alary, Your Majesty, these are minstrels I met on the road to Alysen"
  { .type = type::voice, .voice = { .audioIndex = 214 } }, // 500 leona/c66.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 202 } }, // 501 l "They lay claim to a feather, said to be one of Your Majesty's own"
  { .type = type::voice, .voice = { .audioIndex = 215 } }, // 502 bird/b16.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 203 } }, // 503 b "Really?"
  { .type = type::voice, .voice = { .audioIndex = 216 } }, // 504 bird/b17.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 204 } }, // 505 b "And what else might the two of you claim? Alice and Eily of the West"
  { .type = type::voice, .voice = { .audioIndex = 217 } }, // 506 alice/a42.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 205 } }, // 507 a "I u-uhh..."
  { .type = type::voice, .voice = { .audioIndex = 218 } }, // 508 eily/e71.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 206 } }, // 509 e "Your Majesty, this feather was found by my brother in a castle to the north"
  { .type = type::voice, .voice = { .audioIndex = 219 } }, // 510 eily/e72.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 207 } }, // 511 e "So very far my cousin and I have journeyed"
  { .type = type::voice, .voice = { .audioIndex = 220 } }, // 512 eily/e73.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 208 } }, // 513 e "Over the mountains of Almystice"
  { .type = type::voice, .voice = { .audioIndex = 221 } }, // 514 eily/e74.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 209 } }, // 515 e "Beyond the deep blue waters of the Lilac bay"
  { .type = type::voice, .voice = { .audioIndex = 222 } }, // 516 eily/e75.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 2 } }, // 517 e "And across the vast fields of Alysen"
  { .type = type::voice, .voice = { .audioIndex = 223 } }, // 518 eily/e76.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 210 } }, // 519 e "All in hopes that we might return Your Majesty's feather"
  { .type = type::voice, .voice = { .audioIndex = 224 } }, // 520 bird/b18.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 211 } }, // 521 b "What splendid and courageous little mice the two of you are"
  { .type = type::voice, .voice = { .audioIndex = 225 } }, // 522 leona/c67.ogg
  { .type = type::say, .say = { .characterIndex = 6, .stringIndex = 212 } }, // 523 l "Nyanyanyanyanya"
  { .type = type::voice, .voice = { .audioIndex = 226 } }, // 524 alice/a43.ogg
  { .type = type::say, .say = { .characterIndex = 0, .stringIndex = 213 } }, // 525 a "We also wanted to show our profound gratitude for the aid provided by Your Majesty just four moons ago"
  { .type = type::voice, .voice = { .audioIndex = 227 } }, // 526 eily/e77.ogg
  { .type = type::say, .say = { .characterIndex = 3, .stringIndex = 214 } }, // 527 e "Please allow us to perform a song for Your Majesty and Your Majesty's court"
  { .type = type::stop, .stop = { .audioIndex = 180, .fadeout = 4.2 } }, // 528 Preludium
  { .type = type::voice, .voice = { .audioIndex = 228 } }, // 529 bird/b19.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 215 } }, // 530 b "I appreciate your loyalty to the crown of Corvidae little mice"
  { .type = type::stop, .stop = { .audioIndex = 0, .fadeout = 4.2 } }, // 531 MistAmbience
  { .type = type::voice, .voice = { .audioIndex = 229 } }, // 532 bird/b20.ogg
  { .type = type::say, .say = { .characterIndex = 1, .stringIndex = 216 } }, // 533 b "You are most welcome to proceed with your little song"
  { .type = type::play, .play = { .audioIndex = 230 } }, // 534 poem/Poem3.ogg
  { .type = type::scene, .scene = { .imageIndex = 6 } }, // 535 bgcastle2
  { .type = type::scene, .scene = { .imageIndex = 7 } }, // 536 bgcastle3
  { .type = type::scene, .scene = { .imageIndex = 8 } }, // 537 bgcastle4
  { .type = type::scene, .scene = { .imageIndex = 7 } }, // 538 bgcastle3
  { .type = type::scene, .scene = { .imageIndex = 6 } }, // 539 bgcastle2
  { .type = type::scene, .scene = { .imageIndex = 7 } }, // 540 bgcastle3
  { .type = type::scene, .scene = { .imageIndex = 6 } }, // 541 bgcastle2
  { .type = type::scene, .scene = { .imageIndex = 5 } }, // 542 bgcastle1
  { .type = type::pause, .pause = { .duration = 3 } }, // 543
  { .type = type::scene_color, .scene_color = { .color = 0xffffff } }, // 544 bgwhite
  { .type = type::pause, .pause = { .duration = 33 } }, // 545
  { .type = type::voice, .voice = { .audioIndex = 231 } }, // 546 nara/n11.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 217 } }, // 547 n "In the end, Leona managed to stay out of the dungeon"
  { .type = type::voice, .voice = { .audioIndex = 232 } }, // 548 nara/n12.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 218 } }, // 549 n "Eily and Alice both stayed in service of the queen for 7 harvests"
  { .type = type::voice, .voice = { .audioIndex = 233 } }, // 550 nara/n13.ogg
  { .type = type::say, .say = { .characterIndex = 5, .stringIndex = 219 } }, // 551 n "before returning to their small nameless town, near the Keep of Musia"
  { .type = type::_return }, // 552
};

const int statements_length = (sizeof (statements)) / (sizeof (statements[0]));

}
