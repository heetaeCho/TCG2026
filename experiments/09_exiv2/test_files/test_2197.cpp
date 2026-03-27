#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/orfimage.hpp"

#include "exiv2/image.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (AccessMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const, override));

};



class OrfImageTest_2197 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    std::shared_ptr<OrfImage> orf_image;



    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        EXPECT_CALL(*mock_io, good()).WillRepeatedly(Return(true));

        orf_image = std::make_shared<OrfImage>(std::move(mock_io), false);

    }

};



TEST_F(OrfImageTest_2197, ConstructorInitializesSupportedMetadata_2197) {

    EXPECT_TRUE(orf_image->supportsMetadata(mdExif));

    EXPECT_TRUE(orf_image->supportsMetadata(mdIptc));

    EXPECT_TRUE(orf_image->supportsMetadata(mdXmp));

}



TEST_F(OrfImageTest_2197, MimeTypeReturnsCorrectType_2197) {

    EXPECT_EQ("image/x-orf", orf_image->mimeType());

}



TEST_F(OrfImageTest_2197, SetAndGetCommentWorks_2197) {

    const std::string comment = "Sample Comment";

    orf_image->setComment(comment);

    EXPECT_EQ(comment, orf_image->comment());

}



TEST_F(OrfImageTest_2197, ReadMetadataDoesNotThrow_2197) {

    EXPECT_NO_THROW(orf_image->readMetadata());

}



TEST_F(OrfImageTest_2197, WriteMetadataDoesNotThrow_2197) {

    EXPECT_NO_THROW(orf_image->writeMetadata());

}



TEST_F(OrfImageTest_2197, PrintStructureDoesNotThrow_2197) {

    std::ostringstream out;

    EXPECT_NO_THROW(orf_image->printStructure(out, psNone, 0));

}



TEST_F(OrfImageTest_2197, PixelWidthBoundaryCondition_2197) {

    EXPECT_EQ(0U, orf_image->pixelWidth());

}



TEST_F(OrfImageTest_2197, PixelHeightBoundaryCondition_2197) {

    EXPECT_EQ(0U, orf_image->pixelHeight());

}
