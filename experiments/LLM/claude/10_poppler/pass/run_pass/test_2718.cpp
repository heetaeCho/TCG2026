#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include "GlobalParams.h"
#include "printencodings.cc"

// We need access to globalParams
extern std::unique_ptr<GlobalParams> globalParams;

class PrintEncodingsTest_2718 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>("");
        }
    }

    void TearDown() override {
    }

    // Helper to capture stdout output from printEncodings()
    std::string captureOutput() {
        // Flush before redirecting
        fflush(stdout);

        // Create a temporary file to capture output
        char tmpFileName[] = "/tmp/printenc_test_XXXXXX";
        int fd = mkstemp(tmpFileName);
        EXPECT_NE(fd, -1);

        FILE *tmpFile = fdopen(fd, "w+");
        EXPECT_NE(tmpFile, nullptr);

        // Save original stdout
        int origStdout = dup(fileno(stdout));

        // Redirect stdout to temp file
        fflush(stdout);
        dup2(fileno(tmpFile), fileno(stdout));

        // Call the function
        printEncodings();

        // Flush and restore stdout
        fflush(stdout);
        dup2(origStdout, fileno(stdout));
        close(origStdout);

        // Read the captured output
        fseek(tmpFile, 0, SEEK_SET);
        std::string output;
        char buf[1024];
        while (fgets(buf, sizeof(buf), tmpFile) != nullptr) {
            output += buf;
        }

        fclose(tmpFile);
        remove(tmpFileName);

        return output;
    }
};

// Test that printEncodings produces output starting with the header line
TEST_F(PrintEncodingsTest_2718, OutputStartsWithHeader_2718) {
    std::string output = captureOutput();
    EXPECT_FALSE(output.empty());
    EXPECT_THAT(output, ::testing::StartsWith("Available encodings are:\n"));
}

// Test that printEncodings lists encodings in sorted order
TEST_F(PrintEncodingsTest_2718, EncodingsAreSorted_2718) {
    std::string output = captureOutput();

    // Parse the output: skip the header line, collect encoding names
    std::vector<std::string> lines;
    std::istringstream stream(output);
    std::string line;
    bool headerSkipped = false;
    while (std::getline(stream, line)) {
        if (!headerSkipped) {
            EXPECT_EQ(line, "Available encodings are:");
            headerSkipped = true;
            continue;
        }
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    // Verify they are sorted
    for (size_t i = 1; i < lines.size(); ++i) {
        EXPECT_LE(lines[i - 1], lines[i])
            << "Encoding '" << lines[i - 1] << "' should come before '" << lines[i] << "'";
    }
}

// Test that the encoding names from getEncodingNames match what printEncodings outputs
TEST_F(PrintEncodingsTest_2718, OutputMatchesGetEncodingNames_2718) {
    std::vector<std::string> encNames = globalParams->getEncodingNames();
    std::ranges::sort(encNames);

    std::string output = captureOutput();

    // Build expected output
    std::string expected = "Available encodings are:\n";
    for (const auto &enc : encNames) {
        expected += enc + "\n";
    }

    EXPECT_EQ(output, expected);
}

// Test that printEncodings can be called multiple times without issues
TEST_F(PrintEncodingsTest_2718, MultipleCallsProduceSameOutput_2718) {
    std::string output1 = captureOutput();
    std::string output2 = captureOutput();
    EXPECT_EQ(output1, output2);
}

// Test that each encoding name appears exactly once in the output
TEST_F(PrintEncodingsTest_2718, NoDuplicateEncodings_2718) {
    std::string output = captureOutput();

    std::vector<std::string> lines;
    std::istringstream stream(output);
    std::string line;
    bool headerSkipped = false;
    while (std::getline(stream, line)) {
        if (!headerSkipped) {
            headerSkipped = true;
            continue;
        }
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    // Check for duplicates
    std::vector<std::string> sorted = lines;
    std::sort(sorted.begin(), sorted.end());
    auto it = std::adjacent_find(sorted.begin(), sorted.end());
    EXPECT_EQ(it, sorted.end()) << "Duplicate encoding found: " << *it;
}

// Test that the number of encoding lines matches the count from getEncodingNames
TEST_F(PrintEncodingsTest_2718, EncodingCountMatchesGetEncodingNames_2718) {
    std::vector<std::string> encNames = globalParams->getEncodingNames();

    std::string output = captureOutput();

    std::istringstream stream(output);
    std::string line;
    int lineCount = 0;
    bool headerSkipped = false;
    while (std::getline(stream, line)) {
        if (!headerSkipped) {
            headerSkipped = true;
            continue;
        }
        if (!line.empty()) {
            lineCount++;
        }
    }

    EXPECT_EQ(static_cast<size_t>(lineCount), encNames.size());
}

// Test that header is always present even if there are encodings
TEST_F(PrintEncodingsTest_2718, HeaderAlwaysPresent_2718) {
    std::string output = captureOutput();
    EXPECT_NE(output.find("Available encodings are:"), std::string::npos);
}
