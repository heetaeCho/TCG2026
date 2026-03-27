// File: pcre_constructor_and_basic_api_test_587.cc
#include <gtest/gtest.h>
#include <string>

// Adjust include to match your project include roots.
#include "re2/util/pcre.h"

namespace {

using re2::PCRE;

// We don't know the concrete values of Option, so we pass a neutral integral value.
static constexpr int kNeutralOptionInt = 0;

// Simple fixture in case future tests need shared setup.
class PCRETest_587 : public ::testing::Test {};

TEST_F(PCRETest_587, ConstructWithCStringAndOption_SetsPattern_587) {
  const char* pat = "a.*b(c|d)?";
  // Use a neutral Option without assuming specific enum constants.
  auto opt = static_cast<Option>(kNeutralOptionInt);

  PCRE re(pat, opt);

  // Observable behavior via public accessor.
  EXPECT_EQ(re.pattern(), std::string(pat));
}

TEST_F(PCRETest_587, ConstructWithStdStringAndOption_SetsPattern_587) {
  std::string pat = R"((\w+)\s+\1\b)";
  auto opt = static_cast<Option>(kNeutralOptionInt);

  PCRE re(pat, opt);

  EXPECT_EQ(re.pattern(), pat);
}

TEST_F(PCRETest_587, PatternWithSpecialBytes_IsPreservedVerbatim_587) {
  // Include spaces, punctuation, and backslashes to ensure no unintended transformations.
  std::string pat = R"(^\s+foo\bar[0-9]+\s*$)";
  auto opt = static_cast<Option>(kNeutralOptionInt);

  PCRE re(pat, opt);

  // Verify exact byte-for-byte equality through the public API.
  ASSERT_EQ(re.pattern().size(), pat.size());
  EXPECT_EQ(re.pattern(), pat);
}

TEST_F(PCRETest_587, HitLimit_CanBeCleared_ReportsNoHitAfterClear_587) {
  auto opt = static_cast<Option>(kNeutralOptionInt);
  PCRE re(".*", opt);

  // We do not assert the initial state (black-box). We only assert observable behavior:
  // After calling ClearHitLimit(), HitLimit() must be false.
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRETest_587, Destructor_NoThrowOnScopeExit_587) {
  auto opt = static_cast<Option>(kNeutralOptionInt);

  // Construction + destruction should be safe; this also exercises ~PCRE().
  {
    PCRE re("^abc$", opt);
    EXPECT_EQ(re.pattern(), std::string("^abc$"));
  } // scope exit triggers destructor; test passes if no crash/throw
}

}  // namespace
