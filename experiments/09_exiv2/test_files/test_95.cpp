#include <gtest/gtest.h>

#include "exiv2/matroskavideo.hpp"

#include <memory>



namespace {



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, read, (byte* data, size_t count), (override));

    MOCK_METHOD(void, write, (const byte* data, size_t count), (override));

    MOCK_METHOD(void, seek, (long offset, Position whence), (override));

    MOCK_METHOD(size_t, tell, (), (const override));

    MOCK_METHOD(size_t, size, (), (const override));

};



class MatroskaVideoTest_95 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    MatroskaVideo* matroska_video;



    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        matroska_video = new MatroskaVideo(std::move(mock_io));

    }



    void TearDown() override {

        delete matroska_video;

    }

};



TEST_F(MatroskaVideoTest_95, MimeTypeReturnsCorrectType_95) {

    EXPECT_EQ(matroska_video->mimeType(), "video/matroska");

}



TEST_F(MatroskaVideoTest_95, ReadMetadataDoesNotThrow_95) {

    EXPECT_NO_THROW(matroska_video->readMetadata());

}



TEST_F(MatroskaVideoTest_95, WriteMetadataDoesNotThrow_95) {

    EXPECT_NO_THROW(matroska_video->writeMetadata());

}



}  // namespace
