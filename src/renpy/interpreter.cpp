#include <assert.h>
#include <stdio.h>

#include "renpy/script.h"
#include "renpy/interpreter.h"

#include "audio.h"

namespace renpy {
  void interpreter::reset()
  {
    pc = 0;
    backgroundIndex = ~0u;
    backgroundColor = 0;
    shownImagesCount = 0;
    say.stringIndex = ~0u;
    say.characterIndex = ~0u;
    menu.count = 0;
    dissolveIndex = 0;
    voiceAudioIndex = ~0u;
    pause.voice = false;
    pause.menu = false;
    pause.dissolve = false;
    pause.pause = false;
  }

  uint32_t interpreter::findImage(uint32_t imageIndex)
  {
    for (uint32_t i = 0; i < shownImagesCount; i++) {
      if (shownImages[i].imageIndex == imageIndex) {
        return i;
      }
    }
    return ~0u;
  }

  void interpreter::showImage(uint32_t imageIndex, uint32_t transformIndex)
  {
    uint32_t shownImageIndex = findImage(imageIndex);
    if (shownImageIndex == ~0u) {
      shownImageIndex = shownImagesCount;
      shownImagesCount += 1;
    }

    shownImages[shownImageIndex].imageIndex = imageIndex;
    shownImages[shownImageIndex].transformIndex = transformIndex;
    shownImages[shownImageIndex].highlighted = false;

    assert(shownImagesCount <= maximumShownImagesCount);
    fprintf(stderr, "shownImagesCount: %d\n", shownImagesCount);
  }

  static inline uint32_t countMask(uint32_t count)
  {
    assert(count <= 32);
    uint32_t mask = 0;
    for (uint32_t i = 0; i < count; i++) {
      mask |= (1u << i);
    }
    return mask;
  }

  void interpreter::highlightImages(uint32_t const * const imageIndices, uint32_t count)
  {
    assert(count <= 32);
    uint32_t foundMask = 0;
    for (uint32_t shownImageIndex = 0; shownImageIndex < shownImagesCount; shownImageIndex++) {
      shownImages[shownImageIndex].highlighted = false;
      for (uint32_t i = 0; i < count; i++) {
        bool highlight = shownImages[shownImageIndex].imageIndex == imageIndices[i];
        shownImages[shownImageIndex].highlighted |= highlight;
        foundMask |= (((uint32_t)highlight) << i);
      }
    }
    //uint32_t expectedMask = countMask(count);
    //if (foundMask != expectedMask) {
    //fprintf(stderr, "warning: highlightImages foundMask mismatch: pc %d found %08x expected %08x\n", pc, foundMask, expectedMask);
    //}
    if (count > 0 && foundMask == 0)
      fprintf(stderr, "warning: highlightImages zero images found: pc %d\n", pc);
  }

  void interpreter::hideImage(uint32_t imageIndex)
  {
    uint32_t shownImageIndex = findImage(imageIndex);
    if (shownImageIndex == ~0u) {
      fprintf(stderr, "warning: attempt to hide non-shown image index %d at pc %d\n", imageIndex, pc);
      return;
    }

    for (uint32_t i = shownImageIndex; i < (shownImagesCount - 1); i++) {
      shownImages[i] = shownImages[i+1];
    }
    shownImagesCount -= 1;
  }

  void interpreter::interpret_one()
  {
    uint32_t last_pc = pc;

    assert(pc < (uint32_t)script::statements_length);

    language::statement const& statement = script::statements[pc];

    switch (statement.type) {
    case language::type::play:
      fprintf(stderr, "interpret_one[%d]: play %d\n", pc, statement.play.audioIndex);
      audio::play(statement.play.audioIndex);
      pc += 1;
      break;
    case language::type::stop:
      audio::stop(statement.stop.audioIndex, statement.stop.fadeout);
      pc += 1;
      break;
    case language::type::scene_color:
      fprintf(stderr, "interpret_one[%d]: scene_color\n", pc);
      backgroundIndex = -1;
      backgroundColor = statement.scene_color.color;

      shownImagesCount = 0;
      say.stringIndex = -1;
      say.characterIndex = -1;
      pc += 1;
      break;
    case language::type::scene:
      fprintf(stderr, "interpret_one[%d]: scene\n", pc);
      assert(statement.scene.imageIndex < (uint32_t)script::images_length);
      backgroundIndex = statement.scene.imageIndex;

      shownImagesCount = 0;
      say.stringIndex = ~0u;
      say.characterIndex = ~0u;
      pc += 1;
      break;
    case language::type::say:
      {
        fprintf(stderr, "interpret_one[%d]: say\n", pc);
        assert(statement.say.stringIndex < (uint32_t)script::strings_length);
        say.stringIndex = statement.say.stringIndex;
        say.characterIndex = statement.say.characterIndex;
        language::character const & character = script::characters[statement.say.characterIndex];
        highlightImages(character.images, character.imagesLength);
        pc += 1;
      }
      break;
    case language::type::hide:
      fprintf(stderr, "interpret_one[%d]: hide\n", pc);
      assert(statement.show.imageIndex < (uint32_t)script::images_length);
      assert(statement.show.transformIndex < transformsCount);
      hideImage(statement.show.imageIndex);
      pc += 1;
      break;
    case language::type::show:
      fprintf(stderr, "interpret_one[%d]: show\n", pc);
      assert(statement.show.imageIndex < (uint32_t)script::images_length);
      assert(statement.show.transformIndex < transformsCount);
      showImage(statement.show.imageIndex, statement.show.transformIndex);
      pc += 1;
      break;
    case language::type::menu:
      fprintf(stderr, "interpret_one[%d]: menu\n", pc);
      assert(statement.menu.optionIndex < (uint32_t)script::options_length);
      assert(statement.menu.count > 0);
      menu.count = statement.menu.count;
      menu.optionIndex = statement.menu.optionIndex;
      pause.menu = true;
      pc += 1;
      break;
    case language::type::jump:
      fprintf(stderr, "interpret_one[%d]: jump %d\n", pc, statement.jump.statementIndex);
      assert(statement.jump.statementIndex < (uint32_t)script::statements_length);
      pc = statement.jump.statementIndex;
      break;
    case language::type::pause:
      fprintf(stderr, "interpret_one[%d]: pause %f\n", pc, statement.pause.duration);
      pauseDuration = statement.pause.duration;
      pause.pause = true;
      pc += 1;
      break;
    case language::type::voice:
      fprintf(stderr, "interpret_one[%d]: voice %d\n", pc, statement.voice.audioIndex);
      audio::play(statement.voice.audioIndex);
      voiceAudioIndex = statement.voice.audioIndex;
      pause.voice = true;
      pc += 1;
      printf("pause next_pc %d type %d\n", pc, script::statements[pc].type);
      assert(script::statements[pc].type == language::type::say);
      interpret_one();
      break;
    default:
      fprintf(stderr, "unknown statement type at pc %d\n", pc);
      assert(false);
      pc += 1;
      break;
    }

    assert(pc != last_pc);
  }

  void interpreter::interpret()
  {
    while (!interactionWait()) {
      if (dissolvePC()) {
        fprintf(stderr, "dissolvePC %d\n", pc);
        language::dissolve const & dissolve = script::dissolves[dissolveIndex];
        for (uint32_t i = 0; i < dissolve.count; i++) {
          interpret_one();
        }
        pause.dissolve = true;
        dissolveDuration = dissolve.duration;
        dissolveIndex += 1;
      } else {
        interpret_one();
      }
    }
  }
};
