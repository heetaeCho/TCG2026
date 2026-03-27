#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



// Mock class for BasicIo to satisfy constructor requirements

class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, read, (byte* data, size_t nbytes), (override));

    MOCK_METHOD(void, write, (const byte* data, size_t nbytes), (override));

    MOCK_METHOD(size_t, tellg, (), (const, override));

    MOCK_METHOD(std::streampos, seekg, (std::streampos pos), (override));

    MOCK_METHOD(void, open, (const std::string& path, int mode), (override));

    MOCK_METHOD(void, close, (), (override));

};



class ImageTest_1049 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io_;

    Image* image_;



    void SetUp() override {

        mock_io_ = std::make_unique<MockBasicIo>();

        image_ = new Image(imageTypeJpeg, supportedExif | supportedIptc | supportedXmp, std::move(mock_io_));

    }



    void TearDown() override {

        delete image_;

    }

};



TEST_F(ImageTest_1049, IsLongType_UnsignedLong_1049) {

    EXPECT_TRUE(image_->isLongType(unsignedLong));

}



TEST_F(ImageTest_1049, IsLongType_SignedLong_1049) {

    EXPECT_TRUE(image_->isLongType(signedLong));

}



TEST_F(ImageTest_1049, IsLongType_OtherTypes_1049) {

    EXPECT_FALSE(image_->isLongType(unsignedShort));

    EXPECT_FALSE(image_->isLongType(asciiString));

    EXPECT_FALSE(image_->isLongType(unsignedByte));

}



TEST_F(ImageTest_1049, BoundaryCondition_IsLongType_MinValue_1049) {

    EXPECT_FALSE(image_->isLongType(static_cast<uint16_t>(0)));

}



TEST_F(ImageTest_1049, BoundaryCondition_IsLongType_MaxValue_1049) {

    EXPECT_FALSE(image_->isLongType(lastTypeId));

}
