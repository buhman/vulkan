#include <assert.h>
#include <stdio.h>

#include "renpy/script.h"
#include "renpy/interpreter.h"

namespace renpy {
  void interpreter::reset()
  {
    pc = 0;
    backgroundIndex = -1;
    backgroundColor = 0;
    shownImagesCount = 0;
    say.stringIndex = -1;
    say.characterIndex = -1;
    menu.count = 0;
    interactionWait = false;
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

    assert(shownImagesCount <= maximumShownImagesCount);
    printf("shownImagesCount: %d\n", shownImagesCount);
  }

  void interpreter::hideImage(uint32_t imageIndex)
  {
    uint32_t shownImageIndex = findImage(imageIndex);
    if (shownImageIndex == ~0u)
      return;

    for (uint32_t i = shownImageIndex; i < (shownImagesCount - 1); i++) {
      shownImages[i] = shownImages[i+1];
      printf("here\n");
    }
    printf("return\n");
    shownImagesCount -= 1;
  }

  void interpreter::interpret_one()
  {
    assert(pc < (uint32_t)script::statements_length);

    language::statement const& statement = script::statements[pc];

    switch (statement.type) {
    case language::type::play:
      fprintf(stderr, "interpret_one[%d]: play\n", pc);
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
      say.stringIndex = -1;
      say.characterIndex = -1;
      pc += 1;
      break;
    case language::type::say:
      fprintf(stderr, "interpret_one[%d]: say\n", pc);
      assert(statement.say.stringIndex < (uint32_t)script::strings_length);
      say.stringIndex = statement.say.stringIndex;
      say.characterIndex = statement.say.characterIndex;
      interactionWait = true;
      pc += 1;
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
      pc += 1;
      break;
    case language::type::jump:
      fprintf(stderr, "interpret_one[%d]: jump %d\n", pc, statement.jump.statementIndex);
      assert(statement.jump.statementIndex < (uint32_t)script::statements_length);
      pc = statement.jump.statementIndex;
      break;
    default:
      fprintf(stderr, "unknown statement type at pc %d\n", pc);
      pc += 1;
      break;
    }
  }

  void interpreter::interpret()
  {
    while (!interactionWait) {
    //while (true) {
      uint32_t last_pc = pc;
      interpret_one();
      assert(pc != last_pc);

      //if (pc == 18) break;
    }
  }
};
