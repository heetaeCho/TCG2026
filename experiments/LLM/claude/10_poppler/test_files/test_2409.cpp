#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <poppler.h>
}

class PopplerSetNssDirTest_2409 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that poppler_set_nss_dir does not crash with a valid path
TEST_F(PopplerSetNssDirTest_2409, SetValidPath_2409) {
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir("/tmp/nss"));
}

// Test that poppler_set_nss_dir does not crash with an empty string
TEST_F(PopplerSetNssDirTest_2409, SetEmptyPath_2409) {
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir(""));
}

// Test that poppler_set_nss_dir does not crash with a long path
TEST_F(PopplerSetNssDirTest_2409, SetLongPath_2409) {
    std::string longPath(4096, 'a');
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir(longPath.c_str()));
}

// Test that poppler_set_nss_dir does not crash with special characters in path
TEST_F(PopplerSetNssDirTest_2409, SetPathWithSpecialCharacters_2409) {
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir("/tmp/nss dir/with spaces & special!@#$%"));
}

// Test that poppler_set_nss_dir does not crash when called multiple times
TEST_F(PopplerSetNssDirTest_2409, SetPathMultipleTimes_2409) {
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir("/tmp/nss1"));
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir("/tmp/nss2"));
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir("/tmp/nss3"));
}

// Test that poppler_set_nss_dir does not crash with a path containing null-like content
TEST_F(PopplerSetNssDirTest_2409, SetPathSingleChar_2409) {
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir("/"));
}

// Test that poppler_set_nss_dir does not crash with a relative path
TEST_F(PopplerSetNssDirTest_2409, SetRelativePath_2409) {
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir("relative/path/to/nss"));
}

// Test that poppler_set_nss_dir does not crash with a path containing unicode
TEST_F(PopplerSetNssDirTest_2409, SetPathWithUnicode_2409) {
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir("/tmp/nss_日本語"));
}

// Test that calling poppler_set_nss_dir with the same path twice doesn't cause issues
TEST_F(PopplerSetNssDirTest_2409, SetSamePathTwice_2409) {
    const char *path = "/tmp/same_nss_dir";
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir(path));
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir(path));
}

// Test with a dot path (current directory)
TEST_F(PopplerSetNssDirTest_2409, SetDotPath_2409) {
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir("."));
}

// Test with double dot path (parent directory)
TEST_F(PopplerSetNssDirTest_2409, SetDoubleDotPath_2409) {
    EXPECT_NO_FATAL_FAILURE(poppler_set_nss_dir(".."));
}
