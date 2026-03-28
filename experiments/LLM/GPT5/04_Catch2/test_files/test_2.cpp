// ReusableStringStream_test_2.cpp
#include <gtest/gtest.h>
#include <string>
#include <ostream>
#include <type_traits>

// Include the class under test
#include "Catch2/src/catch2/internal/catch_reusable_string_stream.hpp"

using Catch::ReusableStringStream;

// Compile-time interface property (non-copyable) — checked without inspecting internals.
static_assert(!std::is_copy_constructible<ReusableStringStream>::value,
              "ReusableStringStream should be non-copyable");
static_assert(!std::is_copy_assignable<ReusableStringStream>::value,
              "ReusableStringStream should be non-copy-assignable");

// 1) Construction & initial state (observable via str()).
TEST(ReusableStringStreamTest_2, DefaultConstructedIsEmpty_2) {
    ReusableStringStream rss;
    EXPECT_EQ(rss.str(), "");
}

// 2) Writing via operator<< accumulates text and values (observable via str()).
TEST(ReusableStringStreamTest_2, OperatorShiftAccumulatesToString_2) {
    ReusableStringStream rss;
    rss << "Hello " << 123 << ' ' << 4.5;
    // We only check the presence/format we put in; exact float formatting is implementation-defined,
    // but standard operator<< default formatting should include "4.5". Keep it simple:
    const std::string s = rss.str();
    EXPECT_NE(s.find("Hello "), std::string::npos);
    EXPECT_NE(s.find("123"), std::string::npos);
    EXPECT_NE(s.find("4.5"), std::string::npos);
}

// 3) get() returns an ostream& that affects the same underlying buffer (observable via str()).
TEST(ReusableStringStreamTest_2, GetReturnsStreamThatWritesIntoBuffer_2) {
    ReusableStringStream rss;
    std::ostream& os = rss.get();
    os << "via get()";
    EXPECT_EQ(rss.str(), "via get()");
}

// 4) Setter replaces current contents (observable via str()).
TEST(ReusableStringStreamTest_2, StrSetterReplacesContent_2) {
    ReusableStringStream rss;
    rss << "prefix";
    rss.str("reset");
    EXPECT_EQ(rss.str(), "reset");

    rss.str("");  // also check clearing to empty
    EXPECT_EQ(rss.str(), "");
}

// 5) Operator<< returns self to allow chaining (observable via address equality & final content).
TEST(ReusableStringStreamTest_2, OperatorShiftReturnsSelfForChaining_2) {
    ReusableStringStream rss;
    ReusableStringStream* ret = &(rss << "A");
    // Chaining should be possible and return the same object
    EXPECT_EQ(ret, &rss);
    (rss << "B") << "C";
    EXPECT_EQ(rss.str(), "ABC");
}

// 6) Multiple instances are independent (observable via their separate str()).
TEST(ReusableStringStreamTest_2, MultipleInstancesAreIndependent_2) {
    ReusableStringStream a;
    ReusableStringStream b;

    a << "alpha";
    b << "beta";

    EXPECT_EQ(a.str(), "alpha");
    EXPECT_EQ(b.str(), "beta");

    // Mutate one and ensure the other is unaffected
    a.str("A");
    EXPECT_EQ(a.str(), "A");
    EXPECT_EQ(b.str(), "beta");
}

// 7) Large write (boundary-ish) still accessible via str().
TEST(ReusableStringStreamTest_2, LargeWriteAccessibleViaStr_2) {
    ReusableStringStream rss;
    std::string big(10000, 'x'); // 10k chars
    rss << big;
    EXPECT_EQ(rss.str().size(), big.size());
    EXPECT_EQ(rss.str(), big);
}
