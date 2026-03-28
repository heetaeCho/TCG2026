// TEST_ID: 1408
// File: test_tags_int_print0xa217_1408.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

namespace Exiv2 {
namespace Internal {
// Function under test (implemented in src/tags_int.cpp)
std::ostream& print0xa217(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0xa217Test_1408 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr MakeUShortValue(const std::string& s) {
    // Treat as black-box: create a Value using the public factory and populate via read(string).
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    // read() returns int; we only assert it doesn't obviously fail (<0).
    const int rc = v->read(s);
    EXPECT_GE(rc, 0);
    return v;
  }

  static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    EXPECT_NE(v.get(), nullptr);
    const int rc = v->read(s);
    EXPECT_GE(rc, 0);
    return v;
  }

  static std::string PrintToString(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    Exiv2::Internal::print0xa217(oss, v, md);
    return oss.str();
  }
};

TEST_F(Print0xa217Test_1408, ReturnsSameStreamReference_1408) {
  auto v = MakeUShortValue("2");
  std::ostringstream oss;
  std::ostream& out = Exiv2::Internal::print0xa217(oss, *v, nullptr);
  EXPECT_EQ(&out, &oss);
}

TEST_F(Print0xa217Test_1408, PrintsKnownMapping_NotDefined_1408) {
  auto v = MakeUShortValue("1");
  EXPECT_EQ(PrintToString(*v, nullptr), std::string("Not defined"));
}

TEST_F(Print0xa217Test_1408, PrintsKnownMapping_OneChipColorArea_1408) {
  auto v = MakeUShortValue("2");
  EXPECT_EQ(PrintToString(*v, nullptr), std::string("One-chip color area"));
}

TEST_F(Print0xa217Test_1408, PrintsKnownMapping_TwoChipColorArea_1408) {
  auto v = MakeUShortValue("3");
  EXPECT_EQ(PrintToString(*v, nullptr), std::string("Two-chip color area"));
}

TEST_F(Print0xa217Test_1408, PrintsKnownMapping_ThreeChipColorArea_1408) {
  auto v = MakeUShortValue("4");
  EXPECT_EQ(PrintToString(*v, nullptr), std::string("Three-chip color area"));
}

TEST_F(Print0xa217Test_1408, PrintsKnownMapping_ColorSequentialArea_1408) {
  auto v = MakeUShortValue("5");
  EXPECT_EQ(PrintToString(*v, nullptr), std::string("Color sequential area"));
}

TEST_F(Print0xa217Test_1408, PrintsKnownMapping_TrilinearSensor_1408) {
  auto v = MakeUShortValue("7");
  EXPECT_EQ(PrintToString(*v, nullptr), std::string("Trilinear sensor"));
}

TEST_F(Print0xa217Test_1408, PrintsKnownMapping_ColorSequentialLinear_1408) {
  auto v = MakeUShortValue("8");
  EXPECT_EQ(PrintToString(*v, nullptr), std::string("Color sequential linear"));
}

TEST_F(Print0xa217Test_1408, UnknownValue_StillProducesSomeOutput_1408) {
  auto v = MakeUShortValue("6");  // not present in known TagDetails list
  const std::string out = PrintToString(*v, nullptr);

  // Black-box friendly: don't assume exact formatting for unknowns, but ensure something is produced.
  EXPECT_FALSE(out.empty());
  // Commonly, unknown prints the numeric code; accept either case by requiring it to mention '6'.
  EXPECT_NE(out.find('6'), std::string::npos);
}

TEST_F(Print0xa217Test_1408, BoundaryValue_Zero_StillProducesSomeOutput_1408) {
  auto v = MakeUShortValue("0");
  const std::string out = PrintToString(*v, nullptr);
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find('0'), std::string::npos);
}

TEST_F(Print0xa217Test_1408, BoundaryValue_LargeNumber_StillProducesSomeOutput_1408) {
  auto v = MakeUShortValue("65535");
  const std::string out = PrintToString(*v, nullptr);
  EXPECT_FALSE(out.empty());
  // Do not assume formatting beyond it reflecting the value in some way.
  EXPECT_NE(out.find("65535"), std::string::npos);
}

TEST_F(Print0xa217Test_1408, MetadataPointerProvided_DoesNotBreakPrinting_1408) {
  auto v = MakeUShortValue("2");
  Exiv2::ExifData md;  // empty metadata is fine; we only verify observable output stability

  const std::string out_with_md = PrintToString(*v, &md);
  const std::string out_without_md = PrintToString(*v, nullptr);

  EXPECT_EQ(out_with_md, out_without_md);
  EXPECT_EQ(out_with_md, std::string("One-chip color area"));
}

TEST_F(Print0xa217Test_1408, DifferentValueType_DoesNotThrowAndProducesOutput_1408) {
  // Use an alternate Value type via public factory (no internal assumptions).
  auto v = MakeAsciiValue("2");
  const std::string out = PrintToString(*v, nullptr);

  // Black-box assertions: should not crash; output should be non-empty.
  EXPECT_FALSE(out.empty());
}

}  // namespace