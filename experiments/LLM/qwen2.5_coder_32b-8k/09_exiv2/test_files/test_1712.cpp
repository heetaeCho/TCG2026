#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/pgfimage.hpp"

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

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class PgfImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        pgf_image = std::make_unique<PgfImage>(std::move(mock_io), false);

    }



    std::unique_ptr<MockBasicIo> mock_io;

    std::unique_ptr<PgfImage> pgf_image;

};



TEST_F(PgfImageTest, WriteMetadata_SuccessfulWrite_1712) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, close()).Times(1);

    EXPECT_CALL(*mock_io, transfer(_)).Times(1);



    pgf_image->writeMetadata();

}



TEST_F(PgfImageTest, WriteMetadata_OpenFails_ThrowsError_1712) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(-1));

    EXPECT_THROW(pgf_image->writeMetadata(), Error);

}



TEST_F(PgfImageTest, WriteMetadata_TransferFails_ThrowsError_1712) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, close()).Times(1);

    EXPECT_CALL(*mock_io, transfer(_)).WillOnce(Throw(Error(ErrorCode::kerTransferFailed, "", "")));



    EXPECT_THROW(pgf_image->writeMetadata(), Error);

}



TEST_F(PgfImageTest, WriteMetadata_CloseFails_ThrowsError_1712) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, close()).WillOnce(Return(-1));

    EXPECT_CALL(*mock_io, transfer(_)).Times(1);



    EXPECT_THROW(pgf_image->writeMetadata(), Error);

}
