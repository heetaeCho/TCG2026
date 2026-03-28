// SPDX-License-Identifier: GPL-2.0-or-later
// ----------------------------------------------------------------------------
// Unit tests for Exiv2::Internal::printMinoltaSonyLocalAFAreaPoint
//
// File under test: ./TestProjects/exiv2/src/minoltamn_int.cpp
//
// Constraints:
//  - Treat implementation as a black box
//  - Test only observable behavior via public interface (stream output / no-throw)
//  - No private/internal state access
//  - Use mocks only for external collaborators (none here)
// ----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

// The function under test is defined in a .cpp; declare it here to avoid relying
// on internal headers that may vary between build layouts.
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyLocalAFAreaPoint(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class MinoltaSonyLocalAFAreaPointPrintTest_1030 : public ::testing::Test {
protected:
  static std::string render(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    // Ensure we can observe the returned stream reference as "same stream"
    std::ostream& returned = Exiv2::Internal::printMinoltaSonyLocalAFAreaPoint(oss, v, md);
    EXPECT_EQ(&returned, &oss);
    return oss.str();
  }

  static Exiv2::Value::UniquePtr makeUShortValueFromString(const std::string& s) {
    // Use only the public factory + read interface.
    // If the build does not expose Exiv2::unsignedShort in this version,
    // this will fail to compile and should be adjusted to the project's TypeId.
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    // Use read(string) to avoid assumptions about byte order/encoding.
    (void)v->read(s);
    return v;
  }
};

TEST_F(MinoltaSonyLocalAFAreaPointPrintTest_1030, PrintsKnownMappings_1030) {
  struct Case {
    const char* input;
    const char* expected_substr;
  };

  // Based on the publicly visible TagDetails table in the prompt.
  const Case cases[] = {
      {"1", "Center"},       {"2", "Top"},          {"3", "Top-Right"},
      {"4", "Right"},        {"5", "Bottom-Right"}, {"6", "Bottom"},
      {"7", "Bottom-Left"},  {"8", "Left"},         {"9", "Top-Left"},
      {"10", "Far-Right"},   {"11", "Far-Left"},
  };

  Exiv2::ExifData md;  // empty metadata should be acceptable to pass

  for (const auto& tc : cases) {
    SCOPED_TRACE(std::string("input=") + tc.input + " expected=" + tc.expected_substr);

    auto v = makeUShortValueFromString(tc.input);
    ASSERT_NE(v.get(), nullptr);

    const std::string out_with_md = render(*v, &md);
    const std::string out_no_md   = render(*v, nullptr);

    // Observable behavior: output should contain the mapped label.
    EXPECT_NE(out_with_md.find(tc.expected_substr), std::string::npos);
    EXPECT_NE(out_no_md.find(tc.expected_substr), std::string::npos);

    // If metadata is unused for this tag (expected), output should match.
    // If it is used in some versions, this still guards against regressions
    // where nullptr behaves differently than an empty ExifData.
    EXPECT_EQ(out_with_md, out_no_md);
  }
}

TEST_F(MinoltaSonyLocalAFAreaPointPrintTest_1030, UnknownValueDoesNotCrashAndProducesSomeOutput_1030) {
  auto v = makeUShortValueFromString("9999");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = render(*v, nullptr);

  // Black-box friendly: don’t assume exact formatting for unknown values.
  // Just ensure something is produced (or at least the call is safe).
  // Many Exiv2 printers output either the numeric value or an "Unknown" marker.
  EXPECT_FALSE(out.empty());
}

TEST_F(MinoltaSonyLocalAFAreaPointPrintTest_1030, EmptyOrUnreadValueIsHandledSafely_1030) {
  // Create a value but do not populate it with read(); this is a boundary-ish case.
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  EXPECT_NO_THROW({
    std::ostream& returned = Exiv2::Internal::printMinoltaSonyLocalAFAreaPoint(oss, *v, nullptr);
    EXPECT_EQ(&returned, &oss);
  });

  // Don’t assume whether it prints empty, 0, or something else; just ensure call is safe.
}

}  // namespace