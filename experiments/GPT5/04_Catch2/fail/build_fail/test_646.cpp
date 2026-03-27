// StringStreams_add_tests_646.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

// Include the real header that declares Catch::StringStreams.
// Adjust the include path to match your project layout.
#include "catch2/internal/catch_reusable_string_stream.hpp"

using Catch::StringStreams;

class StringStreamsTest_646 : public ::testing::Test {
protected:
    StringStreams streams;
};

// Verifies: When there are no unused streams, add() creates a new stream
// and returns the next sequential index (starting at 0).
TEST_F(StringStreamsTest_646, AddWhenNoUnused_CreatesNewStreamAndReturnsNextIndex_646) {
    // Precondition
    ASSERT_TRUE(streams.m_unused.empty());
    const auto initialSize = streams.m_streams.size();

    // Act
    std::size_t idx = streams.add();

    // Assert
    EXPECT_EQ(idx, initialSize) << "add() should return index == previous size when creating a new stream";
    EXPECT_EQ(streams.m_streams.size(), initialSize + 1) << "add() should grow m_streams when no unused stream exists";
}

// Verifies: Consecutive add() calls without any release() return sequential indices
// and keep growing the internal container.
TEST_F(StringStreamsTest_646, AddMultipleWithoutRelease_ReturnsSequentialIndices_646) {
    const auto baseSize = streams.m_streams.size();

    std::size_t i0 = streams.add();
    std::size_t i1 = streams.add();
    std::size_t i2 = streams.add();

    EXPECT_EQ(i0, baseSize + 0u);
    EXPECT_EQ(i1, baseSize + 1u);
    EXPECT_EQ(i2, baseSize + 2u);
    EXPECT_EQ(streams.m_streams.size(), baseSize + 3u);
}

// Verifies: After releasing a specific index, the next add() reuses that index
// (observable via the returned index) and does not grow the container.
TEST_F(StringStreamsTest_646, AddAfterRelease_ReusesReleasedIndex_646) {
    // Arrange: create two streams
    std::size_t i0 = streams.add();
    std::size_t i1 = streams.add();
    ASSERT_LT(i0, streams.m_streams.size());
    ASSERT_LT(i1, streams.m_streams.size());

    const auto sizeBeforeRelease = streams.m_streams.size();

    // Act: release the second one and then add again
    streams.release(i1);
    std::size_t reused = streams.add();

    // Assert: index reused and size unchanged (since a previously allocated stream was reused)
    EXPECT_EQ(reused, i1) << "add() should reuse the released index when available";
    EXPECT_EQ(streams.m_streams.size(), sizeBeforeRelease)
        << "Reusing a released stream should not increase m_streams size";
}

// Verifies: If multiple indices are released, add() reuses the most recently released
// index (LIFO behavior) — this is observable via return values and size not growing.
TEST_F(StringStreamsTest_646, AddAfterReleasingMultiple_ReusesInLIFOOrder_646) {
    // Arrange: create three streams
    std::size_t a = streams.add(); // 0
    std::size_t b = streams.add(); // 1
    std::size_t c = streams.add(); // 2
    const auto sizeBeforeRelease = streams.m_streams.size();

    // Release in order: first b, then a
    streams.release(b);
    streams.release(a);

    // Act & Assert: first add() should reuse 'a' (last released), second should reuse 'b'
    std::size_t reuse1 = streams.add();
    EXPECT_EQ(reuse1, a);
    EXPECT_EQ(streams.m_streams.size(), sizeBeforeRelease);

    std::size_t reuse2 = streams.add();
    EXPECT_EQ(reuse2, b);
    EXPECT_EQ(streams.m_streams.size(), sizeBeforeRelease);
}
