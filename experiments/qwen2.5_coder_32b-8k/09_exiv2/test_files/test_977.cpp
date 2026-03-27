#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "pngimage.cpp"  // Assuming pngimage.cpp contains the implementation



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



TEST(isPngTypeTest_977, NormalOperation_PngSignature_977) {

    MockBasicIo mockIo;

    const std::array<byte, 8> pngSig = {137, 80, 78, 71, 13, 10, 26, 10};



    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, read(_, 8)).WillOnce([pngSig](byte* buf, size_t) {

        std::copy(pngSig.begin(), pngSig.end(), buf);

        return 8;

    });



    EXPECT_TRUE(isPngType(mockIo, true));

}



TEST(isPngTypeTest_977, NormalOperation_NotPngSignature_977) {

    MockBasicIo mockIo;

    const std::array<byte, 8> notPngSig = {0, 1, 2, 3, 4, 5, 6, 7};



    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, read(_, 8)).WillOnce([notPngSig](byte* buf, size_t) {

        std::copy(notPngSig.begin(), notPngSig.end(), buf);

        return 8;

    });



    EXPECT_FALSE(isPngType(mockIo, true));

}



TEST(isPngTypeTest_977, BoundaryCondition_ShortRead_977) {

    MockBasicIo mockIo;



    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, read(_, 8)).WillOnce(Return(4));  // Short read



    EXPECT_FALSE(isPngType(mockIo, true));

}



TEST(isPngTypeTest_977, ErrorCondition_ErrorOnRead_977) {

    MockBasicIo mockIo;



    EXPECT_CALL(mockIo, error()).WillOnce(Return(0)).WillOnce(Return(1));  // First call no error, second call error

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, read(_, 8)).WillOnce(Return(8));



    EXPECT_THROW(isPngType(mockIo, true), Error);

}



TEST(isPngTypeTest_977, ErrorCondition_EofOnRead_977) {

    MockBasicIo mockIo;



    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false)).WillOnce(Return(true));  // First call not eof, second call eof

    EXPECT_CALL(mockIo, read(_, 8)).WillOnce(Return(8));



    EXPECT_FALSE(isPngType(mockIo, true));

}



TEST(isPngTypeTest_977, BoundaryCondition_SeekAfterRead_977) {

    MockBasicIo mockIo;

    const std::array<byte, 8> pngSig = {137, 80, 78, 71, 13, 10, 26, 10};



    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, read(_, 8)).WillOnce([pngSig](byte* buf, size_t) {

        std::copy(pngSig.begin(), pngSig.end(), buf);

        return 8;

    });

    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur));



    EXPECT_TRUE(isPngType(mockIo, false));

}



TEST(isPngTypeTest_977, BoundaryCondition_NoSeekIfNotAdvance_977) {

    MockBasicIo mockIo;

    const std::array<byte, 8> pngSig = {137, 80, 78, 71, 13, 10, 26, 10};



    EXPECT_CALL(mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(mockIo, read(_, 8)).WillOnce([pngSig](byte* buf, size_t) {

        std::copy(pngSig.begin(), pngSig.end(), buf);

        return 8;

    });

    EXPECT_CALL(mockIo, seek(-8, BasicIo::cur)).Times(0);  // No seek should be called



    EXPECT_TRUE(isPngType(mockIo, true));

}
