#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/quicktimevideo.cpp"

#include "exiv2/basicio.hpp"

#include "exiv2/types.hpp"



using namespace testing;

using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

};



class QuickTimeTypeTest_662 : public Test {

protected:

    MockBasicIo mockIo;

};



TEST_F(QuickTimeTypeTest_662, NormalOperation_PICT_662) {

    byte testData[] = {'P', 'I', 'C', 'T', 0, 0, 0, 0, 'q', 't', ' ', ' '};

    EXPECT_CALL(mockIo, read(_, 12)).WillOnce(Invoke([&](byte* buf, size_t) {

        memcpy(buf, testData, sizeof(testData));

        return sizeof(testData);

    }));

    EXPECT_TRUE(isQTimeType(mockIo, true));

}



TEST_F(QuickTimeTypeTest_662, NormalOperation_ftyp_662) {

    byte testData[] = {'f', 't', 'y', 'p', 0, 0, 0, 0, 'i', 's', 'o', 'm'};

    EXPECT_CALL(mockIo, read(_, 12)).WillOnce(Invoke([&](byte* buf, size_t) {

        memcpy(buf, testData, sizeof(testData));

        return sizeof(testData);

    }));

    EXPECT_TRUE(isQTimeType(mockIo, true));

}



TEST_F(QuickTimeTypeTest_662, BoundaryCondition_EmptyBuffer_662) {

    EXPECT_CALL(mockIo, read(_, 12)).WillOnce(Return(0));

    EXPECT_FALSE(isQTimeType(mockIo, true));

}



TEST_F(QuickTimeTypeTest_662, ExceptionalCase_ErrorInRead_662) {

    EXPECT_CALL(mockIo, read(_, 12)).WillOnce([](byte*, size_t) -> size_t { return 0; });

    EXPECT_CALL(mockIo, error()).WillOnce(Return(-1));

    EXPECT_FALSE(isQTimeType(mockIo, true));

}



TEST_F(QuickTimeTypeTest_662, ExceptionalCase_EOFInRead_662) {

    EXPECT_CALL(mockIo, read(_, 12)).WillOnce([](byte*, size_t) -> size_t { return 0; });

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(true));

    EXPECT_FALSE(isQTimeType(mockIo, true));

}



TEST_F(QuickTimeTypeTest_662, BoundaryCondition_ShortBuffer_662) {

    byte testData[] = {'P', 'I'};

    EXPECT_CALL(mockIo, read(_, 12)).WillOnce(Invoke([&](byte* buf, size_t) {

        memcpy(buf, testData, sizeof(testData));

        return sizeof(testData);

    }));

    EXPECT_FALSE(isQTimeType(mockIo, true));

}



TEST_F(QuickTimeTypeTest_662, NormalOperation_AdvanceFalse_662) {

    byte testData[] = {'P', 'I', 'C', 'T', 0, 0, 0, 0, 'q', 't', ' ', ' '};

    EXPECT_CALL(mockIo, read(_, 12)).WillOnce(Invoke([&](byte* buf, size_t) {

        memcpy(buf, testData, sizeof(testData));

        return sizeof(testData);

    }));

    EXPECT_CALL(mockIo, seek(0L, BasicIo::beg)).Times(1);

    EXPECT_TRUE(isQTimeType(mockIo, false));

}



TEST_F(QuickTimeTypeTest_662, NormalOperation_UnmatchedTag_662) {

    byte testData[] = {'U', 'N', 'M', 'A', 0, 0, 0, 0, 'q', 't', ' ', ' '};

    EXPECT_CALL(mockIo, read(_, 12)).WillOnce(Invoke([&](byte* buf, size_t) {

        memcpy(buf, testData, sizeof(testData));

        return sizeof(testData);

    }));

    EXPECT_FALSE(isQTimeType(mockIo, true));

}
