# The script of the game goes in this file.

# Declare characters used by this game. The color argument colorizes the
# name of the character.
image bgwhite = "#ffffff"
image bgblack = "#000000"
image bgforest1 = "bg/forest1.png"
image bgforest2 = "bg/forest2.png"
image bgflower1 = "bg/flowerfield1.png"
image bgwheatfield1 = "bg/wheatfield1.png"

image cat = "ch/cat.png"
image catw = "ch/catw.png"
image ei = "ch/Eily.png"
image al = "ch/Alice.png"
#image ei1 = "ch/eily1.png"
#image al1 = "ch/alice1.png"

define a = Character("Alice",color="00765e")
define c = Character("Cat",color="590093")
define e = Character("Eily",color="0b6092")
define mg = Character("Mouse Girls",color="000000")
define n = Character("Narrator",color="000000")
define l = Character("Leona",color="590093")

#this centers the name display
define gui.name_xpos = 0.5
define gui.name_xalign = 0.5

#this centers the dialogue display
define gui.dialogue_xpos = 0.5
define gui.dialogue_text_xalign = 0.5

transform centerleft:
    xalign 0.3
    yalign 1.0



transform centerright:
    xalign 0.7
    yalign 1.0


init:
    python:
        renpy.music.register_channel("ScaredMice", "music", loop=True)
        renpy.music.register_channel("TinyForestMinstrels", "music", loop=True)
        renpy.music.register_channel("MistAmbience", "music", loop=False)
        renpy.music.register_channel("PhrygianButterflies", "music", loop=True)
        renpy.music.register_channel("WheatFields", "music", loop=True)



# The game starts here.

label start:

    # Show a background. This uses a placeholder by default, but you can
    # add a file (named either "bg room.png" or "bg room.jpg") to the
    # images directory to show it.

    #play Chime "sfx/Chime.ogg" fadeout 1.0
    play sound "sfx/Chime.ogg"
    play MistAmbience "sfx/MistAmbience.ogg"
    scene bgblack
    pause 0.0
    scene bgwhite
    with Dissolve(3.0)
    #play music "IntroMusicTest.ogg"

    #play NarratorLoop "n1test.mp3"
    #voice "n1test.mp3"
    n "Far over the mountains of Almystice"
    #voice "n2test.mp3"
    n "Beyond the tumultuous waters of the Lilac Bay"
    #voice "n3test.mp3"
    n "And across the vast fields of Alysen"
    #voice "n4test.mp3"
    play TinyForestMinstrels "music/TinyForestMinstrels.ogg"
    n "Tiny minstrels can be heard amongst the trees"
    stop TinyForestMinstrels fadeout 5.5


    scene bgforest1
    with Dissolve(3.0)

    show al at left
    a "Are we almost there?"

    show ei at right

    e "Hmmm... Not really"

    a "How much further have we to go?"

    e "About two more moons"

    menu:
        "Complain" :

            a "We are still sooo far awayyy"

            e "And it will be even further if you dont stop complaining"

            a "Easy for you to say, all you have to carry is a little memory pipe!"
            a "I'm tired ><"

            e "Don't start whining now!"

            e "You need to remember why we have come all this way"

            a "I understand... I suppose it is for an important purpose"

        "Rationalize" :

            a "I understand... I suppose it is for an important purpose"
    jump mainbranch1


    label mainbranch1:
        e "We're almost out of the forest, we can take a little break once we clear the tree line"

        a "Is that where the flora field is?"

        e "Why yes, If I remember correctly, it should be just up ahead"
        stop TinyForestMinstrels fadeout 5.5

        scene bgwhite
        play sound "sfx/Chime.ogg"
        with Dissolve(1.0)


        #voice "n5test.ogg"
        n "As the minstrel mice girls continue along the path, the forest opens up into a beautiful field of flowers"

        play PhrygianButterflies "music/PhrygianButterflies.ogg"


        scene bgflower1
        with Dissolve(1.0)

        show ei at right

        e "Look at all the butterflies! They are all so pretty!"

        show al at left


        a "This place is like a dream..."

        e "There are so many flowers this time of year"
        e "I told you it would be worth the journey!"

        a "Can we stop for a bit now?"

        e "Of course"
        e "Ya know, Its a shame we didnt save some of those giant strawberries you found"

        a "I told you not to eat them all!"

        e "Yah yah"
        e "Anyways, shall I recite a tale?"

        menu:


            "Good idea" :
                stop PhrygianButterflies fadeout 4.2
                a "Why dont you sing the story of Eleanor the Hero!"
                e "Sure"
                a "..."
                play music "music/Poem1.ogg" noloop
                pause 40
            "I am too tired" :
                e "Serves you right for scaring those elephant-dogs"
                stop PhrygianButterflies fadeout 4.2
                a "They were asking for it, you know"







        jump mainbranch2

        #Improvise music in the butterfly field
        #Choose Between: Fleeting and
        #Elri scares the mice
        #We learn why they want to petition the queen
        # elri: "Arent you sacred she will eat you?"
        # elri: "Also, why would two little mice"
        #Elri shows them to the wheat town with the castle in the distance
        #They wish to speak to the queen of birds, but arent important enough
        #Elri helps




        #Cat is summoned to see the Queen of birds

        #Mouse girls realize its their only chance


        #

        #Lenient on Taxes
        #Removed from the map

        #And what is this? A cat and 2 mice stumbling about into my courtroom?
        #
        #
    label mainbranch2:
        hide ei
        show catw at right
        show ei at centerleft:
            xzoom -1
        voice "placeholdermeow.mp3"
        c "Rawrrrr"
        hide catw
        show cat at right
        play ScaredMice "music/ScaredMice.ogg"


        mg "AHHHHHHHHHH!!!!!"


        c "Nyanyanyanya"
        c "Well, what do we have here? If it isn't two little meowse girls, all alone amongst the flowers"

        menu:
            "Beg for mercy" :
                a "Please don't eat us!!!"

            "Run" :
                e "Alice don't run, our only chance is through pleading!"
                e "Please don't eat us, miss kitty cat!!! ><"



        jump mainbranch3





    label mainbranch3:
        stop ScaredMice fadeout 2.0
        c "I'm not gonna eat you nyanyanya"
        play TinyForestMinstrels "music/TinyForestMinstrels.ogg"
        c "I just want to know what two little meowses are doing so very far away from home"
        c "Also, are you minstrels?"

        e "Y-Yes"
        a "W-We are on a quest to Castle Alysen..."
        e "Shh don't tell her that"

        c "The Castle of Alysen you say?!?"
        c "Why, that's where I am headed!"

        e "You don't say..."

        c "Yah, I do actually"

        e "So... Why might you be traveling to the castle?"

        c "I belong to the lineage of Agrepen"

        e "And what might that mean?"

        c "The Agrepens are a long line of felines loyal to the crown of corvidae"

        e "Really? That must mean you are a noble?"

        c "Well, not really..."
        c "My father was one of the queens knights many years ago"

        e "Ah I see"

        e "So do you live at the castle or something?"

        c "Well, no..."

        a "Then why are you traveling to Castle Alysen?"


        c "uhhh"
        play MistAmbience "sfx/MistAmbience.ogg"
        stop TinyForestMinstrels fadeout 2.0
        c "I DONT NEED TO BE PRESSURED BY LITTLE MICE TO SAY ANYTHING!!!!"
        c "GOOD DAY!"

        hide cat

        a "Wha..."

        e "Phew, I was scared she was gonna follow us the whole way"

        a "She didn't seem so bad"
        #play MistAmbience "sfx/MistAmbience.ogg"

        e "Are you kidding? She's a crazy kitty!"

        scene bgwhite
        play sound "sfx/Chime.ogg"
        with Dissolve(3.0)

        n "After their encounter with the weird cat, the mice scurry out of the flower field and into the nearby meadow"
        scene bgforest2
        with Dissolve(3.0)

        show ei at right
        e "I think this is the right way..."
        show al at left
        a "Then where did the path go?"

        e "How am I supposed to know?"


        a "Did you hear that?!?!"

        show ei at centerleft:
            xzoom -1

        show cat at right
        play PhrygianButterflies "music/PhrygianButterflies.ogg"
        c "Hey there..."
        c "I apologize"
        c "I didn't mean to storm off like that"

        e "Ha ha, no problem..."

        a "So... Why are you traveling to Castle Alysen?"

        e "Alice!!!"

        c "If you must know, I have been summoned by the queen"
        c "I suspect that my poor reputation amongst the locals of Eastern Nidus has come back to haunt me"
        c "Though I know not what what she has summoned me for"

        a "Ahhhhhh"

        c "So then..."
        c "Why are YOU traveling to the Castle?"

        a "We are delivering a feather!!!"

        e "Alice no!"

        a "A feather that belonged to the queen herself!!!"

        e "Why you little..."

        c "A feather you say? One of the queens?"
        c "How on the face of Al Mot might you have aquired such a thing?"
        c "If it is authentic, that is..."

        e "Since Alice cannot keep a secret, I shall tell you"
        e "Seven moons ago, our town was attacked by three owls and a band of mice from the northern principalities"
        e "Eventually word spread to greater nearby settlements, and so"
        e "Messengers from the keep in Musia sent for aid from the Ravens"
        e "Four moons ago, the request was answered"
        e "And a small group of mice accompanied by two ravens a fox, and three squirrels set out to the northern principalities"
        e "Anyways, long story short, we drove those barbaric rats out of their home"

        a "They arent actual rats you know"

        e "Obviously, but you wont catch me speaking kindly of them"

        a "And you forgot the most important part"

        e "Yah yah, I am getting there"
        e "So, essentially, my brother is trained in archery, and..."

        a "Speed it up already"

        e "You tell it then!"

        a "My cousin found this feather in one of the highest towers of a castle far to the north"

        c "How do you know it belongs to the queen?"

        e "It said so itself above the display on the wall"

        a "Supposedly, it was in a room filled with treasures!"

        c "That is very nice and all, but what are the two of you doing out here all alone?"

        c "Do you expect every bird in Avia to respect your alliance with Castle Alysen?"

        e "What do you mean?"

        c "I mean, the two of you probably look like walking dinner to most creatures"

        a "I could go for some dinner..."
        e "Anyways..."
        e "To answer your question, upon returning to the village, the feather was taken from my brother by the needle guild"
        e "So... Yesterday, after sundown"
        e "We stole the feather from the guild hall before vanishing into the night"

        e "Can you imagine the look on their stupid faces, when they woke up, and not only is the feather missing"

        e "But so are we!"

        a "Hahahaha"

        c "Are the two of you mad?"
        c "I assume you are attempting to return the Queens feather?"

        a "Yes, we intend to deliver the feather to its rightful owner"

        c "Absolute madness!"

        mg "..."


        c "I will follow the two of you"
        c "To keep you safe, that is"

        a "Alright!"

        e "Ha ha... Okay..."

        c "Great! Follow me, I know a shortcut! :3"

        hide cat

        a "Sounds good!"

        hide al
        stop PhrygianButterflies fadeout 2.0


        e "Oh dear!"
        hide ei

        #hide al
        #hide ei



        #pause 10
        scene bgwhite
        play sound "sfx/Chime.ogg"
        with Dissolve(2.0)
        n "And so the mice girls follow the noble cat further towards their destination"

        scene bgwheatfield1
        play WheatFields "music/WheatFields.ogg"
        show cat at right
        with Dissolve(1.3)
        c "Nya"
        show al at left
        a "Look, your right, the castle is just up ahead!"
        show ei at centerleft:
            xzoom -1
        e "Wait up"

        c "I told you I knew a shortcut!"
        c "Most people take the long way around"

        e "Yah because these are royal wheatfields!"
        a "Who cares?"
        e "Are you trying to get us killed?"
        e "Its trespassing on royal land!"

        c "Calm down, I have done this a million times"

        e "That doesnt make me calm!"

        c "How can the rolling fields of wheat not calm your spirit?"
        c "You little mice truly are mad!"

        a "I like the wheat!"

        e "Shut up!"

        c "Sounds like someone needs a nap!"

        e "Why? because I'm not insane like you?"

        c "Yah, your so sane, that you decided to steal from your town and then run off alone to the country of birds"
        c "The power of friendship wont protect the two of you from becoming dinner"
        c "And that, is why I feel obligated to accompany you!"

        e "Hey, we have a good reason!"

        c "And what might that be?"

        e "My brother found the feather, not the town guild, its a matter of family pride!"

        c "Pride has touched the chosen meouse"
        c "Flies she towards the Castle"
        c "But her ambition burns far too bright, and silly myice dont have any wings to myelt"

        mg "What?"

        c "Nyanyanya"
        c "Nyevermind"
        c "Sing me a song little minstrels!"

        c "Very Nyice!"
        c "Now tell me little minstrels, what are your names?"

        a "My name is Alice"
        e "And my name is Eily"
        e "What is your name?"

        l "My name is Leona!"

        scene bgwhite
        with Dissolve(3.0)

        n "And so, the odd trio walked through the wheatfields and towards the castle walls"
        n "Upon approaching the castle walls"




    # birds!!!























    return
