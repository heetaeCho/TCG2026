#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

// Include the necessary headers
#include "catch2/internal/catch_reusable_string_stream.cpp"

// We need access to the StringStreams struct
// Since it's in the Catch namespace, we use it directly

class StringStreamsTest_647 : public ::testing::Test {
protected:
    Catch::StringStreams streams;
};

// Test that add() returns a valid index
TEST_F(StringStreamsTest_647, AddReturnsValidIndex_647) {
    std::size_t index = streams.add();
    EXPECT_EQ(index, 0u);
}

// Test that add() returns incrementing indices when no streams are released
TEST_F(StringStreamsTest_647, AddReturnsIncrementingIndices_647) {
    std::size_t idx0 = streams.add();
    std::size_t idx1 = streams.add();
    std::size_t idx2 = streams.add();
    
    EXPECT_EQ(idx0, 0u);
    EXPECT_EQ(idx1, 1u);
    EXPECT_EQ(idx2, 2u);
}

// Test that release makes the index available for reuse
TEST_F(StringStreamsTest_647, ReleaseAndReuseIndex_647) {
    std::size_t idx0 = streams.add();
    std::size_t idx1 = streams.add();
    
    streams.release(idx0);
    
    // Next add should reuse the released index
    std::size_t idx2 = streams.add();
    EXPECT_EQ(idx2, idx0);
}

// Test that releasing multiple streams allows them to be reused
TEST_F(StringStreamsTest_647, ReleaseMultipleAndReuse_647) {
    std::size_t idx0 = streams.add();
    std::size_t idx1 = streams.add();
    std::size_t idx2 = streams.add();
    
    streams.release(idx1);
    streams.release(idx0);
    
    // Should reuse released indices (LIFO order from m_unused)
    std::size_t idx3 = streams.add();
    std::size_t idx4 = streams.add();
    
    // idx0 was pushed last, so it should be reused first (LIFO)
    EXPECT_EQ(idx3, idx0);
    EXPECT_EQ(idx4, idx1);
}

// Test that release resets the stream state
TEST_F(StringStreamsTest_647, ReleaseResetsStreamState_647) {
    std::size_t idx = streams.add();
    
    // Access the stream and modify its state
    auto& stream = *streams.m_streams[idx];
    stream << "some content";
    stream.setf(std::ios::hex, std::ios::basefield);
    
    streams.release(idx);
    
    // After release, the format flags should be restored to reference state
    std::size_t reusedIdx = streams.add();
    EXPECT_EQ(reusedIdx, idx);
    
    auto& reusedStream = *streams.m_streams[reusedIdx];
    // The copyfmt should have restored flags to match the reference stream
    EXPECT_EQ(reusedStream.flags(), streams.m_referenceStream.flags());
}

// Test that the m_unused vector is populated after release
TEST_F(StringStreamsTest_647, UnusedVectorPopulatedAfterRelease_647) {
    std::size_t idx = streams.add();
    EXPECT_TRUE(streams.m_unused.empty());
    
    streams.release(idx);
    EXPECT_EQ(streams.m_unused.size(), 1u);
    EXPECT_EQ(streams.m_unused[0], idx);
}

// Test that the m_streams vector grows with add
TEST_F(StringStreamsTest_647, StreamsVectorGrowsWithAdd_647) {
    EXPECT_EQ(streams.m_streams.size(), 0u);
    
    streams.add();
    EXPECT_EQ(streams.m_streams.size(), 1u);
    
    streams.add();
    EXPECT_EQ(streams.m_streams.size(), 2u);
}

// Test that adding after releasing does not grow m_streams
TEST_F(StringStreamsTest_647, AddAfterReleaseDoesNotGrowStreams_647) {
    std::size_t idx0 = streams.add();
    std::size_t idx1 = streams.add();
    std::size_t originalSize = streams.m_streams.size();
    
    streams.release(idx0);
    
    std::size_t idx2 = streams.add();
    EXPECT_EQ(streams.m_streams.size(), originalSize);
    EXPECT_EQ(idx2, idx0);
}

// Test that release restores precision
TEST_F(StringStreamsTest_647, ReleaseRestoresPrecision_647) {
    std::size_t idx = streams.add();
    auto& stream = *streams.m_streams[idx];
    
    auto originalPrecision = streams.m_referenceStream.precision();
    stream.precision(42);
    
    streams.release(idx);
    
    std::size_t reusedIdx = streams.add();
    auto& reusedStream = *streams.m_streams[reusedIdx];
    EXPECT_EQ(reusedStream.precision(), originalPrecision);
}

// Test adding many streams
TEST_F(StringStreamsTest_647, AddManyStreams_647) {
    const std::size_t count = 100;
    for (std::size_t i = 0; i < count; ++i) {
        std::size_t idx = streams.add();
        EXPECT_EQ(idx, i);
    }
    EXPECT_EQ(streams.m_streams.size(), count);
}

// Test release and re-add cycle multiple times
TEST_F(StringStreamsTest_647, RepeatedReleaseAndReaddCycle_647) {
    std::size_t idx = streams.add();
    
    for (int i = 0; i < 10; ++i) {
        streams.release(idx);
        std::size_t reusedIdx = streams.add();
        EXPECT_EQ(reusedIdx, idx);
    }
    
    // Only one stream should exist
    EXPECT_EQ(streams.m_streams.size(), 1u);
}

// Test that release restores fill character
TEST_F(StringStreamsTest_647, ReleaseRestoresFillCharacter_647) {
    std::size_t idx = streams.add();
    auto& stream = *streams.m_streams[idx];
    
    auto originalFill = streams.m_referenceStream.fill();
    stream.fill('X');
    
    streams.release(idx);
    
    std::size_t reusedIdx = streams.add();
    auto& reusedStream = *streams.m_streams[reusedIdx];
    EXPECT_EQ(reusedStream.fill(), originalFill);
}

// Test that release restores width
TEST_F(StringStreamsTest_647, ReleaseRestoresWidth_647) {
    std::size_t idx = streams.add();
    auto& stream = *streams.m_streams[idx];
    
    stream.width(20);
    
    streams.release(idx);
    
    std::size_t reusedIdx = streams.add();
    auto& reusedStream = *streams.m_streams[reusedIdx];
    EXPECT_EQ(reusedStream.width(), streams.m_referenceStream.width());
}
