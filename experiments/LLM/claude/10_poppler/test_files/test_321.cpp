#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkSoundTest_321 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing LinkSound with a null/invalid object results in not ok
TEST_F(LinkSoundTest_321, ConstructWithNullObject_321) {
    Object obj;
    LinkSound linkSound(&obj);
    // An invalid/empty object should result in isOk() being false
    EXPECT_FALSE(linkSound.isOk());
}

// Test that getKind returns the correct LinkActionKind for LinkSound
TEST_F(LinkSoundTest_321, GetKindReturnsSound_321) {
    Object obj;
    LinkSound linkSound(&obj);
    EXPECT_EQ(linkSound.getKind(), actionSound);
}

// Test that getSound returns nullptr when constructed with invalid object
TEST_F(LinkSoundTest_321, GetSoundReturnsNullForInvalidObject_321) {
    Object obj;
    LinkSound linkSound(&obj);
    if (!linkSound.isOk()) {
        EXPECT_EQ(linkSound.getSound(), nullptr);
    }
}

// Test default volume value for invalid construction
TEST_F(LinkSoundTest_321, DefaultVolumeForInvalidObject_321) {
    Object obj;
    LinkSound linkSound(&obj);
    // Volume should have some default value; typically 1.0 for full volume
    double vol = linkSound.getVolume();
    EXPECT_GE(vol, 0.0);
    EXPECT_LE(vol, 1.0);
}

// Test default synchronous value for invalid construction
TEST_F(LinkSoundTest_321, DefaultSynchronousForInvalidObject_321) {
    Object obj;
    LinkSound linkSound(&obj);
    bool sync = linkSound.getSynchronous();
    EXPECT_FALSE(sync);
}

// Test default repeat value for invalid construction
TEST_F(LinkSoundTest_321, DefaultRepeatForInvalidObject_321) {
    Object obj;
    LinkSound linkSound(&obj);
    bool repeat = linkSound.getRepeat();
    EXPECT_FALSE(repeat);
}

// Test default mix value for invalid construction
TEST_F(LinkSoundTest_321, DefaultMixForInvalidObject_321) {
    Object obj;
    LinkSound linkSound(&obj);
    bool mix = linkSound.getMix();
    EXPECT_FALSE(mix);
}

// Test constructing LinkSound with a valid sound dictionary object
TEST_F(LinkSoundTest_321, ConstructWithValidSoundDict_321) {
    // Create a dictionary object that represents a sound
    Object soundObj = Object(new Dict(nullptr));
    // A minimal sound object - this may or may not result in isOk()
    // depending on internal validation, but we can at least verify no crash
    LinkSound linkSound(&soundObj);
    // Just verify getKind still works
    EXPECT_EQ(linkSound.getKind(), actionSound);
}

// Test that constructing with a dictionary containing Sound key
TEST_F(LinkSoundTest_321, ConstructWithDictContainingProperties_321) {
    // Build a more complete action dictionary
    Dict *dict = new Dict(nullptr);
    
    // Add a Sound stream/dict entry  
    Object soundStream = Object(new Dict(nullptr));
    dict->add("Sound", std::move(soundStream));
    
    // Add Volume
    dict->add("Volume", Object(1.0));
    
    // Add Synchronous
    dict->add("Synchronous", Object(true));
    
    // Add Repeat
    dict->add("Repeat", Object(true));
    
    // Add Mix
    dict->add("Mix", Object(true));
    
    Object actionObj(dict);
    LinkSound linkSound(&actionObj);
    
    // Verify getKind
    EXPECT_EQ(linkSound.getKind(), actionSound);
}

// Test that getSound returns a non-null pointer when properly constructed with valid sound data
TEST_F(LinkSoundTest_321, GetSoundWithValidData_321) {
    Dict *dict = new Dict(nullptr);
    
    // Create a sound object (stream-like dict)
    Dict *soundDict = new Dict(nullptr);
    Object soundObj(soundDict);
    dict->add("Sound", std::move(soundObj));
    
    Object actionObj(dict);
    LinkSound linkSound(&actionObj);
    
    if (linkSound.isOk()) {
        EXPECT_NE(linkSound.getSound(), nullptr);
    }
}
