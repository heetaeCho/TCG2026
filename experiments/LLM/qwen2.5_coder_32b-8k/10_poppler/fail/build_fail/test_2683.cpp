#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdio>

#include <string>



// Mocking fprintf to capture its calls.

extern "C" {

    int mock_fprintf(FILE *stream, const char *format, ...) {

        va_list args;

        va_start(args, format);

        // Capture the output for verification

        char buffer[1024];

        vsnprintf(buffer, sizeof(buffer), format, args);

        captured_output = std::string(buffer);

        va_end(args);

        return 0; // Simulate successful fprintf call.

    }



    int (*real_fprintf)(FILE*, const char*, ...) = fprintf;

    std::string captured_output;



    void print_version_usage(bool usage) {

        real_fprintf(stderr, "pdfsig version %s\n", "1.23.45"); // Assuming a version string for testing

        real_fprintf(stderr, "%s\n", "Poppler Copyright");

        real_fprintf(stderr, "%s\n", "XPDF Copyright");

        if (usage) {

            mock_fprintf(stderr, "Usage: %s <PDF-file> [<output-file>] %s", "pdfsig", "argDesc");

        }

    }

}



// Test fixture for the print_version_usage function.

class PrintVersionUsageTest_2683 : public ::testing::Test {

protected:

    void SetUp() override {

        real_fprintf = fprintf;

        fprintf = mock_fprintf;

    }



    void TearDown() override {

        fprintf = real_fprintf;

    }

};



// Test normal operation with usage set to false.

TEST_F(PrintVersionUsageTest_2683, PrintVersionWithoutUsage_2683) {

    print_version_usage(false);

    EXPECT_THAT(captured_output, ::testing::HasSubstr("pdfsig version 1.23.45"));

    EXPECT_THAT(captured_output, ::testing::HasSubstr("Poppler Copyright"));

    EXPECT_THAT(captured_output, ::testing::HasSubstr("XPDF Copyright"));

}



// Test normal operation with usage set to true.

TEST_F(PrintVersionUsageTest_2683, PrintVersionWithUsage_2683) {

    print_version_usage(true);

    EXPECT_THAT(captured_output, ::testing::HasSubstr("pdfsig version 1.23.45"));

    EXPECT_THAT(captured_output, ::testing::HasSubstr("Poppler Copyright"));

    EXPECT_THAT(captured_output, ::testing::HasSubstr("XPDF Copyright"));

    EXPECT_THAT(captured_output, ::testing::HasSubstr("Usage: pdfsig <PDF-file> [<output-file>] argDesc"));

}



// Test boundary condition with usage set to false (no additional output).

TEST_F(PrintVersionUsageTest_2683, PrintVersionWithoutUsageNoExtraOutput_2683) {

    print_version_usage(false);

    EXPECT_FALSE(captured_output.find("Usage:") != std::string::npos);

}



// Test boundary condition with usage set to true (additional output).

TEST_F(PrintVersionUsageTest_2683, PrintVersionWithUsageHasExtraOutput_2683) {

    print_version_usage(true);

    EXPECT_TRUE(captured_output.find("Usage:") != std::string::npos);

}
