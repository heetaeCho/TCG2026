// File: size_is_tests_235.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

//
// ---- Test scaffolding (public collaborator fakes) ----
// We provide minimal stand-ins for dependencies referenced by the interface.
// This lets us observe *interface-level* behavior (type deduction & forwarding)
// without re-implementing any internal logic.
//
namespace Catch {
namespace Matchers {

// Forward declarations used by the function under test (interface dependencies).
template <typename Matcher>
struct SizeMatchesMatcher;

// Detail::is_matcher_v trait (default false, opt-in via specialization).
namespace Detail {
template <typename T> struct is_matcher : std::false_type {};
template <typename T> constexpr bool is_matcher_v = is_matcher<T>::value;
} // namespace Detail

// A tiny helper to mimic CATCH_FORWARD semantics for value category forwarding.
template <class T>
constexpr T&& forward_like(std::remove_reference_t<T>& t) noexcept { return static_cast<T&&>(t); }
#define CATCH_FORWARD(x) ::Catch::Matchers::forward_like<decltype(x)>(x)

// -------- Function under test (from the provided partial code) --------
template <typename Matcher>
std::enable_if_t<Detail::is_matcher_v<Matcher>, SizeMatchesMatcher<Matcher>>
SizeIs(Matcher&& m) {
    return SizeMatchesMatcher<Matcher>{CATCH_FORWARD(m)};
}

// --------- Observer class to capture how ctor was called (value category) ---------
template <typename Matcher>
struct SizeMatchesMatcher {
    bool received_lvalue;
    const void* received_address;

    SizeMatchesMatcher(const SizeMatchesMatcher&) = delete;
    SizeMatchesMatcher& operator=(const SizeMatchesMatcher&) = delete;

    template <class U>
    explicit SizeMatchesMatcher(U&& u)
        : received_lvalue(std::is_lvalue_reference<U&&>::value),
          received_address(static_cast<const void*>(std::addressof(u))) {}
};

} // namespace Matchers
} // namespace Catch

// A dummy "matcher" type we can opt-in to Detail::is_matcher_v
struct DummyMatcher {
    int tag = 42;
    DummyMatcher() = default;
    DummyMatcher(const DummyMatcher&) = default;
    DummyMatcher(DummyMatcher&&) noexcept = default;
};

// Opt-in specialization: mark DummyMatcher as a valid matcher.
namespace Catch { namespace Matchers { namespace Detail {
template <> struct is_matcher<DummyMatcher> : std::true_type {};
}}}

// A non-matcher type (should NOT satisfy the constraint)
struct NotAMatcher {};

// Detection idiom to check if SizeIs(T) is well-formed
template <class, class = void>
struct has_SizeIs_call : std::false_type {};
template <class T>
struct has_SizeIs_call<T, std::void_t<decltype(Catch::Matchers::SizeIs(std::declval<T>()))>>
    : std::true_type {};

//
// ------------------------- TESTS -------------------------
//

TEST(SizeIsMatcher_235, EnabledOnlyForRecognizedMatchers_235) {
    // SizeIs should participate for DummyMatcher...
    static_assert(has_SizeIs_call<DummyMatcher&&>::value, "SizeIs must accept DummyMatcher rvalue");
    static_assert(has_SizeIs_call<DummyMatcher&>::value,  "SizeIs must accept DummyMatcher lvalue");
    static_assert(has_SizeIs_call<const DummyMatcher&>::value, "SizeIs must accept const DummyMatcher lvalue");

    // ...and SFINAE out for non-matcher types.
    static_assert(!has_SizeIs_call<NotAMatcher&&>::value, "SizeIs must reject non-matcher rvalue");
    static_assert(!has_SizeIs_call<NotAMatcher&>::value,  "SizeIs must reject non-matcher lvalue");
    static_assert(!has_SizeIs_call<const NotAMatcher&>::value, "SizeIs must reject const non-matcher lvalue");

    SUCCEED(); // Compile-time checks above are the essence; test should pass at runtime.
}

TEST(SizeIsMatcher_235, ReturnTypeForLvalueIsReferenceQualified_235) {
    using namespace Catch::Matchers;

    DummyMatcher m;
    // Matcher is deduced as DummyMatcher& when passing an lvalue reference.
    using Expected = SizeMatchesMatcher<DummyMatcher&>;
    using Actual   = decltype(SizeIs(m));
    static_assert(std::is_same<Actual, Expected>::value, "Return type must be SizeMatchesMatcher<DummyMatcher&>");

    auto result = SizeIs(m);
    // Should have received an lvalue
    EXPECT_TRUE(result.received_lvalue);
    // The address observed by SizeMatchesMatcher's ctor must equal the address of the source object.
    EXPECT_EQ(result.received_address, static_cast<const void*>(&m));
}

TEST(SizeIsMatcher_235, ReturnTypeForConstLvalueIsConstRefQualified_235) {
    using namespace Catch::Matchers;

    const DummyMatcher m{};
    // Matcher is deduced as const DummyMatcher& for const lvalues.
    using Expected = SizeMatchesMatcher<const DummyMatcher&>;
    using Actual   = decltype(SizeIs(m));
    static_assert(std::is_same<Actual, Expected>::value, "Return type must be SizeMatchesMatcher<const DummyMatcher&>");

    auto result = SizeIs(m);
    EXPECT_TRUE(result.received_lvalue);
    EXPECT_EQ(result.received_address, static_cast<const void*>(&m));
}

TEST(SizeIsMatcher_235, ReturnTypeForRvalueIsNonReference_235) {
    using namespace Catch::Matchers;

    // Matcher is deduced as DummyMatcher for rvalues (no reference).
    using Expected = SizeMatchesMatcher<DummyMatcher>;
    using Actual   = decltype(SizeIs(DummyMatcher{}));
    static_assert(std::is_same<Actual, Expected>::value, "Return type must be SizeMatchesMatcher<DummyMatcher>");

    auto result = SizeIs(DummyMatcher{});
    // Should have received an rvalue
    EXPECT_FALSE(result.received_lvalue);
    // We cannot compare addresses meaningfully for a temporary; just verify we observed *some* address.
    EXPECT_NE(result.received_address, nullptr);
}
