#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

#include <memory>

class AnnotBorderEffectTest_743 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that constructing with an empty dictionary gives default effect type and intensity
TEST_F(AnnotBorderEffectTest_743, DefaultConstructionFromEmptyDict_743) {
    // Create an empty Dict (no /S or /I keys)
    auto xref = std::unique_ptr<XRef>(nullptr);
    Dict dict(static_cast<XRef*>(nullptr));

    AnnotBorderEffect effect(&dict);

    // Default effect type should be None when no /S key is present
    EXPECT_EQ(effect.getEffectType(), annotBorderEffectNone);
    // Default intensity should be 0 when no /I key is present
    EXPECT_DOUBLE_EQ(effect.getIntensity(), 0.0);
}

// Test that constructing with /S set to /S (None) gives effectNone
TEST_F(AnnotBorderEffectTest_743, EffectTypeNone_743) {
    Dict dict(static_cast<XRef*>(nullptr));

    Object sObj = Object(objName, "S");
    dict.add("S", std::move(sObj));

    AnnotBorderEffect effect(&dict);

    EXPECT_EQ(effect.getEffectType(), annotBorderEffectNone);
}

// Test that constructing with /S set to /C (Cloudy) gives effectCloudy
TEST_F(AnnotBorderEffectTest_743, EffectTypeCloudy_743) {
    Dict dict(static_cast<XRef*>(nullptr));

    Object sObj = Object(objName, "C");
    dict.add("S", std::move(sObj));

    AnnotBorderEffect effect(&dict);

    EXPECT_EQ(effect.getEffectType(), annotBorderEffectCloudy);
}

// Test intensity with a specific value
TEST_F(AnnotBorderEffectTest_743, IntensityWithValue_743) {
    Dict dict(static_cast<XRef*>(nullptr));

    Object iObj = Object(2.0);
    dict.add("I", std::move(iObj));

    AnnotBorderEffect effect(&dict);

    EXPECT_DOUBLE_EQ(effect.getIntensity(), 2.0);
}

// Test cloudy effect with intensity
TEST_F(AnnotBorderEffectTest_743, CloudyEffectWithIntensity_743) {
    Dict dict(static_cast<XRef*>(nullptr));

    Object sObj = Object(objName, "C");
    dict.add("S", std::move(sObj));

    Object iObj = Object(1.5);
    dict.add("I", std::move(iObj));

    AnnotBorderEffect effect(&dict);

    EXPECT_EQ(effect.getEffectType(), annotBorderEffectCloudy);
    EXPECT_DOUBLE_EQ(effect.getIntensity(), 1.5);
}

// Test that getEffectType returns consistent value on multiple calls
TEST_F(AnnotBorderEffectTest_743, GetEffectTypeConsistency_743) {
    Dict dict(static_cast<XRef*>(nullptr));

    AnnotBorderEffect effect(&dict);

    AnnotBorderEffectType type1 = effect.getEffectType();
    AnnotBorderEffectType type2 = effect.getEffectType();

    EXPECT_EQ(type1, type2);
}

// Test that getIntensity returns consistent value on multiple calls
TEST_F(AnnotBorderEffectTest_743, GetIntensityConsistency_743) {
    Dict dict(static_cast<XRef*>(nullptr));

    Object iObj = Object(3.14);
    dict.add("I", std::move(iObj));

    AnnotBorderEffect effect(&dict);

    double i1 = effect.getIntensity();
    double i2 = effect.getIntensity();

    EXPECT_DOUBLE_EQ(i1, i2);
}

// Test zero intensity
TEST_F(AnnotBorderEffectTest_743, ZeroIntensity_743) {
    Dict dict(static_cast<XRef*>(nullptr));

    Object iObj = Object(0.0);
    dict.add("I", std::move(iObj));

    AnnotBorderEffect effect(&dict);

    EXPECT_DOUBLE_EQ(effect.getIntensity(), 0.0);
}

// Test with unknown/invalid effect type name - should default to None
TEST_F(AnnotBorderEffectTest_743, UnknownEffectTypeName_743) {
    Dict dict(static_cast<XRef*>(nullptr));

    Object sObj = Object(objName, "X");
    dict.add("S", std::move(sObj));

    AnnotBorderEffect effect(&dict);

    // Unknown type should fall back to none
    EXPECT_EQ(effect.getEffectType(), annotBorderEffectNone);
}
