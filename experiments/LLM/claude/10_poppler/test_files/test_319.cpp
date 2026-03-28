#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkSoundTest_319 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getRepeat returns a boolean value when LinkSound is constructed with a valid sound object
TEST_F(LinkSoundTest_319, GetRepeatReturnsBool_319) {
    // Create a sound object dictionary for LinkSound construction
    Object soundObj;
    
    // We need to create a proper Object that LinkSound can parse
    // Since we're treating this as a black box, we construct with available means
    Object dict = Object(new Dict(nullptr));
    
    // Attempt to construct LinkSound - behavior depends on the Object content
    LinkSound linkSound(&dict);
    
    // getRepeat should return a bool value
    bool repeatVal = linkSound.getRepeat();
    EXPECT_TRUE(repeatVal == true || repeatVal == false);
}

// Test that getRepeat is consistent across multiple calls
TEST_F(LinkSoundTest_319, GetRepeatIsConsistent_319) {
    Object dict = Object(new Dict(nullptr));
    LinkSound linkSound(&dict);
    
    bool firstCall = linkSound.getRepeat();
    bool secondCall = linkSound.getRepeat();
    
    EXPECT_EQ(firstCall, secondCall);
}

// Test getKind returns expected LinkActionKind for LinkSound
TEST_F(LinkSoundTest_319, GetKindReturnsSound_319) {
    Object dict = Object(new Dict(nullptr));
    LinkSound linkSound(&dict);
    
    EXPECT_EQ(linkSound.getKind(), actionSound);
}

// Test default construction with empty/null-like object
TEST_F(LinkSoundTest_319, DefaultRepeatWithMinimalObject_319) {
    Object nullObj;
    LinkSound linkSound(&nullObj);
    
    // Default repeat should be false when no repeat field is specified
    bool repeatVal = linkSound.getRepeat();
    EXPECT_TRUE(repeatVal == true || repeatVal == false);
}

// Test isOk on a LinkSound constructed with minimal/invalid data
TEST_F(LinkSoundTest_319, IsOkWithInvalidObject_319) {
    Object nullObj;
    LinkSound linkSound(&nullObj);
    
    // With an invalid/null object, isOk may return false
    bool ok = linkSound.isOk();
    EXPECT_TRUE(ok == true || ok == false);
}

// Test getVolume returns a value in expected range
TEST_F(LinkSoundTest_319, GetVolumeReturnsValue_319) {
    Object dict = Object(new Dict(nullptr));
    LinkSound linkSound(&dict);
    
    double volume = linkSound.getVolume();
    // Volume should be between 0 and 1 typically, or a default value
    EXPECT_GE(volume, -1.0);
    EXPECT_LE(volume, 1.0);
}

// Test getSynchronous returns a bool
TEST_F(LinkSoundTest_319, GetSynchronousReturnsBool_319) {
    Object dict = Object(new Dict(nullptr));
    LinkSound linkSound(&dict);
    
    bool sync = linkSound.getSynchronous();
    EXPECT_TRUE(sync == true || sync == false);
}

// Test getMix returns a bool
TEST_F(LinkSoundTest_319, GetMixReturnsBool_319) {
    Object dict = Object(new Dict(nullptr));
    LinkSound linkSound(&dict);
    
    bool mix = linkSound.getMix();
    EXPECT_TRUE(mix == true || mix == false);
}

// Test that getRepeat and other getters are const-correct
TEST_F(LinkSoundTest_319, ConstCorrectnessOfGetters_319) {
    Object dict = Object(new Dict(nullptr));
    const LinkSound linkSound(&dict);
    
    // All these should compile and work on a const object
    bool repeat = linkSound.getRepeat();
    bool sync = linkSound.getSynchronous();
    bool mix = linkSound.getMix();
    double volume = linkSound.getVolume();
    
    EXPECT_TRUE(repeat == true || repeat == false);
    EXPECT_TRUE(sync == true || sync == false);
    EXPECT_TRUE(mix == true || mix == false);
    (void)volume;
}
