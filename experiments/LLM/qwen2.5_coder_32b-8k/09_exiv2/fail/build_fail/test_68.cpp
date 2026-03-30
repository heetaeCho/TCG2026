#include <gtest/gtest.h>

#include "exiv2/webpimage.hpp"

#include <memory>

#include <string>



namespace Exiv2 {

    class BasicIo;

    using BasicIo::UniquePtr;

}



class MockBasicIo : public Exiv2::BasicIo {

public:

    MOCK_METHOD(void, readMemory, (byte* data, size_t nbytes), (override));

    MOCK_METHOD(void, writeMemory, (const byte* data, size_t nbytes), (override));

    MOCK_METHOD(void, seek, (long offset, Position pos), (override));

    MOCK_METHOD(long, tell, (), (override));

    MOCK_METHOD(size_t, size, (), (override));

};



class WebPImageTest_68 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        webpImage = std::make_unique<Exiv2::WebPImage>(std::move(mockIo));

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<Exiv2::WebPImage> webpImage;

};



TEST_F(WebPImageTest_68, MimeTypeReturnsCorrectType_68) {

    EXPECT_EQ(webpImage->mimeType(), "image/webp");

}



TEST_F(WebPImageTest_68, SetCommentDoesNotThrow_68) {

    EXPECT_NO_THROW(webpImage->setComment("Sample comment"));

}



TEST_F(WebPImageTest_68, SetIptcDataDoesNotThrow_68) {

    Exiv2::IptcData iptcData;

    EXPECT_NO_THROW(webpImage->setIptcData(iptcData));

}



TEST_F(WebPImageTest_68, ReadMetadataDoesNotThrow_68) {

    EXPECT_CALL(*mockIo, seek(0L, Exiv2::BasicIo::beg)).Times(1);

    EXPECT_CALL(*mockIo, readMemory(::testing::_, ::testing::_)).Times(::testing::AtLeast(1));

    EXPECT_NO_THROW(webpImage->readMetadata());

}



TEST_F(WebPImageTest_68, WriteMetadataDoesNotThrow_68) {

    EXPECT_CALL(*mockIo, seek(0L, Exiv2::BasicIo::beg)).Times(1);

    EXPECT_CALL(*mockIo, writeMemory(::testing::_, ::testing::_)).Times(::testing::AtLeast(1));

    EXPECT_NO_THROW(webpImage->writeMetadata());

}



TEST_F(WebPImageTest_68, PrintStructureDoesNotThrow_68) {

    std::ostringstream out;

    EXPECT_NO_THROW(webpImage->printStructure(out, Exiv2::kpsNone, 0U));

}
