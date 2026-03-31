#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// A concrete subclass that uses the default implementation
class ConcreteOutputDev : public OutputDev {
};

// A subclass that overrides to return true
class ExtendSupportOutputDev : public OutputDev {
public:
    bool radialShadedSupportExtend(GfxState *state, GfxRadialShading *shading) override {
        return true;
    }
};

// Test that the default implementation returns false
TEST(OutputDevTest_1072, RadialShadedSupportExtendDefaultReturnsFalse_1072) {
    ConcreteOutputDev dev;
    bool result = dev.radialShadedSupportExtend(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test that the default implementation returns false with null state
TEST(OutputDevTest_1072, RadialShadedSupportExtendNullState_1072) {
    ConcreteOutputDev dev;
    bool result = dev.radialShadedSupportExtend(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test that the default implementation returns false with null shading
TEST(OutputDevTest_1072, RadialShadedSupportExtendNullShading_1072) {
    ConcreteOutputDev dev;
    bool result = dev.radialShadedSupportExtend(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test that a subclass can override and return true
TEST(OutputDevTest_1072, RadialShadedSupportExtendOverrideReturnsTrue_1072) {
    ExtendSupportOutputDev dev;
    bool result = dev.radialShadedSupportExtend(nullptr, nullptr);
    EXPECT_TRUE(result);
}

// Test polymorphism: calling through base pointer with default impl
TEST(OutputDevTest_1072, RadialShadedSupportExtendViaBasePointerDefault_1072) {
    ConcreteOutputDev concreteDev;
    OutputDev *dev = &concreteDev;
    bool result = dev->radialShadedSupportExtend(nullptr, nullptr);
    EXPECT_FALSE(result);
}

// Test polymorphism: calling through base pointer with overridden impl
TEST(OutputDevTest_1072, RadialShadedSupportExtendViaBasePointerOverride_1072) {
    ExtendSupportOutputDev extendDev;
    OutputDev *dev = &extendDev;
    bool result = dev->radialShadedSupportExtend(nullptr, nullptr);
    EXPECT_TRUE(result);
}

// Test that calling multiple times consistently returns false for default
TEST(OutputDevTest_1072, RadialShadedSupportExtendConsistentResult_1072) {
    ConcreteOutputDev dev;
    EXPECT_FALSE(dev.radialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev.radialShadedSupportExtend(nullptr, nullptr));
    EXPECT_FALSE(dev.radialShadedSupportExtend(nullptr, nullptr));
}
