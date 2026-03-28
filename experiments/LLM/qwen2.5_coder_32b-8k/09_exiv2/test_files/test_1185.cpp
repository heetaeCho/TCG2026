#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/psdimage.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, read, (char*, long), (override));

    MOCK_METHOD(void, write, (const char*, long), (override));

    MOCK_METHOD(void, seek, (long, PositionFrom), (override));

    MOCK_METHOD(long, tell, (), (override));

};



class PsdImageTest_1185 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    PsdImage psdImage;



    PsdImageTest_1185() : mockIo(std::make_unique<MockBasicIo>()), psdImage(std::move(mockIo)) {}

};



TEST_F(PsdImageTest_1185, MimeTypeReturnsCorrectType_1185) {

    EXPECT_EQ(psdImage.mimeType(), "image/x-photoshop");

}



TEST_F(PsdImageTest_1185, ReadMetadataDoesNotThrow_1185) {

    EXPECT_NO_THROW(psdImage.readMetadata());

}



TEST_F(PsdImageTest_1185, WriteMetadataDoesNotThrow_1185) {

    EXPECT_NO_THROW(psdImage.writeMetadata());

}



TEST_F(PsdImageTest_1185, SetCommentDoesNotThrow_1185) {

    EXPECT_NO_THROW(psdImage.setComment("Sample Comment"));

}



TEST_F(PsdImageTest_1185, ReadMetadataInvokesReadOnIo_1185) {

    EXPECT_CALL(*mockIo, read(_, _)).Times(1);

    psdImage.readMetadata();

}



TEST_F(PsdImageTest_1185, WriteMetadataInvokesWriteOnIo_1185) {

    EXPECT_CALL(*mockIo, write(_, _)).Times(AtLeast(1));

    psdImage.writeMetadata();

}
