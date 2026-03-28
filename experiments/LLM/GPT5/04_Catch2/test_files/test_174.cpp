// operator_or_generic_tests_174.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <string>
#include <sstream>

// Include Catch2 matcher bases and the templated operators under test
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>

namespace {

// ---------- Test helpers (public APIs only) ----------

// A generic matcher: matches values that are equal to their default-constructed value.
// Derives from Catch::Matchers::MatcherGenericBase as per Catch2's public API.
struct IsDefaultGeneric : Catch::Matchers::MatcherGenericBase {
    template <typename T>
    bool match(T const& v) const {
        return v == T{};
    }
    std::string describe() const override { return "is default-constructed"; }
};

// A simple typed matcher: value >= threshold
template <typename T>
class AtLeastMatcher : public Catch::Matchers::MatcherBase<T> {
public:
    explicit AtLeastMatcher(T threshold) : threshold_(threshold) {}

    bool match(T const& v) const override { return v >= threshold_; }

    std::string describe() const override {
        std::ostringstream oss;
        oss << ">= " << threshold_;
        return oss.str();
    }

private:
    T threshold_;
};

// A typed matcher for std::string: length >= N
class LengthAtLeast : public Catch::Matchers::MatcherBase<std::string> {
public:
    explicit LengthAtLeast(std::size_t n) : n_(n) {}
    bool match(std::string const& s) const override { return s.size() >= n_; }
    std::string describe() const override {
        std::ostringstream oss; oss << "length >= " << n_; return oss.str();
    }
private:
    std::size_t n_;
};

} // namespace

// -------------------- Tests --------------------

TEST(OperatorOrGenericTest_174, ReturnTypeIsMatchAnyOfGeneric_Int_174) {
    IsDefaultGeneric lhs;
    AtLeastMatcher<int> rhs(10);

    using ReturnT  = decltype(lhs || rhs);
    using Expected = Catch::Matchers::Detail::MatchAnyOfGeneric<
        IsDefaultGeneric,
        Catch::Matchers::MatcherBase<int>
    >;

    // Type-level assertion based on the exposed function signature.
    static_assert(std::is_same<ReturnT, Expected>::value,
                  "operator|| must return MatchAnyOfGeneric<Generic, MatcherBase<Arg>> for int Arg");
    SUCCEED(); // keep GoogleTest happy when only using static_assert
}

TEST(OperatorOrGenericTest_174, ReturnTypeIsMatchAnyOfGeneric_String_174) {
    IsDefaultGeneric lhs;
    LengthAtLeast rhs(5);

    using ReturnT  = decltype(lhs || rhs);
    using Expected = Catch::Matchers::Detail::MatchAnyOfGeneric<
        IsDefaultGeneric,
        Catch::Matchers::MatcherBase<std::string>
    >;

    static_assert(std::is_same<ReturnT, Expected>::value,
                  "operator|| must return MatchAnyOfGeneric<Generic, MatcherBase<Arg>> for std::string Arg");
    SUCCEED();
}

TEST(OperatorOrGenericTest_174, MatchesWhenEitherMatcherMatches_Int_174) {
    auto combined = IsDefaultGeneric{} || AtLeastMatcher<int>(10);

    // lhs true, rhs false -> true
    EXPECT_TRUE(combined.match(0));

    // lhs false, rhs true -> true
    EXPECT_TRUE(combined.match(15));

    // lhs false, rhs false -> false
    EXPECT_FALSE(combined.match(5));
}

TEST(OperatorOrGenericTest_174, MatchesWhenEitherMatcherMatches_String_174) {
    auto combined = IsDefaultGeneric{} || LengthAtLeast(5);

    // lhs (generic) true on default-constructed string
    EXPECT_TRUE(combined.match(std::string{}));

    // rhs (typed) true on length >= 5
    EXPECT_TRUE(combined.match(std::string("hello")));

    // both false
    EXPECT_FALSE(combined.match(std::string("yo")));
}

TEST(OperatorOrGenericTest_174, CombinedMatcherAcceptsConstArg_174) {
    const int value_zero = 0;
    const int value_big  = 42;

    const auto combined = IsDefaultGeneric{} || AtLeastMatcher<int>(40);

    EXPECT_TRUE(combined.match(value_zero)); // generic side matches
    EXPECT_TRUE(combined.match(value_big));  // typed side matches
}

TEST(OperatorOrGenericTest_174, ChainingGenericWithMultipleTypedRhs_174) {
    // Ensure that the result of (generic || typed) can be further combined with another typed matcher.
    auto combined = IsDefaultGeneric{} || AtLeastMatcher<int>(100) || AtLeastMatcher<int>(10);

    EXPECT_TRUE(combined.match(20)); // second typed matcher matches
    EXPECT_FALSE(combined.match(5)); // none match
}
