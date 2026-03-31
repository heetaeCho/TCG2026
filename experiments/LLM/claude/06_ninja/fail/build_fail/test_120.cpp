#include <gtest/gtest.h>
#include <cstring>
#include <set>

// Declaration of the function under test
void RandomCommand(char** s);

class RandomCommandTest_120 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated memory
        for (char* p : allocated_) {
            delete[] p;
        }
    }
    
    void TrackAllocation(char* p) {
        allocated_.push_back(p);
    }
    
    std::vector<char*> allocated_;
};

TEST_F(RandomCommandTest_120, AllocatesNonNullString_120) {
    char* s = nullptr;
    RandomCommand(&s);
    TrackAllocation(s);
    ASSERT_NE(s, nullptr);
}

TEST_F(RandomCommandTest_120, StringIsNullTerminated_120) {
    char* s = nullptr;
    RandomCommand(&s);
    TrackAllocation(s);
    ASSERT_NE(s, nullptr);
    
    // strlen should work without crashing, meaning string is null-terminated
    size_t len = strlen(s);
    EXPECT_GE(len, 5u);
    EXPECT_LE(len, 100u);
}

TEST_F(RandomCommandTest_120, LengthWithinExpectedRange_120) {
    // Run multiple times to increase confidence about the range
    for (int i = 0; i < 100; ++i) {
        char* s = nullptr;
        RandomCommand(&s);
        TrackAllocation(s);
        ASSERT_NE(s, nullptr);
        
        size_t len = strlen(s);
        EXPECT_GE(len, 5u) << "Length was below minimum at iteration " << i;
        EXPECT_LE(len, 100u) << "Length was above maximum at iteration " << i;
    }
}

TEST_F(RandomCommandTest_120, CharactersInPrintableAsciiRange_120) {
    for (int i = 0; i < 50; ++i) {
        char* s = nullptr;
        RandomCommand(&s);
        TrackAllocation(s);
        ASSERT_NE(s, nullptr);
        
        size_t len = strlen(s);
        for (size_t j = 0; j < len; ++j) {
            int c = static_cast<unsigned char>(s[j]);
            EXPECT_GE(c, 32) << "Character at position " << j << " below range in iteration " << i;
            EXPECT_LE(c, 127) << "Character at position " << j << " above range in iteration " << i;
        }
    }
}

TEST_F(RandomCommandTest_120, ProducesVaryingLengths_120) {
    std::set<size_t> lengths;
    // Run enough times that we should see at least a few different lengths
    for (int i = 0; i < 200; ++i) {
        char* s = nullptr;
        RandomCommand(&s);
        TrackAllocation(s);
        lengths.insert(strlen(s));
    }
    // With random lengths between 5 and 100, we should see more than 1 distinct length
    EXPECT_GT(lengths.size(), 1u) << "Expected varying lengths from random generation";
}

TEST_F(RandomCommandTest_120, ProducesVaryingContent_120) {
    std::set<std::string> contents;
    for (int i = 0; i < 50; ++i) {
        char* s = nullptr;
        RandomCommand(&s);
        TrackAllocation(s);
        contents.insert(std::string(s));
    }
    // Extremely unlikely that 50 random strings are all the same
    EXPECT_GT(contents.size(), 1u) << "Expected varying content from random generation";
}

TEST_F(RandomCommandTest_120, NoNullBytesBeforeTerminator_120) {
    for (int i = 0; i < 50; ++i) {
        char* s = nullptr;
        RandomCommand(&s);
        TrackAllocation(s);
        ASSERT_NE(s, nullptr);
        
        size_t len = strlen(s);
        // Since characters are in range [32, 127], there should be no embedded null bytes
        for (size_t j = 0; j < len; ++j) {
            EXPECT_NE(s[j], '\0') << "Found null byte before end of string at position " << j;
        }
    }
}

TEST_F(RandomCommandTest_120, MultipleCallsEachAllocateNewMemory_120) {
    char* s1 = nullptr;
    char* s2 = nullptr;
    RandomCommand(&s1);
    RandomCommand(&s2);
    TrackAllocation(s1);
    TrackAllocation(s2);
    
    ASSERT_NE(s1, nullptr);
    ASSERT_NE(s2, nullptr);
    // Each call should allocate its own memory
    EXPECT_NE(s1, s2);
}
