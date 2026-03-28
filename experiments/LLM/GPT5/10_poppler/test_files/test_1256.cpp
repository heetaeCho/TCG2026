#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Gfx.h"

class GfxResourcesTest_1256 : public ::testing::Test {
protected:
    GfxResourcesTest_1256() : gfxResources(nullptr) {}

    void SetUp() override {
        // Setup necessary objects and dependencies here
    }

    void TearDown() override {
        // Clean up if necessary
    }

    GfxResources* gfxResources;
};

// Test normal operation of getNext()
TEST_F(GfxResourcesTest_1256, GetNext_ReturnsNextResource_1256) {
    GfxResources nextResource(nullptr);
    gfxResources = new GfxResources(nullptr, nullptr, &nextResource);
    
    EXPECT_EQ(gfxResources->getNext(), &nextResource);
}

// Test boundary condition for getNext() where there is no next resource.
TEST_F(GfxResourcesTest_1256, GetNext_ReturnsNullWhenNoNextResource_1257) {
    gfxResources = new GfxResources(nullptr, nullptr, nullptr);
    
    EXPECT_EQ(gfxResources->getNext(), nullptr);
}

// Test the lookupFont method for normal operation.
TEST_F(GfxResourcesTest_1256, LookupFont_ReturnsValidFont_1258) {
    const char* fontName = "Arial";
    // Mocking necessary objects or setting up expectations
    EXPECT_CALL(*gfxResources, lookupFont(fontName))
        .WillOnce(testing::Return(std::make_shared<GfxFont>()));
    
    std::shared_ptr<GfxFont> font = gfxResources->lookupFont(fontName);
    EXPECT_NE(font, nullptr);
}

// Test exceptional case for lookupFont where the font is not found.
TEST_F(GfxResourcesTest_1256, LookupFont_ReturnsNullForUnknownFont_1259) {
    const char* fontName = "UnknownFont";
    // Mocking necessary behavior to simulate font lookup failure
    EXPECT_CALL(*gfxResources, lookupFont(fontName))
        .WillOnce(testing::Return(nullptr));
    
    std::shared_ptr<GfxFont> font = gfxResources->lookupFont(fontName);
    EXPECT_EQ(font, nullptr);
}

// Test normal operation for lookupXObject method.
TEST_F(GfxResourcesTest_1256, LookupXObject_ReturnsValidObject_1260) {
    const char* objectName = "Object1";
    EXPECT_CALL(*gfxResources, lookupXObject(objectName))
        .WillOnce(testing::Return(Object()));
    
    Object obj = gfxResources->lookupXObject(objectName);
    EXPECT_FALSE(obj.isNull()); // Assuming Object has an isNull() method to check if it's valid
}

// Test boundary condition for lookupPattern method with valid input.
TEST_F(GfxResourcesTest_1256, LookupPattern_ReturnsValidPattern_1261) {
    const char* patternName = "Pattern1";
    OutputDev* out = nullptr;
    GfxState* state = nullptr;
    
    EXPECT_CALL(*gfxResources, lookupPattern(patternName, out, state))
        .WillOnce(testing::Return(0));  // Assuming 0 indicates success
    
    int result = gfxResources->lookupPattern(patternName, out, state);
    EXPECT_EQ(result, 0);
}

// Test exceptional case for lookupShading method where shading is not found.
TEST_F(GfxResourcesTest_1256, LookupShading_ReturnsErrorForUnknownShading_1262) {
    const char* shadingName = "Shading1";
    OutputDev* out = nullptr;
    GfxState* state = nullptr;
    
    EXPECT_CALL(*gfxResources, lookupShading(shadingName, out, state))
        .WillOnce(testing::Return(-1));  // Assuming -1 indicates failure
    
    int result = gfxResources->lookupShading(shadingName, out, state);
    EXPECT_EQ(result, -1);
}

// Test lookupGState for normal operation.
TEST_F(GfxResourcesTest_1256, LookupGState_ReturnsValidGState_1263) {
    const char* gStateName = "GState1";
    
    EXPECT_CALL(*gfxResources, lookupGState(gStateName))
        .WillOnce(testing::Return(Object()));
    
    Object gState = gfxResources->lookupGState(gStateName);
    EXPECT_FALSE(gState.isNull());
}

// Test exceptional case for lookupGStateNF where no GState is found.
TEST_F(GfxResourcesTest_1256, LookupGStateNF_ReturnsNullForUnknownGState_1264) {
    const char* gStateName = "UnknownGState";
    
    EXPECT_CALL(*gfxResources, lookupGStateNF(gStateName))
        .WillOnce(testing::Return(Object()));  // Assuming Object() means failure
    
    Object gState = gfxResources->lookupGStateNF(gStateName);
    EXPECT_TRUE(gState.isNull());
}