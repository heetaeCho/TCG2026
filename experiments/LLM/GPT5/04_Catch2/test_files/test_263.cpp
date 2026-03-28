// File: tests/string_maker_char_ptr_tests_263.cpp

#include <gtest/gtest.h>
#include "catch2/catch_tostring.hpp"

namespace {

using Catch::StringMaker;

class StringMakerCharPtrTest_263 : public ::testing::Test {};

// [Behavior] Null pointer -> exact "{null string}"
TEST_F(StringMakerCharPtrTest_263, NullPtr_YieldsNullStringLiteral_263) {
    char* p = nullptr;
    const std::string out = StringMaker<char*>::convert(p);
    EXPECT_EQ(out, "{null string}");
}

// [Behavior] Non-null pointer -> NOT the "{null string}" literal
TEST_F(StringMakerCharPtrTest_263, NonNullPtr_DoesNotYieldNullLiteral_263) {
    char buf[] = "hello";
    char* p = buf;
    const std::string out = StringMaker<char*>::convert(p);
    EXPECT_NE(out, "{null string}");
}

// [Behavior] Deterministic output for same input (idempotent w.r.t. observable result)
TEST_F(StringMakerCharPtrTest_263, SameInput_ProducesSameOutput_263) {
    char buf[] = "repeatable";
    char* p = buf;
    const std::string out1 = StringMaker<char*>::convert(p);
    const std::string out2 = StringMaker<char*>::convert(p);
    EXPECT_EQ(out1, out2);
    // Sanity: still not the null-literal
    EXPECT_NE(out1, "{null string}");
}

// [Boundary] Empty C-string is treated as non-null (not the null-literal) and input remains unchanged
TEST_F(StringMakerCharPtrTest_263, EmptyCString_HandledAndInputUnchanged_263) {
    char buf[] = "";
    char* p = buf;

    // Preserve original contents to verify no mutation occurs through the interface
    const char before[] = "";
    ASSERT_STREQ(buf, before);

    const std::string out = StringMaker<char*>::convert(p);

    // Non-null input should not yield the explicit null-string literal
    EXPECT_NE(out, "{null string}");

    // Verify the input buffer was not modified as an observable side effect
    EXPECT_STREQ(buf, before);
}

// [API] The overload taking non-const char* is available and callable (compile-time check materialized)
TEST_F(StringMakerCharPtrTest_263, CharPointerOverload_IsCallable_263) {
    using Fn = std::string(*)(char*);
    // Taking the address of the specific overload ensures the interface exists as declared
    Fn fn = &StringMaker<char*>::convert;
    char buf[] = "overload";
    std::string out = fn(buf);
    EXPECT_NE(out, "{null string}");
}

} // namespace
