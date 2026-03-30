// =================================================================================================
// SPDX-License-Identifier: GPL-2.0-or-later
// =================================================================================================
// File:     test_sonymn_int_printFocusFrameSize_1603.cpp
// Author:   Generated unit tests
// Purpose:  Unit tests for Exiv2::Internal::SonyMakerNote::printFocusFrameSize
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

// Internal header for SonyMakerNote (expected to be available in the Exiv2 codebase)
#include "sonymn_int.hpp"

#include <array>
#include <sstream>
#include <string>

namespace {

class SonyMakerNotePrintFocusFrameSizeTest_1603 : public ::testing::Test {
 protected:
  Exiv2::Internal::SonyMakerNote mn_;

  static Exiv2::Value::AutoPtr makeUndefinedValue(const std::vector<Exiv2::byte>& bytes) {
    auto v = Exiv2::Value::create(Exiv2::undefined);
    EXPECT_NE(v.get(), nullptr);
    if (!v.get()) return v;

    // For "undefined" values, byte order is not expected to affect the raw byte storage,
    // but we pass a valid ByteOrder for API completeness.
    v->read(bytes.data(), static_cast<long>(bytes.size()), Exiv2::littleEndian);
    return v;
  }

  static std::string streamValueWrappedInParens(const Exiv2::Value& value) {
    std::ostringstream inner;
    inner << value;
    return "(" + inner.str() + ")";
  }
};

TEST_F(SonyMakerNotePrintFocusFrameSizeTest_1603, NonUndefinedType_WrapsValueInParentheses_1603) {
  // Arrange: Type is not "undefined" -> should return "(" << value << ")"
  auto v = Exiv2::Value::create(Exiv2::unsignedByte);
  ASSERT_NE(v.get(), nullptr);

  const std::vector<Exiv2::byte> bytes = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  v->read(bytes.data(), static_cast<long>(bytes.size()), Exiv2::littleEndian);

  std::ostringstream os;

  // Act
  mn_.printFocusFrameSize(os, *v, nullptr);

  // Assert
  EXPECT_EQ(os.str(), streamValueWrappedInParens(*v));
}

TEST_F(SonyMakerNotePrintFocusFrameSizeTest_1603, UndefinedButWrongCount_WrapsValueInParentheses_1603) {
  // Arrange: Type is "undefined" but count != 6 -> should return "(" << value << ")"
  auto v = makeUndefinedValue({0x01, 0x02, 0x03, 0x04, 0x05});  // 5 bytes
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;

  // Act
  mn_.printFocusFrameSize(os, *v, nullptr);

  // Assert
  EXPECT_EQ(os.str(), streamValueWrappedInParens(*v));
}

TEST_F(SonyMakerNotePrintFocusFrameSizeTest_1603, UndefinedCount6_LastTwoZero_PrintsNA_1603) {
  // Arrange: count == 6, type == undefined, and bytes[4]==0 && bytes[5]==0 -> "n/a"
  // First 4 bytes (width/height) are ignored when last two are zero.
  auto v = makeUndefinedValue({0x34, 0x12, 0x78, 0x56, 0x00, 0x00});
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;

  // Act
  mn_.printFocusFrameSize(os, *v, nullptr);

  // Assert
  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(SonyMakerNotePrintFocusFrameSizeTest_1603, UndefinedCount6_LastTwoNonZero_PrintsWidthAndHeight_1603) {
  // Arrange:
  // width  = (b1<<8)+b0, height=(b3<<8)+b2
  // Use width=0x1234=4660, height=0x5678=22136; last two non-zero to avoid "n/a".
  auto v = makeUndefinedValue({0x34, 0x12, 0x78, 0x56, 0x01, 0x00});
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;

  // Act (ExifData* not used by observable behavior here; pass nullptr)
  mn_.printFocusFrameSize(os, *v, nullptr);

  // Assert
  EXPECT_EQ(os.str(), "4660x22136");
}

TEST_F(SonyMakerNotePrintFocusFrameSizeTest_1603, UndefinedCount6_ZeroDimensionsButNotNA_Prints0x0_1603) {
  // Arrange: width=0, height=0, but last bytes make it not "n/a".
  auto v = makeUndefinedValue({0x00, 0x00, 0x00, 0x00, 0x00, 0x01});
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;

  // Act
  mn_.printFocusFrameSize(os, *v, nullptr);

  // Assert
  EXPECT_EQ(os.str(), "0x0");
}

}  // namespace