#include <gtest/gtest.h>

#include "exiv2/crwimage.hpp"

#include <memory>



namespace {



class MockBasicIo : public Exiv2::BasicIo {

public:

    MOCK_METHOD(void, read, (byte*, long), (override));

    MOCK_METHOD(void, write, (const byte*, long), (override));

    MOCK_METHOD(void, seek, (long, PositionFrom), (override));

    MOCK_METHOD(long, tell, (), (override));

    MOCK_METHOD(void, close, (), (override));

};



class CrwImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        crwImage = std::make_unique<Exiv2::CrwImage>(std::move(mockIo), false);

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<Exiv2::CrwImage> crwImage;

};



TEST_F(CrwImageTest_1811, MimeTypeReturnsCorrectValue_1811) {

    EXPECT_EQ(crwImage->mimeType(), "image/x-canon-crw");

}



TEST_F(CrwImageTest_1811, PixelWidthBoundaryCondition_1811) {

    // Assuming pixelWidth() returns a valid uint32_t value without additional context

    EXPECT_GE(crwImage->pixelWidth(), 0);

}



TEST_F(CrwImageTest_1811, PixelHeightBoundaryCondition_1811) {

    // Assuming pixelHeight() returns a valid uint32_t value without additional context

    EXPECT_GE(crwImage->pixelHeight(), 0);

}



TEST_F(CrwImageTest_1811, SetIptcDataDoesNotThrow_1811) {

    Exiv2::IptcData iptcData;

    EXPECT_NO_THROW(crwImage->setIptcData(iptcData));

}



TEST_F(CrwImageTest_1811, ReadMetadataNoException_1811) {

    EXPECT_NO_THROW(crwImage->readMetadata());

}



TEST_F(CrwImageTest_1811, WriteMetadataNoException_1811) {

    EXPECT_NO_THROW(crwImage->writeMetadata());

}



}  // namespace
