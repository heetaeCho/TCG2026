#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/jpgimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(int, error, (), (override));

};



class JpegImageTest_1221 : public ::testing::Test {

protected:

    void SetUp() override {

        mockBasicIo = std::make_unique<MockBasicIo>();

        jpegImage = std::make_unique<JpegImage>(std::move(mockBasicIo), false);

    }



    std::unique_ptr<MockBasicIo> mockBasicIo;

    std::unique_ptr<JpegImage> jpegImage;

};



TEST_F(JpegImageTest_1221, WriteHeader_NormalOperation_1221) {

    byte expectedData[2] = {0xff, static_cast<byte>(soi_)};

    EXPECT_CALL(*mockBasicIo, write(expectedData, 2)).WillOnce(Return(2));

    EXPECT_CALL(*mockBasicIo, error()).WillOnce(Return(0));



    int result = jpegImage->writeHeader(*mockBasicIo);

    EXPECT_EQ(result, 0);

}



TEST_F(JpegImageTest_1221, WriteHeader_WriteFails_1221) {

    byte expectedData[2] = {0xff, static_cast<byte>(soi_)};

    EXPECT_CALL(*mockBasicIo, write(expectedData, 2)).WillOnce(Return(1));

    EXPECT_CALL(*mockBasicIo, error()).WillOnce(Return(0));



    int result = jpegImage->writeHeader(*mockBasicIo);

    EXPECT_EQ(result, 4);

}



TEST_F(JpegImageTest_1221, WriteHeader_WriteError_1221) {

    byte expectedData[2] = {0xff, static_cast<byte>(soi_)};

    EXPECT_CALL(*mockBasicIo, write(expectedData, 2)).WillOnce(Return(2));

    EXPECT_CALL(*mockBasicIo, error()).WillOnce(Return(1));



    int result = jpegImage->writeHeader(*mockBasicIo);

    EXPECT_EQ(result, 4);

}



TEST_F(JpegImageTest_1221, WriteHeader_WriteZeroBytes_1221) {

    byte expectedData[2] = {0xff, static_cast<byte>(soi_)};

    EXPECT_CALL(*mockBasicIo, write(expectedData, 2)).WillOnce(Return(0));

    EXPECT_CALL(*mockBasicIo, error()).WillOnce(Return(0));



    int result = jpegImage->writeHeader(*mockBasicIo);

    EXPECT_EQ(result, 4);

}
