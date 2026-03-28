// File: listener_typed_listener_factory_getname_tests_567.cpp

#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_registrars.hpp" // Path from your tree
#include <string>

namespace {

using Catch::ListenerRegistrar;
using Catch::StringRef;

class ListenerRegistrarTypedListenerFactoryTest_567 : public ::testing::Test {};

// --- Normal operation: returns exactly what was provided at construction ---
TEST_F(ListenerRegistrarTypedListenerFactoryTest_567, GetName_ReturnsExactName_567) {
    const StringRef expected{"my-listener"};
    ListenerRegistrar::TypedListenerFactory factory{expected};

    const StringRef actual = factory.getName();

    EXPECT_EQ(actual.size(), expected.size());
    EXPECT_TRUE(actual == expected);
}

// --- Boundary: empty name should be returned as empty ---
TEST_F(ListenerRegistrarTypedListenerFactoryTest_567, GetName_EmptyString_567) {
    const StringRef expected{""};
    ListenerRegistrar::TypedListenerFactory factory{expected};

    const StringRef actual = factory.getName();

    EXPECT_EQ(actual.size(), 0u);
    EXPECT_TRUE(actual == expected);
}

// --- Boundary: very long name is preserved exactly ---
TEST_F(ListenerRegistrarTypedListenerFactoryTest_567, GetName_VeryLongName_567) {
    std::string long_name(4096, 'x'); // long but reasonable for a unit test
    const StringRef expected{long_name.c_str(), long_name.size()};

    ListenerRegistrar::TypedListenerFactory factory{expected};

    const StringRef actual = factory.getName();

    EXPECT_EQ(actual.size(), expected.size());
    EXPECT_TRUE(actual == expected);
}

// --- Normal: Unicode / non-ASCII bytes are preserved (byte-for-byte) ---
TEST_F(ListenerRegistrarTypedListenerFactoryTest_567, GetName_NonAsciiUtf8_567) {
    // UTF-8 bytes; comparison is byte-wise via StringRef
    const char* utf8_name = u8"리스너-テスト-λ";
    const StringRef expected{utf8_name};

    ListenerRegistrar::TypedListenerFactory factory{expected};

    const StringRef actual = factory.getName();

    EXPECT_EQ(actual.size(), expected.size());
    EXPECT_TRUE(actual == expected);
}

// --- Consistency: multiple calls return the same value without mutation ---
TEST_F(ListenerRegistrarTypedListenerFactoryTest_567, GetName_IdempotentOnRepeatedCalls_567) {
    const StringRef expected{"repeat-me"};
    ListenerRegistrar::TypedListenerFactory factory{expected};

    const StringRef first  = factory.getName();
    const StringRef second = factory.getName();

    EXPECT_TRUE(first == expected);
    EXPECT_TRUE(second == expected);
    EXPECT_TRUE(first == second);
}

// --- Isolation: separate instances keep their own names ---
TEST_F(ListenerRegistrarTypedListenerFactoryTest_567, GetName_DistinctInstancesAreIndependent_567) {
    const StringRef expectedA{"alpha"};
    const StringRef expectedB{"beta"};

    ListenerRegistrar::TypedListenerFactory factoryA{expectedA};
    ListenerRegistrar::TypedListenerFactory factoryB{expectedB};

    const StringRef nameA = factoryA.getName();
    const StringRef nameB = factoryB.getName();

    EXPECT_TRUE(nameA == expectedA);
    EXPECT_TRUE(nameB == expectedB);
    EXPECT_NE(std::string(nameA.data(), nameA.size()),
              std::string(nameB.data(), nameB.size()));
}

} // namespace
