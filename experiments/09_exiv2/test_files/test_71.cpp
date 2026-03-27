#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/webpimage.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class WebPImageTest_71 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        webpImage = std::make_unique<WebPImage>(std::move(mockIo));

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<WebPImage> webpImage;

};



TEST_F(WebPImageTest_71, ReadMetadata_SuccessfulRead_71) {

    byte dummyData[WEBP_TAG_SIZE * 3] = {0};

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockIo, isopen()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(*mockIo, readOrThrow(::testing::NotNull(), WEBP_TAG_SIZE * 3, ErrorCode::kerCorruptedMetadata)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(dummyData, dummyData + (WEBP_TAG_SIZE * 3)),

        ::testing::Return()

    ));

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(100));



    webpImage->readMetadata();

}



TEST_F(WebPImageTest_71, ReadMetadata_OpenFailed_71) {

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(-1));



    EXPECT_THROW(webpImage->readMetadata(), Error);

}



TEST_F(WebPImageTest_71, ReadMetadata_NotWebPType_71) {

    byte dummyData[WEBP_TAG_SIZE * 3] = {0};

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockIo, isopen()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(*mockIo, readOrThrow(::testing::NotNull(), WEBP_TAG_SIZE * 3, ErrorCode::kerCorruptedMetadata)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(dummyData, dummyData + (WEBP_TAG_SIZE * 3)),

        ::testing::Return()

    ));

    EXPECT_CALL(*mockIo, error()).WillRepeatedly(::testing::Return(0));

    EXPECT_CALL(*mockIo, eof()).WillRepeatedly(::testing::Return(false));



    EXPECT_THROW(webpImage->readMetadata(), Error);

}



TEST_F(WebPImageTest_71, ReadMetadata_CorruptedFilesize_71) {

    byte dummyData[WEBP_TAG_SIZE * 3] = {0};

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockIo, isopen()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(*mockIo, readOrThrow(::testing::NotNull(), WEBP_TAG_SIZE * 3, ErrorCode::kerCorruptedMetadata)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(dummyData, dummyData + (WEBP_TAG_SIZE * 3)),

        ::testing::Return()

    ));

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(::testing::Return(10));



    EXPECT_THROW(webpImage->readMetadata(), Error);

}



TEST_F(WebPImageTest_71, ReadMetadata_ErrorReadingImageData_71) {

    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockIo, isopen()).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(*mockIo, readOrThrow(::testing::NotNull(), WEBP_TAG_SIZE * 3, ErrorCode::kerCorruptedMetadata)).WillOnce(::testing::DoAll(

        ::testing::SetErrnoAndReturn(errno, -1),

        ::testing::Invoke([](byte* /*buf*/, size_t /*rcount*/, ErrorCode err) {

            throw Error(err, "dummyPath", strError());

        })

    ));



    EXPECT_THROW(webpImage->readMetadata(), Error);

}
