#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <memory>

// Reconstruct the minimal interface needed for testing based on the provided code
namespace Catch {
    namespace Detail {
        template<typename T, typename... Args>
        std::unique_ptr<T> make_unique(Args&&... args) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
        
        template<typename T>
        using unique_ptr = std::unique_ptr<T>;
    }

    struct StringStreams {
    public:
        std::vector<Detail::unique_ptr<std::ostringstream>> m_streams;
        std::vector<std::size_t> m_unused;
        std::ostringstream m_referenceStream;

        auto add() -> std::size_t {
            if (m_unused.empty()) {
                m_streams.push_back(Detail::make_unique<std::ostringstream>());
                return m_streams.size() - 1;
            } else {
                auto index = m_unused.back();
                m_unused.pop_back();
                return index;
            }
        }

        void release(std::size_t index) {
            m_unused.push_back(index);
        }
    };
}

class StringStreamsTest_646 : public ::testing::Test {
protected:
    Catch::StringStreams streams;
};

TEST_F(StringStreamsTest_646, AddFirstElementReturnsZero_646) {
    std::size_t index = streams.add();
    EXPECT_EQ(index, 0u);
}

TEST_F(StringStreamsTest_646, AddSecondElementReturnsOne_646) {
    streams.add();
    std::size_t index = streams.add();
    EXPECT_EQ(index, 1u);
}

TEST_F(StringStreamsTest_646, AddMultipleElementsReturnsIncrementingIndices_646) {
    for (std::size_t i = 0; i < 10; ++i) {
        std::size_t index = streams.add();
        EXPECT_EQ(index, i);
    }
}

TEST_F(StringStreamsTest_646, AddIncreasesStreamCount_646) {
    EXPECT_EQ(streams.m_streams.size(), 0u);
    streams.add();
    EXPECT_EQ(streams.m_streams.size(), 1u);
    streams.add();
    EXPECT_EQ(streams.m_streams.size(), 2u);
}

TEST_F(StringStreamsTest_646, AddReusesReleasedIndex_646) {
    std::size_t idx0 = streams.add();
    std::size_t idx1 = streams.add();
    
    streams.release(idx0);
    
    std::size_t reused = streams.add();
    EXPECT_EQ(reused, idx0);
    // Stream count should not increase when reusing
    EXPECT_EQ(streams.m_streams.size(), 2u);
}

TEST_F(StringStreamsTest_646, AddReusesLastReleasedFirst_646) {
    std::size_t idx0 = streams.add();
    std::size_t idx1 = streams.add();
    std::size_t idx2 = streams.add();
    
    streams.release(idx0);
    streams.release(idx2);
    
    // Should reuse idx2 first (last released = back of unused vector)
    std::size_t reused1 = streams.add();
    EXPECT_EQ(reused1, idx2);
    
    // Then idx0
    std::size_t reused2 = streams.add();
    EXPECT_EQ(reused2, idx0);
}

TEST_F(StringStreamsTest_646, ReleaseAddsToUnused_646) {
    std::size_t idx = streams.add();
    EXPECT_EQ(streams.m_unused.size(), 0u);
    
    streams.release(idx);
    EXPECT_EQ(streams.m_unused.size(), 1u);
    EXPECT_EQ(streams.m_unused.back(), idx);
}

TEST_F(StringStreamsTest_646, AddAfterAllReleasedDoesNotCreateNewStream_646) {
    std::size_t idx0 = streams.add();
    std::size_t idx1 = streams.add();
    
    streams.release(idx0);
    streams.release(idx1);
    
    std::size_t streamCountBefore = streams.m_streams.size();
    
    streams.add();
    streams.add();
    
    EXPECT_EQ(streams.m_streams.size(), streamCountBefore);
}

TEST_F(StringStreamsTest_646, AddCreatesNewStreamWhenNoUnused_646) {
    streams.add();
    streams.add();
    
    EXPECT_EQ(streams.m_unused.size(), 0u);
    
    std::size_t idx = streams.add();
    EXPECT_EQ(idx, 2u);
    EXPECT_EQ(streams.m_streams.size(), 3u);
}

TEST_F(StringStreamsTest_646, AddAfterPartialReleaseReusesCorrectly_646) {
    std::size_t idx0 = streams.add();
    std::size_t idx1 = streams.add();
    std::size_t idx2 = streams.add();
    
    // Release only the middle one
    streams.release(idx1);
    
    // Next add should reuse idx1
    std::size_t reused = streams.add();
    EXPECT_EQ(reused, idx1);
    
    // Next add should create new stream
    std::size_t newIdx = streams.add();
    EXPECT_EQ(newIdx, 3u);
}

TEST_F(StringStreamsTest_646, UnusedIsEmptyAfterReuse_646) {
    std::size_t idx = streams.add();
    streams.release(idx);
    EXPECT_EQ(streams.m_unused.size(), 1u);
    
    streams.add();
    EXPECT_EQ(streams.m_unused.size(), 0u);
}

TEST_F(StringStreamsTest_646, MultipleReleaseAndAddCycles_646) {
    std::size_t idx0 = streams.add();
    streams.release(idx0);
    
    std::size_t reused0 = streams.add();
    EXPECT_EQ(reused0, idx0);
    
    streams.release(reused0);
    
    std::size_t reused1 = streams.add();
    EXPECT_EQ(reused1, idx0);
    EXPECT_EQ(streams.m_streams.size(), 1u);
}

TEST_F(StringStreamsTest_646, StreamsAreValidOstringstreamPointers_646) {
    std::size_t idx = streams.add();
    ASSERT_NE(streams.m_streams[idx], nullptr);
    
    // Verify we can write to the stream
    *streams.m_streams[idx] << "hello";
    EXPECT_EQ(streams.m_streams[idx]->str(), "hello");
}

TEST_F(StringStreamsTest_646, LargeNumberOfAdds_646) {
    const std::size_t count = 1000;
    for (std::size_t i = 0; i < count; ++i) {
        std::size_t idx = streams.add();
        EXPECT_EQ(idx, i);
    }
    EXPECT_EQ(streams.m_streams.size(), count);
}

TEST_F(StringStreamsTest_646, ReleaseAllThenAddReusesInLIFOOrder_646) {
    const std::size_t count = 5;
    std::vector<std::size_t> indices;
    for (std::size_t i = 0; i < count; ++i) {
        indices.push_back(streams.add());
    }
    
    // Release in order 0, 1, 2, 3, 4
    for (std::size_t i = 0; i < count; ++i) {
        streams.release(indices[i]);
    }
    
    // Should reuse in reverse order: 4, 3, 2, 1, 0 (LIFO)
    for (std::size_t i = 0; i < count; ++i) {
        std::size_t reused = streams.add();
        EXPECT_EQ(reused, indices[count - 1 - i]);
    }
}
