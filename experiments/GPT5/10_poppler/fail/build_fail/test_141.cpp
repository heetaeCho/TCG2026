// SPDX-License-Identifier: GPL-2.0-or-later
// File: FilterStream_getUndecodedStream_tests_141.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "poppler/Stream.h"

using ::testing::NiceMock;
using ::testing::Return;

namespace {

class MockStream_141 : public Stream {
public:
  MockStream_141() = default;
  ~MockStream_141() override = default;

  MOCK_METHOD(Stream *, getUndecodedStream, (), (override));
};

class FilterStreamTest_141 : public ::testing::Test {};

TEST_F(FilterStreamTest_141, GetUndecodedStream_ForwardsCallAndReturnsValue_141) {
  auto *inner = new NiceMock<MockStream_141>();
  ::testing::Mock::AllowLeak(inner);

  auto *expected = new NiceMock<MockStream_141>();
  ::testing::Mock::AllowLeak(expected);

  EXPECT_CALL(*inner, getUndecodedStream()).Times(1).WillOnce(Return(expected));

  FilterStream fs(inner);
  EXPECT_EQ(fs.getUndecodedStream(), expected);
}

TEST_F(FilterStreamTest_141, GetUndecodedStream_ForwardedNullptrIsReturned_141) {
  auto *inner = new NiceMock<MockStream_141>();
  ::testing::Mock::AllowLeak(inner);

  EXPECT_CALL(*inner, getUndecodedStream()).Times(1).WillOnce(Return(nullptr));

  FilterStream fs(inner);
  EXPECT_EQ(fs.getUndecodedStream(), nullptr);
}

TEST_F(FilterStreamTest_141, GetUndecodedStream_MultipleCallsForwardEachTime_141) {
  auto *inner = new NiceMock<MockStream_141>();
  ::testing::Mock::AllowLeak(inner);

  auto *first = new NiceMock<MockStream_141>();
  ::testing::Mock::AllowLeak(first);

  EXPECT_CALL(*inner, getUndecodedStream())
      .Times(2)
      .WillOnce(Return(first))
      .WillOnce(Return(nullptr));

  FilterStream fs(inner);

  EXPECT_EQ(fs.getUndecodedStream(), first);
  EXPECT_EQ(fs.getUndecodedStream(), nullptr);
}

} // namespace