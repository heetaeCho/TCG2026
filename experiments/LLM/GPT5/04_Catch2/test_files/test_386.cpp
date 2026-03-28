// File: parserrefimpl_tests_386.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_clara.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include <type_traits>
#include <memory>
#include <string>

namespace Catch { namespace Clara { namespace Detail {

// Test helper CRTP derived that just inherits ctors of ParserRefImpl.
// No extra behavior, no access to internal state.
struct DummyDerived : ParserRefImpl<DummyDerived> {
    using Base = ParserRefImpl<DummyDerived>;
    using Base::Base;      // Inherit Base constructors
    using Base::operator(); // Make operator() visible for tests
};

}}} // namespace Catch::Clara::Detail

using Catch::StringRef;
using Catch::Clara::Detail::DummyDerived;

namespace {

// Helper: construct via the (T& ref, StringRef hint) ctor, which does not
// require knowing anything about Bound* internals in tests.
inline DummyDerived makeWithValueRefCtor(int& sink, StringRef hint) {
    return DummyDerived(sink, hint);
}

} // namespace

// ---------------------------------------------------------------
// Tests
// ---------------------------------------------------------------

TEST(ParserRefImplTest_386, HintIsReturnedFromValueRefCtor_386) {
    int sink = 0;
    auto d = makeWithValueRefCtor(sink, StringRef("my-hint"));
    // StringRef is comparable, but to stay robust we compare materialized strings.
    EXPECT_EQ(static_cast<std::string>(d.hint()), std::string("my-hint"));
}

TEST(ParserRefImplTest_386, OptionalityTogglesWithRequiredAndOptional_386) {
    int sink = 0;
    auto d = makeWithValueRefCtor(sink, StringRef("h"));

    // Default should be optional (based on public isOptional() behavior).
    EXPECT_TRUE(d.isOptional());

    // After required(), it should report non-optional.
    d.required();
    EXPECT_FALSE(d.isOptional());

    // After optional(), it should report optional again.
    d.optional();
    EXPECT_TRUE(d.isOptional());
}

TEST(ParserRefImplTest_386, OperatorCallReturnsDerivedLvalueRef_386) {
    int sink = 0;
    auto d = makeWithValueRefCtor(sink, StringRef("h"));

    // Compile-time check: operator() returns DummyDerived& (not by value).
    static_assert(std::is_same<decltype(d(StringRef("desc"))), DummyDerived&>::value,
                  "operator() must return DerivedT&");

    // Runtime check: returned reference is the same object (enables chaining).
    auto& r = d(StringRef("desc"));
    EXPECT_EQ(&r, &d);
}

TEST(ParserRefImplTest_386, OperatorCallSupportsVariousStringRefSources_386) {
    int sink = 0;
    auto d = makeWithValueRefCtor(sink, StringRef("h"));

    const char* cstr = "first";
    std::string s = "second";
    StringRef sr("third");

    // Each call should succeed and keep returning self for chaining.
    auto& r1 = d(StringRef(cstr));
    auto& r2 = r1(StringRef(s.c_str(), s.size()));
    auto& r3 = r2(sr);

    EXPECT_EQ(&r1, &d);
    EXPECT_EQ(&r2, &d);
    EXPECT_EQ(&r3, &d);
}

TEST(ParserRefImplTest_386, OperatorCallIsChainableMultipleTimes_386) {
    int sink = 0;
    auto d = makeWithValueRefCtor(sink, StringRef("h"));

    // Chaining should compile & return the same object throughout.
    auto& r = d(StringRef("a"))(StringRef("b"))(StringRef("c"));
    EXPECT_EQ(&r, &d);
}

