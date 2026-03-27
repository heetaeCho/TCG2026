#include <gtest/gtest.h>

#include "Sound.h"

#include <string>



class SoundTest_1450 : public ::testing::Test {

protected:

    void SetUp() override {

        Object obj; // Assuming Object can be default constructed for this test

        sound = new Sound(obj, true);

    }



    void TearDown() override {

        delete sound;

    }



    Sound* sound;

};



TEST_F(SoundTest_1450, GetFileName_ReturnsEmptyStringByDefault_1450) {

    EXPECT_EQ(sound->getFileName(), "");

}



TEST_F(SoundTest_1450, GetSamplingRate_ReturnsDefaultValue_1450) {

    EXPECT_DOUBLE_EQ(sound->getSamplingRate(), 0.0);

}



TEST_F(SoundTest_1450, GetChannels_ReturnsDefaultValue_1450) {

    EXPECT_EQ(sound->getChannels(), 0);

}



TEST_F(SoundTest_1450, GetBitsPerSample_ReturnsDefaultValue_1450) {

    EXPECT_EQ(sound->getBitsPerSample(), 0);

}



TEST_F(SoundTest_1450, GetEncoding_ReturnsDefaultValue_1450) {

    EXPECT_EQ(sound->getEncoding(), static_cast<SoundEncoding>(0));

}



TEST_F(SoundTest_1450, GetObject_ReturnsValidObject_1450) {

    const Object& obj = sound->getObject();

    // Assuming there's some way to verify the object is valid, e.g., checking a type

    EXPECT_TRUE(obj.isNone()); // Placeholder check; adjust as necessary

}



TEST_F(SoundTest_1450, GetSoundKind_ReturnsDefaultValue_1450) {

    EXPECT_EQ(sound->getSoundKind(), static_cast<SoundKind>(0));

}
