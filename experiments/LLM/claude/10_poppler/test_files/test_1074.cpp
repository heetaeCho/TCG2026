#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// Test fixture for OutputDev
class OutputDevTest_1074 : public ::testing::Test {
protected:
    OutputDev dev;
};

// Test that the default implementation of patchMeshShadedFill returns false with nullptr arguments
TEST_F(OutputDevTest_1074, PatchMeshShadedFillReturnsFalseWithNullArgs_1074) {
    bool result = dev.patchMeshShadedFill(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test that the default implementation of patchMeshShadedFill returns false consistently
TEST_F(OutputDevTest_1074, PatchMeshShadedFillReturnsFalseConsistently_1074) {
    EXPECT_FALSE(dev.patchMeshShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev.patchMeshShadedFill(nullptr, nullptr));
    EXPECT_FALSE(dev.patchMeshShadedFill(nullptr, nullptr));
}

// Derived class that overrides patchMeshShadedFill to return true
class CustomOutputDev : public OutputDev {
public:
    bool patchMeshShadedFill(GfxState *state, GfxPatchMeshShading *shading) override {
        return true;
    }
};

// Test that a derived class can override patchMeshShadedFill and return true
TEST_F(OutputDevTest_1074, DerivedClassCanOverridePatchMeshShadedFill_1074) {
    CustomOutputDev customDev;
    bool result = customDev.patchMeshShadedFill(nullptr, nullptr);
    EXPECT_TRUE(result);
}

// Test polymorphic behavior through base class pointer
TEST_F(OutputDevTest_1074, PolymorphicBehaviorBaseReturnsDefault_1074) {
    OutputDev *basePtr = &dev;
    EXPECT_FALSE(basePtr->patchMeshShadedFill(nullptr, nullptr));
}

// Test polymorphic behavior through base class pointer with derived class
TEST_F(OutputDevTest_1074, PolymorphicBehaviorDerivedReturnsOverridden_1074) {
    CustomOutputDev customDev;
    OutputDev *basePtr = &customDev;
    EXPECT_TRUE(basePtr->patchMeshShadedFill(nullptr, nullptr));
}

// Mock-based derived class for verifying call parameters
class MockOutputDev : public OutputDev {
public:
    MOCK_METHOD(bool, patchMeshShadedFill, (GfxState *state, GfxPatchMeshShading *shading), (override));
};

// Test that patchMeshShadedFill is called with expected arguments using a mock
TEST_F(OutputDevTest_1074, MockVerifiesCallParameters_1074) {
    MockOutputDev mockDev;
    EXPECT_CALL(mockDev, patchMeshShadedFill(nullptr, nullptr))
        .Times(1)
        .WillOnce(::testing::Return(false));

    bool result = mockDev.patchMeshShadedFill(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test that mock can return true when configured
TEST_F(OutputDevTest_1074, MockCanReturnTrue_1074) {
    MockOutputDev mockDev;
    EXPECT_CALL(mockDev, patchMeshShadedFill(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(true));

    OutputDev *basePtr = &mockDev;
    EXPECT_TRUE(basePtr->patchMeshShadedFill(nullptr, nullptr));
}

// Test multiple calls on mock with different return values
TEST_F(OutputDevTest_1074, MockMultipleCallsDifferentReturns_1074) {
    MockOutputDev mockDev;
    EXPECT_CALL(mockDev, patchMeshShadedFill(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));

    EXPECT_FALSE(mockDev.patchMeshShadedFill(nullptr, nullptr));
    EXPECT_TRUE(mockDev.patchMeshShadedFill(nullptr, nullptr));
    EXPECT_FALSE(mockDev.patchMeshShadedFill(nullptr, nullptr));
}
