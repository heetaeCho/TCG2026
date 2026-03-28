#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



namespace Exiv2 {

    class MockBasicIo : public BasicIo {

    public:

        MOCK_METHOD(int, open, (), (override));

        MOCK_METHOD(int, close, (), (override));

        MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

        MOCK_METHOD(size_t, write, (BasicIo& src), (override));

        MOCK_METHOD(int, putb, (byte data), (override));

        MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

        MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

        MOCK_METHOD(int, getb, (), (override));

        MOCK_METHOD(void, transfer, (BasicIo& src), (override));

        MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

        MOCK_METHOD(byte*, mmap, (bool unnamed), (override));

        MOCK_METHOD(int, munmap, (), (override));

        MOCK_METHOD(size_t, tell, () const, (override));

        MOCK_METHOD(size_t, size, () const, (override));

        MOCK_METHOD(bool, isopen, () const, (override));

        MOCK_METHOD(int, error, () const, (override));

        MOCK_METHOD(bool, eof, () const, (override));

        MOCK_METHOD(const std::string&, path, () const noexcept, (override));

    };

}



using namespace Exiv2;



class MemIoTest_585 : public ::testing::Test {

protected:

    MemIo memIo;

};



TEST_F(MemIoTest_585, SizeInitiallyZero_585) {

    EXPECT_EQ(memIo.size(), 0u);

}



TEST_F(MemIoTest_585, OpenReturnsSuccess_585) {

    EXPECT_GE(memIo.open(), 0);

}



TEST_F(MemIoTest_585, CloseReturnsSuccess_585) {

    memIo.open();

    EXPECT_GE(memIo.close(), 0);

}



TEST_F(MemIoTest_585, PutbIncreasesSize_585) {

    memIo.open();

    memIo.putb('a');

    EXPECT_EQ(memIo.size(), 1u);

}



TEST_F(MemIoTest_585, ReadFromEmptyBufferReturnsZero_585) {

    byte buffer[10];

    EXPECT_EQ(memIo.read(buffer, 10), 0u);

}



TEST_F(MemIoTest_585, SeekToBeginningAfterWriteWorks_585) {

    memIo.open();

    memIo.putb('a');

    memIo.seek(0, BasicIo::beg);

    EXPECT_EQ(memIo.tell(), 0u);

}



TEST_F(MemIoTest_585, TellReturnsCurrentPosition_585) {

    memIo.open();

    memIo.putb('a');

    memIo.putb('b');

    EXPECT_EQ(memIo.tell(), 2u);

}



TEST_F(MemIoTest_585, EofInitiallyFalse_585) {

    EXPECT_FALSE(memIo.eof());

}



TEST_F(MemIoTest_585, ErrorInitiallyZero_585) {

    EXPECT_EQ(memIo.error(), 0);

}



TEST_F(MemIoTest_585, IsopenAfterOpenReturnsTrue_585) {

    memIo.open();

    EXPECT_TRUE(memIo.isopen());

}



TEST_F(MemIoTest_585, IsopenAfterCloseReturnsFalse_585) {

    memIo.open();

    memIo.close();

    EXPECT_FALSE(memIo.isopen());

}
