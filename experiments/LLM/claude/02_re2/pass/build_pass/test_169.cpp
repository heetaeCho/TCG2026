#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class ParseFlagsXorTest_169 : public ::testing::Test {
 protected:
};

// Test XOR of two identical flags yields zero
TEST_F(ParseFlagsXorTest_169, XorSameFlag_YieldsZero_169) {
  Regexp::ParseFlags a = Regexp::LikePerl;
  Regexp::ParseFlags result = a ^ a;
  EXPECT_EQ(static_cast<int>(result), 0);
}

// Test XOR with zero (NoParseFlags) is identity
TEST_F(ParseFlagsXorTest_169, XorWithZero_IsIdentity_169) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags zero = static_cast<Regexp::ParseFlags>(0);
  Regexp::ParseFlags result = a ^ zero;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(a));
}

// Test XOR is commutative
TEST_F(ParseFlagsXorTest_169, XorIsCommutative_169) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::OneLine;
  EXPECT_EQ(static_cast<int>(a ^ b), static_cast<int>(b ^ a));
}

// Test XOR of different flags produces expected bitwise result
TEST_F(ParseFlagsXorTest_169, XorDifferentFlags_169) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::OneLine;
  int expected = static_cast<int>(a) ^ static_cast<int>(b);
  EXPECT_EQ(static_cast<int>(a ^ b), expected);
}

// Test XOR is associative
TEST_F(ParseFlagsXorTest_169, XorIsAssociative_169) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::OneLine;
  Regexp::ParseFlags c = Regexp::ClassNL;
  EXPECT_EQ(static_cast<int>((a ^ b) ^ c), static_cast<int>(a ^ (b ^ c)));
}

// Test XOR with compound flags (LikePerl is a combination of multiple flags)
TEST_F(ParseFlagsXorTest_169, XorCompoundFlags_169) {
  Regexp::ParseFlags a = Regexp::LikePerl;
  Regexp::ParseFlags b = Regexp::PerlX;
  int expected = static_cast<int>(a) ^ static_cast<int>(b);
  Regexp::ParseFlags result = a ^ b;
  EXPECT_EQ(static_cast<int>(result), expected);
}

// Test double XOR returns original value (involution)
TEST_F(ParseFlagsXorTest_169, DoubleXorReturnsOriginal_169) {
  Regexp::ParseFlags a = Regexp::LikePerl;
  Regexp::ParseFlags b = Regexp::FoldCase;
  Regexp::ParseFlags result = (a ^ b) ^ b;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(a));
}

// Test XOR with all-bits pattern
TEST_F(ParseFlagsXorTest_169, XorWithAllBits_169) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags allBits = static_cast<Regexp::ParseFlags>(~0);
  Regexp::ParseFlags result = a ^ allBits;
  int expected = static_cast<int>(a) ^ (~0);
  EXPECT_EQ(static_cast<int>(result), expected);
}

// Test XOR of zero with zero
TEST_F(ParseFlagsXorTest_169, XorZeroWithZero_169) {
  Regexp::ParseFlags zero = static_cast<Regexp::ParseFlags>(0);
  Regexp::ParseFlags result = zero ^ zero;
  EXPECT_EQ(static_cast<int>(result), 0);
}

// Test XOR with various individual flags
TEST_F(ParseFlagsXorTest_169, XorMultipleIndividualFlags_169) {
  Regexp::ParseFlags a = Regexp::Literal;
  Regexp::ParseFlags b = Regexp::NeverNL;
  int expected = static_cast<int>(a) ^ static_cast<int>(b);
  EXPECT_EQ(static_cast<int>(a ^ b), expected);
}

// Test XOR result type is ParseFlags
TEST_F(ParseFlagsXorTest_169, XorResultTypeIsParseFlags_169) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::OneLine;
  auto result = a ^ b;
  bool isSameType = std::is_same<decltype(result), Regexp::ParseFlags>::value;
  EXPECT_TRUE(isSameType);
}

}  // namespace re2
