#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Declaration of the function under test
namespace Catch {
    std::ostream& cout();
}

TEST(CatchStdStreamsTest_547, CoutReturnsStdCout_547) {
    // Verify that Catch::cout() returns a reference to std::cout
    std::ostream& result = Catch::cout();
    EXPECT_EQ(&result, &std::cout);
}

TEST(CatchStdStreamsTest_547, CoutIsWritable_547) {
    // Verify that writing to Catch::cout() works (it should behave like std::cout)
    std::ostream& result = Catch::cout();
    // The stream should be in a good state
    EXPECT_TRUE(result.good());
}

TEST(CatchStdStreamsTest_547, CoutReturnsSameReferenceOnMultipleCalls_547) {
    // Verify that multiple calls return the same reference
    std::ostream& first = Catch::cout();
    std::ostream& second = Catch::cout();
    EXPECT_EQ(&first, &second);
}

TEST(CatchStdStreamsTest_547, CoutStreamIsNotInFailState_547) {
    // Verify the returned stream is not in a fail state
    std::ostream& result = Catch::cout();
    EXPECT_FALSE(result.fail());
    EXPECT_FALSE(result.bad());
}

TEST(CatchStdStreamsTest_547, CoutSupportsStreamOperator_547) {
    // Verify that the returned stream supports the << operator without error
    std::ostream& result = Catch::cout();
    result << "";  // Write empty string
    EXPECT_TRUE(result.good());
}

TEST(CatchStdStreamsTest_547, CoutRdbufMatchesStdCout_547) {
    // Verify that the underlying stream buffer is the same as std::cout's
    std::ostream& result = Catch::cout();
    EXPECT_EQ(result.rdbuf(), std::cout.rdbuf());
}
