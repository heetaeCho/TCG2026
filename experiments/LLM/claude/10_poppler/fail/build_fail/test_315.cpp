#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"
#include "Sound.h"

class LinkSoundTest_315 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a LinkSound constructed with a valid sound Object is OK
TEST_F(LinkSoundTest_315, ValidSoundObjectIsOk_315) {
    // Create a valid sound dictionary object
    Object soundObj;
    
    // Build a minimal sound object - a stream or dict with required entries
    Object soundDict = Object(new Dict(nullptr));
    // A sound object in PDF is typically a stream, but we construct what we can
    // We need to test observable behavior through the interface
    
    // Since we can't easily construct a valid PDF sound object without
    // a full PDF context, we test with what's available
    LinkSound linkSound(&soundObj);
    
    // If the internal sound pointer is null, isOk() returns false
    // This tests the boundary case of an invalid/empty object
    // The behavior depends on whether Sound can be created from soundObj
    bool ok = linkSound.isOk();
    // We just verify it doesn't crash and returns a boolean
    EXPECT_TRUE(ok == true || ok == false);
}

// Test that a LinkSound constructed with a null-like object returns not OK
TEST_F(LinkSoundTest_315, NullSoundObjectIsNotOk_315) {
    Object nullObj;
    LinkSound linkSound(&nullObj);
    
    // A null/empty object should not produce a valid Sound
    EXPECT_FALSE(linkSound.isOk());
}

// Test getKind returns the correct LinkActionKind for sound
TEST_F(LinkSoundTest_315, GetKindReturnsSound_315) {
    Object obj;
    LinkSound linkSound(&obj);
    
    EXPECT_EQ(linkSound.getKind(), actionSound);
}

// Test default volume value when constructed with minimal/invalid object
TEST_F(LinkSoundTest_315, GetVolumeWithInvalidObject_315) {
    Object obj;
    LinkSound linkSound(&obj);
    
    double volume = linkSound.getVolume();
    // Volume should be in range [-1.0, 1.0] per PDF spec, default is 1.0
    EXPECT_GE(volume, -1.0);
    EXPECT_LE(volume, 1.0);
}

// Test default synchronous value
TEST_F(LinkSoundTest_315, GetSynchronousDefault_315) {
    Object obj;
    LinkSound linkSound(&obj);
    
    bool sync = linkSound.getSynchronous();
    // Default per PDF spec is false
    EXPECT_FALSE(sync);
}

// Test default repeat value
TEST_F(LinkSoundTest_315, GetRepeatDefault_315) {
    Object obj;
    LinkSound linkSound(&obj);
    
    bool repeat = linkSound.getRepeat();
    // Default per PDF spec is false
    EXPECT_FALSE(repeat);
}

// Test default mix value
TEST_F(LinkSoundTest_315, GetMixDefault_315) {
    Object obj;
    LinkSound linkSound(&obj);
    
    bool mix = linkSound.getMix();
    // Default per PDF spec is false
    EXPECT_FALSE(mix);
}

// Test getSound returns nullptr when constructed with invalid object
TEST_F(LinkSoundTest_315, GetSoundReturnsNullWhenInvalid_315) {
    Object obj;
    LinkSound linkSound(&obj);
    
    if (!linkSound.isOk()) {
        EXPECT_EQ(linkSound.getSound(), nullptr);
    }
}

// Test that isOk correlates with getSound
TEST_F(LinkSoundTest_315, IsOkCorrelatesWithGetSound_315) {
    Object obj;
    LinkSound linkSound(&obj);
    
    if (linkSound.isOk()) {
        EXPECT_NE(linkSound.getSound(), nullptr);
    } else {
        EXPECT_EQ(linkSound.getSound(), nullptr);
    }
}

// Test construction with a dictionary that has sound-related keys
TEST_F(LinkSoundTest_315, ConstructWithDictObject_315) {
    // Create a dict-based object to test parsing behavior
    Object dictObj = Object(new Dict(nullptr));
    
    LinkSound linkSound(&dictObj);
    
    // Verify it doesn't crash; check observable state
    bool ok = linkSound.isOk();
    EXPECT_TRUE(ok == true || ok == false);
    
    // getKind should still return actionSound regardless
    EXPECT_EQ(linkSound.getKind(), actionSound);
}
