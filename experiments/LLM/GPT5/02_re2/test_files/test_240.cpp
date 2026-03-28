// File: re2_regexp_error_to_re2_test.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/re2.h"

// Include the implementation so the internal static function is visible in this TU.
#include "re2/re2.cc"

namespace re2 {

// ----- Parameterized tests covering all known enum mappings -----

struct MappingCase {
  RegexpStatusCode in;
  RE2::ErrorCode out;
};

class RegexpErrorToRE2Test_240
    : public ::testing::TestWithParam<MappingCase> {};

TEST_P(RegexpErrorToRE2Test_240, MapsKnownCodes_240) {
  const auto& c = GetParam();
  EXPECT_EQ(RegexpErrorToRE2(c.in), c.out);
}

INSTANTIATE_TEST_SUITE_P(
    AllKnownMappings_240,
    RegexpErrorToRE2Test_240,
    ::testing::Values(
        MappingCase{kRegexpSuccess, RE2::NoError},
        MappingCase{kRegexpInternalError, RE2::ErrorInternal},
        MappingCase{kRegexpBadEscape, RE2::ErrorBadEscape},
        MappingCase{kRegexpBadCharClass, RE2::ErrorBadCharClass},
        MappingCase{kRegexpBadCharRange, RE2::ErrorBadCharRange},
        MappingCase{kRegexpMissingBracket, RE2::ErrorMissingBracket},
        MappingCase{kRegexpMissingParen, RE2::ErrorMissingParen},
        MappingCase{kRegexpUnexpectedParen, RE2::ErrorUnexpectedParen},
        MappingCase{kRegexpTrailingBackslash, RE2::ErrorTrailingBackslash},
        MappingCase{kRegexpRepeatArgument, RE2::ErrorRepeatArgument},
        MappingCase{kRegexpRepeatSize, RE2::ErrorRepeatSize},
        MappingCase{kRegexpRepeatOp, RE2::ErrorRepeatOp},
        MappingCase{kRegexpBadPerlOp, RE2::ErrorBadPerlOp},
        MappingCase{kRegexpBadUTF8, RE2::ErrorBadUTF8},
        MappingCase{kRegexpBadNamedCapture, RE2::ErrorBadNamedCapture}));

// ----- Boundary & exceptional/unknown input behavior -----

TEST(RegexpErrorToRE2_UnknownInputs_240, ReturnsErrorInternalForUnknownCodes_240) {
  // Below known range
  EXPECT_EQ(RegexpErrorToRE2(static_cast<RegexpStatusCode>(-1)),
            RE2::ErrorInternal);

  // Above known range
  EXPECT_EQ(RegexpErrorToRE2(static_cast<RegexpStatusCode>(999)),
            RE2::ErrorInternal);

  // A value equal to an unrelated RE2::ErrorCode enumerator should still map to ErrorInternal.
  EXPECT_EQ(RegexpErrorToRE2(
                static_cast<RegexpStatusCode>(RE2::ErrorPatternTooLarge)),
            RE2::ErrorInternal);
}

TEST(RegexpErrorToRE2_Boundaries_240, HandlesMinAndMaxKnownEnumValues_240) {
  // Minimum known input
  EXPECT_EQ(RegexpErrorToRE2(kRegexpSuccess), RE2::NoError);
  // Maximum known input (per provided enum)
  EXPECT_EQ(RegexpErrorToRE2(kRegexpBadNamedCapture), RE2::ErrorBadNamedCapture);
}

}  // namespace re2
