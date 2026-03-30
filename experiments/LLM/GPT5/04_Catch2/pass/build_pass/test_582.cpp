// section_operator_bool_tests_582.cpp
#include <type_traits>
#include <gtest/gtest.h>

// Include only the interface declaration (no definitions required).
// Adjust include path to match your project layout.
#include "catch2/internal/catch_section.hpp"

namespace {

// Helper to detect usability in a boolean context without creating an instance.
// SFINAE checks that the expression `declval<const T&>() ? 1 : 0` is well-formed.
template <typename T, typename = void>
struct IsBoolContextUsable : std::false_type {};

template <typename T>
struct IsBoolContextUsable<T,
    std::void_t<decltype( std::declval<const T&>() ? 1 : 0 )>> : std::true_type {};

} // namespace

// Verifies that Catch::Section is implicitly convertible to bool (no explicit cast required).
TEST(SectionOperatorBoolTest_582, ConvertibleToBool_582) {
    // `operator bool() const` implies implicit convertibility.
    EXPECT_TRUE((std::is_convertible<const Catch::Section, bool>::value));
}

// Verifies that the operator is const-qualified on the object (callable on const Section).
TEST(SectionOperatorBoolTest_582, OperatorIsConstQualified_582) {
    // The type of the member pointer must match `bool (Catch::Section::*)() const`.
    using ExpectedPtr = bool (Catch::Section::*)() const;
    // If the declaration differs (e.g., missing const), this comparison will fail to compile or be false.
    EXPECT_TRUE((std::is_same<decltype(&Catch::Section::operator bool), ExpectedPtr>::value));
}

// Verifies that a const Section is usable in boolean contexts (e.g., conditional operator).
TEST(SectionOperatorBoolTest_582, UsableInBooleanContext_582) {
    EXPECT_TRUE((IsBoolContextUsable<Catch::Section>::value));
}

