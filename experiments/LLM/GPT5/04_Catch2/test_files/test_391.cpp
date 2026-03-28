// File: tests/parser_ref_impl_hint_391_tests.cpp

#include <gtest/gtest.h>
#include "Catch2/src/catch2/internal/catch_clara.hpp"

#include <string>

namespace C = Catch::Clara::Detail;

// A tiny derived type to instantiate the CRTP base using its public constructors.
// We do NOT access protected/private members or rely on internal behavior.
struct DummyParser_391 : C::ParserRefImpl<DummyParser_391> {
    using Base = C::ParserRefImpl<DummyParser_391>;
    using Base::Base; // inherit public constructors (T& ref, StringRef hint), etc.
};

// Normal operation: value-ref constructor stores and exposes the provided hint.
TEST(ParserRefImplHintTest_391, ReturnsGivenHintForValueRef_391) {
    int sink{};
    DummyParser_391 p{sink, "port"};
    EXPECT_EQ(std::string(p.hint()), "port");
}

// Boundary: empty hint should be reported as empty.
TEST(ParserRefImplHintTest_391, EmptyHintIsReportedEmpty_391) {
    int sink{};
    DummyParser_391 p{sink, ""};
    auto h = p.hint();
    EXPECT_TRUE(std::string(h).empty());
    EXPECT_EQ(h.size(), 0u);
}

// Boundary: long hint (length & content preserved).
TEST(ParserRefImplHintTest_391, LongHintIsPreserved_391) {
    int sink{};
    std::string long_hint(1024, 'a'); // 1024 'a'
    DummyParser_391 p{sink, long_hint.c_str()}; // pass as C-string to avoid lifetime pitfalls
    auto h = p.hint();
    EXPECT_EQ(h.size(), long_hint.size());
    EXPECT_EQ(std::string(h), long_hint);
}

// Const-correctness: calling hint() on const instance yields the same value.
TEST(ParserRefImplHintTest_391, HintCallableOnConstObject_391) {
    int sink{};
    DummyParser_391 p{sink, "my-hint"};
    const DummyParser_391& cp = p;
    EXPECT_EQ(std::string(cp.hint()), "my-hint");
}
