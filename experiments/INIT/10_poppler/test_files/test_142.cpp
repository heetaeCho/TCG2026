// -*- mode: c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// The TEST_ID is 142
//
// Unit tests for FilterStream::getDict (black-box; verifies observable forwarding behavior)

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "poppler/Stream.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MockStream final : public Stream {
public:
  MockStream() = default;
  ~MockStream() override = default;

  MOCK_METHOD(Dict *, getDict, (), (override));
};

class FilterStreamTest_142 : public ::testing::Test {};

TEST_F(FilterStreamTest_142, GetDict_ForwardsCallAndReturnsPointer_142) {
  // Use a non-null sentinel pointer without dereferencing.
  auto *expected = reinterpret_cast<Dict *>(0x1234);

  auto *underlying = new StrictMock<MockStream>();
  EXPECT_CALL(*underlying, getDict()).WillOnce(Return(expected));

  FilterStream fs(underlying);
  EXPECT_EQ(fs.getDict(), expected);
}

TEST_F(FilterStreamTest_142, GetDict_ForwardsNullptr_142) {
  auto *underlying = new StrictMock<MockStream>();
  EXPECT_CALL(*underlying, getDict()).WillOnce(Return(nullptr));

  FilterStream fs(underlying);
  EXPECT_EQ(fs.getDict(), nullptr);
}

TEST_F(FilterStreamTest_142, GetDict_MultipleCallsForwardEachTime_142) {
  auto *d1 = reinterpret_cast<Dict *>(0x1111);
  auto *d2 = reinterpret_cast<Dict *>(0x2222);

  auto *underlying = new StrictMock<MockStream>();
  EXPECT_CALL(*underlying, getDict()).WillOnce(Return(d1)).WillOnce(Return(d2));

  FilterStream fs(underlying);
  EXPECT_EQ(fs.getDict(), d1);
  EXPECT_EQ(fs.getDict(), d2);
}

} // namespace