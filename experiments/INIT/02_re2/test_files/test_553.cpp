// File: prefilter_info_literal_latin1_test_553.cc

#include "gtest/gtest.h"
#include "re2/prefilter.h"  // Assumes the public declarations for Prefilter::Info live here

using re2::Prefilter;

class PrefilterInfoTest_553 : public ::testing::Test {
protected:
  // Helper to check the single exact literal contained in Info
  static ::testing::AssertionResult HasSingleExact(Prefilter::Info* info,
                                                   const std::string& expected) {
    if (info == nullptr) {
      return ::testing::AssertionFailure() << "info is nullptr";
    }
    const auto& sset = info->exact();
    if (sset.size() != 1) {
      return ::testing::AssertionFailure()
             << "exact() size expected 1 but was " << sset.size();
    }
    if (sset.find(expected) == sset.end()) {
      return ::testing::AssertionFailure()
             << "exact() does not contain expected value '" << expected << "'";
    }
    return ::testing::AssertionSuccess();
  }
};

// Normal operation: uppercase ASCII should be stored as lowercase exact literal.
TEST_F(PrefilterInfoTest_553, LiteralLatin1_StoresLowercasedAscii_553) {
  Prefilter::Info* info = Prefilter::Info::LiteralLatin1(static_cast<Rune>('A'));
  ASSERT_NE(info, nullptr);

  EXPECT_TRUE(info->is_exact());
  EXPECT_TRUE(HasSingleExact(info, "a"));

  delete info;
}

// Normal operation: lowercase ASCII should be preserved as exact literal.
TEST_F(PrefilterInfoTest_553, LiteralLatin1_PreservesLowercaseAscii_553) {
  Prefilter::Info* info = Prefilter::Info::LiteralLatin1(static_cast<Rune>('z'));
  ASSERT_NE(info, nullptr);

  EXPECT_TRUE(info->is_exact());
  EXPECT_TRUE(HasSingleExact(info, "z"));

  delete info;
}

// Boundary-ish case in Latin-1 range: non-alphabetic character should be exact as-is.
TEST_F(PrefilterInfoTest_553, LiteralLatin1_NonAlphaIsExactAsIs_553) {
  Prefilter::Info* info = Prefilter::Info::LiteralLatin1(static_cast<Rune>('1'));
  ASSERT_NE(info, nullptr);

  EXPECT_TRUE(info->is_exact());
  EXPECT_TRUE(HasSingleExact(info, "1"));

  delete info;
}

// Extended Latin-1 letter: should reflect Latin-1 lowercase mapping in exact().
TEST_F(PrefilterInfoTest_553, LiteralLatin1_ExtendedLatin1Lowercasing_553) {
  // 'Å' (0xC5) lowercased in Latin-1 is 'å' (0xE5).
  Prefilter::Info* info = Prefilter::Info::LiteralLatin1(static_cast<Rune>(0xC5));
  ASSERT_NE(info, nullptr);

  EXPECT_TRUE(info->is_exact());
  // "å" encoded as UTF-8 literal in source; the SSet should contain the Latin-1
  // single-character string corresponding to the lowercased rune.
  EXPECT_TRUE(HasSingleExact(info, "å"));

  delete info;
}
