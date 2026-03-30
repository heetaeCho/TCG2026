// ReusableStringStream_tests_650.cpp
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_reusable_string_stream.hpp"

using Catch::ReusableStringStream;

class ReusableStringStreamTest_650 : public ::testing::Test {};

// Normal operation: operator<< writes values and str() returns the full contents
TEST_F(ReusableStringStreamTest_650, DefaultWriteAndStrReturnsConcatenated_650) {
    ReusableStringStream rss;
    rss << "Hello, " << "world" << '!' << ' ' << 42;
    EXPECT_EQ(rss.str(), std::string("Hello, world! 42"));
}

// Normal operation: get() returns an ostream that affects the same buffer
TEST_F(ReusableStringStreamTest_650, GetReturnsOstreamReferenceThatWrites_650) {
    ReusableStringStream rss;
    std::ostream& os = rss.get();
    os << "via-get";
    EXPECT_EQ(rss.str(), std::string("via-get"));
}

// Boundary: setting the string replaces prior contents (and can be called repeatedly)
TEST_F(ReusableStringStreamTest_650, SetStrReplacesContents_650) {
    ReusableStringStream rss;
    rss << "prefix";
    rss.str("first");
    EXPECT_EQ(rss.str(), std::string("first"));

    rss.str("second");
    EXPECT_EQ(rss.str(), std::string("second"));
}

// Boundary: setting empty string results in empty buffer
TEST_F(ReusableStringStreamTest_650, SetEmptyStrClearsContents_650) {
    ReusableStringStream rss;
    rss << "something";
    rss.str("");  // replace with empty
    EXPECT_EQ(rss.str(), std::string());
}

// Boundary: large string round-trip through setter/getter
TEST_F(ReusableStringStreamTest_650, LargeStringRoundTrip_650) {
    ReusableStringStream rss;
    const std::size_t N = 10000;
    std::string big(N, 'a');
    rss.str(big);
    EXPECT_EQ(rss.str().size(), N);
    EXPECT_EQ(rss.str(), big);
}

// Normal operation: stream manipulators (e.g., std::endl) are supported via operator<<
TEST_F(ReusableStringStreamTest_650, StreamManipulatorSupport_650) {
    ReusableStringStream rss;
    rss << "line1" << std::endl << "line2";
    std::string s = rss.str();
    // Expect exactly "line1\nline2" (std::endl inserts '\n')
    EXPECT_NE(s.find("line1\nline2"), std::string::npos);
}

// Normal operation: operator<< chaining returns self (same object reference)
TEST_F(ReusableStringStreamTest_650, OperatorShiftChainsAndReturnsSelf_650) {
    ReusableStringStream rss;
    ReusableStringStream& ref = (rss << "A") << "B";
    EXPECT_EQ(&ref, &rss);
    EXPECT_EQ(rss.str(), std::string("AB"));
}

// Post-set writes are observable: after str(set), additional writes are reflected
TEST_F(ReusableStringStreamTest_650, WritesAfterSetAreAppendedOrReflected_650) {
    ReusableStringStream rss;
    rss.str("base");
    rss << "-plus";
    // We do not assert specific pointer/position semantics; we only require
    // that subsequent writes are visible in the final string.
    std::string out = rss.str();
    // Must contain both the set content and the later write in that order.
    ASSERT_NE(out.find("base"), std::string::npos);
    ASSERT_NE(out.find("base-plus"), std::string::npos);
    EXPECT_EQ(out.rfind("base-plus"), out.size() - std::string("base-plus").size());
}
