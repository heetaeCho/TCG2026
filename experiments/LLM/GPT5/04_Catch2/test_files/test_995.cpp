// File: tests/test_testcaseinfo_isHidden_995.cpp
#include <gtest/gtest.h>

#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_source_line_info.hpp>  // If needed for SourceLineInfo
#include <catch2/internal/catch_stringref.hpp>         // If needed for StringRef
#include <catch2/catch_test_case_info.hpp>             // For NameAndTags (depends on Catch2 layout)

using Catch::TestCaseInfo;
using Catch::TestCaseProperties;
using Catch::StringRef;
using Catch::SourceLineInfo;
using Catch::NameAndTags;

namespace {

// Small helper to make a TestCaseInfo without relying on any internals.
TestCaseInfo makeInfo(const char* name = "Dummy",
                      const char* file = "dummy_file.cpp",
                      std::size_t line = 1) {
    NameAndTags nt;
    nt.name = name;     // Only use public fields; do not assume anything about tags.
    SourceLineInfo sli{file, static_cast<std::uint32_t>(line)};
    return TestCaseInfo(StringRef{}, nt, sli);
}

} // namespace

// Fixture kept trivial for clarity
class TestCaseInfo_IsHidden_995 : public ::testing::Test {};

// [Normal] properties == None -> isHidden() == false
TEST_F(TestCaseInfo_IsHidden_995, NoneFlag_IsNotHidden_995) {
    auto info = makeInfo("case_none");
    info.properties = TestCaseProperties::None;

    const TestCaseInfo& cref = info; // Verify const-call
    EXPECT_FALSE(cref.isHidden());
}

// [Boundary] properties == IsHidden -> isHidden() == true
TEST_F(TestCaseInfo_IsHidden_995, HiddenFlag_IsHidden_995) {
    auto info = makeInfo("case_hidden");
    info.properties = TestCaseProperties::IsHidden;

    const TestCaseInfo& cref = info;
    EXPECT_TRUE(cref.isHidden());
}

// [Combination] properties includes IsHidden among other flags -> isHidden() == true
TEST_F(TestCaseInfo_IsHidden_995, MultipleFlags_IncludingHidden_IsHidden_995) {
    auto info = makeInfo("case_multi_hidden");
    info.properties =
        TestCaseProperties::IsHidden |
        TestCaseProperties::Throws |
        TestCaseProperties::MayFail |
        TestCaseProperties::Benchmark;

    const TestCaseInfo& cref = info;
    EXPECT_TRUE(cref.isHidden());
}

// [Negative Combination] properties excludes IsHidden -> isHidden() == false
TEST_F(TestCaseInfo_IsHidden_995, MultipleFlags_ExcludingHidden_IsNotHidden_995) {
    auto info = makeInfo("case_multi_no_hidden");
    info.properties =
        TestCaseProperties::Throws |
        TestCaseProperties::ShouldFail |
        TestCaseProperties::NonPortable;

    const TestCaseInfo& cref = info;
    EXPECT_FALSE(cref.isHidden());
}
