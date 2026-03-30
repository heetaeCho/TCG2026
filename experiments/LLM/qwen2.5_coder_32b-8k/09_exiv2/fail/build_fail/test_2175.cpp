#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/pngimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(size_t, write, (const byte *data, size_t wcount), (override));

    MOCK_METHOD(bool, isopen, (), (const, override));

};



class PngImageTest_2175 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io_;

    PngImage* png_image_;



    void SetUp() override {

        mock_io_ = std::make_unique<MockBasicIo>();

        png_image_ = new PngImage(std::move(mock_io_), false);

    }



    void TearDown() override {

        delete png_image_;

    }

};



TEST_F(PngImageTest_2175, ConstructorDoesNotWriteWhenCreateIsFalse_2175) {

    EXPECT_CALL(*mock_io_, open()).Times(0);

    EXPECT_CALL(*mock_io_, write(_, _)).Times(0);



    PngImage png_image(std::move(mock_io_), false);

}



TEST_F(PngImageTest_2175, ConstructorWritesWhenCreateIsTrueAndOpenSucceeds_2175) {

    const unsigned char expected_data[] = { /* Expected PNG data */ };

    EXPECT_CALL(*mock_io_, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, write(expected_data, sizeof(expected_data))).WillOnce(Return(sizeof(expected_data)));



    PngImage png_image(std::move(mock_io_), true);

}



TEST_F(PngImageTest_2175, ConstructorDoesNotWriteWhenCreateIsTrueButOpenFails_2175) {

    EXPECT_CALL(*mock_io_, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mock_io_, write(_, _)).Times(0);



    PngImage png_image(std::move(mock_io_), true);

}



TEST_F(PngImageTest_2175, ConstructorDoesNotWriteWhenCreateIsTrueButWriteFails_2175) {

    const unsigned char expected_data[] = { /* Expected PNG data */ };

    EXPECT_CALL(*mock_io_, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, write(expected_data, sizeof(expected_data))).WillOnce(Return(0));



    PngImage png_image(std::move(mock_io_), true);

}



TEST_F(PngImageTest_2175, MimeTypeReturnsCorrectType_2175) {

    EXPECT_EQ(png_image_->mimeType(), "image/png");

}
