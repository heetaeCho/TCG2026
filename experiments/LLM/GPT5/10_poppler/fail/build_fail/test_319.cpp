// LinkSound_getRepeat_test_319.cpp
// Unit tests for LinkSound::getRepeat()
// The TEST_ID is 319

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class LinkSoundTest_319 : public ::testing::Test {
protected:
  static Object MakeNullObject() {
    Object obj;
    obj.initNull();
    return obj;
  }
};

TEST_F(LinkSoundTest_319, ConstructWithNullObject_DoesNotThrow_319) {
  Object obj = MakeNullObject();
  EXPECT_NO_THROW({
    LinkSound sound(&obj);
    (void)sound.getRepeat(); // must be callable
  });
}

TEST_F(LinkSoundTest_319, GetRepeat_IsStableAcrossMultipleCalls_319) {
  Object obj = MakeNullObject();
  LinkSound sound(&obj);

  const bool first = sound.getRepeat();
  const bool second = sound.getRepeat();
  const bool third = sound.getRepeat();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(LinkSoundTest_319, GetRepeat_CanBeCalledOnConstInstance_319) {
  Object obj = MakeNullObject();
  LinkSound sound(&obj);

  const LinkSound& cref = sound;
  EXPECT_NO_THROW({ (void)cref.getRepeat(); });

  const bool v1 = cref.getRepeat();
  const bool v2 = cref.getRepeat();
  EXPECT_EQ(v1, v2);
}

TEST_F(LinkSoundTest_319, GetRepeat_DoesNotCrossAffectOtherInstances_319) {
  Object objA = MakeNullObject();
  Object objB = MakeNullObject();

  LinkSound a(&objA);
  LinkSound b(&objB);

  const bool a0 = a.getRepeat();
  (void)b.getRepeat(); // call on other instance
  const bool a1 = a.getRepeat();

  EXPECT_EQ(a0, a1);
}

} // namespace