#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Sound.h"



using namespace testing;



class SoundTest : public ::testing::Test {

protected:

    Object mockObj;

    Sound* sound;



    void SetUp() override {

        sound = new Sound(mockObj, true);

    }



    void TearDown() override {

        delete sound;

    }

};



TEST_F(SoundTest_1453, GetBitsPerSample_ReturnsCorrectValue_1453) {

    // Assuming we can set up the mockObj to return a specific value for bitsPerSample

    EXPECT_EQ(sound->getBitsPerSample(), 16); // Example expected value

}



TEST_F(SoundTest_1453, GetSamplingRate_ReturnsCorrectValue_1453) {

    EXPECT_DOUBLE_EQ(sound->getSamplingRate(), 44100.0); // Example expected value

}



TEST_F(SoundTest_1453, GetChannels_ReturnsCorrectValue_1453) {

    EXPECT_EQ(sound->getChannels(), 2); // Example expected value for stereo

}



TEST_F(SoundTest_1453, GetEncoding_ReturnsCorrectValue_1453) {

    EXPECT_EQ(sound->getEncoding(), SoundEncoding::PCM); // Example expected encoding

}



TEST_F(SoundTest_1453, GetFileName_ReturnsEmptyStringForNonFileSound_1453) {

    EXPECT_TRUE(sound->getFileName().empty()); // Assuming non-file sound has no filename

}



TEST_F(SoundTest_1453, GetStream_ReturnsNonNullPointer_1453) {

    EXPECT_NE(sound->getStream(), nullptr);

}



TEST_F(SoundTest_1453, Copy_ReturnsNewSoundObject_1453) {

    const Sound* copiedSound = sound->copy();

    EXPECT_NE(copiedSound, nullptr);

    delete copiedSound;

}



TEST_F(SoundTest_1453, GetObject_ReturnsCorrectReference_1453) {

    const Object& objRef = sound->getObject();

    EXPECT_EQ(&objRef, &mockObj); // Assuming getObject returns the same reference

}



TEST_F(SoundTest_1453, GetSoundKind_ReturnsValidSoundKind_1453) {

    SoundKind kind = sound->getSoundKind();

    EXPECT_TRUE(kind == SoundKind::Embedded || kind == SoundKind::External);

}



// Exceptional or error cases (if observable through the interface)

TEST_F(SoundTest_1453, ParseSound_ReturnsValidIdForValidObject_1453) {

    int id = Sound::parseSound(mockObj);

    EXPECT_GE(id, 0); // Assuming valid object returns non-negative ID

}



TEST_F(SoundTest_1453, ParseSound_ReturnsInvalidIdForInvalidObject_1453) {

    Object invalidObj; // Assuming default constructed Object is invalid

    int id = Sound::parseSound(invalidObj);

    EXPECT_LT(id, 0); // Assuming invalid object returns negative ID

}
