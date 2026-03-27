// File: tests/stringref_less_681_tests.cpp

#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Minimal forward declarations matching the provided interface.
// (We only use public constructors and operator<.)
namespace Catch {
    using size_type = std::size_t;

    class StringRef {
    public:
        // Public APIs shown in the provided header snippet
        constexpr StringRef() noexcept = default;
        constexpr StringRef(char const* rawChars, size_type size) noexcept
            : m_start(rawChars), m_size(size) {}
        StringRef(std::string const& s) noexcept
            : m_start(s.c_str()), m_size(s.size()) {}
        StringRef(char const* rawChars) noexcept
            : m_start(rawChars), m_size(std::strlen(rawChars)) {}

        bool operator<(StringRef rhs) const noexcept;

        // We do not use any other members in tests.
    private:
        // Private layout is not used directly in tests (black-box).
        const char* m_start = nullptr;
        size_type m_size = 0;
    };
}

// Bring only what we need into scope for readability in tests.
using Catch::StringRef;

//
// Test suite
//
TEST(StringRefLessTest_681, EmptyVsEmpty_681) {
    StringRef a;
    StringRef b;
    // Both default-constructed (empty). strncmp(..., 0 or 0) yields 0.
    // For lhs.size < rhs.size false; falls through to second branch with rhs.m_size (=0) -> 0 < 0 == false.
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessTest_681, EmptyVsNonEmpty_681) {
    StringRef empty;
    StringRef word("a");
    // lhs.size (0) < rhs.size (1) -> strncmp(..., m_size=0) returns 0, 0 <= 0 -> true
    EXPECT_TRUE(empty < word);
    EXPECT_FALSE(word < empty);
}

TEST(StringRefLessTest_681, EqualNonEmptySameContent_681) {
    StringRef a("hello");
    StringRef b("hello");
    // sizes equal; compares up to rhs.m_size (5) -> strncmp == 0 -> 0 < 0 == false
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessTest_681, LexicographicDifferentFirstChar_681) {
    StringRef a("apple");
    StringRef b("banana");
    // First differing char: 'a' (97) vs 'b' (98) => strncmp negative => a < b true
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessTest_681, Prefix_LhsShorterSamePrefix_681) {
    StringRef a("app");     // size 3
    StringRef b("apple");   // size 5
    // lhs.size < rhs.size -> strncmp up to lhs.m_size (3). Equal prefix -> 0 <= 0 -> true
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessTest_681, Prefix_RhsShorterSamePrefix_681) {
    StringRef a("apple");   // size 5
    StringRef b("app");     // size 3
    // sizes not lhs<rhs, so compare up to rhs.m_size (3). Equal prefix -> 0 < 0 == false
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessTest_681, DifferAfterShorterLength_681) {
    // Same first 2 chars, differ at index 2 which is within the shorter length
    StringRef a("abx");   // size 3
    StringRef b("abyz");  // size 4
    // lhs.size < rhs.size -> strncmp up to 3 compares 'abx' vs 'aby' -> 'x' (120) > 'y' (121) => negative? actually 120 - 121 = -1 -> so 'x' < 'y'
    // 'x' < 'y' => strncmp < 0 -> <= 0 -> true => a < b
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(StringRefLessTest_681, DifferBeforeShorterLength_Opposite_681) {
    StringRef a("abz");   // size 3
    StringRef b("abyz");  // size 4
    // Compare first 3: 'abz' vs 'aby' -> 'z'(122) > 'y'(121) => strncmp > 0 -> <= 0 is false
    EXPECT_FALSE(a < b);
    EXPECT_TRUE(b < a);
}

TEST(StringRefLessTest_681, ConstructFromStdString_681) {
    std::string s1 = "alpha";
    std::string s2 = "beta";
    StringRef a(s1);
    StringRef b(s2);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

//
// Embedded-NUL related observable behaviors due to use of strncmp
// (We exercise only public constructors and operator<; this is purely black-box.)
//
TEST(StringRefLessTest_681, EmbeddedNul_LhsContainsNulWithinSize_LhsShorterBranch_681) {
    // Buffer: 'a' '\0' 'b'
    const char buf[] = {'a', '\0', 'b'};
    StringRef lhs(buf, 3);   // size includes data past the NUL
    StringRef rhs("aXYZ");   // different content past 'a'

    // lhs.size (3) < rhs.size (4) -> strncmp up to lhs.m_size (=3).
    // strncmp stops when it sees '\0' at index 1 and returns comparison for prefix 'a' vs 'a' => 0.
    // In the implementation branch for lhs shorter: <= 0 -> true (so lhs < rhs).
    EXPECT_TRUE(lhs < rhs);
    EXPECT_FALSE(rhs < lhs);
}

TEST(StringRefLessTest_681, EmbeddedNul_RhsContainsNulWithinSize_RhsShorterBranch_681) {
    // RHS is size-limited to include a NUL and one more byte, but strncmp stops at the NUL.
    const char rbuf[] = {'a', '\0', 'b'};
    StringRef lhs("aXYZ");
    StringRef rhs(rbuf, 3);

    // lhs.size (4) !< rhs.size (3) -> second branch uses strncmp up to rhs.m_size (=3),
    // but strncmp stops at NUL (index 1) comparing "a" vs "a" -> 0, and condition is (0 < 0) == false.
    EXPECT_FALSE(lhs < rhs);
    EXPECT_FALSE(rhs < lhs);
}

TEST(StringRefLessTest_681, EmbeddedNul_DifferenceBeforeNul_681) {
    const char lbuf[] = {'b', '\0', 'x'}; // starts with 'b'
    const char rbuf[] = {'a', '\0', 'y'}; // starts with 'a'
    StringRef lhs(lbuf, 3);
    StringRef rhs(rbuf, 3);

    // sizes equal -> second branch compares up to rhs.m_size (=3),
    // but strncmp sees first char differs 'b' vs 'a' -> > 0, so ( >0 < 0 ) == false.
    EXPECT_FALSE(lhs < rhs);
    EXPECT_TRUE(rhs < lhs);
}
