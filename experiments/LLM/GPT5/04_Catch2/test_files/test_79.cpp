// File: stringify_tests_79.cpp

#include <gtest/gtest.h>
#include <string>

// Forward-declare Catch::StringMaker so we can provide a specialization for our test type.
// This is a declaration only; the real implementation lives in the codebase.
namespace Catch { template <typename T> struct StringMaker; }

// Include the function under test.
#include "Catch2/src/catch2/catch_tostring.hpp"

// A simple user-defined type whose value is visible through the public interface.
namespace test_types {
struct Widget {
    int value;
};
} // namespace test_types

// Provide a StringMaker specialization for our test type.
// This is the only "collaborator" stringify() depends on; we treat stringify() as a black box.
namespace Catch {
template <>
struct StringMaker<test_types::Widget> {
    static std::string convert(test_types::Widget const& w) {
        return std::string("Widget(") + std::to_string(w.value) + ")";
    }
};
} // namespace Catch

// --- Tests ---

// Verifies normal operation: stringify returns whatever the registered StringMaker produces.
TEST(StringifyTest_79, CustomType_UsesStringMakerSpecialization_79) {
    test_types::Widget w{123};
    EXPECT_EQ(Catch::Detail::stringify(w), "Widget(123)");
}

// Verifies boundary-like cv/ref scenarios: stringify removes const/volatile and reference qualifiers
// and still finds the same StringMaker<Widget> specialization.
TEST(StringifyTest_79, RemovesConstQualifierWhenSelectingStringMaker_79) {
    const test_types::Widget cw{7};
    // Force T = const Widget explicitly to ensure remove_cv_t is exercised.
    EXPECT_EQ(Catch::Detail::stringify<const test_types::Widget>(cw), "Widget(7)");
}

TEST(StringifyTest_79, RemovesVolatileQualifierWhenSelectingStringMaker_79) {
    volatile test_types::Widget vw{8};
    // Force T = volatile Widget explicitly to ensure remove_cv_t is exercised.
    EXPECT_EQ(Catch::Detail::stringify<volatile test_types::Widget>(vw), "Widget(8)");
}

TEST(StringifyTest_79, RemovesReferenceQualifierWhenSelectingStringMaker_79) {
    test_types::Widget w{5};
    // Force T = Widget& explicitly to ensure remove_reference_t is exercised.
    EXPECT_EQ(Catch::Detail::stringify<test_types::Widget&>(w), "Widget(5)");
}

TEST(StringifyTest_79, RemovesConstVolatileRefQualifiersTogether_79) {
    volatile test_types::Widget vw{11};
    // Force T = const volatile Widget& to exercise both remove_reference_t and remove_cv_t.
    EXPECT_EQ(Catch::Detail::stringify<const volatile test_types::Widget&>(vw), "Widget(11)");
}

TEST(StringifyTest_79, WorksWithRvalueReferenceTemplateArgument_79) {
    // Force T = Widget&&; parameter type becomes const Widget&, which must still stringify correctly.
    EXPECT_EQ(Catch::Detail::stringify<test_types::Widget&&>(test_types::Widget{42}), "Widget(42)");
}

// Basic builtin coverage to ensure typical integral types stringify as expected via the library’s StringMaker.
TEST(StringifyTest_79, BuiltinIntPositiveAndNegative_79) {
    EXPECT_EQ(Catch::Detail::stringify(0), "0");
    EXPECT_EQ(Catch::Detail::stringify(12345), "12345");
    EXPECT_EQ(Catch::Detail::stringify(-17), "-17");
}
