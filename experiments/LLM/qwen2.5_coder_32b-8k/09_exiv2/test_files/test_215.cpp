#include <gtest/gtest.h>

#include "exiv2/jpgimage.hpp"

#include <memory>



namespace Exiv2 {

    class MockBasicIo : public BasicIo {

    public:

        MOCK_METHOD(void, read, (byte* buf, size_t n), (override));

        MOCK_METHOD(void, write, (const byte* buf, size_t n), (override));

        MOCK_METHOD(size_t, tellg, (), (override));

        MOCK_METHOD(void, seekg, (size_t pos), (override));

        MOCK_METHOD(void, seekp, (size_t pos), (override));

        MOCK_METHOD(bool, good, (), (const, override));

    };

}



using namespace Exiv2;



class JpegImageTest_215 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    JpegImage* jpeg_image;



    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        jpeg_image = new JpegImage(std::move(mock_io), false);

    }



    void TearDown() override {

        delete jpeg_image;

    }

};



TEST_F(JpegImageTest_215, numColorComponents_ReturnsDefault_215) {

    EXPECT_EQ(jpeg_image->numColorComponents(), -1);

}



TEST_F(JpegImageTest_215, mimeType_ReturnsExpectedValue_215) {

    EXPECT_EQ(jpeg_image->mimeType(), "image/jpeg");

}



TEST_F(JpegImageTest_215, isJpegType_AdvanceFalse_ReturnsTrue_215) {

    MockBasicIo& io = *mock_io;

    EXPECT_CALL(io, good()).WillRepeatedly(::testing::Return(true));

    EXPECT_TRUE(jpeg_image->isJpegType(io, false));

}



TEST_F(JpegImageTest_215, isJpegType_AdvanceTrue_ReturnsTrue_215) {

    MockBasicIo& io = *mock_io;

    EXPECT_CALL(io, good()).WillRepeatedly(::testing::Return(true));

    EXPECT_TRUE(jpeg_image->isJpegType(io, true));

}



TEST_F(JpegImageTest_215, encodingProcess_ReturnsEmptyString_215) {

    EXPECT_EQ(jpeg_image->encodingProcess(), "");

}
