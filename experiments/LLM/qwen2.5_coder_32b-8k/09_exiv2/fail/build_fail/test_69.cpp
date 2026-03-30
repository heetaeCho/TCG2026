#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/webpimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo&), (override));

    MOCK_METHOD(const std::string&, path, (), (const override));

};



class WebPImageTest : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    WebPImage webp_image{std::make_unique<MockBasicIo>(mock_io)};

};



TEST_F(WebPImageTest_69, WriteMetadata_SuccessfulWrite_69) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, close()).Times(1);

    EXPECT_CALL(mock_io, transfer(_)).Times(1);



    webp_image.writeMetadata();

}



TEST_F(WebPImageTest_69, WriteMetadata_OpenFails_ThrowsException_69) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(-1));

    EXPECT_THROW(webp_image.writeMetadata(), Error);

}



TEST_F(WebPImageTest_69, WriteMetadata_TransferFails_ThrowsException_69) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, close()).Times(1);

    EXPECT_CALL(mock_io, transfer(_)).WillOnce(testing::Throw(Error(ErrorCode::kerTransferFailed)));



    EXPECT_THROW(webp_image.writeMetadata(), Error);

}



TEST_F(WebPImageTest_69, WriteMetadata_CloseFails_AfterSuccessfulWrite_69) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, close()).Times(1).WillOnce(testing::Return(-1));

    EXPECT_CALL(mock_io, transfer(_)).Times(1);



    webp_image.writeMetadata();

}



TEST_F(WebPImageTest_69, WriteMetadata_CloseFails_BeforeSuccessfulWrite_ThrowsException_69) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(-1));



    EXPECT_THROW(webp_image.writeMetadata(), Error);

}
