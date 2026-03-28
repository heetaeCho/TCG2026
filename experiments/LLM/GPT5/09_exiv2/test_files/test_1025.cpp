// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_printMinoltaSonyLensID_1025.cpp
//
// Unit tests for Exiv2::Internal::printMinoltaSonyLensID
// Constraints: treat implementation as black box; test only observable behavior.

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// The function under test is implemented in:
//   ./TestProjects/exiv2/src/minoltamn_int.cpp
// It is typically declared from an internal header in Exiv2.
#if __has_include("minoltamn_int.hpp")
#include "minoltamn_int.hpp"
#elif __has_include("minoltamn_int.h")
#include "minoltamn_int.h"
#else
// Fallback declaration if the internal header is not available in the test build.
// This is only a declaration (NOT a re-implementation).
namespace Exiv2 {
class ExifData;
class Value;
namespace Internal {
std::ostream& printMinoltaSonyLensID(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2
#endif

#include <cstdint>
#include <sstream>
#include <string>

namespace {

class PrintMinoltaSonyLensIDTest_1025 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeValueFromString(Exiv2::TypeId typeId, const std::string& s) {
    auto v = Exiv2::Value::create(typeId);
    EXPECT_NE(v, nullptr);
    // read() return value is implementation-defined; we only require it not to crash.
    (void)v->read(s);
    return v;
  }

  static std::string render(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream os;
    auto& ret = Exiv2::Internal::printMinoltaSonyLensID(os, v, md);
    // Observable: function returns a reference to the passed stream.
    EXPECT_EQ(&ret, &os);
    return os.str();
  }
};

TEST_F(PrintMinoltaSonyLensIDTest_1025, ReturnsSameStreamReference_1025) {
  auto v = makeValueFromString(Exiv2::unsignedShort, "0");
  std::ostringstream os;

  std::ostream& ret = Exiv2::Internal::printMinoltaSonyLensID(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST_F(PrintMinoltaSonyLensIDTest_1025, NoMetadata_KnownId_PrintsNonEmpty_1025) {
  // Boundary/normal: metadata == nullptr should still produce a printable representation.
  auto v = makeValueFromString(Exiv2::unsignedShort, "0");

  const std::string out = render(*v, nullptr);

  EXPECT_FALSE(out.empty());
  // Output may be affected by user config; assert a stable, broad expectation.
  EXPECT_NE(out.find("Minolta"), std::string::npos);
}

TEST_F(PrintMinoltaSonyLensIDTest_1025, NoMetadata_AnotherKnownId_PrintsNonEmpty_1025) {
  // Another known ID from the provided TagDetails list (e.g., 20: "Minolta/Sony 135mm ... STF").
  auto v = makeValueFromString(Exiv2::unsignedShort, "20");

  const std::string out = render(*v, nullptr);

  EXPECT_FALSE(out.empty());
  // Accept either Minolta/Sony wording depending on config or tag print path.
  const bool mentionsMinolta = out.find("Minolta") != std::string::npos;
  const bool mentionsSony = out.find("Sony") != std::string::npos;
  EXPECT_TRUE(mentionsMinolta || mentionsSony);
}

TEST_F(PrintMinoltaSonyLensIDTest_1025, NoMetadata_MaxU16Boundary_PrintsNonEmpty_1025) {
  // Boundary: 0xFFFF is present in the TagDetails list (65535).
  auto v = makeValueFromString(Exiv2::unsignedShort, "65535");

  const std::string out = render(*v, nullptr);

  EXPECT_FALSE(out.empty());
  // TagDetails entry includes "Manual lens | Sony E ...", so expect at least one of these tokens.
  const bool mentionsManual = out.find("Manual") != std::string::npos;
  const bool mentionsSony = out.find("Sony") != std::string::npos;
  EXPECT_TRUE(mentionsManual || mentionsSony);
}

TEST_F(PrintMinoltaSonyLensIDTest_1025, NoMetadata_UnknownLargeValue_DoesNotCrashAndPrintsSomething_1025) {
  // Boundary/error-like: value outside the common table range.
  auto v = makeValueFromString(Exiv2::unsignedLong, "1000000");

  const std::string out = render(*v, nullptr);

  EXPECT_FALSE(out.empty());
}

TEST_F(PrintMinoltaSonyLensIDTest_1025, WithMetadata_KnownId_DoesNotCrashAndReturnsStream_1025) {
  // Normal: provide a valid ExifData pointer (even if empty).
  Exiv2::ExifData md;
  auto v = makeValueFromString(Exiv2::unsignedShort, "0");

  const std::string out = render(*v, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Minolta"), std::string::npos);
}

TEST_F(PrintMinoltaSonyLensIDTest_1025, WithMetadata_SpecialResolverIndexValues_DoNotCrash_1025) {
  // The implementation may dispatch to resolver functions for specific indices when metadata != nullptr.
  // We only verify the observable contract: no crash, returns the stream, and outputs something.
  Exiv2::ExifData md;

  // Indices listed in the implementation snippet: 0x001c, 0x0029, 0x0034, 0x0080, 0x00ff, 0xffff
  const char* indices[] = {"28", "41", "52", "128", "255", "65535"};

  for (const char* s : indices) {
    auto v = makeValueFromString(Exiv2::unsignedShort, s);
    const std::string out = render(*v, &md);
    EXPECT_FALSE(out.empty()) << "index=" << s;
  }
}

TEST_F(PrintMinoltaSonyLensIDTest_1025, EmptyStringValue_DoesNotCrash_1025) {
  // Error-like: attempt to read an empty string into a string-based value.
  // Observable requirement: function should be callable and produce some output.
  auto v = makeValueFromString(Exiv2::asciiString, "");

  const std::string out = render(*v, nullptr);

  EXPECT_FALSE(out.empty());
}

}  // namespace