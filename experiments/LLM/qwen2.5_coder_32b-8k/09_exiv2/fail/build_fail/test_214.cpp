#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class GifTypeTest_214 : public ::testing::Test {

protected:

    MockBasicIo mockBasicIo;

};



TEST_F(GifTypeTest_214, ValidGif87a_ReturnsTrue_214) {

    const std::array<byte, 6> gif87aData{'G', 'I', 'F', '8', '7', 'a'};

    EXPECT_CALL(mockBasicIo, read(::testing::NotNull(), 6)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(gif87aData.begin(), gif87aData.end()),

        ::testing::Return(6)

    ));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(::testing::Return(false));



    EXPECT_TRUE(isGifType(mockBasicIo, true));

}



TEST_F(GifTypeTest_214, ValidGif89a_ReturnsTrue_214) {

    const std::array<byte, 6> gif89aData{'G', 'I', 'F', '8', '9', 'a'};

    EXPECT_CALL(mockBasicIo, read(::testing::NotNull(), 6)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(gif89aData.begin(), gif89aData.end()),

        ::testing::Return(6)

    ));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(::testing::Return(false));



    EXPECT_TRUE(isGifType(mockBasicIo, true));

}



TEST_F(GifTypeTest_214, InvalidData_ReturnsFalse_214) {

    const std::array<byte, 6> invalidData{'N', 'O', 'T', 'A', 'G', 'I'};

    EXPECT_CALL(mockBasicIo, read(::testing::NotNull(), 6)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(invalidData.begin(), invalidData.end()),

        ::testing::Return(6)

    ));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(::testing::Return(false));



    EXPECT_FALSE(isGifType(mockBasicIo, true));

}



TEST_F(GifTypeTest_214, ReadError_ReturnsFalse_214) {

    const std::array<byte, 6> gif87aData{'G', 'I', 'F', '8', '7', 'a'};

    EXPECT_CALL(mockBasicIo, read(::testing::NotNull(), 6)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(gif87aData.begin(), gif87aData.end()),

        ::testing::Return(6)

    ));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(::testing::Return(false));



    EXPECT_FALSE(isGifType(mockBasicIo, true));

}



TEST_F(GifTypeTest_214, EndOfFile_ReturnsFalse_214) {

    const std::array<byte, 6> gif87aData{'G', 'I', 'F', '8', '7', 'a'};

    EXPECT_CALL(mockBasicIo, read(::testing::NotNull(), 6)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(gif87aData.begin(), gif87aData.end()),

        ::testing::Return(6)

    ));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(::testing::Return(true));



    EXPECT_FALSE(isGifType(mockBasicIo, true));

}



TEST_F(GifTypeTest_214, AdvanceFalse_DoesNotSeekBack_214) {

    const std::array<byte, 6> gif87aData{'G', 'I', 'F', '8', '7', 'a'};

    EXPECT_CALL(mockBasicIo, read(::testing::NotNull(), 6)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(gif87aData.begin(), gif87aData.end()),

        ::testing::Return(6)

    ));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockBasicIo, seek(-6, BasicIo::cur)).Times(0);



    isGifType(mockBasicIo, false);

}



TEST_F(GifTypeTest_214, AdvanceTrue_SeeksBackWhenNotMatched_214) {

    const std::array<byte, 6> invalidData{'N', 'O', 'T', 'A', 'G', 'I'};

    EXPECT_CALL(mockBasicIo, read(::testing::NotNull(), 6)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(invalidData.begin(), invalidData.end()),

        ::testing::Return(6)

    ));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockBasicIo, seek(-6, BasicIo::cur)).Times(1);



    isGifType(mockBasicIo, true);

}



TEST_F(GifTypeTest_214, AdvanceTrue_DoesNotSeekBackWhenMatched_214) {

    const std::array<byte, 6> gif87aData{'G', 'I', 'F', '8', '7', 'a'};

    EXPECT_CALL(mockBasicIo, read(::testing::NotNull(), 6)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(gif87aData.begin(), gif87aData.end()),

        ::testing::Return(6)

    ));

    EXPECT_CALL(mockBasicIo, error()).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(::testing::Return(false));

    EXPECT_CALL(mockBasicIo, seek(-6, BasicIo::cur)).Times(0);



    isGifType(mockBasicIo, true);

}
