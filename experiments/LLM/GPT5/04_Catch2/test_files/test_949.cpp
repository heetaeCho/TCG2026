// TEST_ID: 949

#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <functional>

// Include the amalgamated Catch2 header from your tree
// (path given in the prompt)
#include "Catch2/extras/catch_amalgamated.hpp"

// A simple predicate type we can pass to the matcher. The predicate itself
// is irrelevant to describe(), but the constructor requires it.
template <typename T>
struct EqPredicate {
    bool operator()(const T& a, const T& b) const { return a == b; }
};

// A small custom type with controlled streaming to make stringify() predictable.
struct Widget {
    int id;
};

inline std::ostream& operator<<(std::ostream& os, const Widget& w) {
    return os << "Widget(" << w.id << ")";
}

class ContainsElementMatcherTest_949 : public ::testing::Test {
protected:
    // Helper to build the matcher without relying on internal details.
    template <typename T>
    using MatcherT = Catch::Matchers::ContainsElementMatcher<T, EqPredicate<T>>;

    template <typename T>
    MatcherT<T> makeMatcher(T&& desired) {
        return MatcherT<T>(std::forward<T>(desired), EqPredicate<std::decay_t<T>>{});
    }
};

// Normal operation: integral type should be stringified plainly.
TEST_F(ContainsElementMatcherTest_949, DescribeWithIntShowsValue_949) {
    auto m = makeMatcher(3);
    const std::string desc = m.describe();
    EXPECT_EQ(desc, "contains element 3");
}

// Normal operation: custom streamable type — verify describe() includes its streamed form.
TEST_F(ContainsElementMatcherTest_949, DescribeWithCustomTypeUsesOstream_949) {
    Widget w{7};
    auto m = makeMatcher(w);
    const std::string desc = m.describe();
    EXPECT_EQ(desc, "contains element Widget(7)");
}

// Boundary-ish construction: rvalue/temporary desired value should still be reflected in describe().
TEST_F(ContainsElementMatcherTest_949, DescribeWithRvalueDesired_949) {
    auto m = makeMatcher(Widget{9}); // rvalue construction
    const std::string desc = m.describe();
    EXPECT_EQ(desc, "contains element Widget(9)");
}

// String handling: Catch::Detail::stringify may or may not add quotes for std::string,
// so we assert conservatively on acceptable outcomes without assuming internal formatting.
TEST_F(ContainsElementMatcherTest_949, DescribeWithStringIsPrefixedAndContainsValue_949) {
    std::string s = "abc";
    auto m = makeMatcher(s);
    const std::string desc = m.describe();

    // Must start with the fixed prefix:
    ASSERT_TRUE(desc.rfind("contains element ", 0) == 0) << desc;

    // Accept either with quotes or without, depending on stringify's policy.
    const bool exact_no_quotes = (desc == "contains element abc");
    const bool exact_with_quotes = (desc == "contains element \"abc\"");
    const bool contains_value = (desc.find("abc") != std::string::npos);

    EXPECT_TRUE(exact_no_quotes || exact_with_quotes || contains_value)
        << "Unexpected describe() format for std::string: " << desc;
}
