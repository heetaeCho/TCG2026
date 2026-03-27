#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/psdimage.hpp"

#include "exiv2/basicio.hpp"



using namespace testing;

using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

};



class PsdImageTest : public Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io = std::make_unique<MockBasicIo>();

    PsdImage psd_image{std::move(mock_io)};

};



TEST_F(PsdImageTest_1186, ReadMetadata_SuccessfulRead_1186) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.psd"));

    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(1024));



    byte buf[26] = {0x38, 0x42, 0x50, 0x53, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                    0x04, 0x00, 0x08, 0x00, 0x03, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00};

    byte zeroBuf[4] = {0x00, 0x00, 0x00, 0x00};



    EXPECT_CALL(*mock_io, read(_, 26)).WillOnce(DoAll(SetArrayArgument<0>(buf, buf + 26), Return(26)));

    EXPECT_CALL(*mock_io, read(zeroBuf, 4)).WillOnce(Return(4));

    EXPECT_CALL(*mock_io, seek(8, BasicIo::cur)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, read(_, 4)).WillOnce(Return(4));



    byte resourceHeader[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    EXPECT_CALL(*mock_io, read(resourceHeader, 8)).WillOnce(Return(8));

    EXPECT_CALL(*mock_io, seek(10, BasicIo::cur)).WillOnce(Return(0));



    EXPECT_NO_THROW(psd_image.readMetadata());

}



TEST_F(PsdImageTest_1186, ReadMetadata_OpenFileFailed_1186) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.psd"));



    EXPECT_THROW(psd_image.readMetadata(), Error);

}



TEST_F(PsdImageTest_1186, ReadMetadata_NotPsdFile_1186) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.psd"));

    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(1024));



    byte buf[26] = {0x38, 0x42, 0x50, 0x53, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                    0x04, 0x00, 0x08, 0x00, 0x03, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x07};

    EXPECT_CALL(*mock_io, read(_, 26)).WillOnce(DoAll(SetArrayArgument<0>(buf, buf + 26), Return(26)));



    EXPECT_THROW(psd_image.readMetadata(), Error);

}



TEST_F(PsdImageTest_1186, ReadMetadata_ReadFailed_1186) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.psd"));

    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(1024));



    byte buf[26] = {0x38, 0x42, 0x50, 0x53, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                    0x04, 0x00, 0x08, 0x00, 0x03, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00};

    EXPECT_CALL(*mock_io, read(_, 26)).WillOnce(Return(25));



    EXPECT_THROW(psd_image.readMetadata(), Error);

}



TEST_F(PsdImageTest_1186, ReadMetadata_SeekFailed_1186) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.psd"));

    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(1024));



    byte buf[26] = {0x38, 0x42, 0x50, 0x53, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                    0x04, 0x00, 0x08, 0x00, 0x03, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00};

    byte zeroBuf[4] = {0x00, 0x00, 0x00, 0x00};



    EXPECT_CALL(*mock_io, read(_, 26)).WillOnce(DoAll(SetArrayArgument<0>(buf, buf + 26), Return(26)));

    EXPECT_CALL(*mock_io, read(zeroBuf, 4)).WillOnce(Return(4));

    EXPECT_CALL(*mock_io, seek(8, BasicIo::cur)).WillOnce(Return(-1));



    EXPECT_THROW(psd_image.readMetadata(), Error);

}



TEST_F(PsdImageTest_1186, ReadMetadata_CorruptedMetadata_1186) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.psd"));

    EXPECT_CALL(*mock_io, size()).WillRepeatedly(Return(1024));



    byte buf[26] = {0x38, 0x42, 0x50, 0x53, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

                    0x04, 0x00, 0x08, 0x00, 0x03, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00};

    byte zeroBuf[4] = {0xFF, 0xFF, 0xFF, 0xFF};



    EXPECT_CALL(*mock_io, read(_, 26)).WillOnce(DoAll(SetArrayArgument<0>(buf, buf + 26), Return(26)));

    EXPECT_CALL(*mock_io, read(zeroBuf, 4)).WillOnce(Return(4));

    EXPECT_CALL(*mock_io, seek(8, BasicIo::cur)).WillOnce(Return(0));



    EXPECT_THROW(psd_image.readMetadata(), Error);

}
