#include <gtest/gtest.h>
#include <exception>
#include <cstring>

// Include the header or declare the class based on the known interface
namespace Catch {
namespace Benchmark {
namespace Detail {

struct optimized_away_error : public std::exception {
    const char* what() const noexcept override;
};

} // namespace Detail
} // namespace Benchmark
} // namespace Catch

using Catch::Benchmark::Detail::optimized_away_error;

// Test that optimized_away_error can be default constructed
TEST(OptimizedAwayErrorTest_983, DefaultConstruction_983) {
    optimized_away_error error;
    // Should not throw during construction
    SUCCEED();
}

// Test that what() returns the expected error message
TEST(OptimizedAwayErrorTest_983, WhatReturnsExpectedMessage_983) {
    optimized_away_error error;
    const char* msg = error.what();
    ASSERT_NE(msg, nullptr);
    EXPECT_STREQ(msg, "could not measure benchmark, maybe it was optimized away");
}

// Test that what() returns a non-null pointer
TEST(OptimizedAwayErrorTest_983, WhatReturnsNonNull_983) {
    optimized_away_error error;
    EXPECT_NE(error.what(), nullptr);
}

// Test that what() is consistent across multiple calls
TEST(OptimizedAwayErrorTest_983, WhatIsConsistentAcrossMultipleCalls_983) {
    optimized_away_error error;
    const char* msg1 = error.what();
    const char* msg2 = error.what();
    EXPECT_STREQ(msg1, msg2);
}

// Test that optimized_away_error is derived from std::exception
TEST(OptimizedAwayErrorTest_983, IsStdException_983) {
    optimized_away_error error;
    const std::exception& base_ref = error;
    EXPECT_STREQ(base_ref.what(), "could not measure benchmark, maybe it was optimized away");
}

// Test that optimized_away_error can be caught as std::exception
TEST(OptimizedAwayErrorTest_983, CatchableAsStdException_983) {
    bool caught = false;
    try {
        throw optimized_away_error();
    } catch (const std::exception& e) {
        caught = true;
        EXPECT_STREQ(e.what(), "could not measure benchmark, maybe it was optimized away");
    }
    EXPECT_TRUE(caught);
}

// Test that optimized_away_error can be caught by its own type
TEST(OptimizedAwayErrorTest_983, CatchableByOwnType_983) {
    bool caught = false;
    try {
        throw optimized_away_error();
    } catch (const optimized_away_error& e) {
        caught = true;
        EXPECT_STREQ(e.what(), "could not measure benchmark, maybe it was optimized away");
    }
    EXPECT_TRUE(caught);
}

// Test that the error message has expected non-zero length
TEST(OptimizedAwayErrorTest_983, WhatMessageHasNonZeroLength_983) {
    optimized_away_error error;
    EXPECT_GT(std::strlen(error.what()), 0u);
}

// Test copy construction preserves the message
TEST(OptimizedAwayErrorTest_983, CopyConstructionPreservesMessage_983) {
    optimized_away_error original;
    optimized_away_error copy(original);
    EXPECT_STREQ(copy.what(), original.what());
}

// Test copy assignment preserves the message
TEST(OptimizedAwayErrorTest_983, CopyAssignmentPreservesMessage_983) {
    optimized_away_error original;
    optimized_away_error assigned;
    assigned = original;
    EXPECT_STREQ(assigned.what(), original.what());
}

// Test that what() is noexcept
TEST(OptimizedAwayErrorTest_983, WhatIsNoexcept_983) {
    optimized_away_error error;
    EXPECT_TRUE(noexcept(error.what()));
}

// Test multiple instances return the same message
TEST(OptimizedAwayErrorTest_983, MultipleInstancesSameMessage_983) {
    optimized_away_error error1;
    optimized_away_error error2;
    EXPECT_STREQ(error1.what(), error2.what());
}
