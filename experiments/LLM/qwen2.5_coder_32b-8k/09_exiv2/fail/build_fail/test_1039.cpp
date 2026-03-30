#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmpimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using testing::_;

using testing::NiceMock;

using testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class BmpImageTest_1039 : public testing::Test {

protected:

    NiceMock<MockBasicIo> mock_io;

    BmpImage bmp_image{std::make_unique<MockBasicIo>(mock_io)};

};



TEST_F(BmpImageTest_1039, ReadMetadata_SuccessfulRead_1039) {

    byte header[26] = { 'B', 'M', 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                        0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00,

                        0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00 };

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, read(header, 26)).WillOnce(Return(26u));

    EXPECT_CALL(mock_io, path()).Times(1);



    bmp_image.readMetadata();



    EXPECT_EQ(bmp_image.pixelWidth(), 1u);

    EXPECT_EQ(bmp_image.pixelHeight(), 1u);

}



TEST_F(BmpImageTest_1039, ReadMetadata_FileOpenFailed_1039) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(-1));

    EXPECT_CALL(mock_io, path()).Times(1);



    EXPECT_THROW({

        bmp_image.readMetadata();

    }, Error);

}



TEST_F(BmpImageTest_1039, ReadMetadata_NotABmpFile_1039) {

    byte header[26] = { 'B', 'M' };

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, read(header, 26)).WillOnce(Return(2u));

    EXPECT_CALL(mock_io, path()).Times(1);

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(false));



    EXPECT_THROW({

        bmp_image.readMetadata();

    }, Error);

}



TEST_F(BmpImageTest_1039, ReadMetadata_ReadFailed_1039) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, read(_, 26)).WillOnce(Return(25u));

    EXPECT_CALL(mock_io, path()).Times(1);

    EXPECT_CALL(mock_io, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mock_io, eof()).WillRepeatedly(Return(true));



    EXPECT_THROW({

        bmp_image.readMetadata();

    }, Error);

}
