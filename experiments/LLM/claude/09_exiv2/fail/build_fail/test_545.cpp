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

// Test fixture
class BasicIoTest_545 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// seekOrThrow tests

TEST_F(BasicIoTest_545, SeekOrThrowSucceedsWhenSeekReturnsZero_545) {
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg))
        .WillOnce(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.seekOrThrow(0, BasicIo::beg, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, SeekOrThrowThrowsWhenSeekReturnsNonZero_545) {
    EXPECT_CALL(mockIo, seek(100, BasicIo::beg))
        .WillOnce(::testing::Return(-1));
    
    EXPECT_THROW(mockIo.seekOrThrow(100, BasicIo::beg, ErrorCode::kerErrorMessage), Error);
}

TEST_F(BasicIoTest_545, SeekOrThrowWithPositionCur_545) {
    EXPECT_CALL(mockIo, seek(50, BasicIo::cur))
        .WillOnce(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.seekOrThrow(50, BasicIo::cur, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, SeekOrThrowWithPositionEnd_545) {
    EXPECT_CALL(mockIo, seek(-10, BasicIo::end))
        .WillOnce(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.seekOrThrow(-10, BasicIo::end, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, SeekOrThrowWithNegativeOffsetFromCur_545) {
    EXPECT_CALL(mockIo, seek(-5, BasicIo::cur))
        .WillOnce(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.seekOrThrow(-5, BasicIo::cur, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, SeekOrThrowFailsWithPositionEnd_545) {
    EXPECT_CALL(mockIo, seek(0, BasicIo::end))
        .WillOnce(::testing::Return(1));
    
    EXPECT_THROW(mockIo.seekOrThrow(0, BasicIo::end, ErrorCode::kerErrorMessage), Error);
}

TEST_F(BasicIoTest_545, SeekOrThrowWithLargePositiveOffset_545) {
    int64_t largeOffset = static_cast<int64_t>(1) << 40;
    EXPECT_CALL(mockIo, seek(largeOffset, BasicIo::beg))
        .WillOnce(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.seekOrThrow(largeOffset, BasicIo::beg, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, SeekOrThrowWithLargePositiveOffsetFails_545) {
    int64_t largeOffset = static_cast<int64_t>(1) << 40;
    EXPECT_CALL(mockIo, seek(largeOffset, BasicIo::beg))
        .WillOnce(::testing::Return(-1));
    
    EXPECT_THROW(mockIo.seekOrThrow(largeOffset, BasicIo::beg, ErrorCode::kerErrorMessage), Error);
}

TEST_F(BasicIoTest_545, SeekOrThrowWithZeroOffsetFromBeg_545) {
    EXPECT_CALL(mockIo, seek(0, BasicIo::beg))
        .WillOnce(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.seekOrThrow(0, BasicIo::beg, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, SeekOrThrowWithZeroOffsetFromEnd_545) {
    EXPECT_CALL(mockIo, seek(0, BasicIo::end))
        .WillOnce(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.seekOrThrow(0, BasicIo::end, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, SeekOrThrowWithZeroOffsetFromCur_545) {
    EXPECT_CALL(mockIo, seek(0, BasicIo::cur))
        .WillOnce(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.seekOrThrow(0, BasicIo::cur, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, SeekOrThrowSeekReturnsPositiveNonZero_545) {
    EXPECT_CALL(mockIo, seek(10, BasicIo::beg))
        .WillOnce(::testing::Return(1));
    
    EXPECT_THROW(mockIo.seekOrThrow(10, BasicIo::beg, ErrorCode::kerErrorMessage), Error);
}

// readOrThrow tests

TEST_F(BasicIoTest_545, ReadOrThrowSucceedsWhenReadReturnsRequestedCount_545) {
    byte buf[10];
    EXPECT_CALL(mockIo, read(buf, 10))
        .WillOnce(::testing::Return(10));
    
    EXPECT_NO_THROW(mockIo.readOrThrow(buf, 10, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, ReadOrThrowThrowsWhenReadReturnsFewer_545) {
    byte buf[10];
    EXPECT_CALL(mockIo, read(buf, 10))
        .WillOnce(::testing::Return(5));
    
    EXPECT_THROW(mockIo.readOrThrow(buf, 10, ErrorCode::kerErrorMessage), Error);
}

TEST_F(BasicIoTest_545, ReadOrThrowThrowsWhenReadReturnsZero_545) {
    byte buf[10];
    EXPECT_CALL(mockIo, read(buf, 10))
        .WillOnce(::testing::Return(0));
    
    EXPECT_THROW(mockIo.readOrThrow(buf, 10, ErrorCode::kerErrorMessage), Error);
}

TEST_F(BasicIoTest_545, ReadOrThrowWithZeroCount_545) {
    byte buf[1];
    EXPECT_CALL(mockIo, read(buf, 0))
        .WillOnce(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.readOrThrow(buf, 0, ErrorCode::kerErrorMessage));
}

TEST_F(BasicIoTest_545, ReadOrThrowWithSingleByte_545) {
    byte buf[1];
    EXPECT_CALL(mockIo, read(buf, 1))
        .WillOnce(::testing::Return(1));
    
    EXPECT_NO_THROW(mockIo.readOrThrow(buf, 1, ErrorCode::kerErrorMessage));
}

// Tests using MemIo (concrete implementation) for integration-style tests

TEST_F(BasicIoTest_545, SeekOrThrowOnMemIoWithValidSeek_545) {
    MemIo memIo;
    const byte data[] = "Hello, World!";
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    
    EXPECT_NO_THROW(memIo.seekOrThrow(5, BasicIo::beg, ErrorCode::kerErrorMessage));
    EXPECT_EQ(memIo.tell(), 5u);
}

TEST_F(BasicIoTest_545, SeekOrThrowOnMemIoFromEnd_545) {
    MemIo memIo;
    const byte data[] = "Hello, World!";
    memIo.write(data, sizeof(data));
    
    EXPECT_NO_THROW(memIo.seekOrThrow(0, BasicIo::end, ErrorCode::kerErrorMessage));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

TEST_F(BasicIoTest_545, SeekOrThrowOnMemIoFromCur_545) {
    MemIo memIo;
    const byte data[] = "Hello, World!";
    memIo.write(data, sizeof(data));
    memIo.seek(3, BasicIo::beg);
    
    EXPECT_NO_THROW(memIo.seekOrThrow(2, BasicIo::cur, ErrorCode::kerErrorMessage));
    EXPECT_EQ(memIo.tell(), 5u);
}

TEST_F(BasicIoTest_545, ReadOrThrowOnMemIoSucceeds_545) {
    MemIo memIo;
    const byte data[] = "Hello";
    memIo.write(data, 5);
    memIo.seek(0, BasicIo::beg);
    
    byte buf[5];
    EXPECT_NO_THROW(memIo.readOrThrow(buf, 5, ErrorCode::kerErrorMessage));
    EXPECT_EQ(std::memcmp(buf, data, 5), 0);
}

TEST_F(BasicIoTest_545, ReadOrThrowOnMemIoFailsWhenNotEnoughData_545) {
    MemIo memIo;
    const byte data[] = "Hi";
    memIo.write(data, 2);
    memIo.seek(0, BasicIo::beg);
    
    byte buf[10];
    EXPECT_THROW(memIo.readOrThrow(buf, 10, ErrorCode::kerErrorMessage), Error);
}

TEST_F(BasicIoTest_545, MemIoOpenAndClose_545) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_TRUE(memIo.isopen());
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(BasicIoTest_545, MemIoWriteAndRead_545) {
    MemIo memIo;
    const byte data[] = {1, 2, 3, 4, 5};
    EXPECT_EQ(memIo.write(data, 5), 5u);
    EXPECT_EQ(memIo.size(), 5u);
    
    memIo.seek(0, BasicIo::beg);
    byte buf[5];
    EXPECT_EQ(memIo.read(buf, 5), 5u);
    EXPECT_EQ(std::memcmp(buf, data, 5), 0);
}

TEST_F(BasicIoTest_545, MemIoTell_545) {
    MemIo memIo;
    const byte data[] = "Test data";
    memIo.write(data, 9);
    EXPECT_EQ(memIo.tell(), 9u);
    
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
    
    memIo.seek(4, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 4u);
}

TEST_F(BasicIoTest_545, MemIoEof_545) {
    MemIo memIo;
    const byte data[] = "AB";
    memIo.write(data, 2);
    memIo.seek(0, BasicIo::beg);
    
    byte buf[5];
    memIo.read(buf, 5);  // Read more than available
    EXPECT_TRUE(memIo.eof());
}

TEST_F(BasicIoTest_545, MemIoPutbAndGetb_545) {
    MemIo memIo;
    EXPECT_EQ(memIo.putb(0x42), 0);
    EXPECT_EQ(memIo.size(), 1u);
    
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0x42);
}

TEST_F(BasicIoTest_545, MemIoEmptySize_545) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(BasicIoTest_545, SeekOrThrowMultipleTimesSuccess_545) {
    EXPECT_CALL(mockIo, seek(::testing::_, ::testing::_))
        .WillRepeatedly(::testing::Return(0));
    
    EXPECT_NO_THROW(mockIo.seekOrThrow(0, BasicIo::beg, ErrorCode::kerErrorMessage));
    EXPECT_NO_THROW(mockIo.seekOrThrow(10, BasicIo::cur, ErrorCode::kerErrorMessage));
    EXPECT_NO_THROW(mockIo.seekOrThrow(-5, BasicIo::end, ErrorCode::kerErrorMessage));
}
