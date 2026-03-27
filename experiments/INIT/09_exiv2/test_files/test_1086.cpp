#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/image.hpp"
#include "exiv2/error.hpp"

using namespace Exiv2;

class MockErrorHandler {
public:
    MOCK_METHOD(void, handleError, (const Error& error), ());
};

class ImageTest_1086 : public ::testing::Test {
protected:
    ImageTest_1086() 
        : iccProfile(64), // Example initialization, adjust the size accordingly
          image(ImageType::unknown, 0, nullptr) {
        // Initialize with necessary data if needed
    }

    DataBuf iccProfile;
    Image image;

    void setUp() override {
        // Setup code if needed
    }
};

// Test: Valid ICC profile check
TEST_F(ImageTest_1086, CheckIccProfile_Valid_1086) {
    iccProfile.resize(sizeof(long) + 1);
    EXPECT_NO_THROW(image.checkIccProfile());
}

// Test: ICC profile size too small to be valid
TEST_F(ImageTest_1086, CheckIccProfile_InvalidSize_1086) {
    iccProfile.resize(sizeof(long) - 1); // Too small
    EXPECT_THROW(image.checkIccProfile(), Error);
}

// Test: ICC profile read size mismatch
TEST_F(ImageTest_1086, CheckIccProfile_SizeMismatch_1086) {
    iccProfile.resize(sizeof(long) + 2); // Simulate size mismatch
    EXPECT_THROW(image.checkIccProfile(), Error);
}

// Test: Exception thrown for invalid ICC profile size
TEST_F(ImageTest_1086, CheckIccProfile_ThrowOnInvalidSize_1086) {
    iccProfile.resize(0); // Zero size ICC profile
    EXPECT_THROW(image.checkIccProfile(), Error);
}

// Test: Verify external handler interaction for error
TEST_F(ImageTest_1086, CheckIccProfile_ExternalHandler_1086) {
    MockErrorHandler handler;
    EXPECT_CALL(handler, handleError(::testing::_)).Times(1); // Check if handler is invoked on error
    
    // Simulating an error
    iccProfile.resize(0);
    EXPECT_THROW(image.checkIccProfile(), Error);
}