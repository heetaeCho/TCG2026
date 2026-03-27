#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Sound.h"

class SoundTest_1449 : public ::testing::Test {
protected:
    // Setup any necessary test data or mock objects here.
    Sound *sound;

    void SetUp() override {
        // Initialize the Sound object or dependencies.
        sound = new Sound(/* Pass required parameters if needed */);
    }

    void TearDown() override {
        delete sound;
    }
};

// Test normal operation of getSoundKind
TEST_F(SoundTest_1449, GetSoundKind_ReturnsCorrectKind_1449) {
    // Arrange
    SoundKind expectedKind = /* expected value */;

    // Act
    SoundKind result = sound->getSoundKind();

    // Assert
    EXPECT_EQ(result, expectedKind);
}

// Test normal operation of getFileName
TEST_F(SoundTest_1449, GetFileName_ReturnsCorrectFileName_1449) {
    // Arrange
    std::string expectedFileName = "testfile.wav";

    // Act
    std::string result = sound->getFileName();

    // Assert
    EXPECT_EQ(result, expectedFileName);
}

// Test boundary condition for getSamplingRate
TEST_F(SoundTest_1449, GetSamplingRate_ReturnsNonNegativeValue_1449) {
    // Act
    double result = sound->getSamplingRate();

    // Assert
    EXPECT_GE(result, 0);
}

// Test exceptional case for invalid Sound object (if applicable)
TEST_F(SoundTest_1449, GetSoundKind_InvalidSound_1449) {
    // This is just an example, adjust as per actual implementation if error handling is defined
    Sound invalidSound(/* some invalid parameters */);
    EXPECT_THROW(invalidSound.getSoundKind(), std::invalid_argument);
}

// Verify external interaction (e.g., mock Stream object)
class MockStream : public Stream {
public:
    MOCK_METHOD(void, someMethod, (), (override));
};

TEST_F(SoundTest_1449, StreamInteraction_VerifyMethodCall_1449) {
    // Arrange
    MockStream mockStream;
    EXPECT_CALL(mockStream, someMethod()).Times(1);

    // Act
    Stream* stream = sound->getStream();
    stream->someMethod();

    // Assert
    // Verify if the interaction with the mock object occurred.
    testing::Mock::VerifyAndClearExpectations(&mockStream);
}