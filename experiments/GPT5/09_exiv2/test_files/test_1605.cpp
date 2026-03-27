// File: test_sonymn_printColorCompensationFilter_1605.cpp
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Internal header for SonyMakerNote (adjust include if your tree differs)
#include "sonymn_int.hpp"

#include <cstdint>
#include <memory>
#include <sstream>
#include <string>

namespace {

using Exiv2::Internal::SonyMakerNote;

// Helper: create a Value of given type and initialize by calling read() with a text list.
static Exiv2::Value::UniquePtr MakeValue(Exiv2::TypeId type, const std::string& text) {
  auto v = Exiv2::Value::create(type);
  // Exiv2::Value::read() is part of the public interface; treat it as a black box initializer.
  v->read(text);
  return v;
}

static std::string StreamValue(const Exiv2::Value& v) {
  std::ostringstream os;
  os << v;
  return os.str();
}

}  // namespace

TEST(SonyMakerNotePrintColorCompensationFilterTest_1605, ReturnsParenthesizedValueWhenCountNotOne_1605) {
  SonyMakerNote mn;

  // count != 1
  auto v = MakeValue(Exiv2::unsignedLong, "1 2");
  const std::string inner = StreamValue(*v);

  std::ostringstream os;
  mn.printColorCompensationFilter(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST(SonyMakerNotePrintColorCompensationFilterTest_1605, ReturnsParenthesizedValueWhenTypeNotUnsignedLong_1605) {
  SonyMakerNote mn;

  // typeId != unsignedLong
  auto v = MakeValue(Exiv2::unsignedShort, "1");
  const std::string inner = StreamValue(*v);

  std::ostringstream os;
  mn.printColorCompensationFilter(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST(SonyMakerNotePrintColorCompensationFilterTest_1605, PrintsZeroWhenValueIsZero_1605) {
  SonyMakerNote mn;

  auto v = MakeValue(Exiv2::unsignedLong, "0");

  std::ostringstream os;
  mn.printColorCompensationFilter(os, *v, nullptr);

  EXPECT_EQ(os.str(), "G/M: 0");
}

TEST(SonyMakerNotePrintColorCompensationFilterTest_1605, PrintsMForPositiveValues_1605) {
  SonyMakerNote mn;

  auto v = MakeValue(Exiv2::unsignedLong, "5");

  std::ostringstream os;
  mn.printColorCompensationFilter(os, *v, nullptr);

  EXPECT_EQ(os.str(), "G/M: M5");
}

TEST(SonyMakerNotePrintColorCompensationFilterTest_1605, PrintsGForNegativeValuesViaTwoComplement_1605) {
  SonyMakerNote mn;

  // 0xFFFFFFFF interpreted as int32_t becomes -1
  auto v = MakeValue(Exiv2::unsignedLong, "4294967295");

  std::ostringstream os;
  mn.printColorCompensationFilter(os, *v, nullptr);

  EXPECT_EQ(os.str(), "G/M: G1");
}

TEST(SonyMakerNotePrintColorCompensationFilterTest_1605, HandlesInt32MinMagnitudeBoundary_1605) {
  SonyMakerNote mn;

  // 0x80000000 interpreted as int32_t becomes INT32_MIN (-2147483648)
  auto v = MakeValue(Exiv2::unsignedLong, "2147483648");

  std::ostringstream os;
  mn.printColorCompensationFilter(os, *v, nullptr);

  EXPECT_EQ(os.str(), "G/M: G2147483648");
}