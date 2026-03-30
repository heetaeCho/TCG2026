// File: tests/testcaseinfo_oktofail_997.cpp
#include <gtest/gtest.h>

// Catch2 headers (public interface)
#include <catch2/catch_test_case_info.hpp>
#include <type_traits>

using Catch::NameAndTags;
using Catch::SourceLineInfo;
using Catch::StringRef;
using Catch::TestCaseInfo;
using Catch::TestCaseProperties;

namespace {

// Small helper to combine enum-class flags without assuming operator| exists.
template <typename Enum>
constexpr Enum bit_or(Enum a, Enum b) {
    using U = std::underlying_type_t<Enum>;
    return static_cast<Enum>(static_cast<U>(a) | static_cast<U>(b));
}

struct TestCaseInfo_OkToFailTest_997 : ::testing::Test {
    // Creates a minimally valid TestCaseInfo via its public ctor.
    static TestCaseInfo makeBase() {
        NameAndTags nt{ "sample-test", "" }; // name + empty tags
        SourceLineInfo sli{ __FILE__, static_cast<std::size_t>(__LINE__) };
        return TestCaseInfo(StringRef("SampleClass"), nt, sli);
    }
};

} // namespace

// Normal: no flags set -> okToFail() should be false
TEST_F(TestCaseInfo_OkToFailTest_997, OkToFail_False_WhenNone_997) {
    auto info = makeBase();
    info.properties = TestCaseProperties::None;

    EXPECT_FALSE(info.okToFail());
}

// Boundary: ShouldFail set -> okToFail() should be true
TEST_F(TestCaseInfo_OkToFailTest_997, OkToFail_True_WhenShouldFail_997) {
    auto info = makeBase();
    info.properties = TestCaseProperties::ShouldFail;

    EXPECT_TRUE(info.okToFail());
}

// Boundary: MayFail set -> okToFail() should be true
TEST_F(TestCaseInfo_OkToFailTest_997, OkToFail_True_WhenMayFail_997) {
    auto info = makeBase();
    info.properties = TestCaseProperties::MayFail;

    EXPECT_TRUE(info.okToFail());
}

// Boundary: both ShouldFail and MayFail set -> okToFail() should be true
TEST_F(TestCaseInfo_OkToFailTest_997, OkToFail_True_WhenBothFlags_997) {
    auto info = makeBase();
    info.properties = bit_or(TestCaseProperties::ShouldFail, TestCaseProperties::MayFail);

    EXPECT_TRUE(info.okToFail());
}

// Negative/Exceptional surface: unrelated flags only -> okToFail() should be false
TEST_F(TestCaseInfo_OkToFailTest_997, OkToFail_False_WithUnrelatedFlagsOnly_997) {
    auto info = makeBase();
    // Combine a couple of flags that are not ShouldFail/MayFail
    info.properties = bit_or(TestCaseProperties::IsHidden, TestCaseProperties::Throws);

    EXPECT_FALSE(info.okToFail());
}
