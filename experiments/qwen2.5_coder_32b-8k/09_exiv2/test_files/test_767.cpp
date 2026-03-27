#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/types.hpp"

#include <string>



using namespace Exiv2;

using ::testing::NiceMock;

using ::testing::_;



// Mock the Thumbnail class to control its behavior in tests

class MockThumbnail : public Thumbnail {

public:

    MOCK_METHOD(UniquePtr, create, (const ExifData& exifData), (override));

    MOCK_CONST_METHOD0(copy, DataBuf());

    MOCK_CONST_METHOD0(mimeType, const char*());

    MOCK_CONST_METHOD0(extension, const char*());

};



// Fixture for testing the ExifThumbC class

class ExifThumbCTest : public ::testing::Test {

protected:

    MockThumbnail mockThumbnail;

    ExifData exifData;



    ExifThumbCTest() {

        // Replace the real Thumbnail creation with our mock version

        EXPECT_CALL(mockThumbnail, create(_))

            .WillRepeatedly([](const ExifData& data) -> UniquePtr { return UniquePtr(new MockThumbnail()); });

    }

};



// Test normal operation: writeFile writes the file and returns a non-zero size

TEST_F(ExifThumbCTest_767, WriteFile_WritesFile_ReturnsNonZeroSize_767) {

    const char* mockExtension = ".jpg";

    const std::string path = "test_path";



    // Set up the expectations for the mock Thumbnail methods

    EXPECT_CALL(mockThumbnail, copy()).WillOnce([]() -> DataBuf { return DataBuf(new byte[1], 1); });

    EXPECT_CALL(mockThumbnail, extension()).WillOnce(testing::Return(mockExtension));



    ExifThumbC exifThumb(exifData);

    size_t result = exifThumb.writeFile(path + mockExtension);



    EXPECT_GT(result, 0);

}



// Test boundary condition: writeFile with an empty DataBuf returns 0

TEST_F(ExifThumbCTest_767, WriteFile_EmptyData_ReturnsZeroSize_767) {

    const char* mockExtension = ".jpg";

    const std::string path = "test_path";



    // Set up the expectations for the mock Thumbnail methods

    EXPECT_CALL(mockThumbnail, copy()).WillOnce([]() -> DataBuf { return DataBuf(); });

    EXPECT_CALL(mockThumbnail, extension()).WillOnce(testing::Return(mockExtension));



    ExifThumbC exifThumb(exifData);

    size_t result = exifThumb.writeFile(path + mockExtension);



    EXPECT_EQ(result, 0);

}



// Test exceptional case: writeFile with no thumbnail creation returns 0

TEST_F(ExifThumbCTest_767, WriteFile_NoThumbnail_ReturnsZeroSize_767) {

    const std::string path = "test_path";



    // Set up the expectations for the mock Thumbnail methods

    EXPECT_CALL(mockThumbnail, create(_)).WillOnce(testing::Return(UniquePtr(nullptr)));



    ExifThumbC exifThumb(exifData);

    size_t result = exifThumb.writeFile(path);



    EXPECT_EQ(result, 0);

}
