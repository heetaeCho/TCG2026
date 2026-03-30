// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_fuji_mn_header_test_id_1456.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "makernote_int.hpp"

namespace {

// Helper that avoids hard-coding any internal values.
static bool IsRecognizedByteOrder(Exiv2::ByteOrder bo) {
  return bo == Exiv2::invalidByteOrder || bo == Exiv2::littleEndian || bo == Exiv2::bigEndian;
}

class FujiMnHeaderTest_1456 : public ::testing::Test {};

}  // namespace

TEST_F(FujiMnHeaderTest_1456, DefaultConstructed_ByteOrderIsRecognized_1456) {
  Exiv2::Internal::FujiMnHeader header;
  const Exiv2::ByteOrder bo = header.byteOrder();
  EXPECT_TRUE(IsRecognizedByteOrder(bo));
}

TEST_F(FujiMnHeaderTest_1456, ByteOrderCallableOnConstObject_1456) {
  const Exiv2::Internal::FujiMnHeader header;
  EXPECT_NO_THROW((void)header.byteOrder());
  EXPECT_TRUE(IsRecognizedByteOrder(header.byteOrder()));
}

TEST_F(FujiMnHeaderTest_1456, ConstAndNonConstAccessReturnSameValue_1456) {
  Exiv2::Internal::FujiMnHeader header;
  const Exiv2::ByteOrder bo_nonconst = header.byteOrder();

  const Exiv2::Internal::FujiMnHeader& cheader = header;
  const Exiv2::ByteOrder bo_const = cheader.byteOrder();

  EXPECT_EQ(bo_nonconst, bo_const);
}

TEST_F(FujiMnHeaderTest_1456, CopyConstruction_PreservesByteOrder_1456) {
  Exiv2::Internal::FujiMnHeader original;
  const Exiv2::ByteOrder before = original.byteOrder();

  Exiv2::Internal::FujiMnHeader copy(original);
  EXPECT_EQ(copy.byteOrder(), before);
}

TEST_F(FujiMnHeaderTest_1456, CopyAssignment_PreservesByteOrder_1456) {
  Exiv2::Internal::FujiMnHeader original;
  const Exiv2::ByteOrder before = original.byteOrder();

  Exiv2::Internal::FujiMnHeader assigned;
  assigned = original;

  EXPECT_EQ(assigned.byteOrder(), before);
}

TEST_F(FujiMnHeaderTest_1456, MoveConstruction_WhenAvailable_PreservesByteOrder_1456) {
  using H = Exiv2::Internal::FujiMnHeader;
  if constexpr (std::is_move_constructible_v<H>) {
    H original;
    const Exiv2::ByteOrder before = original.byteOrder();

    H moved(std::move(original));
    EXPECT_EQ(moved.byteOrder(), before);
  } else {
    GTEST_SKIP() << "FujiMnHeader is not move-constructible.";
  }
}

TEST_F(FujiMnHeaderTest_1456, MoveAssignment_WhenAvailable_PreservesByteOrder_1456) {
  using H = Exiv2::Internal::FujiMnHeader;
  if constexpr (std::is_move_assignable_v<H>) {
    H original;
    const Exiv2::ByteOrder before = original.byteOrder();

    H target;
    target = std::move(original);

    EXPECT_EQ(target.byteOrder(), before);
  } else {
    GTEST_SKIP() << "FujiMnHeader is not move-assignable.";
  }
}