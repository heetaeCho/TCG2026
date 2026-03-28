#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>



namespace Exiv2 {

    class MockBasicIo : public BasicIo {

    public:

        MOCK_METHOD(void, clear, (), (override));

        MOCK_METHOD(size_t, read, (byte* data, size_t count), (override));

        MOCK_METHOD(size_t, write, (const byte* data, size_t count), (override));

        MOCK_METHOD(bool, seek, (int64_t offset, Position pos), (override));

        MOCK_METHOD(int64_t, tell, (), (override));

        MOCK_METHOD(void, close, (), (override));

        MOCK_METHOD(bool, good, (), (const, override));

    };

}



using namespace Exiv2;



class ImageTest_1067 : public ::testing::Test {

protected:

    void SetUp() override {

        auto mockIo = std::make_unique<MockBasicIo>();

        image = std::make_unique<Image>(ImageType::jpeg, 0x3F, std::move(mockIo));

    }



    std::unique_ptr<Image> image;

};



TEST_F(ImageTest_1067, ClearMetadata_ClearsAllData_1067) {

    // Assuming that after clearMetadata() all the data is cleared

    // We check if the getters return default values after clearing



    image->clearMetadata();



    EXPECT_TRUE(image->exifData().empty());

    EXPECT_TRUE(image->iptcData().empty());

    EXPECT_TRUE(image->xmpPacket().empty());

    EXPECT_TRUE(image->xmpData().empty());

    EXPECT_TRUE(image->comment().empty());

    EXPECT_TRUE(!image->iccProfileDefined());

}



TEST_F(ImageTest_1067, ClearExifData_ExifDataIsEmpty_1067) {

    image->clearExifData();

    EXPECT_TRUE(image->exifData().empty());

}



TEST_F(ImageTest_1067, ClearIptcData_IptcDataIsEmpty_1067) {

    image->clearIptcData();

    EXPECT_TRUE(image->iptcData().empty());

}



TEST_F(ImageTest_1067, ClearXmpPacket_XmpPacketIsEmpty_1067) {

    image->clearXmpPacket();

    EXPECT_TRUE(image->xmpPacket().empty());

}



TEST_F(ImageTest_1067, ClearXmpData_XmpDataIsEmpty_1067) {

    image->clearXmpData();

    EXPECT_TRUE(image->xmpData().empty());

}



TEST_F(ImageTest_1067, ClearComment_CommentIsEmpty_1067) {

    image->clearComment();

    EXPECT_TRUE(image->comment().empty());

}



TEST_F(ImageTest_1067, ClearIccProfile_IccProfileIsNotDefined_1067) {

    image->clearIccProfile();

    EXPECT_FALSE(image->iccProfileDefined());

}
