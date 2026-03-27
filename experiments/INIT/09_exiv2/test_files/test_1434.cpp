// File: test_makernote_int_mnheader_test_1434.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "makernote_int.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;
using Exiv2::bigEndian;
using Exiv2::Internal::MnHeader;

class MnHeaderTest_1434 : public ::testing::Test {};

TEST_F(MnHeaderTest_1434, IsNotCopyableOrAssignable_1434) {
  static_assert(!std::is_copy_constructible_v<MnHeader>, "MnHeader must not be copy-constructible");
  static_assert(!std::is_copy_assignable_v<MnHeader>, "MnHeader must not be copy-assignable");
}

TEST_F(MnHeaderTest_1434, ByteOrderDefaultIsInvalid_1434) {
  MnHeader h;
  const MnHeader& ch = h;
  EXPECT_EQ(ch.byteOrder(), invalidByteOrder);
}

TEST_F(MnHeaderTest_1434, ByteOrderRepeatedCallsAreConsistent_1434) {
  MnHeader h;
  const MnHeader& ch = h;
  const ByteOrder b1 = ch.byteOrder();
  const ByteOrder b2 = ch.byteOrder();
  const ByteOrder b3 = ch.byteOrder();
  EXPECT_EQ(b1, invalidByteOrder);
  EXPECT_EQ(b2, invalidByteOrder);
  EXPECT_EQ(b3, invalidByteOrder);
}

TEST_F(MnHeaderTest_1434, ByteOrderUnaffectedBySetByteOrderCalls_1434) {
  MnHeader h;
  h.setByteOrder(littleEndian);
  EXPECT_EQ(h.byteOrder(), invalidByteOrder);

  h.setByteOrder(bigEndian);
  EXPECT_EQ(h.byteOrder(), invalidByteOrder);

  h.setByteOrder(invalidByteOrder);
  EXPECT_EQ(h.byteOrder(), invalidByteOrder);
}

}  // namespace