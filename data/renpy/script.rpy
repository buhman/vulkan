# The script of the game goes in this file.

# Declare characters used by this game. The color argument colorizes the
# name of the character.
image bgblue = "#000000"
image bgwhite = "#ffffff"
image bgforest1 = "bg/forest1.png"
image bgforest2 = "bg/forest2.png"
image bgflower1 = "bg/flowerfield1.png"
image bgwheatfield1 = "bg/wheatfield1.png"
image bgcastle1 = "bg/castle1.png"
image bgcastle2 = "bg/castle2.png"
image bgcastle3 = "bg/castle3.png"
image bgcastle4 = "bg/castle4.png"

image bgend = "end.png"


image bi = "ch/ibird/Bird.png"
image cat = "ch/icat/Cat.png"
image catw = "ch/icat/Catw.png"
image ei = "ch/ieily/Eily.png"
image al = "ch/ialice/Alice.png"
image sei = "ch/ieily/Seily.png"
image sal = "ch/ialice/Salice.png"
image wal = "ch/ialice/Walice.png"

define a = Character("Alice",color="409b5d")
define b = Character("Queen Alary",color="0b1845")
define c = Character("Cat",color="590093")
define e = Character("Eily",color="0b6092")
define mg = Character("Mouse Girls",color="000000")
define n = Character("Narrator",color="000000")
define l = Character("Leona",color="590093")
define h = Character("Herald",color="860000")

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
        renpy.music.register_channel("MistAmbience", "music", loop=True)
        renpy.music.register_channel("PhrygianButterflies", "music", loop=True)
        renpy.music.register_channel("WheatFields", "music", loop=True)
        renpy.music.register_channel("Preludium", "music", loop=True)



# The game starts here.

label start:


    play MistAmbience "music/MistAmbience.ogg"
    scene bgblue
    pause 1.0
    play sound "sfx/Chime.ogg"
    scene bgwhite
    with Dissolve(3.0)
    #play music "IntroMusicTest.ogg"

    #play NarratorLoop "n1test.mp3"
    voice "nara/n1.ogg"
    n "Far over the mountains of Almystice"
    voice "nara/n2.ogg"
    n "Beyond the tumultuous waters of the Lilac Bay"
    voice "nara/n3.ogg"
    n "And across the vast fields of Alysen"
    #voice "n4test.mp3"
    stop MistAmbience fadeout 4.2
    play TinyForestMinstrels "music/TinyForestMinstrels.ogg"
    voice "nara/n4.ogg"
    n "Tiny minstrels can be heard amongst the trees"



    scene bgforest1
    play sound "sfx/Chime.ogg"
    with Dissolve(3.0)

    show al at left
    voice "alice/a1.ogg"
    a "Are we almost there?"

    show ei at right

    voice "eily/e1.ogg"
    e "Hmmm... Not really"


    voice "alice/a2.ogg"
    a "How much further have we to go?"

    voice "eily/e2.ogg"
    e "About two more moons"

    menu:
        "Complain" :

            voice "alice/a3.ogg"
            a "We are still sooo far awayyy"

            voice "eily/e3.ogg"
            e "And it will be even further if you dont stop complaining"

            voice "alice/a4.ogg"
            a "Easy for you to say, all you have to carry is a little memory pipe!"
            voice "alice/a5.ogg"
            a "I'm tired ><"

            voice "eily/e4.ogg"
            e "Don't start whining now!"

            voice "eily/e5.ogg"
            e "You need to remember why we have come all this way"

            voice "alice/a6.ogg"
            a "I understand... I suppose it is for an important purpose"

        "Rationalize" :

            voice "alice/a6.ogg"
            a "I understand... I suppose it is for an important purpose"
    jump mainbranch1


    label mainbranch1:
        voice "eily/e6.ogg"
        e "We're almost out of the forest, we can take a little break once we clear the tree line"

        voice "alice/a7.ogg"
        a "Is that where the flora field is?"

        voice "eily/e7.ogg"
        e "Why yes, If I remember correctly, it should be just up ahead"
        stop TinyForestMinstrels fadeout 5.5

        scene bgwhite
        play sound "sfx/Chime.ogg"
        with Dissolve(1.0)


        voice "nara/n5.ogg"
        n "As the minstrel mice girls continue along the path, the forest opens up into a beautiful field of flowers"

        play PhrygianButterflies "music/PhrygianButterflies.ogg"


        scene bgflower1
        with Dissolve(1.0)

        show ei at right

        voice "eily/e8.ogg"
        e "Look at all the butterflies! They are all so pretty!"

        show al at left


        voice "alice/a8.ogg"
        a "This place is like a dream..."

        voice "eily/e9.ogg"
        e "There are so many flowers this time of year"
        voice "eily/e10.ogg"
        e "I told you it would be worth the journey!"

        voice "alice/a9.ogg"
        a "Can we stop for a bit?"

        voice "eily/e11.ogg"
        e "Of course"
        voice "eily/e12.ogg"
        e "Ya know, Its a shame we didnt save some of those giant strawberries you found"

        voice "alice/a10.ogg"
        a "I told you not to eat them all!"

        voice "eily/e13.ogg"
        e "Yah yah"
        voice "eily/e14.ogg"
        e "Anyways, shall I recite a tale?"

        menu:


            "Good idea" :
                stop PhrygianButterflies fadeout 4.2
                voice "alice/a11.ogg"
                a "Why dont you sing the story of Eleanor the Hero!"
                voice "eily/e15.ogg"
                e "Sure"
                #voice "mousegirls/mg2.ogg"
                e "..."
                play music "poem/EleanorTheHero.ogg" noloop
                pause 38.8875
            "I am too tired" :
                voice "eily/e16.ogg"
                e "Serves you right for scaring those elephant-dogs"
                stop PhrygianButterflies fadeout 4.2
                voice "alice/a12.ogg"
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
        #voice "placeholdermeow.mp3"
        #voice "leona/c1.ogg"
        c "Rawrrrr"
        play music "leona/c1.ogg" noloop
        pause 0.7
        hide catw
        show cat at right
        play ScaredMice "music/ScaredMice.ogg"


        hide ei
        hide al
        show sei at centerleft:
            xzoom -1

        show sal at left

        #voice "alice/a13.ogg"
        voice "mousegirls/mg1.ogg"
        mg "AHHHHHHHHHH!!!!!"


        voice "leona/c2.ogg"
        c "Nyanyanyanya"
        voice "leona/c3.ogg"
        c "Well, what do we have here? If it isn't two little meowse girls, all alone amongst the flowers"

        menu:
            "Beg for mercy" :
                voice "alice/a14.ogg"
                a "Please don't eat us!!!"

            "Run" :
                voice "eily/e18.ogg"
                e "Alice don't run, our only chance is through pleading!"
                voice "eily/e19.ogg"
                e "Please don't eat us, miss kitty cat!!! ><"



        jump mainbranch3





    label mainbranch3:
        stop ScaredMice fadeout 2.0

        voice "leona/c4.ogg"
        c "I'm not gonna eat you nyanyanya"
        hide sal
        show al at left
        play TinyForestMinstrels "music/TinyForestMinstrels.ogg"
        voice "leona/c5.ogg"
        c "I just want to know what two little meowses are doing so very far away from home"
        hide sei
        show ei at centerleft:
            xzoom -1
        voice "leona/c6.ogg"
        c "Also, are you minstrels?"

        voice "eily/e20.ogg"
        e "Y-Yes"
        voice "alice/a15.ogg"
        a "W-We are on a quest to Castle Alysen..."
        voice "eily/e21.ogg"
        e "Shh don't tell her that"

        voice "leona/c7.ogg"
        c "The Castle of Alysen you say?!?"
        voice "leona/c8.ogg"
        c "Why, that's where I am headed!"

        voice "eily/e22.ogg"
        e "You don't say..."

        voice "leona/c9.ogg"
        c "Yah, I do actually"

        voice "eily/e23.ogg"
        e "So... Why might you be traveling to the castle?"

        voice "leona/c10.ogg"
        c "I belong to the lineage of Agrepen"

        voice "eily/e24.ogg"
        e "And what might that mean?"

        voice "leona/c11.ogg"
        c "The Agrepens are a long line of felines loyal to the crown of corvidae"

        voice "eily/e25.ogg"
        e "Really? That must mean you are a noble?"

        voice "leona/c12.ogg"
        c "Well, not really..."
        voice "leona/c13.ogg"
        c "My father was one of the queens knights many years ago"

        voice "eily/e26.ogg"
        e "Ah I see"

        voice "eily/e27.ogg"
        e "So do you live at the castle or something?"

        voice "leona/c14.ogg"
        c "Well, no..."

        voice "alice/a16.ogg"
        a "Then why are you traveling to The Castle Alysen?"


        voice "leona/c15.ogg"
        c "uhhh"
        play MistAmbience "music/MistAmbience.ogg"
        stop TinyForestMinstrels fadeout 2.0
        voice "leona/c16.ogg"
        c "I DONT NEED TO BE PRESSURED BY LITTLE MICE TO SAY ANYTHING!!!!"
        voice "leona/c17.ogg"
        c "GOOD DAY!"

        hide cat

        voice "alice/a17.ogg"
        a "Wha..."

        voice "eily/e28.ogg"
        e "Phew, I was scared she was gonna follow us the whole way"

        voice "alice/a18.ogg"
        a "She didn't seem so bad"
        #play MistAmbience "sfx/MistAmbience.ogg"

        voice "eily/e29.ogg"
        e "Are you kidding? She's a crazy kitty!"

        scene bgwhite
        play sound "sfx/Chime.ogg"
        with Dissolve(3.0)




        voice "nara/n6.ogg"
        n "After their encounter with the weird cat, the mice scurry out of the flower field and into the nearby meadow"
        scene bgforest2
        with Dissolve(3.0)

        show ei at right
        voice "eily/e30.ogg"
        e "I think this is the right way..."
        show al at left
        voice "alice/a19.ogg"
        a "Then where did the path go?"

        voice "eily/e31.ogg"
        e "How am I supposed to know?"


        voice "alice/a20.ogg"
        a "Did you hear that?!?!"

        show ei at centerleft:
            xzoom -1

        show cat at right
        play PhrygianButterflies "music/PhrygianButterflies.ogg"
        voice "leona/c18.ogg"
        c "Hey there... I apologize, I didn't mean to storm off like that"
        #voice "leona/c19.ogg"
        #c "I apologize"
        #voice "leona/c20.ogg"
        #c "I didn't mean to storm off like that"

        voice "eily/e32.ogg"
        e "Ha ha, no problem..."

        voice "alice/a21.ogg"
        a "So... Why are you traveling to Castle Alysen?"


        voice "eily/e33.ogg"
        e "Alice!!!"

        voice "leona/c19.ogg"
        c "If you must know, I have been summoned by the queen"
        voice "leona/c20.ogg"
        c "I suspect that my poor reputation amongst the locals of Eastern Nidus has come back to haunt me"
        voice "leona/c21.ogg"
        c "Though I know not what what she has summoned me for"

        voice "alice/a22.ogg"
        a "Ahhhhhh"

        voice "leona/c22.ogg"
        c "So then..."
        voice "leona/c23.ogg"
        c "Why are YOU traveling to the Castle?"

        voice "alice/a23.ogg"
        a "We are delivering a feather!!!"

        voice "eily/e34.ogg"
        e "Alice no!"

        voice "alice/a24.ogg"
        a "A feather that belonged to the queen herself!!!"

        voice "eily/e35.ogg"
        e "Why you little..."

        voice "leona/c24.ogg"
        c "A feather you say? One of the queens?"
        voice "leona/c25.ogg"
        c "How on the face of Al Mot might you have aquired such a thing?"
        voice "leona/c26.ogg"
        c "If it is authentic"

        voice "eily/e36.ogg"
        e "Since Alice cannot keep a secret, I shall tell you"
        voice "eily/e37.ogg"
        e "Seven moons ago, our town was attacked by three owls and a band of mice from the northern principalities"
        voice "eily/e38.ogg"
        e "Eventually word spread to greater nearby settlements, and so"
        voice "eily/e39.ogg"
        e "Messengers from the keep in Musia sent for aid from the Ravens"
        voice "eily/e40.ogg"
        e "Four moons ago, the request was answered"
        voice "eily/e41.ogg"
        e "And a small group of mice accompanied by two ravens a fox, and three squirrels set out to the northern principalities"
        voice "eily/e42.ogg"
        e "Anyways, long story short, we drove those barbaric rats out of their home"

        voice "alice/a25.ogg"
        a "They arent actual rats you know"

        voice "eily/e43.ogg"
        e "Obviously, but you wont catch me speaking kindly of them"

        voice "alice/a26.ogg"
        a "And you forgot the most important part"

        voice "eily/e44.ogg"
        e "Yah yah, I am getting there"
        voice "eily/e45.ogg"
        e "So, essentially, my brother is trained in archery, and..."

        voice "alice/a27.ogg"
        a "Speed it up already"

        voice "eily/e46.ogg"
        e "You tell it then!"

        voice "alice/a28.ogg"
        a "My cousin found this feather in one of the highest towers of a castle far to the north"

        voice "leona/c27.ogg"
        c "How do you know it belongs to the queen?"

        voice "eily/e47.ogg"
        e "It said so itself above the display on the wall"

        voice "alice/a29.ogg"
        a "Supposedly, it was in a room filled with treasures!"

        voice "leona/c28.ogg"
        c "That is very nice and all, but what are the two of you doing out here all alone?"

        voice "leona/c29.ogg"
        c "Do you expect every bird in Avia to respect your alliance with Castle Alysen?"

        voice "eily/e48.ogg"
        e "What do you mean?"

        voice "leona/c30.ogg"
        c "I mean, the two of you probably look like walking dinner to most creatures"



        menu:
            "Sarcasm" :
                voice "alice/a30.ogg"
                a "I could go for some dinner..."

            "Nod" :
                jump mainbranch4
        jump mainbranch4

    label mainbranch4:
        voice "eily/e49.ogg"
        e "Anyways..."
        voice "eily/e50.ogg"
        e "To answer your question, upon returning to the village, the feather was taken from my brother by the needle guild"
        voice "eily/e51.ogg"
        e "So... Yesterday, after sundown"
        voice "eily/e52.ogg"
        e "We stole the feather from the guild hall before vanishing into the night"

        voice "eily/e53.ogg"
        e "Can you imagine the look on their stupid faces, when they woke up, and not only is the feather missing"

        voice "eily/e54.ogg"
        e "But so are we!"

        voice "alice/a31.ogg"
        a "Hahahaha"

        voice "leona/c31.ogg"
        c "Are the two of you mad?"
        voice "leona/c32.ogg"
        c "I assume you are attempting to return the Queens feather?"

        voice "alice/a32.ogg"
        a "Yes, we intend to deliver the feather to its rightful owner"

        voice "leona/c33.ogg"
        c "Absolute madness!"


        voice "mousegirls/mg2.ogg"
        mg "..."
        #pause 1.0


        voice "leona/c34.ogg"
        c "I will follow the two of you"
        voice "leona/c35.ogg"
        c "To keep you safe, that is"

        menu:
            "Agree" :
                voice "alice/a33.ogg"
                a "Alright!"
            "Stay Silent" :
                jump mainbranch4



                #voice "alice/a33.ogg"
                #a "Alright!"

        jump mainbranch5

    label mainbranch5:
        voice "eily/e55.ogg"
        e "Ha ha... Okay..."

        voice "leona/c36.ogg"
        c "Great! Follow me, I know a shortcut! :3"

        hide cat

        voice "alice/a34.ogg"
        a "Sounds good!"

        hide al
        stop PhrygianButterflies fadeout 2.0


        voice "eily/e56.ogg"
        e "Oh dear!"
        hide ei

        #hide al
        #hide ei



        #pause 10
        scene bgwhite
        play sound "sfx/Chime.ogg"
        with Dissolve(2.0)
        voice "nara/n7.ogg"
        n "And so the mice girls follow the noble cat further towards their destination"

        scene bgwheatfield1
        play WheatFields "music/WheatFields.ogg"
        show cat at right
        with Dissolve(1.3)
        voice "leona/c37.ogg"
        c "Nya"
        show wal at left
        voice "alice/a35.ogg"
        a "Look, your right, the castle is just up ahead!"
        show ei at centerleft:
            xzoom -1
        voice "eily/e57.ogg"
        e "Wait up"

        voice "leona/c38.ogg"
        c "I told you I knew a shortcut!"
        voice "leona/c39.ogg"
        c "Most people take the long way around"

        voice "eily/e58.ogg"
        e "Yah because those are royal wheatfields!"
        voice "alice/a36.ogg"
        a "Who cares?"
        voice "eily/e59.ogg"
        e "Are you trying to get us killed?"
        voice "eily/e60.ogg"
        e "Its trespassing on royal land!"

        voice "leona/c40.ogg"
        c "Calm down, I have done this like a million times"

        voice "eily/e61.ogg"
        e "That doesnt make me calm!"

        voice "leona/c41.ogg"
        c "How can the rolling fields of wheat not calm your spirit?"
        voice "leona/c42.ogg"
        c "You little mice truly are mad!"

        voice "alice/a37.ogg"
        a "I like the wheat!"

        voice "eily/e62.ogg"
        e "Shut up!"

        voice "leona/c43.ogg"
        c "Sounds like someone needs a nap!"

        voice "eily/e63.ogg"
        e "Why? because I'm not insane like you?"

        voice "leona/c44.ogg"
        c "Yah, your so sane, that you decided to steal from your town and then run off alone to the country of birds"
        voice "leona/c45.ogg"
        c "The power of friendship wont protect the two of you from becoming dinner"
        voice "leona/c46.ogg"
        c "And that, is why I feel obligated to accompany you!"

        voice "eily/e64.ogg"
        e "Hey, we have a good reason!"

        voice "leona/c47.ogg"
        c "And what might that be?"

        voice "eily/e65.ogg"
        e "My brother found the feather, not the town guild, its a matter of family pride!"

        voice "leona/c48.ogg"
        c "Pride has touched the chosen meouse"
        voice "leona/c49.ogg"
        c "Flies she towards the Castle"
        voice "leona/c50.ogg"
        c "But her ambition burns far too bright, and silly mice dont have any wings to melt"

        #voice "eily/e66.ogg"
        #voice "alice/a38.ogg"
        voice "mousegirls/mg3.ogg"
        mg "What?"

        voice "leona/c51.ogg"
        c "Nyanyanya"
        voice "leona/c52.ogg"
        c "Nyevermind"

        stop WheatFields fadeout 3.0

        voice "leona/c53.ogg"
        c "Sing me a song little minstrels!"

        #menu:
        #    Estevie Kiri Stella
        #    The Hero of Eleanor (again)
        #stop WheatFields fadeout 3.0

        #voice "mousegirls/mg2.ogg"
        e "..."
        play music "poem/KiriStella.ogg" noloop
        pause 67



        voice "leona/c54.ogg"
        c "Very Nyice!"
        voice "leona/c55.ogg"
        c "Now tell me little minstrels, what are your names?"

        voice "alice/a39.ogg"
        a "My name is Alice"
        voice "eily/e67.ogg"
        e "And my name is Eily"
        voice "eily/e68.ogg"
        e "What is your name?"

        #stop WheatFields fadeout 2.0

        voice "leona/c56.ogg"
        l "My name is Leona!"

        scene bgwhite
        with Dissolve(3.0)

        voice "nara/n8.ogg"
        n "And so, the odd trio walked through the wheatfields and towards the castle"
        voice "nara/n9.ogg"
        n "Upon approaching the gates, the three were escorted to a large room"
        voice "nara/n10.ogg"
        n "They were then instructed to wait for an audience with the Queen"
        #play Preludium "music/Preludium.ogg"
        voice "hera/h1.ogg"
        h "You may now present yourselves before her Majesty, Queen Alary of Alysen"


        scene bgcastle1
        play Preludium "music/Preludium.ogg"
        #show bi at right
        with Dissolve(2.0)
        show bi at right
        pause 1.0
        voice "hera/h2.ogg"
        h "Leona Agrepen of Elmindeer"

        #pause 1.0

        show cat at center:
            xzoom -1
        voice "leona/c57.ogg"
        l "Hail, your Majesty"

        voice "hera/h3.ogg"
        h "Eily VeraWheat of the Western Principalities"

        show ei at centerleft
        voice "eily/e69.ogg"
        e "Hail, your Majesty"
        voice "hera/h4.ogg"
        h "Alice SeraWheat of the Western Principalities"
        play sound "sfx/Glass.ogg"
        #e "Heyy watch it!"
        #glass breaks lol
        pause 1.0
        voice "alice/a40.ogg"
        a "I'm alright!"

        show wal at left
        voice "alice/a41.ogg"
        a "H-Hail, your majesty"





        voice "leona/c58.ogg"
        l "Nyanyanya"



        voice "bird/b1.ogg"
        b "And what is this?"
        voice "bird/b2.ogg"
        b "A cat and two mice in my court?"
        voice "bird/b3.ogg"
        b "Is this some kind of joke?"

        voice "leona/c59.ogg"
        l "Not a joke Your Majesty, these are my friends"

        voice "eily/e70.ogg"
        e "Friends?"

        #b "And why have you brought your little friends before my royal court?"

        voice "bird/b4.ogg"
        b "Miss Agrepen, your reputation is far from acceptable"

        voice "bird/b5.ogg"
        b "And I can imagine, you already know why I have summoned you here today"

        voice "leona/c60.ogg"
        l "Uhhmmmm...."
        voice "leona/c61.ogg"
        l "Does it have anything to do with Eastern Nidus?"

        voice "bird/b6.ogg"
        b "I think you already know the answer to that"

        voice "bird/b7.ogg"
        b "Your father would be rather dissapointed if he were still alive"

        voice "leona/c0.ogg"
        l "..."

        voice "bird/b8.ogg"
        b "Leona Agrepen, the court has found you guilty of two cases of larceny and seven cases of petty pilfering"
        voice "bird/b9.ogg"
        b "Miss Agrepen, you are hereby banned from stepping foot in Eastern Nidus"
        voice "bird/b10.ogg"
        b "From here on out, you shall be restricted to the central principalities of Avia"

        voice "leona/c62.ogg"
        l "Owww c'mon! There is nothing to do around here!"

        voice "bird/b11.ogg"
        b "Silence!"
        voice "bird/b12.ogg"
        b "It is here, in the Central city of Alysen that you shall remain, where I can keep a watchful eye on you"
        voice "bird/b13.ogg"
        b "Or would you prefer that I permit the request of the lesser courts to have you declawed?"

        voice "leona/c63.ogg"
        l "No ><"

        voice "bird/b14.ogg"
        b "Take my leniency as a display of gratitude for the services rendered by your father"

        voice "leona/c64.ogg"
        l "Yes Your Majesty... Forgive me for speaking out of turn"

        voice "bird/b15.ogg"
        b "Now, why have you brought these little mice before me?"

        voice "leona/c65.ogg"
        l "Alary, Your Majesty, these are minstrels I met on the road to Alysen"
        voice "leona/c66.ogg"
        l "They lay claim to a feather, said to be one of Your Majesty's own"

        voice "bird/b16.ogg"
        b "Really?"
        voice "bird/b17.ogg"
        b "And what else might the two of you claim? Alice and Eily of the West"

        voice "alice/a42.ogg"
        a "I u-uhh..."

        voice "eily/e71.ogg"
        e "Your Majesty, this feather was found by my brother in a castle to the north"
        voice "eily/e72.ogg"
        e "So very far my cousin and I have journeyed"
        voice "eily/e73.ogg"
        e "Over the mountains of Almystice"
        voice "eily/e74.ogg"
        e "Beyond the deep blue waters of the Lilac bay"
        voice "eily/e75.ogg"
        e "And across the vast fields of Alysen"
        voice "eily/e76.ogg"
        e "All in hopes that we might return Your Majesty's feather"

        voice "bird/b18.ogg"
        b "What splendid and courageous little mice the two of you are"

        voice "leona/c67.ogg"
        l "Nyanyanyanyanya"

        voice "alice/a43.ogg"
        a "We also wanted to show our profound gratitude for the aid provided by Your Majesty just four moons ago"
        voice "eily/e77.ogg"
        e "Please allow us to perform a song for Your Majesty and Your Majesty's court"

        stop Preludium fadeout 4.2

        voice "bird/b19.ogg"
        b "I appreciate your loyalty to the crown of Corvidae little mice"
        stop MistAmbience fadeout 4.2
        voice "bird/b20.ogg"
        b "You are most welcome to proceed with your little song"

        play music "poem/BirdSong.ogg" noloop
        scene bgcastle1
        e "..."

        pause 73.5


        #scene bgcastle2

        #with Dissolve(7.0)

        #scene bgcastle3
        #with Dissolve(7.0)

        #scene bgcastle4
        #with Dissolve(7.0)

        #scene bgcastle3
        #with Dissolve(7.0)

        #scene bgcastle2
        #with Dissolve(7.0)
        #scene bgcastle3
        #with Dissolve(7.0)
        #scene bgcastle2
        #with Dissolve(7.0)
        #scene bgcastle1
        #with Dissolve(10.0)


        #pause 3
        scene bgwhite
        with Dissolve(14.0)
        #pause 0.25
        #scene bgwhite
        #with Dissolve(3.0)

        voice "nara/n11.ogg"
        n "In the end, Leona managed to stay out of the dungeon"
        voice "nara/n12.ogg"
        n "Eily and Alice both stayed in service of the queen for 7 harvests"
        voice "nara/n13.ogg"
        n "before returning to their small nameless town, near the Keep of Musia"


        scene bgwhite
        show bgend at center
    label end:
        pause 1.0
        jump end



        #n "The End"










    # birds!!!























    return
