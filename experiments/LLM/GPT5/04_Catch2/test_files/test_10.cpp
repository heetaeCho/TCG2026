// File: stringref_data_tests_10.cpp
#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <type_traits>

// Adjust include path as needed for your project layout.
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;

TEST(StringRefDataTest_10, CStrCtor_DataReturnsSamePointer_10) {
    const char* raw = "hello";
    StringRef s(raw);
    EXPECT_EQ(s.data(), raw) << "data() should point at the same address passed to the c-string constructor";
}

TEST(StringRefDataTest_10, StdStringCtor_DataMatchesStdStringCStrWhileAlive_10) {
    std::string backing = "backed by std::string";
    StringRef s(backing);
    // While 'backing' is alive, data() should match backing.c_str()
    EXPECT_EQ(s.data(), backing.c_str());
}

TEST(StringRefDataTest_10, DefaultCtor_DataPointsToValidNullTerminator_10) {
    StringRef s; // default constructed
    ASSERT_NE(s.data(), nullptr) << "Default-constructed data() should be a valid pointer";
    EXPECT_EQ(*s.data(), '\0') << "Default-constructed data() should point to a null terminator";
}

TEST(StringRefDataTest_10, SizeCtor_ZeroLengthStillReturnsOriginalPointer_10) {
    const char* raw = "abcdef";
    StringRef s(raw, 0); // length 0, but data() should still be raw
    EXPECT_EQ(s.data(), raw);
}

TEST(StringRefDataTest_10, SizeCtor_EmbeddedNulls_DataPointsToRawBuffer_10) {
    // Raw buffer with embedded NUL
    const char raw[3] = { 'a', '\0', 'b' };
    StringRef s(raw, 3);
    // data() must be the same address; verify first 3 bytes match the raw buffer
    ASSERT_EQ(s.data(), raw);
    EXPECT_EQ(std::memcmp(s.data(), raw, 3), 0);
}

TEST(StringRefDataTest_10, DataIsConstCharPtr_TypeAndNoexcept_10) {
    StringRef s("x");
    // Type check
    static_assert(std::is_same<decltype(s.data()), const char*>::value,
                  "data() must return const char*");
    // noexcept check
    static_assert(noexcept(s.data()), "data() should be noexcept");
    // Simple runtime sanity too
    EXPECT_STREQ(s.data(), "x");
}
