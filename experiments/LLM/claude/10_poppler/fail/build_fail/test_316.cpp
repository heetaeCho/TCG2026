#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkSoundTest_316 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getKind returns actionSound
TEST_F(LinkSoundTest_316, GetKindReturnsActionSound_316) {
    // Create a minimal sound Object for constructing LinkSound
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    EXPECT_EQ(linkSound.getKind(), actionSound);
}

// Test that getKind returns the correct enum value (7)
TEST_F(LinkSoundTest_316, GetKindReturnsCorrectEnumValue_316) {
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    EXPECT_EQ(static_cast<int>(linkSound.getKind()), 7);
}

// Test isOk with a null/invalid sound object
TEST_F(LinkSoundTest_316, IsOkWithNullObject_316) {
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    // With a null object, the sound should not be valid
    EXPECT_FALSE(linkSound.isOk());
}

// Test getSound with invalid object returns null
TEST_F(LinkSoundTest_316, GetSoundWithInvalidObject_316) {
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    // With an invalid/null object, getSound should return nullptr
    EXPECT_EQ(linkSound.getSound(), nullptr);
}

// Test default volume value with invalid sound object
TEST_F(LinkSoundTest_316, DefaultVolumeWithInvalidObject_316) {
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    // Volume should have some default value (typically 1.0)
    double vol = linkSound.getVolume();
    EXPECT_GE(vol, 0.0);
    EXPECT_LE(vol, 1.0);
}

// Test default synchronous value with invalid sound object
TEST_F(LinkSoundTest_316, DefaultSynchronousWithInvalidObject_316) {
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    // Default sync should be false
    EXPECT_FALSE(linkSound.getSynchronous());
}

// Test default repeat value with invalid sound object
TEST_F(LinkSoundTest_316, DefaultRepeatWithInvalidObject_316) {
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    // Default repeat should be false
    EXPECT_FALSE(linkSound.getRepeat());
}

// Test default mix value with invalid sound object
TEST_F(LinkSoundTest_316, DefaultMixWithInvalidObject_316) {
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    // Default mix should be false
    EXPECT_FALSE(linkSound.getMix());
}

// Test construction with a dict-based sound object
TEST_F(LinkSoundTest_316, ConstructWithDictObject_316) {
    // Create a dictionary object to represent a sound action
    Object soundDict;
    soundDict.initDict(nullptr);
    
    // Even with an empty dict, construction should not crash
    LinkSound linkSound(&soundDict);
    EXPECT_EQ(linkSound.getKind(), actionSound);
}

// Test that getKind is consistent across multiple calls
TEST_F(LinkSoundTest_316, GetKindConsistentAcrossCalls_316) {
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    EXPECT_EQ(linkSound.getKind(), actionSound);
    EXPECT_EQ(linkSound.getKind(), actionSound);
    EXPECT_EQ(linkSound.getKind(), actionSound);
}

// Test that getKind returns actionSound and not other kinds
TEST_F(LinkSoundTest_316, GetKindIsNotOtherKinds_316) {
    Object soundObj;
    soundObj.initNull();
    
    LinkSound linkSound(&soundObj);
    EXPECT_NE(linkSound.getKind(), actionGoTo);
    EXPECT_NE(linkSound.getKind(), actionGoToR);
    EXPECT_NE(linkSound.getKind(), actionLaunch);
    EXPECT_NE(linkSound.getKind(), actionURI);
    EXPECT_NE(linkSound.getKind(), actionNamed);
    EXPECT_NE(linkSound.getKind(), actionMovie);
    EXPECT_NE(linkSound.getKind(), actionRendition);
    EXPECT_NE(linkSound.getKind(), actionJavaScript);
    EXPECT_NE(linkSound.getKind(), actionOCGState);
    EXPECT_NE(linkSound.getKind(), actionHide);
    EXPECT_NE(linkSound.getKind(), actionResetForm);
    EXPECT_NE(linkSound.getKind(), actionSubmitForm);
    EXPECT_NE(linkSound.getKind(), actionUnknown);
}
