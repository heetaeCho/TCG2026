#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// A concrete subclass that uses the default implementation
class ConcreteOutputDev : public OutputDev {
};

// A subclass that overrides axialShadedSupportExtend to return true
class OverriddenOutputDev : public OutputDev {
public:
    bool axialShadedSupportExtend(GfxState *state, GfxAxialShading *shading) override {
        return true;
    }
};

// Test that the default implementation returns false with nullptr arguments
TEST(OutputDevTest_1070, DefaultAxialShadedSupportExtendReturnsFalse_1070) {
    ConcreteOutputDev dev;
    bool result = dev.axialShadedSupportExtend(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test that calling through base class pointer still returns false for default impl
TEST(OutputDevTest_1070, BasePointerDefaultReturnsFalse_1070) {
    ConcreteOutputDev dev;
    OutputDev *basePtr = &dev;
    bool result = basePtr->axialShadedSupportExtend(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test that a subclass can override and return true
TEST(OutputDevTest_1070, OverriddenAxialShadedSupportExtendReturnsTrue_1070) {
    OverriddenOutputDev dev;
    bool result = dev.axialShadedSupportExtend(nullptr, nullptr);
    EXPECT_TRUE(result);
}

// Test polymorphic behavior through base pointer with overridden subclass
TEST(OutputDevTest_1070, PolymorphicOverrideReturnsTrue_1070) {
    OverriddenOutputDev dev;
    OutputDev *basePtr = &dev;
    bool result = basePtr->axialShadedSupportExtend(nullptr, nullptr);
    EXPECT_TRUE(result);
}

// Test that calling multiple times consistently returns false for default
TEST(OutputDevTest_1070, DefaultReturnsConsistentlyFalse_1070) {
    ConcreteOutputDev dev;
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(dev.axialShadedSupportExtend(nullptr, nullptr));
    }
}

// Test default implementation with nullptr state and nullptr shading (boundary)
TEST(OutputDevTest_1070, NullptrArgumentsBoundary_1070) {
    ConcreteOutputDev dev;
    EXPECT_FALSE(dev.axialShadedSupportExtend(nullptr, nullptr));
}
