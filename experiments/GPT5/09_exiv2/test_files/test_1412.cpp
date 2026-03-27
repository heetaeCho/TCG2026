// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_print0xa402_1412.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Under test (defined in ./TestProjects/exiv2/src/tags_int.cpp)
std::ostream& print0xa402(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0xa402Test_1412 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeNumericValue(uint32_t n) {
    // We only rely on the public Value factory + read(string) interface.
    // Using unsignedShort is the most typical for "ExposureMode" (0/1/2).
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
    if (v) {
      (void)v->read(std::to_string(n));
    }
    return v;
  }

  static std::string printToString(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    EXPECT_NO_THROW({
      Exiv2::Internal::print0xa402(oss, v, md);
    });
    return oss.str();
  }
};

TEST_F(Print0xa402Test_1412, PrintsAutoForZero_NullMetadata_1412) {
  auto v = makeNumericValue(0);
  ASSERT_TRUE(v);

  const std::string out = printToString(*v, nullptr);
  EXPECT_NE(out.find("Auto"), std::string::npos);
}

TEST_F(Print0xa402Test_1412, PrintsManualForOne_NullMetadata_1412) {
  auto v = makeNumericValue(1);
  ASSERT_TRUE(v);

  const std::string out = printToString(*v, nullptr);
  EXPECT_NE(out.find("Manual"), std::string::npos);
}

TEST_F(Print0xa402Test_1412, PrintsAutoBracketForTwo_NullMetadata_1412) {
  auto v = makeNumericValue(2);
  ASSERT_TRUE(v);

  const std::string out = printToString(*v, nullptr);
  EXPECT_NE(out.find("Auto bracket"), std::string::npos);
}

TEST_F(Print0xa402Test_1412, WorksWithNonNullMetadata_1412) {
  auto v = makeNumericValue(1);
  ASSERT_TRUE(v);

  Exiv2::ExifData md;  // metadata is optional per interface; verify it can be non-null.
  const std::string out = printToString(*v, &md);

  // Observable expectation: still prints a human-readable label for known values.
  EXPECT_NE(out.find("Manual"), std::string::npos);
}

TEST_F(Print0xa402Test_1412, UnknownValueDoesNotMatchKnownLabels_1412) {
  auto v = makeNumericValue(3);
  ASSERT_TRUE(v);

  const std::string out = printToString(*v, nullptr);

  // We do not assume the exact formatting for unknown values; just that it
  // doesn't incorrectly claim one of the known labels.
  EXPECT_EQ(out.find("Auto bracket"), std::string::npos);
  EXPECT_EQ(out.find("Manual"), std::string::npos);

  // "Auto" is a substring of "Auto bracket"; to avoid false positives, check
  // it isn't *exactly* the known full strings.
  EXPECT_NE(out, "Auto");
  EXPECT_NE(out, "Manual");
  EXPECT_NE(out, "Auto bracket");
}

TEST_F(Print0xa402Test_1412, HandlesValueWithNonNumericInputGracefully_1412) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v);

  // read() error handling is implementation-defined; just ensure print function
  // remains safe/observable via stream output and no throw.
  (void)v->read(std::string("not-a-number"));

  std::ostringstream oss;
  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa402(oss, *v, nullptr);
  });

  // Output may be empty or some fallback; require only that stream is usable.
  EXPECT_TRUE(oss.good() || oss.eof());
}

TEST_F(Print0xa402Test_1412, HandlesDefaultConstructedValueObjectFromFactory_1412) {
  // Boundary-ish case: created value but no successful read performed.
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v);

  std::ostringstream oss;
  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa402(oss, *v, nullptr);
  });

  // Minimal observable check: call did not break the stream.
  EXPECT_TRUE(oss.good() || oss.eof());
}

}  // namespace