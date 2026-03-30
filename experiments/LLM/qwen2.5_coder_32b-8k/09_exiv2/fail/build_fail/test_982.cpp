#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/mrwimage.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using namespace testing;



// Mocking BasicIo class as an external collaborator

class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (OpenMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(size_t, read, (byte* data, size_t len), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t len), (override));

    MOCK_METHOD(bool, seek, (long offset, Position whence), (override));

    MOCK_METHOD(long, tell, (), (override));

    MOCK_METHOD(void, invalidate, (), (override));

    MOCK_METHOD(void, muteErrors, (bool onOff), (override));

};



class MrwImageTest_982 : public Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    MrwImage* mrwImage;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        mrwImage = new MrwImage(std::move(mockIo), false);

    }



    void TearDown() override {

        delete mrwImage;

    }

};



TEST_F(MrwImageTest_982, WriteMetadataThrowsError_982) {

    EXPECT_THROW(mrwImage->writeMetadata(), Error);

}



TEST_F(MrwImageTest_982, WriteMetadataErrorHasCorrectCode_982) {

    try {

        mrwImage->writeMetadata();

        FAIL() << "Expected an exception to be thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerWritingImageFormatUnsupported);

    }

}



TEST_F(MrwImageTest_982, WriteMetadataErrorHasCorrectMessage_982) {

    try {

        mrwImage->writeMetadata();

        FAIL() << "Expected an exception to be thrown";

    } catch (const Error& e) {

        EXPECT_STREQ(e.what(), "MRW");

    }

}



TEST_F(MrwImageTest_982, ReadMetadataDoesNotThrowError_982) {

    EXPECT_NO_THROW(mrwImage->readMetadata());

}



TEST_F(MrwImageTest_982, SetExifDataDoesNotThrowError_982) {

    ExifData exifData;

    EXPECT_NO_THROW(mrwImage->setExifData(exifData));

}



TEST_F(MrwImageTest_982, SetIptcDataDoesNotThrowError_982) {

    IptcData iptcData;

    EXPECT_NO_THROW(mrwImage->setIptcData(iptcData));

}



TEST_F(MrwImageTest_982, SetCommentDoesNotThrowError_982) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(mrwImage->setComment(comment));

}



TEST_F(MrwImageTest_982, MimeTypeReturnsCorrectValue_982) {

    EXPECT_EQ(mrwImage->mimeType(), "image/x-minolta-mrw");

}



TEST_F(MrwImageTest_982, PixelWidthDoesNotThrowError_982) {

    EXPECT_NO_THROW(mrwImage->pixelWidth());

}



TEST_F(MrwImageTest_982, PixelHeightDoesNotThrowError_982) {

    EXPECT_NO_THROW(mrwImage->pixelHeight());

}
