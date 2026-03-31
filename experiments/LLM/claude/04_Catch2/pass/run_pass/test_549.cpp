#include <gtest/gtest.h>
#include <sstream>
#include <ostream>

// Declaration of the function under test
namespace Catch {
    std::ostream& clog();
}

TEST(CatchStdStreamsTest_549, ClogReturnsValidOstream_549) {
    std::ostream& result = Catch::clog();
    // The returned reference should be a valid ostream
    EXPECT_TRUE(result.good());
}

TEST(CatchStdStreamsTest_549, ClogReturnsSameAsStdClog_549) {
    std::ostream& result = Catch::clog();
    // The function should return a reference to std::clog
    EXPECT_EQ(&result, &std::clog);
}

TEST(CatchStdStreamsTest_549, ClogReturnsConsistentReference_549) {
    // Multiple calls should return the same reference
    std::ostream& first = Catch::clog();
    std::ostream& second = Catch::clog();
    EXPECT_EQ(&first, &second);
}

TEST(CatchStdStreamsTest_549, ClogIsWritable_549) {
    std::ostream& result = Catch::clog();
    // Should be able to write to the returned stream without failure
    result << "";
    EXPECT_FALSE(result.fail());
}

TEST(CatchStdStreamsTest_549, ClogStreamStateIsGood_549) {
    std::ostream& result = Catch::clog();
    EXPECT_FALSE(result.bad());
    EXPECT_FALSE(result.fail());
    EXPECT_FALSE(result.eof());
}

TEST(CatchStdStreamsTest_549, ClogCanWriteString_549) {
    std::ostream& result = Catch::clog();
    result << "test message from unit test";
    EXPECT_TRUE(result.good());
}

TEST(CatchStdStreamsTest_549, ClogCanWriteInteger_549) {
    std::ostream& result = Catch::clog();
    result << 42;
    EXPECT_TRUE(result.good());
}

TEST(CatchStdStreamsTest_549, ClogCanWriteDouble_549) {
    std::ostream& result = Catch::clog();
    result << 3.14;
    EXPECT_TRUE(result.good());
}

TEST(CatchStdStreamsTest_549, ClogRdbufMatchesStdClog_549) {
    std::ostream& result = Catch::clog();
    EXPECT_EQ(result.rdbuf(), std::clog.rdbuf());
}
