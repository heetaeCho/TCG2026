// FilterStream_getUnfilteredChar_145_test.cpp
// Unit tests for FilterStream::getUnfilteredChar (TEST_ID=145)

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "poppler/Stream.h"

using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockStream final : public Stream {
public:
  MockStream() = default;
  ~MockStream() override = default;

  MOCK_METHOD(int, getUnfilteredChar, (), (override));
};

class FilterStreamTest_145 : public ::testing::Test {};

TEST_F(FilterStreamTest_145, GetUnfilteredChar_ForwardsCallAndReturnsValue_145) {
  auto *mock = new StrictMock<MockStream>();
  FilterStream fs(mock);

  EXPECT_CALL(*mock, getUnfilteredChar()).WillOnce(Return(42));

  EXPECT_EQ(fs.getUnfilteredChar(), 42);
}

TEST_F(FilterStreamTest_145, GetUnfilteredChar_ForwardsMultipleCallsInOrder_145) {
  auto *mock = new StrictMock<MockStream>();
  FilterStream fs(mock);

  InSequence seq;
  EXPECT_CALL(*mock, getUnfilteredChar()).WillOnce(Return(0));
  EXPECT_CALL(*mock, getUnfilteredChar()).WillOnce(Return(255));
  EXPECT_CALL(*mock, getUnfilteredChar()).WillOnce(Return(7));

  EXPECT_EQ(fs.getUnfilteredChar(), 0);
  EXPECT_EQ(fs.getUnfilteredChar(), 255);
  EXPECT_EQ(fs.getUnfilteredChar(), 7);
}

TEST_F(FilterStreamTest_145, GetUnfilteredChar_PropagatesEOFOrErrorValues_145) {
  auto *mock = new StrictMock<MockStream>();
  FilterStream fs(mock);

  EXPECT_CALL(*mock, getUnfilteredChar()).WillOnce(Return(-1));

  EXPECT_EQ(fs.getUnfilteredChar(), -1);
}

} // namespace