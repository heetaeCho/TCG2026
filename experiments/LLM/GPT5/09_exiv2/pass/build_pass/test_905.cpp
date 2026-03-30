// ***************************************************************** -*- C++ -*-
// Unit tests for OlympusMakerNote::print0x1209
// TEST_ID: 905
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

// Include the internal header that declares Exiv2::Internal::OlympusMakerNote.
// Adjust include path if your build uses a different internal header layout.
#include "olympusmn_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::unsignedShort;
using Exiv2::Value;

class OlympusMakerNoteTest_905 : public ::testing::Test {
protected:
  Exiv2::Internal::OlympusMakerNote mn_;

  static std::string StreamValueDirectly(const Value& v) {
    std::ostringstream os;
    os << v;
    return os.str();
  }

  static Value::UniquePtr MakeUShortValueFromString(const std::string& s) {
    auto v = Value::create(unsignedShort);
    v->read(s);
    return v;
  }
};

TEST_F(OlympusMakerNoteTest_905, StreamsValueDirectlyWhenCountIsNotTwo_905) {
  // count == 1
  auto v = MakeUShortValueFromString("0");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(1U, v->count());

  std::ostringstream os_actual;
  mn_.print0x1209(os_actual, *v, nullptr);

  // Compare against the observable baseline: streaming the value itself.
  EXPECT_EQ(os_actual.str(), StreamValueDirectly(*v));
}

TEST_F(OlympusMakerNoteTest_905, StreamsValueDirectlyWhenTypeIsNotUnsignedShort_905) {
  // Create a value with count==2 but a different type.
  auto v = Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);
  v->read("0 7");
  ASSERT_EQ(2U, v->count());
  ASSERT_NE(unsignedShort, v->typeId());

  std::ostringstream os_actual;
  mn_.print0x1209(os_actual, *v, nullptr);

  EXPECT_EQ(os_actual.str(), StreamValueDirectly(*v));
}

TEST_F(OlympusMakerNoteTest_905, PrintsOffAndSecondValueWhenFirstIsZero_905) {
  auto v = MakeUShortValueFromString("0 5");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(2U, v->count());
  ASSERT_EQ(unsignedShort, v->typeId());

  std::ostringstream os_actual;
  mn_.print0x1209(os_actual, *v, nullptr);

  EXPECT_EQ(os_actual.str(), std::string("Off 5"));
}

TEST_F(OlympusMakerNoteTest_905, PrintsOnAndSecondValueWhenFirstIsOne_905) {
  auto v = MakeUShortValueFromString("1 9");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(2U, v->count());
  ASSERT_EQ(unsignedShort, v->typeId());

  std::ostringstream os_actual;
  mn_.print0x1209(os_actual, *v, nullptr);

  EXPECT_EQ(os_actual.str(), std::string("On 9"));
}

TEST_F(OlympusMakerNoteTest_905, PrintsNumericFirstValueWhenFirstIsNeitherZeroNorOne_905) {
  auto v = MakeUShortValueFromString("42 7");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(2U, v->count());
  ASSERT_EQ(unsignedShort, v->typeId());

  std::ostringstream os_actual;
  mn_.print0x1209(os_actual, *v, nullptr);

  EXPECT_EQ(os_actual.str(), std::string("42 7"));
}

TEST_F(OlympusMakerNoteTest_905, AcceptsNullExifDataPointer_905) {
  auto v = MakeUShortValueFromString("0 1");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os_actual;
  EXPECT_NO_THROW({ mn_.print0x1209(os_actual, *v, nullptr); });
  EXPECT_EQ(os_actual.str(), std::string("Off 1"));
}

TEST_F(OlympusMakerNoteTest_905, AcceptsNonNullExifDataPointer_905) {
  auto v = MakeUShortValueFromString("1 2");
  ASSERT_NE(v.get(), nullptr);

  ExifData exif; // Not used by the interface, but should be accepted.
  std::ostringstream os_actual;
  EXPECT_NO_THROW({ mn_.print0x1209(os_actual, *v, &exif); });
  EXPECT_EQ(os_actual.str(), std::string("On 2"));
}

TEST_F(OlympusMakerNoteTest_905, BoundaryValuesForUnsignedShortArePrintedNumerically_905) {
  // Use maximum unsigned short for the first field to exercise boundary printing.
  auto v = MakeUShortValueFromString("65535 0");
  ASSERT_NE(v.get(), nullptr);
  ASSERT_EQ(2U, v->count());
  ASSERT_EQ(unsignedShort, v->typeId());

  std::ostringstream os_actual;
  mn_.print0x1209(os_actual, *v, nullptr);

  EXPECT_EQ(os_actual.str(), std::string("65535 0"));
}

}  // namespace