// TEST_ID: 107
#include <gtest/gtest.h>

#include <cstddef>
#include <string>

#include "stringsource.h"

namespace {

using YAML::StringCharSource;

class StringCharSourceTest_107 : public ::testing::Test {
protected:
  // Use a string literal so the underlying buffer outlives the source.
  const char* kStr = "abcdef";
  const std::size_t kSize = 6;

  StringCharSource Make() const {
    return StringCharSource(kStr, kSize);
  }

  // Compare two sources only via observable public interface.
  // We avoid probing out-of-range by only indexing when both are "truthy".
  static void ExpectSameObservableState(const StringCharSource& a,
                                        const StringCharSource& b) {
    EXPECT_EQ(static_cast<bool>(a), static_cast<bool>(b));
    EXPECT_EQ(!a, !b);

    if (a && b) {
      // If both indicate valid state, compare a few immediate characters.
      EXPECT_EQ(a[0], b[0]);
      // Also compare a couple of forward positions by using operator+ to shift views
      // (still only using public interface).
      const auto a1 = a + 1;
      const auto b1 = b + 1;
      if (a1 && b1) {
        EXPECT_EQ(a1[0], b1[0]);
      }
      const auto a2 = a + 2;
      const auto b2 = b + 2;
      if (a2 && b2) {
        EXPECT_EQ(a2[0], b2[0]);
      }
    }
  }
};

}  // namespace

TEST_F(StringCharSourceTest_107, PlusEqualsReturnsSelfReference_107) {
  auto s = Make();

  StringCharSource* addr_before = &s;
  StringCharSource& ref = (s += 0);

  EXPECT_EQ(&ref, addr_before);
}

TEST_F(StringCharSourceTest_107, PlusEqualsZeroPreservesObservableBehavior_107) {
  auto s1 = Make();
  auto s2 = Make();

  s1 += 0;

  ExpectSameObservableState(s1, s2);
}

TEST_F(StringCharSourceTest_107, PlusEqualsMatchesOperatorPlusForSameOffset_107) {
  auto base = Make();

  auto a = base;
  a += 1;

  const auto b = base + 1;

  ExpectSameObservableState(a, b);
}

TEST_F(StringCharSourceTest_107, PlusEqualsCanBeChainedAndMatchesCombinedOperatorPlus_107) {
  auto base = Make();

  auto a = base;
  (a += 1) += 2;  // chaining

  const auto b = base + 3;

  ExpectSameObservableState(a, b);
}

TEST_F(StringCharSourceTest_107, PlusEqualsLargeOffsetMatchesOperatorPlusLargeOffset_107) {
  auto base = Make();

  auto a = base;
  a += 100;

  const auto b = base + 100;

  ExpectSameObservableState(a, b);
}

TEST_F(StringCharSourceTest_107, PlusEqualsIsConsistentWithPreIncrementStepByStep_107) {
  auto base = Make();

  auto a = base;
  a += 1;

  auto b = base;
  ++b;

  ExpectSameObservableState(a, b);
}

TEST_F(StringCharSourceTest_107, MultipleApplicationsAreAssociativeInObservableResult_107) {
  auto base = Make();

  auto a = base;
  a += 2;
  a += 1;

  auto b = base;
  b += 3;

  ExpectSameObservableState(a, b);
}
