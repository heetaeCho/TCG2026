#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/riffvideo.hpp"

#include <memory>



using namespace Exiv2;



class RiffVideoTest_77 : public ::testing::Test {

protected:

    class MockBasicIo : public BasicIo {

    public:

        MOCK_METHOD(void, read, (byte* buf, long cnt), (override));

        MOCK_METHOD(void, write, (const byte* buf, long cnt), (override));

        MOCK_METHOD(long, tellg, (), (const override));

        MOCK_METHOD(void, seekg, (long offset, Position pos), (override));

        MOCK_METHOD(void, seekp, (long offset, Position pos), (override));

        MOCK_METHOD(long, size, (), (const override));

    };



    std::unique_ptr<MockBasicIo> mockIo;

    RiffVideo* riffVideo;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        riffVideo = new RiffVideo(std::move(mockIo));

    }



    void TearDown() override {

        delete riffVideo;

    }

};



TEST_F(RiffVideoTest_77, MimeTypeReturnsCorrectValue_77) {

    EXPECT_EQ(riffVideo->mimeType(), "video/riff");

}



TEST_F(RiffVideoTest_77, ReadMetadataDoesNotThrowOnNormalOperation_77) {

    EXPECT_NO_THROW(riffVideo->readMetadata());

}



TEST_F(RiffVideoTest_77, WriteMetadataDoesNotThrowOnNormalOperation_77) {

    EXPECT_NO_THROW(riffVideo->writeMetadata());

}
