// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_printMinoltaSonyColorMode_1026.cpp
//
// Unit tests for:
//   Exiv2::Internal::printMinoltaSonyColorMode(std::ostream&, const Value&, const ExifData*)
//
// Constraints honored:
// - Treat implementation as a black box (only check observable output / return)
// - No private/internal state access
// - No re-implementation of internal logic
// - Boundary + error/exceptional (as observable) cases included

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace Exiv2::Internal {
// Forward declaration (avoid relying on private headers)
std::ostream& printMinoltaSonyColorMode(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

class MinoltaMnIntPrintColorModeTest_1026 : public ::testing::Test {
 protected:
  // Helper to create a numeric Value with best-effort type choice.
  // We only rely on public Value API; actual formatting is treated as a black box.
  static Exiv2::Value::UniquePtr makeUintValue(uint32_t v) {
    // Use a commonly supported integral TypeId in Exiv2.
    // (If your build prefers another, adjust the TypeId here.)
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    if (!val) {
      // Fallback to unsignedLong if unsignedShort isn't available in this build configuration.
      val = Exiv2::Value::create(Exiv2::unsignedLong);
    }
    EXPECT_TRUE(static_cast<bool>(val));
    if (!val) return nullptr;

    // Prefer string read (public API) to avoid depending on concrete Value subclasses.
    (void)val->read(std::to_string(v));
    return val;
  }
};

TEST_F(MinoltaMnIntPrintColorModeTest_1026, ReturnsSameOstreamReference_1026) {
  auto value = makeUintValue(0);
  ASSERT_TRUE(static_cast<bool>(value));

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyColorMode(oss, *value, /*metadata=*/nullptr);

  // Observable behavior: function returns an std::ostream& (should be the same stream passed in).
  EXPECT_EQ(&ret, &oss);
}

TEST_F(MinoltaMnIntPrintColorModeTest_1026, AcceptsNullMetadataPointer_1026) {
  auto value = makeUintValue(1);
  ASSERT_TRUE(static_cast<bool>(value));

  std::ostringstream oss;
  EXPECT_NO_THROW({
    (void)Exiv2::Internal::printMinoltaSonyColorMode(oss, *value, /*metadata=*/nullptr);
  });

  // Observable: some output should be produced (format unspecified).
  EXPECT_FALSE(oss.str().empty());
}

TEST_F(MinoltaMnIntPrintColorModeTest_1026, PrintsExpectedLabelForKnownValues_Boundaries_1026) {
  struct Case {
    uint32_t code;
    const char* expected_substring;
  };

  // Based on the provided TagDetails table in the prompt.
  const std::vector<Case> cases = {
      {0, "Standard"},            // first entry boundary
      {105, "Autumn Leaves"},     // last entry boundary
  };

  for (const auto& tc : cases) {
    auto value = makeUintValue(tc.code);
    ASSERT_TRUE(static_cast<bool>(value));

    std::ostringstream oss;
    (void)Exiv2::Internal::printMinoltaSonyColorMode(oss, *value, /*metadata=*/nullptr);

    const std::string out = oss.str();
    EXPECT_NE(out.find(tc.expected_substring), std::string::npos)
        << "code=" << tc.code << " output=[" << out << "]";
  }
}

TEST_F(MinoltaMnIntPrintColorModeTest_1026, PrintsExpectedLabelForKnownValues_SpotChecks_1026) {
  struct Case {
    uint32_t code;
    const char* expected_substring;
  };

  // A few representative values across the table (not exhaustive).
  const std::vector<Case> cases = {
      {1, "Vivid Color"},
      {6, "Black & White"},
      {7, "AdobeRGB"},
      {12, "Neutral"},
      {100, "Neutral"},
      {104, "Night View"},
  };

  for (const auto& tc : cases) {
    auto value = makeUintValue(tc.code);
    ASSERT_TRUE(static_cast<bool>(value));

    std::ostringstream oss;
    (void)Exiv2::Internal::printMinoltaSonyColorMode(oss, *value, /*metadata=*/nullptr);

    const std::string out = oss.str();
    EXPECT_NE(out.find(tc.expected_substring), std::string::npos)
        << "code=" << tc.code << " output=[" << out << "]";
  }
}

TEST_F(MinoltaMnIntPrintColorModeTest_1026, UnknownValueDoesNotCrashAndProducesOutput_1026) {
  auto value = makeUintValue(999);  // not in provided TagDetails list
  ASSERT_TRUE(static_cast<bool>(value));

  std::ostringstream oss;
  EXPECT_NO_THROW({
    (void)Exiv2::Internal::printMinoltaSonyColorMode(oss, *value, /*metadata=*/nullptr);
  });

  // We do not assume formatting for unknown values, only that something observable happens.
  EXPECT_FALSE(oss.str().empty());
}

TEST_F(MinoltaMnIntPrintColorModeTest_1026, WorksWithRealExifDataObject_1026) {
  auto value = makeUintValue(2);
  ASSERT_TRUE(static_cast<bool>(value));

  Exiv2::ExifData exif;
  std::ostringstream oss;

  EXPECT_NO_THROW({
    (void)Exiv2::Internal::printMinoltaSonyColorMode(oss, *value, &exif);
  });

  // Observable: output should contain the expected label for code 2 ("Portrait") per provided table.
  EXPECT_NE(oss.str().find("Portrait"), std::string::npos) << "output=[" << oss.str() << "]";
}

}  // namespace