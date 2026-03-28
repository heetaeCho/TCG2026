// File: assertion_result_get_source_info_tests_301.cpp

#include <gtest/gtest.h>

#include <catch2/catch_assertion_result.hpp>
#include <catch2/catch_assertion_info.hpp>

// If your environment separates these, you may also need:
// #include <catch2/catch_result_type.hpp>
// #include <catch2/catch_source_line_info.hpp>
// #include <catch2/internal/catch_stringref.hpp>

class AssertionResultGetSourceInfoTest_301 : public ::testing::Test {
protected:
    static Catch::AssertionResult MakeResult(const char* file, std::size_t line) {
        using Catch::StringRef;

        // Build the source location we want to observe via getSourceInfo()
        Catch::SourceLineInfo src{ file, line };

        // Build minimal AssertionInfo required by the interface
        // Note: Constructor signature is part of Catch2's public API.
        Catch::AssertionInfo info(
            StringRef("TEST_MACRO"),
            src,
            StringRef("1 == 1"),
            Catch::ResultDisposition::Normal
        );

        // Result data is not used by getSourceInfo(); we pass a default instance.
        Catch::AssertionResultData data{};
        return Catch::AssertionResult(info, std::move(data));
    }
};

// Normal operation: returns the exact SourceLineInfo provided at construction.
TEST_F(AssertionResultGetSourceInfoTest_301, ReturnsProvidedSourceLineInfo_301) {
    const char* kFile = "foo.cpp";
    const std::size_t kLine = 42;

    auto ar = MakeResult(kFile, kLine);
    Catch::SourceLineInfo returned = ar.getSourceInfo();

    // Verify both file path and line number match.
    ASSERT_NE(returned.file, nullptr);
    EXPECT_STREQ(kFile, returned.file);
    EXPECT_EQ(kLine, returned.line);
}

// Boundary: very large line number should be preserved.
TEST_F(AssertionResultGetSourceInfoTest_301, PreservesLargeLineNumber_301) {
    const char* kFile = "big_lines.cpp";
    const std::size_t kLine = 1'000'000;

    auto ar = MakeResult(kFile, kLine);
    Catch::SourceLineInfo returned = ar.getSourceInfo();

    ASSERT_NE(returned.file, nullptr);
    EXPECT_STREQ(kFile, returned.file);
    EXPECT_EQ(kLine, returned.line);
}

// Boundary: non-ASCII/UTF-8 file paths are returned intact.
TEST_F(AssertionResultGetSourceInfoTest_301, HandlesUtf8FilePath_301) {
    const char* kFile = u8"/경로/테스트/파일.cpp";
    const std::size_t kLine = 7;

    auto ar = MakeResult(kFile, kLine);
    Catch::SourceLineInfo returned = ar.getSourceInfo();

    ASSERT_NE(returned.file, nullptr);
    EXPECT_STREQ(kFile, returned.file);
    EXPECT_EQ(kLine, returned.line);
}

// Const correctness: getSourceInfo() must be callable on const objects and return the same info.
TEST_F(AssertionResultGetSourceInfoTest_301, ConstGetSourceInfoReturnsSameData_301) {
    const char* kFile = "const_ok.cpp";
    const std::size_t kLine = 123;

    const auto ar = MakeResult(kFile, kLine); // const object
    Catch::SourceLineInfo returned = ar.getSourceInfo();

    ASSERT_NE(returned.file, nullptr);
    EXPECT_STREQ(kFile, returned.file);
    EXPECT_EQ(kLine, returned.line);
}

// Independence: two different AssertionResults must keep their own SourceLineInfo.
TEST_F(AssertionResultGetSourceInfoTest_301, IndependentInstancesKeepOwnSourceInfo_301) {
    auto a = MakeResult("a.cpp", 1);
    auto b = MakeResult("b.cpp", 2);

    Catch::SourceLineInfo aSrc = a.getSourceInfo();
    Catch::SourceLineInfo bSrc = b.getSourceInfo();

    ASSERT_NE(aSrc.file, nullptr);
    ASSERT_NE(bSrc.file, nullptr);

    EXPECT_STREQ("a.cpp", aSrc.file);
    EXPECT_EQ(1u, aSrc.line);

    EXPECT_STREQ("b.cpp", bSrc.file);
    EXPECT_EQ(2u, bSrc.line);
}
