#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>

// We need to capture stderr output to verify print_version_usage behavior.
// Since print_version_usage is a static function in pdfsig.cc, we need to
// include it or replicate the declaration. However, since it's static,
// we cannot directly link to it from outside the translation unit.
//
// To test this, we'll include the source file indirectly or use a wrapper.
// For the purpose of this test, we'll define the necessary externs and
// include the relevant parts.

// Forward declarations of poppler dependencies
#include "config.h"

// We need access to the static function and global variables.
// Since print_version_usage is static, we include the .cc file directly
// to bring it into this translation unit. This is a common testing technique
// for static functions.

// Mock/stub out the main() function to avoid conflicts
#define main pdfsig_main

// Provide necessary includes that pdfsig.cc expects
#include "goo/GooString.h"
#include "parseargs.h"
#include "GlobalParams.h"

// Include the source to get access to the static function
#include "pdfsig.cc"

#undef main

class PdfsigPrintVersionUsageTest_2683 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to capture stderr output
    std::string captureStderr(bool usage) {
        // Redirect stderr to a temporary file
        FILE *original_stderr = stderr;
        char tmpname[] = "/tmp/pdfsig_test_XXXXXX";
        int fd = mkstemp(tmpname);
        EXPECT_NE(fd, -1);
        FILE *tmp = fdopen(fd, "w+");
        EXPECT_NE(tmp, nullptr);

        stderr = tmp;
        print_version_usage(usage);
        fflush(stderr);
        stderr = original_stderr;

        // Read back what was written
        fseek(tmp, 0, SEEK_SET);
        std::string result;
        char buf[1024];
        while (fgets(buf, sizeof(buf), tmp)) {
            result += buf;
        }
        fclose(tmp);
        unlink(tmpname);
        return result;
    }
};

// Test that print_version_usage with usage=false prints version info but not usage
TEST_F(PdfsigPrintVersionUsageTest_2683, PrintsVersionInfoWithoutUsage_2683) {
    std::string output = captureStderr(false);

    // Should contain version string
    EXPECT_NE(output.find("pdfsig version"), std::string::npos)
        << "Output should contain 'pdfsig version'. Got: " << output;

    // Should contain PACKAGE_VERSION
    EXPECT_NE(output.find(PACKAGE_VERSION), std::string::npos)
        << "Output should contain the package version. Got: " << output;

    // Should contain copyright info
    EXPECT_NE(output.find(popplerCopyright), std::string::npos)
        << "Output should contain poppler copyright. Got: " << output;
    EXPECT_NE(output.find(xpdfCopyright), std::string::npos)
        << "Output should contain xpdf copyright. Got: " << output;
}

// Test that print_version_usage with usage=true prints version info AND usage
TEST_F(PdfsigPrintVersionUsageTest_2683, PrintsVersionInfoWithUsage_2683) {
    std::string output = captureStderr(true);

    // Should contain version string
    EXPECT_NE(output.find("pdfsig version"), std::string::npos)
        << "Output should contain 'pdfsig version'. Got: " << output;

    // Should contain PACKAGE_VERSION
    EXPECT_NE(output.find(PACKAGE_VERSION), std::string::npos)
        << "Output should contain the package version. Got: " << output;

    // Should contain copyright info
    EXPECT_NE(output.find(popplerCopyright), std::string::npos)
        << "Output should contain poppler copyright. Got: " << output;

    // Should contain usage-related text (from printUsage call)
    // The printUsage call includes "pdfsig" and the args pattern
    EXPECT_NE(output.find("pdfsig"), std::string::npos)
        << "Output should contain 'pdfsig' usage text. Got: " << output;
    EXPECT_NE(output.find("<PDF-file>"), std::string::npos)
        << "Output should contain '<PDF-file>' in usage. Got: " << output;
}

// Test that usage=true produces more output than usage=false
TEST_F(PdfsigPrintVersionUsageTest_2683, UsageTrueProducesMoreOutput_2683) {
    std::string outputNoUsage = captureStderr(false);
    std::string outputWithUsage = captureStderr(true);

    EXPECT_GT(outputWithUsage.size(), outputNoUsage.size())
        << "Output with usage=true should be longer than usage=false";
}

// Test that usage=true includes argument descriptions from argDesc
TEST_F(PdfsigPrintVersionUsageTest_2683, UsageTrueIncludesArgDescriptions_2683) {
    std::string output = captureStderr(true);

    // Check for some known argument descriptions
    EXPECT_NE(output.find("-nssdir"), std::string::npos)
        << "Usage output should contain '-nssdir'. Got: " << output;
    EXPECT_NE(output.find("-dump"), std::string::npos)
        << "Usage output should contain '-dump'. Got: " << output;
    EXPECT_NE(output.find("-h"), std::string::npos)
        << "Usage output should contain '-h'. Got: " << output;
}

// Test that usage=false does NOT include argument descriptions
TEST_F(PdfsigPrintVersionUsageTest_2683, UsageFalseDoesNotIncludeArgDescriptions_2683) {
    std::string output = captureStderr(false);

    // Without usage, there should be no argument description lines
    EXPECT_EQ(output.find("-nssdir"), std::string::npos)
        << "Version-only output should not contain '-nssdir'. Got: " << output;
    EXPECT_EQ(output.find("-dump"), std::string::npos)
        << "Version-only output should not contain '-dump'. Got: " << output;
}

// Test that the argDesc global array is properly terminated
TEST_F(PdfsigPrintVersionUsageTest_2683, ArgDescArrayIsTerminated_2683) {
    // Walk through argDesc to find the terminator (empty entry)
    int count = 0;
    while (argDesc[count].arg != nullptr) {
        count++;
        // Safety check - shouldn't have more than 100 entries
        ASSERT_LT(count, 100) << "argDesc appears to be unterminated";
    }
    // We expect 27 entries based on the provided code (28 entries including terminator)
    EXPECT_EQ(count, 27) << "Expected 27 argument descriptors before terminator";
}

// Verify specific argDesc entries
TEST_F(PdfsigPrintVersionUsageTest_2683, ArgDescContainsExpectedEntries_2683) {
    // Check first entry
    EXPECT_STREQ(argDesc[0].arg, "-nssdir");

    // Check a middle entry - "-dump" should be at index 7
    EXPECT_STREQ(argDesc[7].arg, "-dump");

    // Check "-v" flag
    bool foundV = false;
    for (int i = 0; argDesc[i].arg != nullptr; i++) {
        if (strcmp(argDesc[i].arg, "-v") == 0) {
            foundV = true;
            EXPECT_EQ(argDesc[i].kind, argFlag);
            break;
        }
    }
    EXPECT_TRUE(foundV) << "Should find '-v' in argDesc";

    // Check "-help" flag exists
    bool foundHelp = false;
    for (int i = 0; argDesc[i].arg != nullptr; i++) {
        if (strcmp(argDesc[i].arg, "-help") == 0) {
            foundHelp = true;
            EXPECT_EQ(argDesc[i].kind, argFlag);
            break;
        }
    }
    EXPECT_TRUE(foundHelp) << "Should find '-help' in argDesc";
}

// Test calling print_version_usage multiple times doesn't crash
TEST_F(PdfsigPrintVersionUsageTest_2683, MultipleCallsDoNotCrash_2683) {
    EXPECT_NO_FATAL_FAILURE({
        std::string output1 = captureStderr(false);
        std::string output2 = captureStderr(false);
        EXPECT_EQ(output1, output2) << "Multiple calls should produce identical output";
    });
}

TEST_F(PdfsigPrintVersionUsageTest_2683, MultipleCallsWithUsageDoNotCrash_2683) {
    EXPECT_NO_FATAL_FAILURE({
        std::string output1 = captureStderr(true);
        std::string output2 = captureStderr(true);
        EXPECT_EQ(output1, output2) << "Multiple calls should produce identical output";
    });
}
