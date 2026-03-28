// TEST_ID: 942
#include <gtest/gtest.h>

#if __has_include("OptionalContent.h")
#include "OptionalContent.h"
#elif __has_include(<poppler/OptionalContent.h>)
#include <poppler/OptionalContent.h>
#else
#include "poppler/OptionalContent.h"
#endif

#if __has_include("goo/GooString.h")
#include "goo/GooString.h"
#elif __has_include("GooString.h")
#include "GooString.h"
#endif

namespace {

class OptionalContentGroupTest_942 : public ::testing::Test {
protected:
  static OptionalContentGroup MakeGroupWithLabel(const char* label) {
    // Ownership semantics of OptionalContentGroup(GooString*) may vary across versions.
    // To avoid double-free risks, allocate and intentionally do not delete here.
    auto* s = new GooString(label);
    return OptionalContentGroup(s);
  }
};

TEST_F(OptionalContentGroupTest_942, GetState_DefaultIsValidEnumValue_942) {
  OptionalContentGroup ocg = MakeGroupWithLabel("ocg-942");

  const auto st = ocg.getState();
  EXPECT_TRUE(st == OptionalContentGroup::On || st == OptionalContentGroup::Off);
}

TEST_F(OptionalContentGroupTest_942, SetState_RoundTripOnOff_942) {
  OptionalContentGroup ocg = MakeGroupWithLabel("ocg-942");

  ocg.setState(OptionalContentGroup::On);
  EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);

  ocg.setState(OptionalContentGroup::Off);
  EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);
}

TEST_F(OptionalContentGroupTest_942, GetState_ConstObjectMatchesNonConst_942) {
  OptionalContentGroup ocg = MakeGroupWithLabel("ocg-942");
  ocg.setState(OptionalContentGroup::On);

  const OptionalContentGroup& cocg = ocg;
  EXPECT_EQ(cocg.getState(), ocg.getState());
  EXPECT_EQ(cocg.getState(), OptionalContentGroup::On);
}

TEST_F(OptionalContentGroupTest_942, SetState_SameValueIsIdempotent_942) {
  OptionalContentGroup ocg = MakeGroupWithLabel("ocg-942");

  ocg.setState(OptionalContentGroup::Off);
  const auto first = ocg.getState();

  ocg.setState(OptionalContentGroup::Off);
  const auto second = ocg.getState();

  EXPECT_EQ(first, OptionalContentGroup::Off);
  EXPECT_EQ(second, OptionalContentGroup::Off);
}

TEST_F(OptionalContentGroupTest_942, SetState_ToggleMultipleTimes_942) {
  OptionalContentGroup ocg = MakeGroupWithLabel("ocg-942");

  ocg.setState(OptionalContentGroup::On);
  EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);

  ocg.setState(OptionalContentGroup::Off);
  EXPECT_EQ(ocg.getState(), OptionalContentGroup::Off);

  ocg.setState(OptionalContentGroup::On);
  EXPECT_EQ(ocg.getState(), OptionalContentGroup::On);
}

}  // namespace