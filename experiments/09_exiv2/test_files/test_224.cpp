#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "rafimage.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::InSequence;

using ::testing::Return;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo& src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

};



class RafImageTest_224 : public ::testing::Test {

protected:

    BasicIoMock mockBasicIo;

};



TEST_F(RafImageTest_224, ValidRafTypeIdentification_224) {

    byte rafId[] = {'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M'};

    EXPECT_CALL(mockBasicIo, read(_, 8)).WillOnce([](byte* buf, size_t) {

        std::copy(std::begin(rafId), std::end(rafId), buf);

        return 8;

    });

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));



    EXPECT_TRUE(isRafType(mockBasicIo, false));

}



TEST_F(RafImageTest_224, InvalidRafTypeIdentification_224) {

    byte invalidId[] = {'I', 'N', 'V', 'A', 'L', 'I', 'D'};

    EXPECT_CALL(mockBasicIo, read(_, 8)).WillOnce([](byte* buf, size_t) {

        std::copy(std::begin(invalidId), std::end(invalidId), buf);

        return 8;

    });

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));



    EXPECT_FALSE(isRafType(mockBasicIo, false));

}



TEST_F(RafImageTest_224, ReadErrorDuringIdentification_224) {

    byte rafId[] = {'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M'};

    EXPECT_CALL(mockBasicIo, read(_, 8)).WillOnce([](byte* buf, size_t) {

        std::copy(std::begin(rafId), std::end(rafId), buf);

        return 8;

    });

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(1));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));



    EXPECT_FALSE(isRafType(mockBasicIo, false));

}



TEST_F(RafImageTest_224, EofDuringIdentification_224) {

    byte rafId[] = {'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M'};

    EXPECT_CALL(mockBasicIo, read(_, 8)).WillOnce([](byte* buf, size_t) {

        std::copy(std::begin(rafId), std::end(rafId), buf);

        return 8;

    });

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(true));



    EXPECT_FALSE(isRafType(mockBasicIo, false));

}



TEST_F(RafImageTest_224, AdvanceOnValidIdentification_224) {

    byte rafId[] = {'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M'};

    EXPECT_CALL(mockBasicIo, read(_, 8)).WillOnce([](byte* buf, size_t) {

        std::copy(std::begin(rafId), std::end(rafId), buf);

        return 8;

    });

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, seek(-8, BasicIo::cur)).Times(0);



    EXPECT_TRUE(isRafType(mockBasicIo, true));

}



TEST_F(RafImageTest_224, DoNotAdvanceOnInvalidIdentification_224) {

    byte invalidId[] = {'I', 'N', 'V', 'A', 'L', 'I', 'D'};

    EXPECT_CALL(mockBasicIo, read(_, 8)).WillOnce([](byte* buf, size_t) {

        std::copy(std::begin(invalidId), std::end(invalidId), buf);

        return 8;

    });

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, seek(-8, BasicIo::cur)).Times(1);



    EXPECT_FALSE(isRafType(mockBasicIo, true));

}



TEST_F(RafImageTest_224, DoNotAdvanceOnReadError_224) {

    byte rafId[] = {'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M'};

    EXPECT_CALL(mockBasicIo, read(_, 8)).WillOnce([](byte* buf, size_t) {

        std::copy(std::begin(rafId), std::end(rafId), buf);

        return 8;

    });

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(1));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockBasicIo, seek(-8, BasicIo::cur)).Times(1);



    EXPECT_FALSE(isRafType(mockBasicIo, true));

}



TEST_F(RafImageTest_224, DoNotAdvanceOnEof_224) {

    byte rafId[] = {'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M'};

    EXPECT_CALL(mockBasicIo, read(_, 8)).WillOnce([](byte* buf, size_t) {

        std::copy(std::begin(rafId), std::end(rafId), buf);

        return 8;

    });

    EXPECT_CALL(mockBasicIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, eof()).WillOnce(Return(true));

    EXPECT_CALL(mockBasicIo, seek(-8, BasicIo::cur)).Times(1);



    EXPECT_FALSE(isRafType(mockBasicIo, true));

}
