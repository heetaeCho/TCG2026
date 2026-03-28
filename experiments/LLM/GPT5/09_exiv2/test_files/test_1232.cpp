#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/tgaimage.hpp"
#include "exiv2/error.hpp"

namespace Exiv2 {

class TgaImageTest : public ::testing::Test {
protected:
    // Setup or teardown logic if needed.
    void SetUp() override {}
    void TearDown() override {}
};

// Test for normal operation, where the function is expected to throw an error.
TEST_F(TgaImageTest, WriteMetadataThrowsError_1232) {
    TgaImage tgaImage(nullptr);  // Passing a nullptr to simulate normal behavior (as per the partial code).

    // Test if writeMetadata throws the correct error.
    EXPECT_THROW({
        tgaImage.writeMetadata();
    }, Error);  // Expecting the Error exception to be thrown.
}

// Test case for boundary condition: handling an invalid or unexpected input.
TEST_F(TgaImageTest, WriteMetadataThrowsOnInvalidInput_1233) {
    TgaImage tgaImage(nullptr);  // Passing nullptr, assuming that it could be invalid in some scenarios.

    // Test if writeMetadata throws the correct error in this case too.
    EXPECT_THROW({
        tgaImage.writeMetadata();
    }, Error);  // Expecting the Error exception to be thrown.
}

// Test for verifying the specific error code when writeMetadata fails.
TEST_F(TgaImageTest, WriteMetadataErrorCode_1234) {
    TgaImage tgaImage(nullptr);

    try {
        tgaImage.writeMetadata();
    } catch (const Error& e) {
        // Check if the error code matches the expected error code.
        EXPECT_EQ(e.code(), ErrorCode::kerWritingImageFormatUnsupported);
    }
}

}  // namespace Exiv2