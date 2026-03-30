// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "exiv2/slice.hpp"

namespace {

using Exiv2::Internal::PtrSliceStorage;

TEST(PtrSliceStorageTest_2148, NullptrThrowsInvalidArgument_2148) {
  EXPECT_THROW((void)PtrSliceStorage(nullptr, 0u, 0u), std::invalid_argument);
}

TEST(PtrSliceStorageTest_2148, NonNullPointerDoesNotThrow_2148) {
  std::uint8_t buf[1] = {0};
  EXPECT_NO_THROW((void)PtrSliceStorage(buf, 0u, 1u));
}

TEST(PtrSliceStorageTest_2148, NonNullPointerAllowsZeroLengthSlice_2148) {
  std::uint8_t buf[4] = {0, 1, 2, 3};
  EXPECT_NO_THROW((void)PtrSliceStorage(buf, 0u, 0u));
}

TEST(PtrSliceStorageTest_2148, NonNullPointerAllowsLargeIndices_2148) {
  std::uint8_t buf[2] = {0, 0};
  EXPECT_NO_THROW((void)PtrSliceStorage(buf, 0u, static_cast<size_t>(-1)));
}

TEST(PtrSliceStorageTest_2148, NonNullPointerWithBeginGreaterThanEndDoesNotThrow_2148) {
  std::uint8_t buf[3] = {0, 0, 0};
  EXPECT_NO_THROW((void)PtrSliceStorage(buf, 2u, 1u));
}

}  // namespace