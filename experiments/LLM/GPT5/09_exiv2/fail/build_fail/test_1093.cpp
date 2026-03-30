#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"

using namespace Exiv2;
using ::testing::Return;

// Mocking the BasicIo class for external dependencies
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(void, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(void, seek, (size_t), (override));
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, read, (uint8_t* buffer, size_t size), (override));
    MOCK_METHOD(void, write, (const uint8_t* buffer, size_t size), (override));
};

// Test Fixture for Image class
class ImageTest : public ::testing::Test {
protected:
    std::unique_ptr<MockBasicIo> mockIo;
    Image* image;

    // SetUp for initializing mock Io object and Image instance
    void SetUp() override {
        mockIo = std::make_unique<MockBasicIo>();
        image = new Image(ImageType::tiffImage, 0, std::move(mockIo));
    }

    // TearDown for cleaning up
    void TearDown() override {
        delete image;
    }
};

// TEST_ID 1093
TEST_F(ImageTest, IoFunctionality_1093) {
    // Verify if the io function returns the expected object reference
    EXPECT_EQ(&image->io(), mockIo.get());
}

// TEST_ID 1094
TEST_F(ImageTest, SetComment_1094) {
    std::string comment = "Test comment";

    // Using the mock image instance to test the setComment functionality
    EXPECT_CALL(*mockIo, write(::testing::_, ::testing::_))
        .Times(1);

    image->setComment(comment);
    EXPECT_EQ(image->comment(), comment);
}

// TEST_ID 1095
TEST_F(ImageTest, ClearComment_1095) {
    std::string comment = "Test comment";
    image->setComment(comment);
    
    // Verify the comment is set
    EXPECT_EQ(image->comment(), comment);
    
    // Now, clear the comment and verify it's empty
    image->clearComment();
    EXPECT_EQ(image->comment(), "");
}

// TEST_ID 1096
TEST_F(ImageTest, SetMetadata_1096) {
    // Prepare mock image object for setting metadata
    Image anotherImage(ImageType::jpegImage, 0, std::move(mockIo));
    anotherImage.setComment("Another comment");

    // Test setMetadata
    image->setMetadata(anotherImage);
    
    // Verify the metadata was copied (by verifying comment in this case)
    EXPECT_EQ(image->comment(), "Another comment");
}

// TEST_ID 1097
TEST_F(ImageTest, BoundaryConditions_1097) {
    // Testing boundary condition for pixel width and height
    EXPECT_EQ(image->pixelWidth(), 0); // default value
    EXPECT_EQ(image->pixelHeight(), 0); // default value
}

// TEST_ID 1098
TEST_F(ImageTest, InvalidExifData_1098) {
    ExifData invalidExifData;
    // Test setting invalid ExifData
    EXPECT_NO_THROW(image->setExifData(invalidExifData));
    
    // Clear and ensure it's reset
    image->clearExifData();
    EXPECT_EQ(image->exifData().size(), 0);
}

// TEST_ID 1099
TEST_F(ImageTest, WriteXmpFromPacket_1099) {
    // Verify the writeXmpFromPacket method
    image->writeXmpFromPacket(true);
    EXPECT_TRUE(image->writeXmpFromPacket());
    
    image->writeXmpFromPacket(false);
    EXPECT_FALSE(image->writeXmpFromPacket());
}