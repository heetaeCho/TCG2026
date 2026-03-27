// HtmlOutputDev_DevType_test_2711.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Adjust include path if your build uses a different include layout.
#include "TestProjects/poppler/utils/HtmlOutputDev.h"

using ::testing::Return;

namespace {

class HtmlOutputDevTest_2711 : public ::testing::Test {};

// Normal operation: returns the documented constant.
TEST_F(HtmlOutputDevTest_2711, DevTypeReturns1234_2711) {
  HtmlOutputDev dev;
  EXPECT_EQ(1234, dev.DevType());
}

// Normal operation: virtual call through a base pointer.
TEST_F(HtmlOutputDevTest_2711, DevTypeVirtualDispatchThroughPointer_2711) {
  HtmlOutputDev dev;
  HtmlOutputDev* as_ptr = &dev;
  EXPECT_EQ(1234, as_ptr->DevType());
}

// Boundary-ish: calling multiple times should be stable/consistent via observable behavior.
TEST_F(HtmlOutputDevTest_2711, DevTypeIsStableAcrossMultipleCalls_2711) {
  HtmlOutputDev dev;
  const int first = dev.DevType();
  const int second = dev.DevType();
  EXPECT_EQ(first, second);
  EXPECT_EQ(1234, first);
}

// Verifies it is actually virtual/overridable (observable via polymorphism).
TEST_F(HtmlOutputDevTest_2711, DevTypeCanBeOverridden_2711) {
  class DerivedHtmlOutputDev : public HtmlOutputDev {
   public:
    int DevType() override { return 5678; }
  };

  DerivedHtmlOutputDev derived;
  HtmlOutputDev* as_base = &derived;

  EXPECT_EQ(5678, as_base->DevType());
}

// Verification of external interactions: use a mock override and ensure it's invoked.
class MockHtmlOutputDev_2711 : public HtmlOutputDev {
 public:
  MOCK_METHOD(int, DevType, (), (override));
};

TEST_F(HtmlOutputDevTest_2711, DevTypeCallsMockOverride_2711) {
  MockHtmlOutputDev_2711 mock;

  EXPECT_CALL(mock, DevType()).Times(1).WillOnce(Return(42));

  HtmlOutputDev* as_base = &mock;
  EXPECT_EQ(42, as_base->DevType());
}

}  // namespace