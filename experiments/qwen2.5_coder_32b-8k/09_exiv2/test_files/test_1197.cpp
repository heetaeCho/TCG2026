#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmffimage.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

};



class BmffImageTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io_;

    std::unique_ptr<BmffImage> bmff_image_;



    void SetUp() override {

        mock_io_ = std::make_unique<MockBasicIo>();

        bmff_image_ = std::make_unique<BmffImage>(std::move(mock_io_), false, 10);

    }

};



TEST_F(BmffImageTest_1197, ParseTiffValidInput_1197) {

    EXPECT_CALL(*mock_io_, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, size()).WillOnce(Return(20));

    EXPECT_CALL(*mock_io_, read(_, 12)).WillOnce([](byte* buf, size_t rcount) -> size_t {

        std::memset(buf, 0xFF, rcount);

        return rcount;

    });



    bmff_image_->parseTiff(0x87654321, 20);

}



TEST_F(BmffImageTest_1197, ParseTiffLengthZero_1197) {

    EXPECT_NO_THROW(bmff_image_->parseTiff(0x87654321, 0));

}



TEST_F(BmffImageTest_1197, ParseTiffLengthTooLarge_1197) {

    EXPECT_CALL(*mock_io_, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, size()).WillOnce(Return(8));



    EXPECT_THROW(bmff_image_->parseTiff(0x87654321, 10), Error);

}



TEST_F(BmffImageTest_1197, ParseTiffInsufficientDataRead_1197) {

    EXPECT_CALL(*mock_io_, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, size()).WillOnce(Return(20));

    EXPECT_CALL(*mock_io_, read(_, 12)).WillOnce(Return(8));



    EXPECT_THROW(bmff_image_->parseTiff(0x87654321, 20), Error);

}



TEST_F(BmffImageTest_1197, ParseTiffReadError_1197) {

    EXPECT_CALL(*mock_io_, tell()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, size()).WillOnce(Return(20));

    EXPECT_CALL(*mock_io_, read(_, 12)).WillOnce([](byte*, size_t) -> size_t {

        return 0;

    });

    EXPECT_CALL(*mock_io_, error()).WillOnce(Return(1));



    EXPECT_THROW(bmff_image_->parseTiff(0x87654321, 20), Error);

}
