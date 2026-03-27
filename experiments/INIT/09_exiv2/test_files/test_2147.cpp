// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_slice_containerstorage_2147.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <stdexcept>

#include "exiv2/slice.hpp"

namespace {

using Exiv2::Internal::ContainerStorage;
using Exiv2::Internal::container;

class ContainerStorageTest_2147 : public ::testing::Test {};

TEST_F(ContainerStorageTest_2147, ConstructDoesNotThrowWhenEndLessThanSize_2147) {
  container data;
  data.resize(10);

  EXPECT_NO_THROW((ContainerStorage{data, /*begin*/ 0u, /*end*/ 9u}));
}

TEST_F(ContainerStorageTest_2147, ConstructDoesNotThrowWhenEndEqualsSize_2147) {
  container data;
  data.resize(10);

  EXPECT_NO_THROW((ContainerStorage{data, /*begin*/ 0u, /*end*/ data.size()}));
}

TEST_F(ContainerStorageTest_2147, ConstructDoesNotThrowWhenEndIsZeroOnNonEmpty_2147) {
  container data;
  data.resize(3);

  EXPECT_NO_THROW((ContainerStorage{data, /*begin*/ 0u, /*end*/ 0u}));
}

TEST_F(ContainerStorageTest_2147, ConstructDoesNotThrowWhenEndIsZeroOnEmpty_2147) {
  container data;  // size() == 0

  EXPECT_NO_THROW((ContainerStorage{data, /*begin*/ 0u, /*end*/ 0u}));
}

TEST_F(ContainerStorageTest_2147, ConstructThrowsOutOfRangeWhenEndGreaterThanSize_2147) {
  container data;
  data.resize(5);

  EXPECT_THROW((ContainerStorage{data, /*begin*/ 0u, /*end*/ data.size() + 1u}),
               std::out_of_range);
}

TEST_F(ContainerStorageTest_2147, ConstructThrowsOutOfRangeWhenEndOneOnEmpty_2147) {
  container data;  // size() == 0

  EXPECT_THROW((ContainerStorage{data, /*begin*/ 0u, /*end*/ 1u}), std::out_of_range);
}

}  // namespace