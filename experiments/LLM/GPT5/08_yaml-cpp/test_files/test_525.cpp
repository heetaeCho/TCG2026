#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

using namespace YAML;

// Test fixture for Emitter::SetPreCommentIndent
class EmitterSetPreCommentIndentTest_525 : public ::testing::Test {
protected:
    Emitter emitter;
};

/**
 * Normal operation:
 * Verifies that setting a typical pre-comment indent value succeeds.
 */
TEST_F(EmitterSetPreCommentIndentTest_525,
       SetTypicalIndentReturnsTrue_525) {
    bool result = emitter.SetPreCommentIndent(2);

    EXPECT_TRUE(result);
    EXPECT_TRUE(emitter.good());
}

/**
 * Boundary condition:
 * Verifies that setting the pre-comment indent to zero is handled.
 */
TEST_F(EmitterSetPreCommentIndentTest_525,
       SetZeroIndentBoundary_525) {
    bool result = emitter.SetPreCommentIndent(0);

    EXPECT_TRUE(result);
    EXPECT_TRUE(emitter.good());
}

/**
 * Boundary condition:
 * Verifies that a very large indent value does not cause failure.
 */
TEST_F(EmitterSetPreCommentIndentTest_525,
       SetLargeIndentBoundary_525) {
    std::size_t largeIndent = static_cast<std::size_t>(1024);

    bool result = emitter.SetPreCommentIndent(largeIndent);

    EXPECT_TRUE(result);
    EXPECT_TRUE(emitter.good());
}

/**
 * Repeated invocation:
 * Verifies that calling SetPreCommentIndent multiple times is supported.
 */
TEST_F(EmitterSetPreCommentIndentTest_525,
       RepeatedCallsRemainConsistent_525) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(1));
    EXPECT_TRUE(emitter.SetPreCommentIndent(3));
    EXPECT_TRUE(emitter.SetPreCommentIndent(0));

    EXPECT_TRUE(emitter.good());
}

/**
 * Error observability:
 * Ensures no error message is produced during valid usage.
 */
TEST_F(EmitterSetPreCommentIndentTest_525,
       NoErrorReportedAfterValidCalls_525) {
    emitter.SetPreCommentIndent(4);

    EXPECT_TRUE(emitter.GetLastError().empty());
}