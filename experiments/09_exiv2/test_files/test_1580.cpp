#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/rw2image.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class Rw2ImageTest : public ::testing::Test {

protected:

    class MockBasicIo : public BasicIo {

    public:

        MOCK_METHOD(void, open, (), (override));

        MOCK_METHOD(void, close, (), (override));

        MOCK_METHOD(size_t, read, (byte* data, size_t count), (override));

        MOCK_METHOD(void, write, (const byte* data, size_t count), (override));

        MOCK_METHOD(void, seek, (int64_t offset, Position pos), (override));

        MOCK_METHOD(int64_t, tell, (), (override));

        MOCK_METHOD(size_t, size, (), (override));

    };



    MockBasicIo mockBasicIo;

    std::unique_ptr<MockBasicIo> ioPtr = std::make_unique<MockBasicIo>();

    Rw2Image rw2Image{std::move(ioPtr)};

};



TEST_F(Rw2ImageTest_1580, WriteMetadataThrowsError_1580) {

    EXPECT_THROW(rw2Image.writeMetadata(), Error);

}



TEST_F(Rw2ImageTest_1580, WriteMetadataErrorCode_1580) {

    try {

        rw2Image.writeMetadata();

    } catch (const Error& error) {

        EXPECT_EQ(error.code(), ErrorCode::kerWritingImageFormatUnsupported);

    }

}



TEST_F(Rw2ImageTest_1580, WriteMetadataErrorMessage_1580) {

    try {

        rw2Image.writeMetadata();

    } catch (const Error& error) {

        EXPECT_STREQ(error.what(), "RW2");

    }

}
