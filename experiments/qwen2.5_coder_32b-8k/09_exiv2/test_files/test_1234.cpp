#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/tgaimage.cpp"  // Assuming this file contains the necessary declarations



namespace Exiv2 {



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(std::string, path, (), (const override));

    MOCK_METHOD(void, seek, (long pos, Position from), (override));

    MOCK_METHOD(size_t, tell, (), (const override));

    MOCK_METHOD(bool, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t n), (override));

};



class TgaTypeTest : public ::testing::Test {

protected:

    MockBasicIo mock_io;

};



TEST_F(TgaTypeTest_1234, FileExtensionLowercaseTga_ReturnsTrue_1234) {

    EXPECT_CALL(mock_io, path()).WillOnce(::testing::Return("image.tga"));

    EXPECT_TRUE(isTgaType(mock_io, false));

}



TEST_F(TgaTypeTest_1234, FileExtensionUppercaseTga_ReturnsTrue_1234) {

    EXPECT_CALL(mock_io, path()).WillOnce(::testing::Return("IMAGE.TGA"));

    EXPECT_TRUE(isTgaType(mock_io, false));

}



TEST_F(TgaTypeTest_1234, FileWithoutTgaExtension_ReturnsFalse_1234) {

    EXPECT_CALL(mock_io, path()).WillOnce(::testing::Return("image.jpg"));

    EXPECT_FALSE(isTgaType(mock_io, false));

}



TEST_F(TgaTypeTest_1234, BufferTooSmall_ReturnsFalse_1234) {

    EXPECT_CALL(mock_io, path()).WillOnce(::testing::Return("image.tga"));

    EXPECT_CALL(mock_io, tell()).WillOnce(::testing::Return(10)); // Less than 26

    EXPECT_FALSE(isTgaType(mock_io, false));

}



TEST_F(TgaTypeTest_1234, SeekToEndOfFileError_ReturnsFalse_1234) {

    EXPECT_CALL(mock_io, path()).WillOnce(::testing::Return("image.tga"));

    EXPECT_CALL(mock_io, tell()).WillOnce(::testing::Return(30));

    EXPECT_CALL(mock_io, seek(-26, BasicIo::end)).WillOnce(testing::DoAll(testing::SetArgReferee<1>(true), testing::Return()));

    EXPECT_FALSE(isTgaType(mock_io, false));

}



TEST_F(TgaTypeTest_1234, SeekToEndOfFileEof_ReturnsFalse_1234) {

    EXPECT_CALL(mock_io, path()).WillOnce(::testing::Return("image.tga"));

    EXPECT_CALL(mock_io, tell()).WillOnce(::testing::Return(30));

    EXPECT_CALL(mock_io, seek(-26, BasicIo::end)).WillOnce(testing::DoAll(testing::SetArgReferee<1>(false), testing::Return()));

    EXPECT_CALL(mock_io, eof()).WillOnce(::testing::Return(true));

    EXPECT_FALSE(isTgaType(mock_io, false));

}



TEST_F(TgaTypeTest_1234, ReadFromFileError_ReturnsFalse_1234) {

    EXPECT_CALL(mock_io, path()).WillOnce(::testing::Return("image.tga"));

    EXPECT_CALL(mock_io, tell()).WillOnce(::testing::Return(30));

    EXPECT_CALL(mock_io, seek(-26, BasicIo::end)).WillOnce(testing::DoAll(testing::SetArgReferee<1>(false), testing::Return()));

    EXPECT_CALL(mock_io, eof()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mock_io, read(::testing::_, 26)).WillOnce(testing::DoAll(testing::SetArgReferee<0>(static_cast<byte*>(nullptr)), testing::Return(0)));

    EXPECT_CALL(mock_io, error()).WillOnce(::testing::Return(true));

    EXPECT_FALSE(isTgaType(mock_io, false));

}



TEST_F(TgaTypeTest_1234, ValidTruevisionSignature_ReturnsTrue_1234) {

    byte buf[26] = {0};

    memcpy(buf + 8, "TRUEVISION-XFILE", 16);



    EXPECT_CALL(mock_io, path()).WillOnce(::testing::Return("image.tga"));

    EXPECT_CALL(mock_io, tell()).WillOnce(::testing::Return(30));

    EXPECT_CALL(mock_io, seek(-26, BasicIo::end)).WillOnce(testing::DoAll(testing::SetArgReferee<1>(false), testing::Return()));

    EXPECT_CALL(mock_io, eof()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mock_io, read(::testing::_, 26)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(buf, buf + 26), testing::Return(26)));

    EXPECT_FALSE(mock_io.error());

    EXPECT_TRUE(isTgaType(mock_io, false));

}



TEST_F(TgaTypeTest_1234, InvalidTruevisionSignature_ReturnsFalse_1234) {

    byte buf[26] = {0};

    memcpy(buf + 8, "INVALID-SIGNATURE", 16);



    EXPECT_CALL(mock_io, path()).WillOnce(::testing::Return("image.tga"));

    EXPECT_CALL(mock_io, tell()).WillOnce(::testing::Return(30));

    EXPECT_CALL(mock_io, seek(-26, BasicIo::end)).WillOnce(testing::DoAll(testing::SetArgReferee<1>(false), testing::Return()));

    EXPECT_CALL(mock_io, eof()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mock_io, read(::testing::_, 26)).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(buf, buf + 26), testing::Return(26)));

    EXPECT_FALSE(mock_io.error());

    EXPECT_FALSE(isTgaType(mock_io, false));

}



}  // namespace Exiv2
