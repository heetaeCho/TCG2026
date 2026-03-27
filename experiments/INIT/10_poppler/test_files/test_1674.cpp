// MarkedContentOutputDev_test_1674.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MarkedContentOutputDev.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

class MarkedContentOutputDevTest_1674 : public ::testing::Test {};

// A simple derived type to validate virtual dispatch without inferring internals.
class DerivedMarkedContentOutputDev_1674 : public MarkedContentOutputDev {
public:
  bool isOk() override { return false; }
};

// A mock to verify the observable external interaction: the virtual method is invoked.
class MockMarkedContentOutputDev_1674 : public MarkedContentOutputDev {
public:
  MOCK_METHOD(bool, isOk, (), (override));
};

TEST_F(MarkedContentOutputDevTest_1674, DefaultIsOkReturnsTrue_1674) {
  MarkedContentOutputDev dev;
  EXPECT_TRUE(dev.isOk());
}

TEST_F(MarkedContentOutputDevTest_1674, IsOkReturnsTrueOnRepeatedCalls_1674) {
  MarkedContentOutputDev dev;
  EXPECT_TRUE(dev.isOk());
  EXPECT_TRUE(dev.isOk());
  EXPECT_TRUE(dev.isOk());
}

TEST_F(MarkedContentOutputDevTest_1674, IsOkIsVirtualAndDispatchesToDerivedOverride_1674) {
  DerivedMarkedContentOutputDev_1674 derived;
  MarkedContentOutputDev* base = &derived;

  // Observable behavior: calling through base pointer should hit the override.
  EXPECT_FALSE(base->isOk());
}

TEST_F(MarkedContentOutputDevTest_1674, IsOkInvocationCanBeVerifiedWithMockThroughBasePointer_1674) {
  StrictMock<MockMarkedContentOutputDev_1674> mock;
  MarkedContentOutputDev* base = &mock;

  EXPECT_CALL(mock, isOk()).Times(2).WillRepeatedly(Return(true));

  EXPECT_TRUE(base->isOk());
  EXPECT_TRUE(base->isOk());
}

}  // namespace