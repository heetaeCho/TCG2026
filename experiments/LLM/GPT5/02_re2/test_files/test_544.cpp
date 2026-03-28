// File: prefilter_info_concat_test.cc
#include "re2/prefilter.h"  // Path per your tree: ./TestProjects/re2/re2/prefilter.h
#include <gtest/gtest.h>

namespace re2 {

class PrefilterInfoConcatTest_544 : public ::testing::Test {
protected:
  // Helper to build a simple exact Info via public factories.
  // We avoid any assumption about how exactness is represented internally.
  static Prefilter::Info* MakeExactCharLatin1(char c) {
    return Prefilter::Info::LiteralLatin1(static_cast<Rune>(static_cast<unsigned char>(c)));
  }
};

// [Normal] If a == nullptr, Concat returns b as-is (no new object allocation implied by interface)
TEST_F(PrefilterInfoConcatTest_544, ReturnsSecondWhenFirstIsNull_544) {
  // Arrange
  Prefilter::Info* b = Prefilter::Info::EmptyString();
  ASSERT_NE(b, nullptr);

  // Act
  Prefilter::Info* res = Prefilter::Info::Concat(nullptr, b);

  // Assert
  // Observable: exact pointer equality proves "return b".
  EXPECT_EQ(res, b);

  // Cleanup
  delete res;  // res == b
}

// [Normal] Concat of two exact infos yields a new exact info
TEST_F(PrefilterInfoConcatTest_544, ConcatTwoExactInfosProducesExactResult_544) {
  // Arrange
  Prefilter::Info* a = PrefilterInfoConcatTest_544::MakeExactCharLatin1('x');
  Prefilter::Info* b = PrefilterInfoConcatTest_544::MakeExactCharLatin1('y');
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  ASSERT_TRUE(a->is_exact());
  ASSERT_TRUE(b->is_exact());

  // Act
  Prefilter::Info* res = Prefilter::Info::Concat(a, b);

  // Assert
  // Result is a different object (ownership of a/b consumed internally).
  EXPECT_NE(res, a);
  EXPECT_NE(res, b);
  ASSERT_NE(res, nullptr);
  EXPECT_TRUE(res->is_exact());

  // We don't assert on specific internal contents; we only rely on public API.
  // ToString() is public and reflects observable state, so it's safe to call.
  std::string s = res->ToString();
  EXPECT_FALSE(s.empty());  // At minimum, should provide some representation.

  // Cleanup
  delete res;
}

// [Boundary] Concat with EmptyString() on the right should preserve the left's observable exact set
TEST_F(PrefilterInfoConcatTest_544, ConcatWithEmptyStringOnRightPreservesLeft_544) {
  // Arrange
  Prefilter::Info* a = PrefilterInfoConcatTest_544::MakeExactCharLatin1('A');
  Prefilter::Info* empty = Prefilter::Info::EmptyString();
  ASSERT_NE(a, nullptr);
  ASSERT_NE(empty, nullptr);
  ASSERT_TRUE(a->is_exact());
  ASSERT_TRUE(empty->is_exact());

  // Capture observable state before Concat (since a will be consumed).
  const std::string before = a->ToString();

  // Act
  Prefilter::Info* res = Prefilter::Info::Concat(a, empty);

  // Assert
  ASSERT_NE(res, nullptr);
  EXPECT_TRUE(res->is_exact());
  // Observable behavior: concatenating with empty string should not change the set.
  EXPECT_EQ(res->ToString(), before);

  // Cleanup
  delete res;
}

// [Boundary] Concat with EmptyString() on the left should preserve the right's observable exact set
TEST_F(PrefilterInfoConcatTest_544, ConcatWithEmptyStringOnLeftPreservesRight_544) {
  // Arrange
  Prefilter::Info* empty = Prefilter::Info::EmptyString();
  Prefilter::Info* b = PrefilterInfoConcatTest_544::MakeExactCharLatin1('Z');
  ASSERT_NE(empty, nullptr);
  ASSERT_NE(b, nullptr);
  ASSERT_TRUE(empty->is_exact());
  ASSERT_TRUE(b->is_exact());

  // Capture observable state before Concat (since b will be consumed).
  const std::string expected = b->ToString();

  // Act
  Prefilter::Info* res = Prefilter::Info::Concat(empty, b);

  // Assert
  ASSERT_NE(res, nullptr);
  EXPECT_TRUE(res->is_exact());
  EXPECT_EQ(res->ToString(), expected);

  // Cleanup
  delete res;
}

}  // namespace re2
