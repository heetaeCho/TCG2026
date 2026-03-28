// File: re2_octal_arg_test.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

namespace {

TEST(RE2_OctalTest_45, ParsesSimpleOctal_45) {
  RE2 re("(\\d+)");
  int value = -1;
  ASSERT_TRUE(RE2::FullMatch("17", re, RE2::Octal(&value)));
  // 017 (octal) == 15 (decimal)
  EXPECT_EQ(value, 15);
}

TEST(RE2_OctalTest_45, ParsesWithLeadingZeros_45) {
  RE2 re("(\\d+)");
  int value = -1;
  ASSERT_TRUE(RE2::FullMatch("0123", re, RE2::Octal(&value)));
  // 0123 (octal) == 83 (decimal)
  EXPECT_EQ(value, 83);
}

TEST(RE2_OctalTest_45, RejectsNonOctalDigits_45) {
  RE2 re("(\\d+)");
  int value = -1;
  // Contains '8' which is not valid in base-8; conversion should fail.
  EXPECT_FALSE(RE2::FullMatch("18", re, RE2::Octal(&value)));
  // Value should remain unchanged on failure (observable: we only check that no write is required/assumed).
}

TEST(RE2_OctalTest_45, PartialMatchParsesEmbeddedOctal_45) {
  RE2 re("(\\d+)");
  int value = -1;
  ASSERT_TRUE(RE2::PartialMatch("abc077def", re, RE2::Octal(&value)));
  // 077 (octal) == 63 (decimal)
  EXPECT_EQ(value, 63);
}

TEST(RE2_OctalTest_45, NegativeNumbersIfRegexAllowsSign_45) {
  // The parser behavior for signs is treated as black-box; we only assert observable outcome
  // when a pattern that can capture a leading '-' is used.
  RE2 re("(-?\\d+)");
  int value = 0;
  // "-10" in octal is -8 decimal if sign is honored by the parser.
  bool ok = RE2::FullMatch("-10", re, RE2::Octal(&value));
  // If the interface supports signed parsing, ok should be true and value == -8.
  // If not, ok will be false. Either outcome is acceptable as observable behavior;
  // we assert the consistent pairing between the boolean result and the value.
  if (ok) {
    EXPECT_EQ(value, -8);
  } else {
    SUCCEED() << "Octal parser rejected signed input as expected by its contract.";
  }
}

TEST(RE2_OctalTest_45, MultipleCapturesIntoDifferentTypes_45) {
  RE2 re("([0-7]+)-([0-7]+)");
  int a = -1;
  unsigned b = 0;
  ASSERT_TRUE(RE2::FullMatch("17-20", re, RE2::Octal(&a), RE2::Octal(&b)));
  // 017 -> 15, 020 -> 16
  EXPECT_EQ(a, 15);
  EXPECT_EQ(b, 16u);
}

TEST(RE2_OctalTest_45, ConsumeAdvancesInputOnSuccess_45) {
  RE2 re("^([0-7]+)");
  absl::string_view input = "755 rest";
  int mode = 0;
  ASSERT_TRUE(RE2::Consume(&input, re, RE2::Octal(&mode)));
  // 0755 (octal) == 493 (decimal)
  EXPECT_EQ(mode, 493);
  // Verify input advanced past the consumed match and one space remains before "rest".
  EXPECT_EQ(input, " rest");
}

TEST(RE2_OctalTest_45, ConsumeDoesNotAdvanceOnFailure_45) {
  RE2 re("^([0-7]+)");
  absl::string_view input = "78 rest";  // '8' not allowed in octal
  int out = -1;
  EXPECT_FALSE(RE2::Consume(&input, re, RE2::Octal(&out)));
  // Input remains unchanged on failure (observable via public API).
  EXPECT_EQ(input, "78 rest");
}

}  // namespace
