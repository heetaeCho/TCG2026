#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// Test fixture for OutputDev
class OutputDevTest_1068 : public ::testing::Test {
protected:
    OutputDev outputDev;
};

// Test that the default implementation of functionShadedFill returns false with nullptr arguments
TEST_F(OutputDevTest_1068, FunctionShadedFillReturnsFlaseWithNullArgs_1068) {
    bool result = outputDev.functionShadedFill(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test that the default implementation of functionShadedFill consistently returns false
TEST_F(OutputDevTest_1068, FunctionShadedFillConsistentlyReturnsFalse_1068) {
    // Call multiple times to ensure consistent behavior
    EXPECT_FALSE(outputDev.functionShadedFill(nullptr, nullptr));
    EXPECT_FALSE(outputDev.functionShadedFill(nullptr, nullptr));
    EXPECT_FALSE(outputDev.functionShadedFill(nullptr, nullptr));
}

// A derived class that overrides functionShadedFill to return true
class MockOutputDev : public OutputDev {
public:
    MOCK_METHOD(bool, functionShadedFill, (GfxState*, GfxFunctionShading*), (override));
};

// Test that a derived class can override functionShadedFill
TEST_F(OutputDevTest_1068, DerivedClassCanOverrideFunctionShadedFill_1068) {
    MockOutputDev mockDev;
    EXPECT_CALL(mockDev, functionShadedFill(nullptr, nullptr))
        .WillOnce(::testing::Return(true));
    
    bool result = mockDev.functionShadedFill(nullptr, nullptr);
    EXPECT_TRUE(result);
}

// Test that derived class override can return false as well
TEST_F(OutputDevTest_1068, DerivedClassCanReturnFalse_1068) {
    MockOutputDev mockDev;
    EXPECT_CALL(mockDev, functionShadedFill(nullptr, nullptr))
        .WillOnce(::testing::Return(false));
    
    bool result = mockDev.functionShadedFill(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// A concrete derived class that overrides to return true
class TrueOutputDev : public OutputDev {
public:
    bool functionShadedFill(GfxState* state, GfxFunctionShading* shading) override {
        return true;
    }
};

// Test polymorphic behavior through base pointer
TEST_F(OutputDevTest_1068, PolymorphicBehaviorBaseReturnsFlase_1068) {
    OutputDev* base = &outputDev;
    EXPECT_FALSE(base->functionShadedFill(nullptr, nullptr));
}

// Test polymorphic behavior through base pointer with derived class
TEST_F(OutputDevTest_1068, PolymorphicBehaviorDerivedReturnsTrue_1068) {
    TrueOutputDev derived;
    OutputDev* base = &derived;
    EXPECT_TRUE(base->functionShadedFill(nullptr, nullptr));
}

// Test that the base class default is indeed false (boundary: no override)
TEST_F(OutputDevTest_1068, BaseClassDefaultIsFalse_1068) {
    OutputDev dev;
    EXPECT_EQ(false, dev.functionShadedFill(nullptr, nullptr));
}
