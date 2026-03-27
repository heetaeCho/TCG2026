#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmffimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using testing::NiceMock;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (OpenMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, read, (byte* data, size_t n), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t n), (override));

    MOCK_METHOD(void, seek, (long offset, Position pos), (override));

    MOCK_METHOD(long, tell, (), (override));

};



class BmffImageTest : public testing::Test {

protected:

    std::unique_ptr<NiceMock<MockBasicIo>> io_;

    std::unique_ptr<Image> image_;



    void SetUp() override {

        io_ = std::make_unique<NiceMock<MockBasicIo>>();

        image_ = newBmffInstance(std::move(io_), false);

    }

};



TEST_F(BmffImageTest_1203, ImageCreationNormalOperation_1203) {

    EXPECT_NE(image_, nullptr);

}



TEST_F(BmffImageTest_1203, ImageCreationWithCreateFlagTrue_1203) {

    io_.reset(new NiceMock<MockBasicIo>());

    auto image = newBmffInstance(std::move(io_), true);

    EXPECT_NE(image, nullptr);

}



TEST_F(BmffImageTest_1203, ImageCreationWhenIoIsNotGood_1203) {

    ON_CALL(*io_, good()).WillByDefault(testing::Return(false));

    io_.reset(new NiceMock<MockBasicIo>());

    auto image = newBmffInstance(std::move(io_), false);

    EXPECT_EQ(image, nullptr);

}



TEST_F(BmffImageTest_1203, ImageGoodMethodReturnsTrueAfterCreation_1203) {

    EXPECT_TRUE(image_->good());

}



TEST_F(BmffImageTest_1203, ImageGoodMethodReturnsFalseWhenIoIsNotGood_1203) {

    ON_CALL(*io_, good()).WillByDefault(testing::Return(false));

    io_.reset(new NiceMock<MockBasicIo>());

    auto image = newBmffInstance(std::move(io_), false);

    EXPECT_EQ(image->good(), false);

}



TEST_F(BmffImageTest_1203, ImageReadMetadataDoesNotCrash_1203) {

    EXPECT_NO_THROW(image_->readMetadata());

}



TEST_F(BmffImageTest_1203, ImageWriteMetadataDoesNotCrash_1203) {

    EXPECT_NO_THROW(image_->writeMetadata());

}



TEST_F(BmffImageTest_1203, ImageSetAndGetExifDataWorks_1203) {

    ExifData exifData;

    image_->setExifData(exifData);

    EXPECT_EQ(&image_->exifData(), &exifData);

}



TEST_F(BmffImageTest_1203, ImageClearExifDataDoesNotCrash_1203) {

    EXPECT_NO_THROW(image_->clearExifData());

}



TEST_F(BmffImageTest_1203, ImageSetAndGetIptcDataWorks_1203) {

    IptcData iptcData;

    image_->setIptcData(iptcData);

    EXPECT_EQ(&image_->iptcData(), &iptcData);

}



TEST_F(BmffImageTest_1203, ImageClearIptcDataDoesNotCrash_1203) {

    EXPECT_NO_THROW(image_->clearIptcData());

}



TEST_F(BmffImageTest_1203, ImageSetAndGetXmpPacketWorks_1203) {

    std::string xmpPacket = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">Some XMP Packet</x:xmpmeta>";

    image_->setXmpPacket(xmpPacket);

    EXPECT_EQ(image_->xmpPacket(), xmpPacket);

}



TEST_F(BmffImageTest_1203, ImageClearXmpPacketDoesNotCrash_1203) {

    EXPECT_NO_THROW(image_->clearXmpPacket());

}



TEST_F(BmffImageTest_1203, ImageSetAndGetXmpDataWorks_1203) {

    XmpData xmpData;

    image_->setXmpData(xmpData);

    EXPECT_EQ(&image_->xmpData(), &xmpData);

}



TEST_F(BmffImageTest_1203, ImageClearXmpDataDoesNotCrash_1203) {

    EXPECT_NO_THROW(image_->clearXmpData());

}



TEST_F(BmffImageTest_1203, ImageSetAndGetCommentWorks_1203) {

    std::string comment = "Sample Comment";

    image_->setComment(comment);

    EXPECT_EQ(image_->comment(), comment);

}



TEST_F(BmffImageTest_1203, ImageClearCommentDoesNotCrash_1203) {

    EXPECT_NO_THROW(image_->clearComment());

}



TEST_F(BmffImageTest_1203, ImageSetAndGetIccProfileWorks_1203) {

    DataBuf iccProfile = {"Some ICC Profile Data", 21};

    image_->setIccProfile(std::move(iccProfile), false);

    EXPECT_EQ(image_->iccProfile().pData_, "Some ICC Profile Data");

}



TEST_F(BmffImageTest_1203, ImageClearIccProfileDoesNotCrash_1203) {

    EXPECT_NO_THROW(image_->clearIccProfile());

}
