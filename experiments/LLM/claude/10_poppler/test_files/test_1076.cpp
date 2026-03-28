#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// Since OutputDev methods are virtual, we can test the default implementations directly
// and also test that derived classes can override them.

class OutputDevTest_1076 : public ::testing::Test {
protected:
    OutputDev dev;
};

// Test default implementation of checkTransparencyGroup with knockout=true
TEST_F(OutputDevTest_1076, CheckTransparencyGroupKnockoutTrue_1076) {
    bool result = dev.checkTransparencyGroup(nullptr, true);
    EXPECT_TRUE(result);
}

// Test default implementation of checkTransparencyGroup with knockout=false
TEST_F(OutputDevTest_1076, CheckTransparencyGroupKnockoutFalse_1076) {
    bool result = dev.checkTransparencyGroup(nullptr, false);
    EXPECT_TRUE(result);
}

// Test default implementation with nullptr state
TEST_F(OutputDevTest_1076, CheckTransparencyGroupNullState_1076) {
    bool result = dev.checkTransparencyGroup(nullptr, false);
    EXPECT_TRUE(result);
}

// Test that the method is virtual and can be overridden
class MockOutputDev : public OutputDev {
public:
    MOCK_METHOD(bool, checkTransparencyGroup, (GfxState*, bool), (override));
};

TEST_F(OutputDevTest_1076, CheckTransparencyGroupCanBeOverridden_1076) {
    MockOutputDev mockDev;
    EXPECT_CALL(mockDev, checkTransparencyGroup(nullptr, true))
        .WillOnce(::testing::Return(false));
    
    bool result = mockDev.checkTransparencyGroup(nullptr, true);
    EXPECT_FALSE(result);
}

TEST_F(OutputDevTest_1076, CheckTransparencyGroupOverriddenReturnTrue_1076) {
    MockOutputDev mockDev;
    EXPECT_CALL(mockDev, checkTransparencyGroup(nullptr, false))
        .WillOnce(::testing::Return(true));
    
    bool result = mockDev.checkTransparencyGroup(nullptr, false);
    EXPECT_TRUE(result);
}

// Derived class that overrides to return false
class DerivedOutputDev : public OutputDev {
public:
    bool checkTransparencyGroup(GfxState* state, bool knockout) override {
        return false;
    }
};

TEST_F(OutputDevTest_1076, DerivedClassCanReturnFalse_1076) {
    DerivedOutputDev derived;
    bool result = derived.checkTransparencyGroup(nullptr, true);
    EXPECT_FALSE(result);
}

TEST_F(OutputDevTest_1076, DerivedClassReturnsFalseForBothKnockoutValues_1076) {
    DerivedOutputDev derived;
    EXPECT_FALSE(derived.checkTransparencyGroup(nullptr, true));
    EXPECT_FALSE(derived.checkTransparencyGroup(nullptr, false));
}

// Test polymorphic behavior through base pointer
TEST_F(OutputDevTest_1076, PolymorphicCallDefaultReturnsTrue_1076) {
    OutputDev* basePtr = &dev;
    EXPECT_TRUE(basePtr->checkTransparencyGroup(nullptr, true));
    EXPECT_TRUE(basePtr->checkTransparencyGroup(nullptr, false));
}

TEST_F(OutputDevTest_1076, PolymorphicCallDerivedReturnsFalse_1076) {
    DerivedOutputDev derived;
    OutputDev* basePtr = &derived;
    EXPECT_FALSE(basePtr->checkTransparencyGroup(nullptr, true));
    EXPECT_FALSE(basePtr->checkTransparencyGroup(nullptr, false));
}

// Test multiple calls to ensure consistent behavior
TEST_F(OutputDevTest_1076, CheckTransparencyGroupConsistentResults_1076) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(dev.checkTransparencyGroup(nullptr, true));
        EXPECT_TRUE(dev.checkTransparencyGroup(nullptr, false));
    }
}
