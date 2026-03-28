// OptionalContentGroupTest_945.cpp
// Unit tests for OptionalContentGroup::getPrintState()
// The TEST_ID is 945

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "OptionalContent.h"

// Poppler headers commonly needed to construct Dict (constructor signature varies by version).
// If your build already includes Dict via OptionalContent.h, these are harmless.
// If not present in your Poppler snapshot, remove/adjust includes accordingly.
#include "Dict.h"
#include "XRef.h"

namespace {

class OptionalContentGroupTest_945 : public ::testing::Test {
 protected:
  // Create a minimally-constructed Dict. Many Poppler snapshots accept nullptr XRef.
  static Dict MakeMinimalDict() {
    return Dict(nullptr);
  }
};

TEST_F(OptionalContentGroupTest_945, GetPrintState_IsStableAcrossCalls_945) {
  Dict dict = MakeMinimalDict();
  OptionalContentGroup ocg(&dict);

  const auto first = ocg.getPrintState();
  const auto second = ocg.getPrintState();

  EXPECT_EQ(first, second);
}

TEST_F(OptionalContentGroupTest_945, GetPrintState_CanBeCalledOnConstObject_945) {
  Dict dict = MakeMinimalDict();
  const OptionalContentGroup ocg(&dict);

  EXPECT_NO_THROW({
    (void)ocg.getPrintState();
  });
}

TEST_F(OptionalContentGroupTest_945, GetPrintState_ReturnTypeIsUsageState_945) {
  Dict dict = MakeMinimalDict();
  OptionalContentGroup ocg(&dict);

  using RetT = decltype(ocg.getPrintState());
  static_assert(std::is_same_v<std::remove_cv_t<std::remove_reference_t<RetT>>, UsageState>,
                "OptionalContentGroup::getPrintState() must return UsageState");
  (void)ocg.getPrintState();
}

TEST_F(OptionalContentGroupTest_945, GetPrintState_DoesNotThrow_945) {
  Dict dict = MakeMinimalDict();
  OptionalContentGroup ocg(&dict);

  EXPECT_NO_THROW({
    (void)ocg.getPrintState();
  });
}

// Boundary-style check: repeated calls in a loop remain consistent and do not throw.
TEST_F(OptionalContentGroupTest_945, GetPrintState_RepeatedCallsRemainConsistent_945) {
  Dict dict = MakeMinimalDict();
  OptionalContentGroup ocg(&dict);

  const auto baseline = ocg.getPrintState();
  for (int i = 0; i < 100; ++i) {
    EXPECT_NO_THROW({
      const auto v = ocg.getPrintState();
      EXPECT_EQ(v, baseline);
    });
  }
}

}  // namespace