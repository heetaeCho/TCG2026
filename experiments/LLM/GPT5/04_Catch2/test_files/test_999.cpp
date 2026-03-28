// TEST_ID: 999
// File: tests/test_testcaseinfo_addfilenametag_999.cpp

#include <gtest/gtest.h>

#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

using namespace Catch;

namespace {

// Small helper to build a TestCaseInfo with minimal, empty metadata.
// We rely only on its public constructor & public observable APIs.
TestCaseInfo makeTCIForFile(const char* filePath) {
    // NameAndTags is part of Catch2's public interface here.
    NameAndTags nt;
    nt.name = "DummyTest";
    nt.tags = ""; // start with no tags so effects of addFilenameTag are isolated

    StringRef clsName(""); // empty class name
    SourceLineInfo sli(filePath, 123);
    return TestCaseInfo(clsName, nt, sli);
}

} // namespace

// --- Normal operation: UNIX-style path ---
TEST(TestCaseInfoAddFilenameTag_999, AddsBasenameFromUnixPath_999) {
    auto tci = makeTCIForFile("dir/subdir/sample_test.cpp");

    // Act
    tci.addFilenameTag();

    // Assert via observable public API
    const std::string tags = tci.tagsAsString();
    // Should include a tag with just the basename prefixed by '#'
    EXPECT_NE(tags.find("#sample_test.cpp"), std::string::npos);
    // Should not include directory separators from the original path
    EXPECT_EQ(tags.find("dir/"), std::string::npos);
    EXPECT_EQ(tags.find("subdir/"), std::string::npos);
}

// --- Normal operation: Windows-style path ---
TEST(TestCaseInfoAddFilenameTag_999, AddsBasenameFromWindowsPath_999) {
    auto tci = makeTCIForFile("C:\\path\\to\\suite\\win_case.cxx");

    tci.addFilenameTag();

    const std::string tags = tci.tagsAsString();
    EXPECT_NE(tags.find("#win_case.cxx"), std::string::npos);
    // No directory fragments should leak into the tag
    EXPECT_EQ(tags.find("path\\"), std::string::npos);
    EXPECT_EQ(tags.find("to\\"), std::string::npos);
    EXPECT_EQ(tags.find("suite\\"), std::string::npos);
}

// --- Boundary: filename without any directory component ---
TEST(TestCaseInfoAddFilenameTag_999, HandlesBareFilename_999) {
    auto tci = makeTCIForFile("standalone");

    tci.addFilenameTag();

    const std::string tags = tci.tagsAsString();
    EXPECT_NE(tags.find("#standalone"), std::string::npos);
    // Obviously there should be no slash/backslash fragments
    EXPECT_EQ(tags.find("/"), std::string::npos);
    EXPECT_EQ(tags.find("\\"), std::string::npos);
}

// --- Boundary: UTF-8 / non-ASCII filenames (should be passed through) ---
TEST(TestCaseInfoAddFilenameTag_999, HandlesUTF8Filenames_999) {
    // Korean letters; we only assert that the resulting tag contains the exact basename
    auto tci = makeTCIForFile("경로/서브/테스트파일.cpp");

    tci.addFilenameTag();

    const std::string tags = tci.tagsAsString();
    EXPECT_NE(tags.find("#테스트파일.cpp"), std::string::npos);
    EXPECT_EQ(tags.find("경로/"), std::string::npos);
    EXPECT_EQ(tags.find("서브/"), std::string::npos);
}

// --- Boundary: deep/mixed separators (robustness wrt basename extraction) ---
TEST(TestCaseInfoAddFilenameTag_999, MixedSeparatorsOnlyBasenameIncluded_999) {
    auto tci = makeTCIForFile("a/b\\c/d\\e/final.name.hpp");

    tci.addFilenameTag();

    const std::string tags = tci.tagsAsString();
    EXPECT_NE(tags.find("#final.name.hpp"), std::string::npos);
    // Ensure no path fragments remain (either slash type)
    EXPECT_EQ(tags.find("a/"), std::string::npos);
    EXPECT_EQ(tags.find("b\\"), std::string::npos);
    EXPECT_EQ(tags.find("c/"), std::string::npos);
    EXPECT_EQ(tags.find("d\\"), std::string::npos);
}

