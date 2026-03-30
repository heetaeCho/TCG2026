#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "TestProjects/exiv2/src/riffvideo.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

};



class RiffVideoTest_83 : public ::testing::Test {

protected:

    MockBasicIo mockIo;

};



TEST_F(RiffVideoTest_83, ValidRiffType_83) {

    constexpr int len = 4;

    std::array<byte, len> riffId{'R', 'I', 'F', 'F'};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(riffId.begin(), riffId.end()),

        Return(len)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));



    bool result = isRiffType(mockIo, true);

    EXPECT_TRUE(result);

}



TEST_F(RiffVideoTest_83, InvalidRiffType_83) {

    constexpr int len = 4;

    std::array<byte, len> invalidId{'N', 'O', 'T', 'R'};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(invalidId.begin(), invalidId.end()),

        Return(len)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));



    bool result = isRiffType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(RiffVideoTest_83, ReadError_83) {

    constexpr int len = 4;

    std::array<byte, len> riffId{'R', 'I', 'F', 'F'};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(riffId.begin(), riffId.end()),

        Return(0) // Simulate a read error by returning 0 bytes read

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(1)); // Simulate an error



    bool result = isRiffType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(RiffVideoTest_83, EofBeforeRead_83) {

    constexpr int len = 4;

    std::array<byte, len> riffId{'R', 'I', 'F', 'F'};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(riffId.begin(), riffId.end()),

        Return(len)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(true));



    bool result = isRiffType(mockIo, true);

    EXPECT_FALSE(result);

}



TEST_F(RiffVideoTest_83, DoNotAdvanceOnMatch_83) {

    constexpr int len = 4;

    std::array<byte, len> riffId{'R', 'I', 'F', 'F'};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(riffId.begin(), riffId.end()),

        Return(len)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, seek(-1 * len, BasicIo::cur)).Times(1);



    bool result = isRiffType(mockIo, false);

    EXPECT_TRUE(result);

}



TEST_F(RiffVideoTest_83, DoNotAdvanceOnMismatch_83) {

    constexpr int len = 4;

    std::array<byte, len> invalidId{'N', 'O', 'T', 'R'};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(invalidId.begin(), invalidId.end()),

        Return(len)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, seek(-1 * len, BasicIo::cur)).Times(1);



    bool result = isRiffType(mockIo, false);

    EXPECT_FALSE(result);

}



TEST_F(RiffVideoTest_83, AdvanceOnMatch_83) {

    constexpr int len = 4;

    std::array<byte, len> riffId{'R', 'I', 'F', 'F'};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(riffId.begin(), riffId.end()),

        Return(len)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, seek(-1 * len, BasicIo::cur)).Times(0);



    bool result = isRiffType(mockIo, true);

    EXPECT_TRUE(result);

}



TEST_F(RiffVideoTest_83, AdvanceOnMismatch_83) {

    constexpr int len = 4;

    std::array<byte, len> invalidId{'N', 'O', 'T', 'R'};

    EXPECT_CALL(mockIo, read(_, len)).WillOnce(::testing::DoAll(

        ::testing::SetArrayArgument<0>(invalidId.begin(), invalidId.end()),

        Return(len)

    ));

    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, seek(-1 * len, BasicIo::cur)).Times(1);



    bool result = isRiffType(mockIo, true);

    EXPECT_FALSE(result);

}
