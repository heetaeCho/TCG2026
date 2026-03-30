// File: test_tags_int_print0x0009_1387.cpp
// Unit tests for Exiv2::Internal::print0x0009
// TEST_ID: 1387

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

namespace Exiv2::Internal {
// The function under test is implemented in src/tags_int.cpp but may not have a public header.
// Declare it here so we can link against the real implementation.
std::ostream& print0x0009(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

class Print0x0009Test_1387 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
    // Use the public factory + read(string) interface only.
    // asciiString is a standard Exiv2 TypeId for string values.
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_GE(v->read(s), 0);
    return v;
  }

  static std::string run(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    auto& ret = Exiv2::Internal::print0x0009(oss, v, md);
    EXPECT_EQ(&ret, &oss);  // should return the same stream reference
    return oss.str();
  }
};

TEST_F(Print0x0009Test_1387, ReturnsSameStreamReference_1387) {
  auto v = makeAsciiValue("A");
  std::ostringstream oss;
  auto& ret = Exiv2::Internal::print0x0009(oss, *v, nullptr);
  EXPECT_EQ(&ret, &oss);
}

TEST_F(Print0x0009Test_1387, MapsAValueToHumanReadableText_1387) {
  auto v = makeAsciiValue("A");
  Exiv2::ExifData md;

  const std::string out = run(*v, &md);

  // Observable behavior: should produce some output; and for a known status value,
  // should include the known description from TagDetails (provided in prompt).
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Measurement in progress"), std::string::npos);
}

TEST_F(Print0x0009Test_1387, MapsVValueToHumanReadableText_1387) {
  auto v = makeAsciiValue("V");
  Exiv2::ExifData md;

  const std::string out = run(*v, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Measurement interrupted"), std::string::npos);
}

TEST_F(Print0x0009Test_1387, AcceptsNullMetadataPointer_1387) {
  auto v = makeAsciiValue("A");

  const std::string out = run(*v, nullptr);

  // Should not crash and should still produce output.
  EXPECT_FALSE(out.empty());
}

TEST_F(Print0x0009Test_1387, UnknownValueProducesNonEmptyOutput_1387) {
  auto v = makeAsciiValue("X");
  Exiv2::ExifData md;

  const std::string out = run(*v, &md);

  // Black-box expectation: should produce *some* representation for an unknown value.
  EXPECT_FALSE(out.empty());

  // Keep this loose: many Exiv2 printers either echo the raw value or show some fallback.
  // We only require that the raw token appears somewhere OR that it doesn't falsely map
  // to one of the known descriptions.
  const bool containsRaw = (out.find("X") != std::string::npos);
  const bool containsKnownA = (out.find("Measurement in progress") != std::string::npos);
  const bool containsKnownV = (out.find("Measurement interrupted") != std::string::npos);
  EXPECT_TRUE(containsRaw || (!containsKnownA && !containsKnownV));
}

TEST_F(Print0x0009Test_1387, EmptyStringValueDoesNotCrashAndProducesOutput_1387) {
  auto v = makeAsciiValue("");
  Exiv2::ExifData md;

  const std::string out = run(*v, &md);

  // Interface-level behavior: no crash; output is allowed to be empty or not depending
  // on implementation. Prefer a minimal assertion that it is at least safe to call.
  // Still, most printers emit something, so we assert non-empty to catch regressions.
  EXPECT_FALSE(out.empty());
}

}  // namespace