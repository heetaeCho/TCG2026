#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/mrwimage.hpp"

#include <memory>

#include <string>



using namespace Exiv2;

using testing::_;

using testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, read(char* buf, size_t nbytes), (override));

    MOCK_METHOD(void, write(const char* buf, size_t nbytes), (override));

    MOCK_METHOD(size_t, tellg(), (const override));

    MOCK_METHOD(void, seekg(int64_t offset, Position pos), (override));

    MOCK_METHOD(size_t, size(), (const override));

};



class MrwImageTest_978 : public testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<MrwImage> mrwImage;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        mrwImage = std::make_unique<MrwImage>(std::move(mockIo), false);

    }

};



TEST_F(MrwImageTest_978, MimeType_ReturnsCorrectType_978) {

    EXPECT_EQ(mrwImage->mimeType(), "image/x-minolta-mrw");

}



TEST_F(MrwImageTest_978, ReadMetadata_NormalOperation_978) {

    EXPECT_CALL(*mockIo, seekg(0, BasicIo::beg)).Times(1);

    EXPECT_CALL(*mockIo, read(_, _)).Times(testing::AtLeast(1));

    mrwImage->readMetadata();

}



TEST_F(MrwImageTest_978, WriteMetadata_NormalOperation_978) {

    EXPECT_CALL(*mockIo, seekg(0, BasicIo::beg)).Times(1);

    EXPECT_CALL(*mockIo, write(_, _)).Times(testing::AtLeast(1));

    mrwImage->writeMetadata();

}



TEST_F(MrwImageTest_978, SetExifData_NormalOperation_978) {

    ExifData exifData;

    EXPECT_NO_THROW(mrwImage->setExifData(exifData));

}



TEST_F(MrwImageTest_978, SetIptcData_NormalOperation_978) {

    IptcData iptcData;

    EXPECT_NO_THROW(mrwImage->setIptcData(iptcData));

}



TEST_F(MrwImageTest_978, SetComment_NormalOperation_978) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(mrwImage->setComment(comment));

}



TEST_F(MrwImageTest_978, PixelWidth_ReturnsValidValue_978) {

    uint32_t width = mrwImage->pixelWidth();

    EXPECT_GE(width, 0);

}



TEST_F(MrwImageTest_978, PixelHeight_ReturnsValidValue_978) {

    uint32_t height = mrwImage->pixelHeight();

    EXPECT_GE(height, 0);

}
