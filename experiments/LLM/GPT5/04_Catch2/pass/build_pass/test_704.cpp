// File: tests/approx_custom_704_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Include the public interface only
#include "catch_approx.hpp"

using Catch::Approx;

// Test fixture kept minimal — we treat Approx as a black box.
class ApproxCustomTest_704 : public ::testing::Test {};

// [704] Verify that the static Approx::custom() is callable and returns Approx
TEST_F(ApproxCustomTest_704, StaticCustom_ReturnsApprox_704) {
    // Compile-time type check (interface-based)
    static_assert(std::is_same<Approx, decltype(Approx::custom())>::value,
                  "Approx::custom() must return Approx by value");

    // Runtime: should not throw constructing via custom()
    EXPECT_NO_THROW({
        auto a = Approx::custom();
        (void)a; // silence unused warning
    });
}

// [704] Verify that the member custom() is callable on an instance and returns Approx
TEST_F(ApproxCustomTest_704, MemberCustom_ReturnsApprox_704) {
    Approx base(1.0);

    // Compile-time type check (interface-based)
    static_assert(std::is_same<Approx, decltype(base.custom())>::value,
                  "member custom() must return Approx by value");

    EXPECT_NO_THROW({
        auto derived = base.custom();
        (void)derived;
    });
}

// [704] Returned object from custom() supports toString() per interface
TEST_F(ApproxCustomTest_704, Custom_ToString_DoesNotThrow_704) {
    auto a = Approx::custom();

    std::string s;
    EXPECT_NO_THROW({
        s = a.toString();
    });

    // We cannot assert specific contents; just that we got a std::string successfully.
    EXPECT_TRUE(s.size() >= 0u); // trivial sanity check without assuming formatting
}

// [704] Returned object from custom() supports unary minus per interface
TEST_F(ApproxCustomTest_704, Custom_UnaryMinus_ReturnsApprox_704) {
    auto a = Approx::custom();

    // Compile-time type check for operator-
    static_assert(std::is_same<Approx, decltype(-a)>::value,
                  "operator- on Approx should return Approx");

    EXPECT_NO_THROW({
        auto b = -a;
        (void)b;
    });
}

// [704] Returned object from custom() is callable via operator()(T) per interface
TEST_F(ApproxCustomTest_704, Custom_CallableForm_ReturnsApprox_704) {
    auto a = Approx::custom();

    // We only verify that calling with a constructible-to-double type works
    // and returns Approx by value, without assuming internal behavior.
    static_assert(std::is_same<Approx, decltype(a(42.0))>::value,
                  "Approx::operator()(double) should return Approx");

    EXPECT_NO_THROW({
        auto b = a(42.0);
        (void)b;
    });
}

// [704] The fluent modifiers on the result of custom() are chainable (interface says they return Approx&)
TEST_F(ApproxCustomTest_704, Custom_FluentModifiers_AreChainable_704) {
    auto a = Approx::custom();

    // The public interface advertises epsilon, margin, scale returning Approx&.
    // We verify they are callable and chainable without inferring any effects.
    EXPECT_NO_THROW({
        auto& ref = a.epsilon(0.01).margin(0.1).scale(1.0);
        (void)ref;
    });
}

// [704] Both static and member custom() entry points are usable without throwing
TEST_F(ApproxCustomTest_704, StaticVsMemberCustom_Available_NoThrow_704) {
    EXPECT_NO_THROW({
        auto s = Approx::custom();
        (void)s;
    });

    EXPECT_NO_THROW({
        Approx instance(5.0);
        auto m = instance.custom();
        (void)m;
    });
}
