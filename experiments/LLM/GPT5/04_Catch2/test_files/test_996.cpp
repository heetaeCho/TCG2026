// File: tests/test_testcaseinfo_throws_996.cpp

#include <gtest/gtest.h>

#include "catch2/catch_test_case_info.hpp"  // Adjust include path if needed

using namespace Catch;

namespace {

// Small helper to build a valid TestCaseInfo via public constructor only.
inline TestCaseInfo makeInfo(StringRef name = "X",
                             StringRef className = "C") {
    NameAndTags nat;
    nat.name = std::string{name};
    // No tags needed for these tests
    SourceLineInfo sli{__FILE__, static_cast<std::size_t>(__LINE__)};
    TestCaseInfo info(className, nat, sli);
    return info;
}

} // namespace

// Default constructed via public ctor -> properties defaults to None
TEST(TestCaseInfo_996, Throws_DefaultIsFalse_996) {
    auto info = makeInfo();
    info.properties = TestCaseProperties::None; // explicit for clarity
    EXPECT_FALSE(info.throws());
}

// When the Throws bit is set alone, throws() should report true
TEST(TestCaseInfo_996, Throws_TrueWhenThrowsFlagSet_996) {
    auto info = makeInfo();
    info.properties = TestCaseProperties::Throws;
    EXPECT_TRUE(info.throws());
}

// When other bits are set but not Throws, throws() should report false
TEST(TestCaseInfo_996, Throws_FalseWhenOtherFlagsWithoutThrows_996) {
    auto info = makeInfo();
    info.properties = TestCaseProperties::IsHidden; // pick any non-Throws flag
    EXPECT_FALSE(info.throws());

    info.properties = TestCaseProperties::ShouldFail;
    EXPECT_FALSE(info.throws());

    info.properties = TestCaseProperties::MayFail;
    EXPECT_FALSE(info.throws());
}

// When multiple bits are set and one of them is Throws, throws() should report true
TEST(TestCaseInfo_996, Throws_TrueWhenCombinedFlagsIncludeThrows_996) {
    auto info = makeInfo();
    info.properties = TestCaseProperties::MayFail | TestCaseProperties::Throws;
    EXPECT_TRUE(info.throws());

    info.properties = TestCaseProperties::IsHidden | TestCaseProperties::Throws;
    EXPECT_TRUE(info.throws());

    info.properties = TestCaseProperties::Benchmark | TestCaseProperties::Throws;
    EXPECT_TRUE(info.throws());
}

// Observable behavior should follow current properties: toggling the flag toggles the result
TEST(TestCaseInfo_996, Throws_TracksPropertyChanges_996) {
    auto info = makeInfo();

    info.properties = TestCaseProperties::None;
    EXPECT_FALSE(info.throws());

    info.properties = TestCaseProperties::Throws;
    EXPECT_TRUE(info.throws());

    info.properties = TestCaseProperties::None;
    EXPECT_FALSE(info.throws());
}
