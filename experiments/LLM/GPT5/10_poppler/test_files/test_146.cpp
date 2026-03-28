// SPDX-License-Identifier: GPL-2.0-or-later
// File: FilterStream_unfilteredRewind_tests_146.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "poppler/Stream.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockStream_146 : public Stream {
public:
  MockStream_146() = default;
  ~MockStream_146() override = default;

  MOCK_METHOD(bool, unfilteredRewind, (), (override));
};

class FilterStreamTest_146 : public ::testing::Test {};

TEST_F(FilterStreamTest_146, UnfilteredRewind_PropagatesTrue_146) {
  auto *mock = new StrictMock<MockStream_146>();
  ::testing::Mock::AllowLeak(mock); // ownership may be taken by FilterStream

  FilterStream fs(mock);

  EXPECT_CALL(*mock, unfilteredRewind()).Times(1).WillOnce(Return(true));
  EXPECT_TRUE(fs.unfilteredRewind());
}

TEST_F(FilterStreamTest_146, UnfilteredRewind_PropagatesFalse_146) {
  auto *mock = new StrictMock<MockStream_146>();
  ::testing::Mock::AllowLeak(mock);

  FilterStream fs(mock);

  EXPECT_CALL(*mock, unfilteredRewind()).Times(1).WillOnce(Return(false));
  EXPECT_FALSE(fs.unfilteredRewind());
}

TEST_F(FilterStreamTest_146, UnfilteredRewind_ForwardsEachCall_146) {
  auto *mock = new StrictMock<MockStream_146>();
  ::testing::Mock::AllowLeak(mock);

  FilterStream fs(mock);

  EXPECT_CALL(*mock, unfilteredRewind())
      .Times(3)
      .WillOnce(Return(true))
      .WillOnce(Return(false))
      .WillOnce(Return(true));

  EXPECT_TRUE(fs.unfilteredRewind());
  EXPECT_FALSE(fs.unfilteredRewind());
  EXPECT_TRUE(fs.unfilteredRewind());
}

} // namespace