// File: matchers_templated_not_operator_tests_171.cpp

#include <gtest/gtest.h>

#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>

#include <string>
#include <type_traits>
#include <utility>

// ---------- Test helpers (public API only) ----------
// Minimal generic matcher for testing: derives from Catch::Matchers::MatcherGenericBase
// and provides templated match(...) + describe(). This is a *test double* that exercises
// the operator! without depending on library internals.
struct AlwaysMatcher : Catch::Matchers::MatcherGenericBase {
    explicit AlwaysMatcher(bool expected) : expected_(expected) {}

    // Templated match to satisfy "generic matcher" concept.
    template <typename T>
    bool match(T const&) const {
        return expected_;
    }

    std::string describe() const override {
        return expected_ ? "always true" : "always false";
    }

private:
    bool expected_;
};

// Compile-time check that applying '!' returns the documented wrapper type.
static_assert(std::is_same<
                  decltype(Catch::Matchers::operator!(std::declval<const AlwaysMatcher&>())),
                  Catch::Matchers::Detail::MatchNotOfGeneric<AlwaysMatcher>>::value,
              "operator! on a generic matcher must return MatchNotOfGeneric<MatcherT>");



// ---------- Tests ----------

TEST(MatchersTemplatedNotOpTest_171, NegatesTrueToFalse_Int_171) {
    const AlwaysMatcher m_true{true};
    // Call operator! explicitly from the defining namespace to avoid ADL surprises.
    auto neg = Catch::Matchers::operator!(m_true);

    // Observable behavior: result of match(...) is negated
    EXPECT_FALSE(neg.match(123));      // int
}

TEST(MatchersTemplatedNotOpTest_171, NegatesFalseToTrue_String_171) {
    const AlwaysMatcher m_false{false};
    auto neg = Catch::Matchers::operator!(m_false);

    // Works across types because the matcher is generic (templated match)
    EXPECT_TRUE(neg.match(std::string{"hello"}));  // std::string
}

TEST(MatchersTemplatedNotOpTest_171, DoubleNegationRestoresOriginal_171) {
    const AlwaysMatcher base{true};
    auto neg1 = Catch::Matchers::operator!(base);
    auto neg2 = Catch::Matchers::operator!(neg1); // Should itself be a generic matcher

    // For multiple representative types, !!matcher behaves like the original
    EXPECT_EQ(neg2.match(7), base.match(7));
    EXPECT_EQ(neg2.match(std::string{"x"}), base.match(std::string{"x"}));
}

TEST(MatchersTemplatedNotOpTest_171, WorksWithTemporaryOperand_171) {
    // Use a temporary generic matcher; the negated object should be usable immediately
    EXPECT_FALSE(Catch::Matchers::operator!(AlwaysMatcher{true}).match(0));
    EXPECT_TRUE (Catch::Matchers::operator!(AlwaysMatcher{false}).match(0));
}

TEST(MatchersTemplatedNotOpTest_171, AcceptsConstOperand_171) {
    const AlwaysMatcher const_m{false};
    auto neg = Catch::Matchers::operator!(const_m);

    // Ensures the operator accepts const& and returns a usable matcher
    EXPECT_TRUE(neg.match(42));
}

TEST(MatchersTemplatedNotOpTest_171, ReturnsExpectedWrapperType_RuntimeSmoke_171) {
    const AlwaysMatcher m{true};
    auto neg = Catch::Matchers::operator!(m);

    // Runtime smoke check that the wrapper behaves like a matcher object
    // (we already statically asserted the exact return type above).
    EXPECT_FALSE(neg.match(1));
    SUCCEED();  // Explicitly mark that we reached this point
}
