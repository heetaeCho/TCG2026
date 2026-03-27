// File: catch_message_stream_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_message.hpp"  // Path from the prompt

using namespace Catch;

// A simple custom type with ostream<< defined to verify forwarding works
struct Point {
    int x{}, y{};
};
static std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "Point(" << p.x << "," << p.y << ")";
    return os;
}

// --- Tests ---

// Verifies that operator<< returns a MessageStream& so chaining is possible, and
// that streamed content is accumulated in the underlying public m_stream.
TEST(MessageStreamTest_106, ChainingAccumulatesAndReturnsSelf_106) {
    MessageStream ms;

    // Chaining should compile and not throw
    ASSERT_NO_THROW({
        MessageStream& ref = (ms << "Hello" << 123 << ' ' << 4.5);
        // Must be the same object (self-return)
        EXPECT_EQ(&ref, &ms);
    });

    // Observable result through the public interface
    EXPECT_EQ(ms.m_stream.str(), std::string("Hello123 4.5"));
}

// Verifies streaming of different basic types (boundary-ish small set).
TEST(MessageStreamTest_106, StreamsVariousFundamentalTypes_106) {
    MessageStream ms;

    ASSERT_NO_THROW({
        ms << true      // usually prints 1
           << ' ' 
           << false     // usually prints 0
           << ' '
           << -42
           << ' '
           << 0u
           << ' '
           << 3.1415
           << ' '
           << "ok";
    });

    // Compare against an independently constructed expected string
    std::ostringstream oss;
    oss << true << ' ' << false << ' ' << -42 << ' ' << 0u << ' ' << 3.1415 << ' ' << "ok";
    EXPECT_EQ(ms.m_stream.str(), oss.str());
}

// Verifies that strings with edge characters (empty, whitespace, newline, Unicode)
// are forwarded intact into the underlying stream.
TEST(MessageStreamTest_106, PreservesEdgeCaseStrings_106) {
    MessageStream ms;

    const std::string empty = "";
    const std::string spaces = "   ";
    const std::string newline = "line1\nline2";
    const std::string unicode = u8"한글😊";

    ms << empty << spaces << newline << unicode;

    std::ostringstream oss;
    oss << empty << spaces << newline << unicode;

    EXPECT_EQ(ms.m_stream.str(), oss.str());
}

// Verifies that user-defined types with an ostream<< overload are forwarded correctly.
TEST(MessageStreamTest_106, StreamsUserDefinedType_106) {
    MessageStream ms;
    Point p{3, 7};

    ms << "P=" << p;

    EXPECT_EQ(ms.m_stream.str(), std::string("P=Point(3,7)"));
}

// Verifies that multiple independent MessageStream instances do not interfere with each other
// (observable via their public m_stream outputs).
TEST(MessageStreamTest_106, MultipleInstancesAreIndependent_106) {
    MessageStream a;
    MessageStream b;

    a << "A" << 1;
    b << "B" << 2;

    EXPECT_EQ(a.m_stream.str(), std::string("A1"));
    EXPECT_EQ(b.m_stream.str(), std::string("B2"));
    EXPECT_NE(&a, &b);
}

// Verifies that operator<< is noexcept-safe in practice for typical insertions by asserting no throws.
// (We are not asserting noexcept at the type level; just observable behavior.)
TEST(MessageStreamTest_106, NoThrowOnTypicalInsertions_106) {
    MessageStream ms;

    EXPECT_NO_THROW({
        ms << "start" << 0 << ' ' << 42.0 << ' ' << std::string("end");
    });

    std::ostringstream oss;
    oss << "start" << 0 << ' ' << 42.0 << ' ' << std::string("end");
    EXPECT_EQ(ms.m_stream.str(), oss.str());
}
