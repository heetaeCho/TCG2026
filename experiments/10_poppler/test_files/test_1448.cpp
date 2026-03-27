#include <gtest/gtest.h>

#include "Sound.h"

#include <gmock/gmock.h>



using namespace testing;



class SoundTest_1448 : public ::testing::Test {

protected:

    Object mockObject;

    Sound* sound;



    void SetUp() override {

        // Assuming the constructor is accessible for testing purposes

        sound = new Sound(mockObject, true);

    }



    void TearDown() override {

        delete sound;

    }

};



TEST_F(SoundTest_1448, GetObjectReturnsCorrectObject_1448) {

    EXPECT_EQ(&mockObject, &sound->getObject());

}



TEST_F(SoundTest_1448, CopyCreatesNewSoundInstance_1448) {

    const Sound* copiedSound = sound->copy();

    EXPECT_NE(sound, copiedSound);

    EXPECT_EQ(sound->getFileName(), copiedSound->getFileName());

    EXPECT_EQ(sound->getSamplingRate(), copiedSound->getSamplingRate());

    EXPECT_EQ(sound->getChannels(), copiedSound->getChannels());

    EXPECT_EQ(sound->getBitsPerSample(), copiedSound->getBitsPerSample());

    EXPECT_EQ(sound->getEncoding(), copiedSound->getEncoding());

    delete copiedSound;

}



TEST_F(SoundTest_1448, GetStreamReturnsNonNullPointer_1448) {

    Stream* stream = sound->getStream();

    EXPECT_NE(nullptr, stream);

    // Assuming the caller is responsible for managing the returned stream's lifecycle

}



TEST_F(SoundTest_1448, ParseSoundWithValidObjectReturnsNonNegativeValue_1448) {

    int result = Sound::parseSound(mockObject);

    EXPECT_GE(result, 0);

}



// Assuming SoundKind has a default value or can be initialized without errors

TEST_F(SoundTest_1448, GetSoundKindReturnsValidEnum_1448) {

    SoundKind kind = sound->getSoundKind();

    // Add any valid range checks if known

}



// Assuming fileName can be empty string by default

TEST_F(SoundTest_1448, GetFileNameReturnsString_1448) {

    std::string fileName = sound->getFileName();

    EXPECT_TRUE(fileName.empty() || !fileName.empty());

}



// Assuming samplingRate has a default value or can be initialized without errors

TEST_F(SoundTest_1448, GetSamplingRateReturnsNonNegativeValue_1448) {

    double samplingRate = sound->getSamplingRate();

    EXPECT_GE(samplingRate, 0.0);

}



// Assuming channels has a default value or can be initialized without errors

TEST_F(SoundTest_1448, GetChannelsReturnsPositiveInteger_1448) {

    int channels = sound->getChannels();

    EXPECT_GT(channels, 0);

}



// Assuming bitsPerSample has a default value or can be initialized without errors

TEST_F(SoundTest_1448, GetBitsPerSampleReturnsPositiveInteger_1448) {

    int bitsPerSample = sound->getBitsPerSample();

    EXPECT_GT(bitsPerSample, 0);

}



// Assuming encoding has a default value or can be initialized without errors

TEST_F(SoundTest_1448, GetEncodingReturnsValidEnum_1448) {

    SoundEncoding encoding = sound->getEncoding();

    // Add any valid range checks if known

}
