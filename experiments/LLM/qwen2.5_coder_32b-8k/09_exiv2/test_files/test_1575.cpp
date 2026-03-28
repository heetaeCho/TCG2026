#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/rw2image.hpp"

#include <memory>

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (OpenMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(size_t, read, (char* data, size_t length), (override));

    MOCK_METHOD(size_t, write, (const char* data, size_t length), (override));

    MOCK_METHOD(void, seek, (long offset, Position pos), (override));

    MOCK_METHOD(long, tell, (), (override));

    MOCK_METHOD(bool, good, (), (override));

};



class Rw2ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    std::unique_ptr<Rw2Image> rw2_image;



    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        rw2_image = std::make_unique<Rw2Image>(std::move(mock_io));

    }

};



TEST_F(Rw2ImageTest_1575, MimeTypeReturnsCorrectValue_1575) {

    EXPECT_EQ(rw2_image->mimeType(), "image/x-panasonic-rw2");

}



TEST_F(Rw2ImageTest_1575, PrintStructureDoesNotThrow_1575) {

    std::ostringstream oss;

    EXPECT_NO_THROW(rw2_image->printStructure(oss, 0, 0));

}



TEST_F(Rw2ImageTest_1575, ReadMetadataDoesNotThrow_1575) {

    EXPECT_CALL(*mock_io, open(_)).WillOnce(Return());

    EXPECT_CALL(*mock_io, good()).WillRepeatedly(Return(true));

    EXPECT_NO_THROW(rw2_image->readMetadata());

}



TEST_F(Rw2ImageTest_1575, WriteMetadataDoesNotThrow_1575) {

    EXPECT_CALL(*mock_io, open(_)).WillOnce(Return());

    EXPECT_CALL(*mock_io, good()).WillRepeatedly(Return(true));

    EXPECT_NO_THROW(rw2_image->writeMetadata());

}



TEST_F(Rw2ImageTest_1575, SetExifDataDoesNotThrow_1575) {

    ExifData exif_data;

    EXPECT_NO_THROW(rw2_image->setExifData(exif_data));

}



TEST_F(Rw2ImageTest_1575, SetIptcDataDoesNotThrow_1575) {

    IptcData iptc_data;

    EXPECT_NO_THROW(rw2_image->setIptcData(iptc_data));

}



TEST_F(Rw2ImageTest_1575, SetCommentDoesNotThrow_1575) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(rw2_image->setComment(comment));

}
