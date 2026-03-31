#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

using namespace Exiv2;

// Mock class for BasicIo since it's abstract
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
    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class BasicIoTest_544 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test readOrThrow succeeds when read returns exact count and no error
TEST_F(BasicIoTest_544, ReadOrThrowSucceedsWhenReadReturnsExactCount_544) {
    byte buf[10];
    size_t rcount = 10;

    EXPECT_CALL(mockIo, read(buf, rcount))
        .WillOnce(::testing::Return(rcount));
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0));

    EXPECT_NO_THROW(mockIo.readOrThrow(buf, rcount, ErrorCode::kerFailedToReadImageData));
}

// Test readOrThrow throws when read returns fewer bytes than requested
TEST_F(BasicIoTest_544, ReadOrThrowThrowsWhenReadReturnsFewerBytes_544) {
    byte buf[10];
    size_t rcount = 10;

    EXPECT_CALL(mockIo, read(buf, rcount))
        .WillOnce(::testing::Return(5u));

    EXPECT_THROW(mockIo.readOrThrow(buf, rcount, ErrorCode::kerFailedToReadImageData), Error);
}

// Test readOrThrow throws when error() returns non-zero even if read count matches
TEST_F(BasicIoTest_544, ReadOrThrowThrowsWhenErrorIsSet_544) {
    byte buf[10];
    size_t rcount = 10;

    EXPECT_CALL(mockIo, read(buf, rcount))
        .WillOnce(::testing::Return(rcount));
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(1));

    EXPECT_THROW(mockIo.readOrThrow(buf, rcount, ErrorCode::kerFailedToReadImageData), Error);
}

// Test readOrThrow with zero bytes requested - should succeed
TEST_F(BasicIoTest_544, ReadOrThrowZeroBytesSucceeds_544) {
    byte buf[1];
    size_t rcount = 0;

    EXPECT_CALL(mockIo, read(buf, 0u))
        .WillOnce(::testing::Return(0u));
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0));

    EXPECT_NO_THROW(mockIo.readOrThrow(buf, rcount, ErrorCode::kerFailedToReadImageData));
}

// Test readOrThrow throws when read returns zero for non-zero request
TEST_F(BasicIoTest_544, ReadOrThrowThrowsWhenReadReturnsZeroForNonZeroRequest_544) {
    byte buf[10];
    size_t rcount = 10;

    EXPECT_CALL(mockIo, read(buf, rcount))
        .WillOnce(::testing::Return(0u));

    EXPECT_THROW(mockIo.readOrThrow(buf, rcount, ErrorCode::kerFailedToReadImageData), Error);
}

// Test readOrThrow with single byte read succeeding
TEST_F(BasicIoTest_544, ReadOrThrowSingleByteSucceeds_544) {
    byte buf[1];
    size_t rcount = 1;

    EXPECT_CALL(mockIo, read(buf, rcount))
        .WillOnce(::testing::Return(1u));
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0));

    EXPECT_NO_THROW(mockIo.readOrThrow(buf, rcount, ErrorCode::kerFailedToReadImageData));
}

// Test readOrThrow propagates the specific error code
TEST_F(BasicIoTest_544, ReadOrThrowPropagatesErrorCode_544) {
    byte buf[10];
    size_t rcount = 10;

    EXPECT_CALL(mockIo, read(buf, rcount))
        .WillOnce(::testing::Return(3u));

    try {
        mockIo.readOrThrow(buf, rcount, ErrorCode::kerCorruptedMetadata);
        FAIL() << "Expected an exception to be thrown";
    } catch (const Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerCorruptedMetadata);
    }
}

// Test readOrThrow with large read succeeding
TEST_F(BasicIoTest_544, ReadOrThrowLargeReadSucceeds_544) {
    std::vector<byte> buf(65536);
    size_t rcount = 65536;

    EXPECT_CALL(mockIo, read(buf.data(), rcount))
        .WillOnce(::testing::Return(rcount));
    EXPECT_CALL(mockIo, error())
        .WillOnce(::testing::Return(0));

    EXPECT_NO_THROW(mockIo.readOrThrow(buf.data(), rcount, ErrorCode::kerFailedToReadImageData));
}

// Test seekOrThrow succeeds when seek returns 0 (success)
TEST_F(BasicIoTest_544, SeekOrThrowSucceedsWhenSeekReturnsZero_544) {
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg))
        .WillOnce(::testing::Return(0));

    EXPECT_NO_THROW(mockIo.seekOrThrow(0, BasicIo::beg, ErrorCode::kerFailedToReadImageData));
}

// Test seekOrThrow throws when seek returns non-zero (failure)
TEST_F(BasicIoTest_544, SeekOrThrowThrowsWhenSeekFails_544) {
    EXPECT_CALL(mockIo, seek(100, BasicIo::beg))
        .WillOnce(::testing::Return(-1));

    EXPECT_THROW(mockIo.seekOrThrow(100, BasicIo::beg, ErrorCode::kerFailedToReadImageData), Error);
}

// Test seekOrThrow with different positions
TEST_F(BasicIoTest_544, SeekOrThrowWithCurrentPosition_544) {
    EXPECT_CALL(mockIo, seek(50, BasicIo::cur))
        .WillOnce(::testing::Return(0));

    EXPECT_NO_THROW(mockIo.seekOrThrow(50, BasicIo::cur, ErrorCode::kerFailedToReadImageData));
}

TEST_F(BasicIoTest_544, SeekOrThrowWithEndPosition_544) {
    EXPECT_CALL(mockIo, seek(-10, BasicIo::end))
        .WillOnce(::testing::Return(0));

    EXPECT_NO_THROW(mockIo.seekOrThrow(-10, BasicIo::end, ErrorCode::kerFailedToReadImageData));
}

// MemIo tests using concrete implementation
class MemIoTest_544 : public ::testing::Test {
protected:
};

TEST_F(MemIoTest_544, DefaultConstructionCreatesEmptyIo_544) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_544, ConstructFromData_544) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_544, OpenAndClose_544) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_TRUE(memIo.isopen());
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(MemIoTest_544, WriteAndReadBack_544) {
    MemIo memIo;
    memIo.open();

    const byte writeData[] = {0xAA, 0xBB, 0xCC, 0xDD};
    size_t written = memIo.write(writeData, sizeof(writeData));
    EXPECT_EQ(written, sizeof(writeData));
    EXPECT_EQ(memIo.size(), sizeof(writeData));

    memIo.seek(0, BasicIo::beg);

    byte readBuf[4] = {};
    size_t bytesRead = memIo.read(readBuf, sizeof(readBuf));
    EXPECT_EQ(bytesRead, sizeof(readBuf));
    EXPECT_EQ(readBuf[0], 0xAA);
    EXPECT_EQ(readBuf[1], 0xBB);
    EXPECT_EQ(readBuf[2], 0xCC);
    EXPECT_EQ(readBuf[3], 0xDD);
}

TEST_F(MemIoTest_544, ReadOrThrowOnMemIoSucceeds_544) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    memIo.seek(0, BasicIo::beg);

    byte buf[3] = {};
    EXPECT_NO_THROW(memIo.readOrThrow(buf, 3, ErrorCode::kerFailedToReadImageData));
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
}

TEST_F(MemIoTest_544, ReadOrThrowOnMemIoFailsWhenNotEnoughData_544) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    memIo.seek(0, BasicIo::beg);

    byte buf[10] = {};
    EXPECT_THROW(memIo.readOrThrow(buf, 10, ErrorCode::kerFailedToReadImageData), Error);
}

TEST_F(MemIoTest_544, SeekTell_544) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 3u);

    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_544, PutbAndGetb_544) {
    MemIo memIo;
    memIo.open();

    EXPECT_EQ(memIo.putb(0x42), 0);
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0x42);
}

TEST_F(MemIoTest_544, EofAfterReadPastEnd_544) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    byte buf[2] = {};
    memIo.read(buf, 2);
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_544, ReadOrThrowZeroBytesOnEmptyMemIo_544) {
    MemIo memIo;
    memIo.open();

    byte buf[1] = {};
    EXPECT_NO_THROW(memIo.readOrThrow(buf, 0, ErrorCode::kerFailedToReadImageData));
}

TEST_F(MemIoTest_544, SeekOrThrowSucceedsOnValidSeek_544) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    EXPECT_NO_THROW(memIo.seekOrThrow(2, BasicIo::beg, ErrorCode::kerFailedToReadImageData));
    EXPECT_EQ(memIo.tell(), 2u);
}

TEST_F(MemIoTest_544, ReadDataBuf_544) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    memIo.seek(0, BasicIo::beg);

    DataBuf result = memIo.read(4);
    EXPECT_EQ(result.size(), 4u);
}

TEST_F(MemIoTest_544, ErrorReturnsZeroOnNormalOperation_544) {
    MemIo memIo;
    memIo.open();
    EXPECT_EQ(memIo.error(), 0);
}

TEST_F(MemIoTest_544, PathReturnsNonEmpty_544) {
    MemIo memIo;
    const std::string& p = memIo.path();
    // MemIo should have some path representation
    EXPECT_FALSE(p.empty());
}

TEST_F(MemIoTest_544, WriteFromAnotherIo_544) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo src(data, sizeof(data));
    src.open();
    src.seek(0, BasicIo::beg);

    MemIo dst;
    dst.open();
    size_t written = dst.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dst.size(), sizeof(data));
}
