#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/asfvideo.hpp"



using namespace Exiv2;

using testing::NiceMock;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, read, (byte* data, size_t n), (override));

    MOCK_METHOD(void, write, (const byte* data, size_t n), (override));

    MOCK_METHOD(void, seek, (long offset, Position pos), (override));

    MOCK_METHOD(long, tell, (), (override));

    MOCK_METHOD(void, close, (), (override));

};



class AsfVideoTest_1561 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    AsfVideo* asfVideo;



    void SetUp() override {

        mockIo = std::make_unique<NiceMock<MockBasicIo>>();

        asfVideo = new AsfVideo(std::move(mockIo));

    }



    void TearDown() override {

        delete asfVideo;

    }

};



TEST_F(AsfVideoTest_1561, MimeTypeReturnsCorrectValue_1561) {

    EXPECT_EQ(asfVideo->mimeType(), "video/asf");

}



TEST_F(AsfVideoTest_1561, ReadMetadataDoesNotThrowOnValidIo_1561) {

    EXPECT_NO_THROW(asfVideo->readMetadata());

}



TEST_F(AsfVideoTest_1561, WriteMetadataDoesNotThrowOnValidIo_1561) {

    EXPECT_NO_THROW(asfVideo->writeMetadata());

}
