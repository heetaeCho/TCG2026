#include <gtest/gtest.h>

#include "Sound.h"

#include <string>



// Mock Stream class if needed (not used in this case as it's not a dependency for the tests)

class MockStream : public Stream {

    // Add mock methods if necessary

};



TEST_F(SoundTest_1451, GetSamplingRate_ReturnsCorrectValue_1451) {

    // Arrange

    Object obj;  // Assuming Object can be default constructed or properly initialized

    Sound sound(obj, true);  // Assuming the constructor is accessible for testing



    // Act & Assert

    EXPECT_DOUBLE_EQ(44100.0, sound.getSamplingRate());  // Example value, replace with actual expected value if known

}



TEST_F(SoundTest_1451, GetSoundKind_ReturnsCorrectValue_1451) {

    // Arrange

    Object obj;

    Sound sound(obj, true);



    // Act & Assert

    EXPECT_EQ(SoundKind::SomeExpectedKind, sound.getSoundKind());  // Replace with actual expected kind if known

}



TEST_F(SoundTest_1451, GetFileName_ReturnsCorrectValue_1451) {

    // Arrange

    Object obj;

    Sound sound(obj, true);



    // Act & Assert

    EXPECT_EQ("expected_filename.wav", sound.getFileName());  // Replace with actual expected filename if known

}



TEST_F(SoundTest_1451, GetChannels_ReturnsCorrectValue_1451) {

    // Arrange

    Object obj;

    Sound sound(obj, true);



    // Act & Assert

    EXPECT_EQ(2, sound.getChannels());  // Example value, replace with actual expected number of channels if known

}



TEST_F(SoundTest_1451, GetBitsPerSample_ReturnsCorrectValue_1451) {

    // Arrange

    Object obj;

    Sound sound(obj, true);



    // Act & Assert

    EXPECT_EQ(16, sound.getBitsPerSample());  // Example value, replace with actual expected bits per sample if known

}



TEST_F(SoundTest_1451, GetEncoding_ReturnsCorrectValue_1451) {

    // Arrange

    Object obj;

    Sound sound(obj, true);



    // Act & Assert

    EXPECT_EQ(SoundEncoding::SomeExpectedEncoding, sound.getEncoding());  // Replace with actual expected encoding if known

}



TEST_F(SoundTest_1451, GetObject_ReturnsCorrectReference_1451) {

    // Arrange

    Object obj;

    Sound sound(obj, true);



    // Act & Assert

    EXPECT_EQ(&obj, &sound.getObject());

}
