// File: ./TestProjects/yaml-cpp/test/getstringescapingstyle_test.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/emitterutils.h"  // for YAML::StringEscaping

namespace YAML {
// Function under test is implemented in src/emitter.cpp.
// Declare it here to test the existing implementation (black-box).
StringEscaping::value GetStringEscapingStyle(const EMITTER_MANIP emitterManip);
}  // namespace YAML

namespace {

class GetStringEscapingStyleTest_533 : public ::testing::Test {};

TEST_F(GetStringEscapingStyleTest_533, EscapeNonAsciiMapsToNonAscii_533) {
  EXPECT_EQ(YAML::StringEscaping::NonAscii,
            YAML::GetStringEscapingStyle(YAML::EscapeNonAscii));
}

TEST_F(GetStringEscapingStyleTest_533, EscapeAsJsonMapsToJson_533) {
  EXPECT_EQ(YAML::StringEscaping::JSON,
            YAML::GetStringEscapingStyle(YAML::EscapeAsJson));
}

TEST_F(GetStringEscapingStyleTest_533, AutoDefaultsToNone_533) {
  EXPECT_EQ(YAML::StringEscaping::None,
            YAML::GetStringEscapingStyle(YAML::Auto));
}

TEST_F(GetStringEscapingStyleTest_533, LowestAndHighestDefinedEnumsDefaultToNone_533) {
  // Boundary within the known enum range.
  EXPECT_EQ(YAML::StringEscaping::None,
            YAML::GetStringEscapingStyle(YAML::Auto));     // lowest (0)
  EXPECT_EQ(YAML::StringEscaping::None,
            YAML::GetStringEscapingStyle(YAML::LongKey));  // highest (34)
}

class GetStringEscapingStyleDefaultsToNoneTest_533
    : public ::testing::TestWithParam<YAML::EMITTER_MANIP> {};

TEST_P(GetStringEscapingStyleDefaultsToNoneTest_533, NonEscapeManipsReturnNone_533) {
  EXPECT_EQ(YAML::StringEscaping::None, YAML::GetStringEscapingStyle(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    CommonNonEscapeManips_533,
    GetStringEscapingStyleDefaultsToNoneTest_533,
    ::testing::Values(
        YAML::Auto,
        YAML::EmitNonAscii,
        YAML::SingleQuoted,
        YAML::DoubleQuoted,
        YAML::Literal,
        YAML::BeginDoc,
        YAML::EndDoc,
        YAML::BeginSeq,
        YAML::EndSeq,
        YAML::BeginMap,
        YAML::EndMap,
        YAML::Key,
        YAML::Value,
        YAML::LongKey));

TEST_F(GetStringEscapingStyleTest_533, UnknownEnumValueDefaultsToNone_533) {
  // Error/exceptional (observable) cases: values outside the enum set.
  EXPECT_EQ(YAML::StringEscaping::None,
            YAML::GetStringEscapingStyle(static_cast<YAML::EMITTER_MANIP>(-1)));
  EXPECT_EQ(YAML::StringEscaping::None,
            YAML::GetStringEscapingStyle(static_cast<YAML::EMITTER_MANIP>(999)));
}

}  // namespace