// File: tests/approx_stringmaker_convert_tests_709.cpp

#include <gtest/gtest.h>

#include "Catch2/src/catch2/catch_approx.hpp"
#include "Catch2/src/catch2/catch_tostring.hpp"

#include <limits>
#include <type_traits>

using Catch::Approx;

// [TEST_ID: 709]
TEST(ApproxStringMakerTest_709, DelegatesToToString_Default_709) {
    Approx a(1.2345);

    // Compile-time: ensure returned type is std::string (part of interface)
    {
        auto s = Catch::StringMaker<Approx>::convert(a);
        static_assert(std::is_same<decltype(s), std::string>::value, "convert must return std::string");
    }

    const std::string expected = a.toString();
    const std::string got = Catch::StringMaker<Approx>::convert(a);
    EXPECT_EQ(got, expected);
}

// [TEST_ID: 709]
TEST(ApproxStringMakerTest_709, DelegatesToToString_WithChainedCustomization_709) {
    // Exercise observable states via public API (epsilon/margin/scale/operator())
    auto obj = Approx::custom()
                   .epsilon(std::numeric_limits<double>::epsilon() * 1000.0)
                   .margin(0.0)     // boundary-friendly value (allowed by public API)
                   .scale(0.0)      // boundary-friendly value (matches default init seen)
                   (3.14159);       // set target value via operator()

    const std::string expected = obj.toString();
    const std::string got = Catch::StringMaker<Approx>::convert(obj);
    EXPECT_EQ(got, expected);
}

// [TEST_ID: 709]
TEST(ApproxStringMakerTest_709, DelegatesToToString_ConstLvalue_709) {
    const Approx ca = Approx(0.0).epsilon(1e-6).margin(1e-3).scale(10.0);

    const std::string expected = ca.toString();
    const std::string got = Catch::StringMaker<Approx>::convert(ca);
    EXPECT_EQ(got, expected);
}

// [TEST_ID: 709]
TEST(ApproxStringMakerTest_709, DelegatesToToString_TemporaryObject_709) {
    auto make_temp = [] {
        return Approx::custom().epsilon(1e-4).margin(1e-2).scale(2.0)(42.0);
    };

    auto temp = make_temp(); // avoid double-constructing different temporaries
    const std::string expected = temp.toString();
    const std::string got = Catch::StringMaker<Approx>::convert(temp);
    EXPECT_EQ(got, expected);
}

// [TEST_ID: 709]
TEST(ApproxStringMakerTest_709, DelegatesToToString_Negated_709) {
    Approx a(4.2);
    const auto neg = -a;

    const std::string expected = neg.toString();
    const std::string got = Catch::StringMaker<Approx>::convert(neg);
    EXPECT_EQ(got, expected);
}
