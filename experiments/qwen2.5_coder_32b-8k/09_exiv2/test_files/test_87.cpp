#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/jp2image.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using testing::_;

using testing::Return;

using testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte *data, size_t wcount), (override));

    MOCK_METHOD(void, transfer, (BasicIo &src), (override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class Jp2ImageTest_87 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        jp2_image = new Jp2Image(std::move(mock_io), false);

    }



    void TearDown() override {

        delete jp2_image;

    }



    MockBasicIo* mock_io;

    Jp2Image* jp2_image;

};



TEST_F(Jp2ImageTest_87, WriteMetadata_SuccessfulWrite_87) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, close()).Times(1);

    EXPECT_CALL(*mock_io, transfer(_)).Times(1);



    ASSERT_NO_THROW(jp2_image->writeMetadata());

}



TEST_F(Jp2ImageTest_87, WriteMetadata_OpenFails_ThrowsError_87) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mock_io, path()).WillOnce(Return("test_path"));



    ASSERT_THROW(jp2_image->writeMetadata(), Error);

}



TEST_F(Jp2ImageTest_87, WriteMetadata_TransferFails_ThrowsError_87) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, close()).Times(1);

    EXPECT_CALL(*mock_io, transfer(_)).WillOnce(Throw(Error(ErrorCode::kerTransferFailed)));



    ASSERT_THROW(jp2_image->writeMetadata(), Error);

}



TEST_F(Jp2ImageTest_87, WriteMetadata_NormalOperation_TransferCalledWithMemIo_87) {

    MockBasicIo mock_temp_io;

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, close()).Times(1);

    EXPECT_CALL(mock_temp_io, transfer(_)).Times(1);



    jp2_image->writeMetadata();

}
