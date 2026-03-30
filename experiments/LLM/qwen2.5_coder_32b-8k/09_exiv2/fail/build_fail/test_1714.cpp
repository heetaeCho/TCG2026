#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "pgfimage.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



TEST(IsPgfTypeTest_1714, NormalOperation_PgfSignature_1714) {

    MockBasicIo mockIo;

    byte pgfBytes[] = {80, 71, 70};

    EXPECT_CALL(mockIo, read(_, 3)).WillOnce([](byte* buf, size_t) -> size_t {

        memcpy(buf, pgfBytes, 3);

        return 3;

    });

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));



    EXPECT_TRUE(isPgfType(mockIo, true));

}



TEST(IsPgfTypeTest_1714, NormalOperation_NotPgfSignature_1714) {

    MockBasicIo mockIo;

    byte notPgfBytes[] = {0x00, 0x01, 0x02};

    EXPECT_CALL(mockIo, read(_, 3)).WillOnce([](byte* buf, size_t) -> size_t {

        memcpy(buf, notPgfBytes, 3);

        return 3;

    });

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));



    EXPECT_FALSE(isPgfType(mockIo, true));

}



TEST(IsPgfTypeTest_1714, BoundaryCondition_AdvanceFalse_1714) {

    MockBasicIo mockIo;

    byte pgfBytes[] = {80, 71, 70};

    EXPECT_CALL(mockIo, read(_, 3)).WillOnce([](byte* buf, size_t) -> size_t {

        memcpy(buf, pgfBytes, 3);

        return 3;

    });

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));



    EXPECT_TRUE(isPgfType(mockIo, false));

}



TEST(IsPgfTypeErrorTest_1714, ErrorReading_1714) {

    MockBasicIo mockIo;

    EXPECT_CALL(mockIo, read(_, 3)).WillOnce([](byte*, size_t) -> size_t {

        return 0; // Simulate error in reading

    });

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(true));



    EXPECT_FALSE(isPgfType(mockIo, true));

}



TEST(IsPgfTypeErrorTest_1714, EofReading_1714) {

    MockBasicIo mockIo;

    EXPECT_CALL(mockIo, read(_, 3)).WillOnce([](byte*, size_t) -> size_t {

        return 0; // Simulate EOF

    });

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(true));



    EXPECT_FALSE(isPgfType(mockIo, true));

}



TEST(IsPgfTypeTest_1714, SeekAfterRead_1714) {

    MockBasicIo mockIo;

    byte pgfBytes[] = {80, 71, 70};

    EXPECT_CALL(mockIo, read(_, 3)).WillOnce([](byte* buf, size_t) -> size_t {

        memcpy(buf, pgfBytes, 3);

        return 3;

    });

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, seek(-3, BasicIo::cur)).Times(1);



    EXPECT_TRUE(isPgfType(mockIo, true));

}



TEST(IsPgfTypeTest_1714, NoSeekIfAdvanceFalseAndMatch_1714) {

    MockBasicIo mockIo;

    byte pgfBytes[] = {80, 71, 70};

    EXPECT_CALL(mockIo, read(_, 3)).WillOnce([](byte* buf, size_t) -> size_t {

        memcpy(buf, pgfBytes, 3);

        return 3;

    });

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, seek(-3, BasicIo::cur)).Times(0);



    EXPECT_TRUE(isPgfType(mockIo, false));

}



TEST(IsPgfTypeErrorTest_1714, SeekErrorAfterRead_1714) {

    MockBasicIo mockIo;

    byte pgfBytes[] = {80, 71, 70};

    EXPECT_CALL(mockIo, read(_, 3)).WillOnce([](byte* buf, size_t) -> size_t {

        memcpy(buf, pgfBytes, 3);

        return 3;

    });

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockIo, seek(-3, BasicIo::cur)).WillOnce(Return(-1)); // Simulate error in seeking



    EXPECT_TRUE(isPgfType(mockIo, true)); // Function should still return true as match is found

}
