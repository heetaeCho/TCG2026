// ReusableStringStream_tests_648.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "catch2/internal/catch_reusable_string_stream.hpp"

using Catch::ReusableStringStream;

class ReusableStringStreamTest_648 : public ::testing::Test {};

// Ensures a freshly constructed stream is empty and usable.
TEST_F(ReusableStringStreamTest_648, ConstructDefaultEmpty_648) {
    ReusableStringStream rss;
    EXPECT_EQ(rss.str(), "");
    EXPECT_TRUE(rss.get().good());
}

// Writing via operator<< is reflected in str()
TEST_F(ReusableStringStreamTest_648, WriteAndStrReturnsContent_648) {
    ReusableStringStream rss;
    rss << "hello " << 123 << ' ' << 4.5;
    const std::string s = rss.str();
    EXPECT_NE(s.find("hello"), std::string::npos);
    EXPECT_NE(s.find("123"), std::string::npos);
    EXPECT_NE(s.find("4.5"), std::string::npos);
}

// Setting content via str(const std::string&) overwrites previous content
TEST_F(ReusableStringStreamTest_648, StrSetterOverwritesContent_648) {
    ReusableStringStream rss;
    rss << "initial";
    EXPECT_NE(rss.str().find("initial"), std::string::npos);

    rss.str(std::string("reset"));
    EXPECT_EQ(rss.str(), "reset");

    rss << "X";
    EXPECT_EQ(rss.str(), "resetX");
}

// get() returns an ostream reference that affects the same buffer
TEST_F(ReusableStringStreamTest_648, GetReturnsOstreamReference_648) {
    ReusableStringStream rss;
    std::ostream& os = rss.get();
    os << "via_get";
    EXPECT_EQ(rss.str(), "via_get");
}

// Two instances do not interfere with each other's contents
TEST_F(ReusableStringStreamTest_648, MultipleInstancesAreIndependent_648) {
    ReusableStringStream a;
    ReusableStringStream b;

    a << "stream_a";
    b << "stream_b";

    EXPECT_EQ(a.str(), "stream_a");
    EXPECT_EQ(b.str(), "stream_b");
}

// After destruction, an internally pooled stream is cleared and reusable
TEST_F(ReusableStringStreamTest_648, DestructorResetsForReuse_648) {
    // Create a scope to force destruction
    {
        ReusableStringStream rss;
        rss << "to be cleared";
        // Simulate a non-good state that should be cleared by dtor
        rss.get().setstate(std::ios::badbit);
        EXPECT_FALSE(rss.get().good());
        // rss goes out of scope here; dtor should clear flags & buffer and
        // release it back to the pool.
    }

    // New instance should observe a clean, empty, good stream, regardless of
    // whether it reuses the same underlying stream or a different one.
    ReusableStringStream rss2;
    EXPECT_TRUE(rss2.get().good());
    EXPECT_EQ(rss2.str(), "");

    rss2 << "ok";
    EXPECT_EQ(rss2.str(), "ok");
}

// Repeated construction/destruction should always yield a clean stream
TEST_F(ReusableStringStreamTest_648, RepeatedReuseYieldsCleanState_648) {
    for (int i = 0; i < 5; ++i) {
        {
            ReusableStringStream rss;
            EXPECT_TRUE(rss.get().good());
            EXPECT_EQ(rss.str(), "");

            rss << "round" << i;
            EXPECT_NE(rss.str().find(std::to_string(i)), std::string::npos);
        }
        // Next iteration should start clean again
    }

    // Final sanity: a fresh one is still clean
    ReusableStringStream finalRss;
    EXPECT_TRUE(finalRss.get().good());
    EXPECT_EQ(finalRss.str(), "");
}
