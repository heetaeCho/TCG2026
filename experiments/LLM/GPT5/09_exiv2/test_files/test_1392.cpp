// TEST_ID 1392
// Unit tests for Exiv2::Internal::print0x0112 (Orientation tag printer)

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

// The function under test is implemented in src/tags_int.cpp.
// It is typically declared in Exiv2's internal tags header.
#include "tags_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ByteOrder;
using Exiv2::TypeId;
using Exiv2::Value;

class Print0x0112Test_1392 : public ::testing::Test {
 protected:
  static Value::UniquePtr MakeUShortValueFromInt(int v) {
    auto val = Value::create(TypeId::unsignedShort);
    // Value::read(const std::string&) is part of the public interface.
    // Using it avoids relying on any specific concrete Value type.
    const int rc = val->read(std::to_string(v));
    EXPECT_EQ(0, rc);
    EXPECT_TRUE(val->ok());
    return val;
  }
};

TEST_F(Print0x0112Test_1392, ReturnsSameStreamReference_1392) {
  auto v = MakeUShortValueFromInt(1);

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::print0x0112(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.fail());
}

TEST_F(Print0x0112Test_1392, PrintsExpectedStringForValue1_TopLeft_1392) {
  auto v = MakeUShortValueFromInt(1);

  std::ostringstream os;
  Exiv2::Internal::print0x0112(os, *v, nullptr);

  const std::string out = os.str();
  EXPECT_NE(std::string::npos, out.find("top, left"));
}

TEST_F(Print0x0112Test_1392, PrintsExpectedStringForValue8_LeftBottom_1392) {
  auto v = MakeUShortValueFromInt(8);

  std::ostringstream os;
  Exiv2::Internal::print0x0112(os, *v, nullptr);

  const std::string out = os.str();
  EXPECT_NE(std::string::npos, out.find("left, bottom"));
}

TEST_F(Print0x0112Test_1392, PrintsExpectedStringForValue6_RightTop_1392) {
  auto v = MakeUShortValueFromInt(6);

  std::ostringstream os;
  Exiv2::Internal::print0x0112(os, *v, nullptr);

  const std::string out = os.str();
  EXPECT_NE(std::string::npos, out.find("right, top"));
}

TEST_F(Print0x0112Test_1392, AcceptsNonNullMetadataPointer_1392) {
  // The metadata pointer is part of the interface. This test only checks the call is safe
  // and produces output; it does not assume metadata-dependent formatting.
  Exiv2::ExifData md;
  auto v = MakeUShortValueFromInt(3);

  std::ostringstream os;
  EXPECT_NO_THROW({
    Exiv2::Internal::print0x0112(os, *v, &md);
  });

  EXPECT_FALSE(os.fail());
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Print0x0112Test_1392, OutOfRangeValueDoesNotThrowAndProducesSomeOutput_1392) {
  // Out-of-range values are possible (e.g., corrupted metadata). We only assert the function
  // is robust and produces *some* observable output.
  for (int invalid : {0, 9, 65535}) {
    auto v = MakeUShortValueFromInt(invalid);

    std::ostringstream os;
    EXPECT_NO_THROW({
      Exiv2::Internal::print0x0112(os, *v, nullptr);
    }) << "invalid=" << invalid;

    EXPECT_FALSE(os.fail()) << "invalid=" << invalid;
    EXPECT_FALSE(os.str().empty()) << "invalid=" << invalid;
  }
}

}  // namespace