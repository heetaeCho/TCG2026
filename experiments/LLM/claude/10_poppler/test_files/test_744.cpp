#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

#include <memory>

class AnnotBorderEffectTest_744 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that constructing AnnotBorderEffect with an empty dict gives default values
TEST_F(AnnotBorderEffectTest_744, DefaultConstructionFromEmptyDict_744) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Dict dict(xref.get());
    
    AnnotBorderEffect effect(&dict);
    
    // Default intensity should be 0 when not specified
    EXPECT_DOUBLE_EQ(effect.getIntensity(), 0.0);
    // Default effect type should be effectNone when not specified
    EXPECT_EQ(effect.getEffectType(), AnnotBorderEffect::effectNone);
}

// Test that constructing AnnotBorderEffect with S effect type
TEST_F(AnnotBorderEffectTest_744, EffectTypeNone_744) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Dict dict(xref.get());
    
    Object sObj = Object(new GooString("S"));
    dict.add("S", std::move(sObj));
    
    AnnotBorderEffect effect(&dict);
    
    EXPECT_EQ(effect.getEffectType(), AnnotBorderEffect::effectNone);
}

// Test that constructing AnnotBorderEffect with C (cloudy) effect type
TEST_F(AnnotBorderEffectTest_744, EffectTypeCloudy_744) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Dict dict(xref.get());
    
    Object sObj = Object(new GooString("C"));
    dict.add("S", std::move(sObj));
    
    AnnotBorderEffect effect(&dict);
    
    EXPECT_EQ(effect.getEffectType(), AnnotBorderEffect::effectCloudy);
}

// Test intensity value when explicitly set
TEST_F(AnnotBorderEffectTest_744, IntensitySetExplicitly_744) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Dict dict(xref.get());
    
    Object iObj = Object(2.0);
    dict.add("I", std::move(iObj));
    
    AnnotBorderEffect effect(&dict);
    
    EXPECT_DOUBLE_EQ(effect.getIntensity(), 2.0);
}

// Test intensity with cloudy effect
TEST_F(AnnotBorderEffectTest_744, CloudyWithIntensity_744) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Dict dict(xref.get());
    
    Object sObj = Object(new GooString("C"));
    dict.add("S", std::move(sObj));
    Object iObj = Object(1.5);
    dict.add("I", std::move(iObj));
    
    AnnotBorderEffect effect(&dict);
    
    EXPECT_EQ(effect.getEffectType(), AnnotBorderEffect::effectCloudy);
    EXPECT_DOUBLE_EQ(effect.getIntensity(), 1.5);
}

// Test intensity with zero value
TEST_F(AnnotBorderEffectTest_744, ZeroIntensity_744) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Dict dict(xref.get());
    
    Object iObj = Object(0.0);
    dict.add("I", std::move(iObj));
    
    AnnotBorderEffect effect(&dict);
    
    EXPECT_DOUBLE_EQ(effect.getIntensity(), 0.0);
}

// Test getIntensity returns consistent value on multiple calls
TEST_F(AnnotBorderEffectTest_744, IntensityConsistency_744) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Dict dict(xref.get());
    
    Object iObj = Object(3.14);
    dict.add("I", std::move(iObj));
    
    AnnotBorderEffect effect(&dict);
    
    double first = effect.getIntensity();
    double second = effect.getIntensity();
    EXPECT_DOUBLE_EQ(first, second);
}

// Test getEffectType returns consistent value on multiple calls
TEST_F(AnnotBorderEffectTest_744, EffectTypeConsistency_744) {
    auto xref = std::unique_ptr<XRef>(new XRef());
    Dict dict(xref.get());
    
    Object sObj = Object(new GooString("C"));
    dict.add("S", std::move(sObj));
    
    AnnotBorderEffect effect(&dict);
    
    auto first = effect.getEffectType();
    auto second = effect.getEffectType();
    EXPECT_EQ(first, second);
}
