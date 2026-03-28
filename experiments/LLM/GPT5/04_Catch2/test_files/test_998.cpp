// File: tests/test_expectedToFail_998.cpp

#include <gtest/gtest.h>
#include <catch2/catch_test_case_info.hpp>  // Adjust include path if needed

using namespace Catch;

namespace {

// Small helper to construct a TestCaseInfo using only public interfaces/types.
inline TestCaseInfo makeTCI(StringRef className = StringRef{},
                            NameAndTags const& nat = NameAndTags{"", ""},
                            SourceLineInfo const& sli = SourceLineInfo{"<test>", 1}) {
    return TestCaseInfo{className, nat, sli};
}

} // namespace

// -----------------------------------------------------------------------------

// Normal operation: with no flags set, expectedToFail() should report false.
TEST(TestCaseInfoExpectedToFail_998, ReturnsFalseWhenNoFlag_998) {
    auto tci = makeTCI();
    tci.properties = TestCaseProperties::None; // public member per interface
    EXPECT_FALSE(tci.expectedToFail());
}

// Normal operation: with ShouldFail set, expectedToFail() should report true.
TEST(TestCaseInfoExpectedToFail_998, ReturnsTrueWhenShouldFailSet_998) {
    auto tci = makeTCI();
    tci.properties = TestCaseProperties::ShouldFail;
    EXPECT_TRUE(tci.expectedToFail());
}

// Boundary: other flags without ShouldFail must not trigger expectedToFail().
TEST(TestCaseInfoExpectedToFail_998, ReturnsFalseWithOtherFlagsOnly_998) {
    auto tci = makeTCI();

    // Combine several non-ShouldFail flags. Uses only public enum flags.
    tci.properties =
        TestCaseProperties::IsHidden
      | TestCaseProperties::Throws
      | TestCaseProperties::MayFail
      | TestCaseProperties::NonPortable
      | TestCaseProperties::Benchmark;

    EXPECT_FALSE(tci.expectedToFail());
}

// Boundary/combination: ShouldFail combined with other flags must still return true.
TEST(TestCaseInfoExpectedToFail_998, ReturnsTrueWhenShouldFailCombined_998) {
    auto tci = makeTCI();

    tci.properties =
        TestCaseProperties::ShouldFail
      | TestCaseProperties::Throws
      | TestCaseProperties::IsHidden
      | TestCaseProperties::Benchmark;

    EXPECT_TRUE(tci.expectedToFail());
}

// Const-correctness / observable behavior through const interface.
TEST(TestCaseInfoExpectedToFail_998, CallableOnConstObject_998) {
    auto tciMutable = makeTCI();
    tciMutable.properties = TestCaseProperties::ShouldFail;

    const TestCaseInfo& tciConst = tciMutable;
    // Calling the const-qualified function should observe the same behavior.
    EXPECT_TRUE(tciConst.expectedToFail());
}
