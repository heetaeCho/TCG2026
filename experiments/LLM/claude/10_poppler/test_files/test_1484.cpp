#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CachedFile.h"
#include <memory>
#include <vector>

// Mock the CachedFileLoader dependency
class MockCachedFileLoader : public CachedFileLoader {
public:
    MOCK_METHOD(size_t, init, (GooString *url, CachedFile *cachedFile), (override));
    MOCK_METHOD(int, load, (const std::vector<ByteRange> &ranges, CachedFileWriter *writer), (override));
};

class CachedFileTest_1484 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly created CachedFile reports a length based on loader initialization
TEST_F(CachedFileTest_1484, GetLengthReturnsInitializedLength_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    // The loader's init method is expected to be called during CachedFile construction
    // and should return the total length of the file
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    EXPECT_EQ(cachedFile.getLength(), 1024u);
}

// Test getLength with zero-length file
TEST_F(CachedFileTest_1484, GetLengthZeroLength_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(0));
    
    CachedFile cachedFile(std::move(loader));
    
    EXPECT_EQ(cachedFile.getLength(), 0u);
}

// Test getLength with a large file size
TEST_F(CachedFileTest_1484, GetLengthLargeFile_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    size_t largeSize = 1024 * 1024 * 100; // 100 MB
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(largeSize));
    
    CachedFile cachedFile(std::move(loader));
    
    EXPECT_EQ(cachedFile.getLength(), static_cast<unsigned int>(largeSize));
}

// Test tell() returns initial position (should be 0 at start)
TEST_F(CachedFileTest_1484, TellReturnsZeroInitially_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    EXPECT_EQ(cachedFile.tell(), 0);
}

// Test seek with SEEK_SET
TEST_F(CachedFileTest_1484, SeekSetMovesPosition_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    int result = cachedFile.seek(100, SEEK_SET);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(cachedFile.tell(), 100);
}

// Test seek with SEEK_CUR
TEST_F(CachedFileTest_1484, SeekCurMovesRelative_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    cachedFile.seek(50, SEEK_SET);
    int result = cachedFile.seek(25, SEEK_CUR);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(cachedFile.tell(), 75);
}

// Test seek with SEEK_END
TEST_F(CachedFileTest_1484, SeekEndMovesFromEnd_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    int result = cachedFile.seek(0, SEEK_END);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(cachedFile.tell(), 1024);
}

// Test seek beyond file length
TEST_F(CachedFileTest_1484, SeekBeyondLength_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    int result = cachedFile.seek(2048, SEEK_SET);
    // Depending on implementation, this may return error or clamp
    // We just check it doesn't crash and returns some result
    (void)result;
}

// Test seek with negative offset from start (should fail or be invalid)
TEST_F(CachedFileTest_1484, SeekNegativeFromStart_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    int result = cachedFile.seek(-1, SEEK_SET);
    // Negative seek from start should likely return an error
    EXPECT_NE(result, 0);
}

// Test read triggers cache loading
TEST_F(CachedFileTest_1484, ReadFromCachedFile_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    EXPECT_CALL(*loader, load(testing::_, testing::_))
        .WillRepeatedly(testing::Return(0));
    
    CachedFile cachedFile(std::move(loader));
    
    char buffer[100];
    size_t bytesRead = cachedFile.read(buffer, 1, 100);
    // Bytes read should be between 0 and 100
    EXPECT_LE(bytesRead, 100u);
}

// Test read with zero count
TEST_F(CachedFileTest_1484, ReadZeroCount_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    char buffer[10];
    size_t bytesRead = cachedFile.read(buffer, 1, 0);
    EXPECT_EQ(bytesRead, 0u);
}

// Test read with zero unit size
TEST_F(CachedFileTest_1484, ReadZeroUnitSize_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    char buffer[10];
    size_t bytesRead = cachedFile.read(buffer, 0, 10);
    EXPECT_EQ(bytesRead, 0u);
}

// Test that read advances the stream position
TEST_F(CachedFileTest_1484, ReadAdvancesPosition_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    EXPECT_CALL(*loader, load(testing::_, testing::_))
        .WillRepeatedly(testing::Return(0));
    
    CachedFile cachedFile(std::move(loader));
    
    long posBefore = cachedFile.tell();
    char buffer[50];
    size_t bytesRead = cachedFile.read(buffer, 1, 50);
    long posAfter = cachedFile.tell();
    
    EXPECT_EQ(posAfter, posBefore + static_cast<long>(bytesRead));
}

// Test cache with empty ranges
TEST_F(CachedFileTest_1484, CacheEmptyRanges_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    std::vector<ByteRange> emptyRanges;
    int result = cachedFile.cache(emptyRanges);
    // Caching empty ranges should succeed or return 0
    EXPECT_EQ(result, 0);
}

// Test cache with valid ranges
TEST_F(CachedFileTest_1484, CacheValidRanges_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    EXPECT_CALL(*loader, load(testing::_, testing::_))
        .WillRepeatedly(testing::Return(0));
    
    CachedFile cachedFile(std::move(loader));
    
    std::vector<ByteRange> ranges;
    ByteRange range;
    range.offset = 0;
    range.length = 512;
    ranges.push_back(range);
    
    int result = cachedFile.cache(ranges);
    EXPECT_EQ(result, 0);
}

// Test getLength is const and can be called multiple times
TEST_F(CachedFileTest_1484, GetLengthIsIdempotent_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(4096));
    
    CachedFile cachedFile(std::move(loader));
    
    unsigned int len1 = cachedFile.getLength();
    unsigned int len2 = cachedFile.getLength();
    unsigned int len3 = cachedFile.getLength();
    
    EXPECT_EQ(len1, len2);
    EXPECT_EQ(len2, len3);
    EXPECT_EQ(len1, 4096u);
}

// Test seek to beginning after seeking to middle
TEST_F(CachedFileTest_1484, SeekBackToBeginning_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    cachedFile.seek(500, SEEK_SET);
    EXPECT_EQ(cachedFile.tell(), 500);
    
    cachedFile.seek(0, SEEK_SET);
    EXPECT_EQ(cachedFile.tell(), 0);
}

// Test seek with negative offset from end
TEST_F(CachedFileTest_1484, SeekNegativeFromEnd_1484) {
    auto loader = std::make_unique<MockCachedFileLoader>();
    EXPECT_CALL(*loader, init(testing::_, testing::_))
        .WillOnce(testing::Return(1024));
    
    CachedFile cachedFile(std::move(loader));
    
    int result = cachedFile.seek(-100, SEEK_END);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(cachedFile.tell(), 924);
}

// Test that CachedFile is not copyable
TEST_F(CachedFileTest_1484, NotCopyable_1484) {
    EXPECT_FALSE(std::is_copy_constructible<CachedFile>::value);
    EXPECT_FALSE(std::is_copy_assignable<CachedFile>::value);
}
