// File: test_langaltvalue_toRational_861.cpp
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

// Prefer the public header that declares Exiv2::LangAltValue and Exiv2::Rational.
#include <exiv2/value.hpp>

namespace {

class LangAltValueTest_861 : public ::testing::Test {
 protected:
  Exiv2::LangAltValue value_;
};

TEST_F(LangAltValueTest_861, ToRational_Index0_ReturnsZeroZero_861) {
  EXPECT_NO_THROW({
    const Exiv2::Rational r = value_.toRational(0);
    EXPECT_EQ(r, (Exiv2::Rational{0, 0}));
  });
}

TEST_F(LangAltValueTest_861, ToRational_NonZeroIndex_ReturnsZeroZero_861) {
  EXPECT_NO_THROW({
    const Exiv2::Rational r = value_.toRational(1);
    EXPECT_EQ(r, (Exiv2::Rational{0, 0}));
  });
}

TEST_F(LangAltValueTest_861, ToRational_LargeIndex_ReturnsZeroZero_861) {
  const std::size_t largeIndex = (std::numeric_limits<std::size_t>::max)();

  EXPECT_NO_THROW({
    const Exiv2::Rational r = value_.toRational(largeIndex);
    EXPECT_EQ(r, (Exiv2::Rational{0, 0}));
  });
}

TEST_F(LangAltValueTest_861, ToRational_CanBeCalledOnConstObject_861) {
  const Exiv2::LangAltValue& cref = value_;
  EXPECT_NO_THROW({
    const Exiv2::Rational r = cref.toRational(0);
    EXPECT_EQ(r, (Exiv2::Rational{0, 0}));
  });
}

TEST_F(LangAltValueTest_861, ToRational_RepeatedCalls_AreConsistent_861) {
  EXPECT_NO_THROW({
    const Exiv2::Rational r0 = value_.toRational(0);
    const Exiv2::Rational r1 = value_.toRational(123);
    const Exiv2::Rational r2 = value_.toRational(0);

    EXPECT_EQ(r0, (Exiv2::Rational{0, 0}));
    EXPECT_EQ(r1, (Exiv2::Rational{0, 0}));
    EXPECT_EQ(r2, (Exiv2::Rational{0, 0}));
    EXPECT_EQ(r0, r2);
  });
}

}  // namespace