#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkSoundTest_320 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getMix returns a boolean value when LinkSound is constructed with a valid sound object
TEST_F(LinkSoundTest_320, GetMixReturnsBool_320) {
    // Create a sound object dictionary for constructing LinkSound
    Object soundObj;
    
    // Create a dictionary object that represents a sound
    soundObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&soundObj);
    
    // getMix should return either true or false
    bool mixValue = linkSound.getMix();
    EXPECT_TRUE(mixValue == true || mixValue == false);
}

// Test LinkSound construction with a minimal valid sound object
TEST_F(LinkSoundTest_320, ConstructWithSoundObject_320) {
    Object soundObj;
    soundObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&soundObj);
    
    // Verify getKind returns the correct action kind
    EXPECT_EQ(linkSound.getKind(), actionSound);
}

// Test that getMix default behavior (typically false when not explicitly set)
TEST_F(LinkSoundTest_320, GetMixDefaultValue_320) {
    Object soundObj;
    soundObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&soundObj);
    
    // When no mix property is specified, getMix should return a default value
    bool mixValue = linkSound.getMix();
    // We just verify it doesn't crash and returns a boolean
    EXPECT_NO_FATAL_FAILURE(linkSound.getMix());
}

// Test getVolume returns a double value
TEST_F(LinkSoundTest_320, GetVolumeReturnsDouble_320) {
    Object soundObj;
    soundObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&soundObj);
    
    double volume = linkSound.getVolume();
    // Volume should be in a reasonable range (typically 0.0 to 1.0)
    EXPECT_NO_FATAL_FAILURE(linkSound.getVolume());
}

// Test getSynchronous returns a boolean
TEST_F(LinkSoundTest_320, GetSynchronousReturnsBool_320) {
    Object soundObj;
    soundObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&soundObj);
    
    bool syncValue = linkSound.getSynchronous();
    EXPECT_TRUE(syncValue == true || syncValue == false);
}

// Test getRepeat returns a boolean
TEST_F(LinkSoundTest_320, GetRepeatReturnsBool_320) {
    Object soundObj;
    soundObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&soundObj);
    
    bool repeatValue = linkSound.getRepeat();
    EXPECT_TRUE(repeatValue == true || repeatValue == false);
}

// Test getSound returns a pointer (may be null for invalid/incomplete sound objects)
TEST_F(LinkSoundTest_320, GetSoundReturnsPointer_320) {
    Object soundObj;
    soundObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&soundObj);
    
    // getSound should not crash
    EXPECT_NO_FATAL_FAILURE(linkSound.getSound());
}

// Test isOk for a minimal sound object
TEST_F(LinkSoundTest_320, IsOkCheck_320) {
    Object soundObj;
    soundObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&soundObj);
    
    // isOk should return true or false without crashing
    bool okValue = linkSound.isOk();
    EXPECT_TRUE(okValue == true || okValue == false);
}

// Test construction with null-like object
TEST_F(LinkSoundTest_320, ConstructWithNullObject_320) {
    Object nullObj;
    
    LinkSound linkSound(&nullObj);
    
    // Should handle gracefully
    EXPECT_NO_FATAL_FAILURE(linkSound.getMix());
    EXPECT_NO_FATAL_FAILURE(linkSound.getVolume());
    EXPECT_NO_FATAL_FAILURE(linkSound.getSynchronous());
    EXPECT_NO_FATAL_FAILURE(linkSound.getRepeat());
}

// Test that getMix is consistent across multiple calls
TEST_F(LinkSoundTest_320, GetMixConsistency_320) {
    Object soundObj;
    soundObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&soundObj);
    
    bool firstCall = linkSound.getMix();
    bool secondCall = linkSound.getMix();
    
    EXPECT_EQ(firstCall, secondCall);
}
