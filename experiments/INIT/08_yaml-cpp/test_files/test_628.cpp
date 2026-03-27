// File: ./TestProjects/yaml-cpp/test/emitterutils_test_628.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/emitterutils.h"
#include "yaml-cpp/emitterstyle.h"  // For FlowType, StringFormat (commonly declared here in yaml-cpp)

namespace {

using YAML::EMITTER_MANIP;
using YAML::FlowType;
using YAML::StringFormat;

TEST(ComputeStringFormatTest_628, AutoReturnsPlainForSimpleAscii_628) {
  const char* s = "abc";
  const std::size_t n = 3;

  const StringFormat::value fmt = YAML::Utils::ComputeStringFormat(
      s, n, EMITTER_MANIP::Auto, FlowType::Block, /*escapeNonAscii=*/false);

  EXPECT_EQ(fmt, StringFormat::Plain);
}

TEST(ComputeStringFormatTest_628, AutoFallsBackToDoubleQuotedWhenPlainInvalid_628) {
  // Plain scalars should not accept embedded newlines.
  const char* s = "a\nb";
  const std::size_t n = 3;

  const StringFormat::value fmt = YAML::Utils::ComputeStringFormat(
      s, n, EMITTER_MANIP::Auto, FlowType::Block, /*escapeNonAscii=*/false);

  EXPECT_EQ(fmt, StringFormat::DoubleQuoted);
}

TEST(ComputeStringFormatTest_628, SingleQuotedReturnsSingleQuotedForSimpleAscii_628) {
  const char* s = "hello";
  const std::size_t n = 5;

  const StringFormat::value fmt = YAML::Utils::ComputeStringFormat(
      s, n, EMITTER_MANIP::SingleQuoted, FlowType::Block, /*escapeNonAscii=*/false);

  EXPECT_EQ(fmt, StringFormat::SingleQuoted);
}

TEST(ComputeStringFormatTest_628, SingleQuotedFallsBackToDoubleQuotedWhenNonAsciiEscapingRequested_628) {
  // If non-ASCII escaping is requested, single-quoted may be rejected and should fall back.
  const char* s = u8"é";  // UTF-8 (2 bytes)
  const std::size_t n = 2;

  const StringFormat::value fmt = YAML::Utils::ComputeStringFormat(
      s, n, EMITTER_MANIP::SingleQuoted, FlowType::Block, /*escapeNonAscii=*/true);

  EXPECT_EQ(fmt, StringFormat::DoubleQuoted);
}

TEST(ComputeStringFormatTest_628, LiteralReturnsLiteralForMultilineInBlock_628) {
  const char* s = "a\nb";
  const std::size_t n = 3;

  const StringFormat::value fmt = YAML::Utils::ComputeStringFormat(
      s, n, EMITTER_MANIP::Literal, FlowType::Block, /*escapeNonAscii=*/false);

  EXPECT_EQ(fmt, StringFormat::Literal);
}

TEST(ComputeStringFormatTest_628, LiteralFallsBackToDoubleQuotedInFlow_628) {
  // Literal style is typically not allowed in flow context; it should fall back.
  const char* s = "a\nb";
  const std::size_t n = 3;

  const StringFormat::value fmt = YAML::Utils::ComputeStringFormat(
      s, n, EMITTER_MANIP::Literal, FlowType::Flow, /*escapeNonAscii=*/false);

  EXPECT_EQ(fmt, StringFormat::DoubleQuoted);
}

TEST(ComputeStringFormatTest_628, DoubleQuotedAlwaysReturnsDoubleQuoted_628) {
  const char* s = "anything";
  const std::size_t n = 8;

  const StringFormat::value fmt = YAML::Utils::ComputeStringFormat(
      s, n, EMITTER_MANIP::DoubleQuoted, FlowType::Flow, /*escapeNonAscii=*/true);

  EXPECT_EQ(fmt, StringFormat::DoubleQuoted);
}

TEST(ComputeStringFormatTest_628, UnknownManipFallsBackToDoubleQuoted_628) {
  const char* s = "abc";
  const std::size_t n = 3;

  const auto unknown = static_cast<EMITTER_MANIP>(999);

  const StringFormat::value fmt = YAML::Utils::ComputeStringFormat(
      s, n, unknown, FlowType::Block, /*escapeNonAscii=*/false);

  EXPECT_EQ(fmt, StringFormat::DoubleQuoted);
}

}  // namespace