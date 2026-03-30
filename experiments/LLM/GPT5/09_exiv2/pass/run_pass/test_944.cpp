// File: test_canonmn_int_print0x000a_944.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2
#include "canonmn_int.hpp"   // Exiv2::Internal::CanonMakerNote
#include "exif.hpp"          // Exiv2::ExifData
#include "value.hpp"         // Exiv2::Value, Exiv2::TypeId, Exiv2::Value::create

namespace {

class CanonMakerNotePrint0x000aTest_944 : public ::testing::Test {
protected:
  Exiv2::Internal::CanonMakerNote sut_{};

  static Exiv2::Value::UniquePtr makeValueFromString(const std::string& s) {
    // Use a real Exiv2 Value implementation (no mocking).
    // The function under test calls value.toString(), so any Value that can be read from a string works.
    auto v = Exiv2::Value::create(Exiv2::unsignedLong);
    if (!v) {
      // Fallback: some builds may not support unsignedLong via create().
      // Try asciiString as a minimal string-based Value type.
      v = Exiv2::Value::create(Exiv2::asciiString);
    }
    EXPECT_TRUE(static_cast<bool>(v));
    v->read(s);
    return v;
  }
};

TEST_F(CanonMakerNotePrint0x000aTest_944, FormatsHigh16BitsHexAndLow16BitsDecimal_944) {
  auto v = makeValueFromString("65536");  // 0x00010000 => high=0x0001, low=0

  std::ostringstream os;
  auto& ret = sut_.print0x000a(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "000100000"); // "0001" + "00000"
}

TEST_F(CanonMakerNotePrint0x000aTest_944, PreservesExistingStreamContentByAppending_944) {
  auto v = makeValueFromString("1"); // 0x00000001 => "0000" + "00001"

  std::ostringstream os;
  os << "prefix:";
  sut_.print0x000a(os, *v, nullptr);

  EXPECT_EQ(os.str(), "prefix:000000001");
}

TEST_F(CanonMakerNotePrint0x000aTest_944, HandlesLeadingZerosInInputString_944) {
  auto v = makeValueFromString("00001");

  std::ostringstream os;
  sut_.print0x000a(os, *v, nullptr);

  EXPECT_EQ(os.str(), "000000001");
}

TEST_F(CanonMakerNotePrint0x000aTest_944, FormatsMaxUint32Value_944) {
  auto v = makeValueFromString("4294967295"); // 0xFFFFFFFF => "ffff" + "65535"

  std::ostringstream os;
  sut_.print0x000a(os, *v, nullptr);

  EXPECT_EQ(os.str(), "ffff65535");
}

TEST_F(CanonMakerNotePrint0x000aTest_944, ThrowsOnNonNumericValueString_944) {
  // Use asciiString to ensure toString() yields the non-numeric token.
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(static_cast<bool>(v));
  v->read("abc");

  std::ostringstream os;
  EXPECT_THROW((void)sut_.print0x000a(os, *v, nullptr), std::exception);
}

TEST_F(CanonMakerNotePrint0x000aTest_944, ThrowsOnOutOfRangeNumericValueString_944) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(static_cast<bool>(v));
  v->read("999999999999999999999999999999999999");

  std::ostringstream os;
  EXPECT_THROW((void)sut_.print0x000a(os, *v, nullptr), std::exception);
}

} // namespace