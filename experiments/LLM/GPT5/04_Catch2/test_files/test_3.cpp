// stringref_tests_3.cc
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

namespace {

// ---------- Construction & basic conversion ----------

TEST(StringRefTest_3, CStrToStdString_3) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST(StringRefTest_3, StdStringCtorEqualityAndInequality_3) {
    std::string base = "world";
    StringRef a(base);
    StringRef b("world");
    StringRef c("worlds");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a == c);
}

// ---------- Empty & size/iteration/data ----------

TEST(StringRefTest_3, DefaultCtorIsEmpty_3) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);

    std::string s = static_cast<std::string>(sr);
    EXPECT_TRUE(s.empty());

    // begin() == end() when empty
    auto it_b = sr.begin();
    auto it_e = sr.end();
    EXPECT_TRUE(it_b == it_e);
}

TEST(StringRefTest_3, DataAndIterationMatchContent_3) {
    StringRef sr("xyz");
    ASSERT_FALSE(sr.empty());

    // data()
    EXPECT_EQ(sr.data()[0], sr[0]);

    // Iteration builds the same string
    std::string iterated;
    for (auto ch : sr) iterated.push_back(ch);
    EXPECT_EQ(iterated, static_cast<std::string>(sr));
}

// ---------- Indexing & substr ----------

TEST(StringRefTest_3, IndexOperatorValidBounds_3) {
    StringRef sr("abc");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[2], 'c');
    // (No out-of-bounds access; behavior would be undefined.)
}

TEST(StringRefTest_3, SubstrBasic_3) {
    StringRef sr("abcdef");
    StringRef mid = sr.substr(2, 3);       // "cde"
    StringRef zero = sr.substr(0, 0);      // ""
    StringRef at_end = sr.substr(sr.size(), 0); // ""

    EXPECT_EQ(static_cast<std::string>(mid), "cde");
    EXPECT_EQ(static_cast<std::string>(zero), "");
    EXPECT_EQ(static_cast<std::string>(at_end), "");
}

// ---------- Embedded NULs via (ptr, size) ctor ----------

TEST(StringRefTest_3, AllowsEmbeddedNullsWithSizeCtor_3) {
    const char raw[] = { 'a', '\0', 'b' };
    StringRef sr(raw, 3);
    std::string s = static_cast<std::string>(sr);

    ASSERT_EQ(s.size(), 3u);
    EXPECT_EQ(s[0], 'a');
    EXPECT_EQ(s[1], '\0');
    EXPECT_EQ(s[2], 'b');
}

// ---------- Streaming & concatenation ----------

TEST(StringRefTest_3, OstreamInsertionPrintsContents_3) {
    StringRef sr("hi");
    std::ostringstream oss;
    oss << sr;
    EXPECT_EQ(oss.str(), "hi");
}

TEST(StringRefTest_3, OperatorPlusConcatenates_3) {
    StringRef a("12");
    StringRef b("34");
    std::string combined = a + b;
    EXPECT_EQ(combined, "1234");
}

TEST(StringRefTest_3, StringPlusEqualWithStringRef_3) {
    std::string s = "foo";
    s += StringRef("bar");
    EXPECT_EQ(s, "foobar");
}

// ---------- Ordering & compare ----------

TEST(StringRefTest_3, LexicographicalOrderingAndCompare_3) {
    StringRef a("abc");
    StringRef b("abd");
    StringRef c("abc");

    // operator<
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
    EXPECT_FALSE(a < c);

    // compare: negative/zero/positive relationship
    int ab = a.compare(b);
    int ba = b.compare(a);
    int ac = a.compare(c);

    EXPECT_LT(ab, 0);
    EXPECT_GT(ba, 0);
    EXPECT_EQ(ac, 0);
}

TEST(StringRefTest_3, CompareWithEmpty_3) {
    StringRef empty;
    StringRef nonempty("x");

    int e_n = empty.compare(nonempty);
    int n_e = nonempty.compare(empty);
    int e_e = empty.compare(empty);

    EXPECT_LT(e_n, 0);
    EXPECT_GT(n_e, 0);
    EXPECT_EQ(e_e, 0);
}

} // namespace
