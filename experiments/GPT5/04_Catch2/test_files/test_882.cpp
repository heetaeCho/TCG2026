// File: tests/coverage_helper_parse_log_file_arg_882_test.cpp

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

// Forward-declare the function under test (treat implementation as a black box)
int parse_log_file_arg(std::string const& arg);

namespace fs = std::filesystem;

class ParseLogFileArgTest_882 : public ::testing::Test {
protected:
    // Helper: make an argument string with the expected prefix and a given file path
    static std::string MakeArg(const std::string& filePath) {
        // We do not include or rely on the internal global; we just pass the string arg.
        return std::string("--log-file=") + filePath;
    }

    // Helper: create a unique target file path inside the temp directory
    static fs::path UniqueLogPath(const std::string& stem) {
        fs::path tmp = fs::temp_directory_path();
        // Construct a unique filename to avoid collisions between parallel tests
        // Using PID and an incrementing counter in the name for uniqueness.
        static std::atomic<unsigned long> counter{0};
        unsigned long n = ++counter;
        return tmp / fs::path(stem + "_" + std::to_string(::getpid()) + "_" + std::to_string(n));
    }

    // Ensure the file does not exist before the test runs (best-effort cleanup).
    static void RemoveIfExists(const fs::path& p) {
        std::error_code ec;
        if (fs::exists(p, ec)) {
            fs::remove(p, ec);
        }
    }
};

// Normal operation: valid name, returns the numeric id and creates the file.
TEST_F(ParseLogFileArgTest_882, ReturnsIdAndCreatesFile_882) {
    fs::path p = UniqueLogPath("MemoryChecker.123.log");
    RemoveIfExists(p);

    const std::string arg = MakeArg(p.string());
    int id = parse_log_file_arg(arg);

    EXPECT_EQ(id, 123);
    std::error_code ec;
    EXPECT_TRUE(fs::exists(p, ec));
    // Best-effort cleanup
    RemoveIfExists(p);
}

// Normal operation: case-insensitive match on "MemoryChecker"
TEST_F(ParseLogFileArgTest_882, CaseInsensitiveMatch_882) {
    fs::path p = UniqueLogPath("memorychecker.77.log"); // lower-case
    RemoveIfExists(p);

    const std::string arg = MakeArg(p.string());
    int id = parse_log_file_arg(arg);

    EXPECT_EQ(id, 77);
    std::error_code ec;
    EXPECT_TRUE(fs::exists(p, ec));
    RemoveIfExists(p);
}

// Normal operation: leading zeros in the numeric part are accepted by stoi
TEST_F(ParseLogFileArgTest_882, LeadingZerosAreHandled_882) {
    fs::path p = UniqueLogPath("MemoryChecker.00042.log");
    RemoveIfExists(p);

    const std::string arg = MakeArg(p.string());
    int id = parse_log_file_arg(arg);

    EXPECT_EQ(id, 42);
    std::error_code ec;
    EXPECT_TRUE(fs::exists(p, ec));
    RemoveIfExists(p);
}

// Boundary-ish: file path contains directory components; id still extracted.
TEST_F(ParseLogFileArgTest_882, WorksWithDirectoriesInPath_882) {
    fs::path dir = fs::temp_directory_path() / "covhelper_882_dir";
    std::error_code ec;
    fs::create_directories(dir, ec); // ignore if already exists

    fs::path p = dir / "MemoryChecker.5.log";
    RemoveIfExists(p);

    const std::string arg = MakeArg(p.string());
    int id = parse_log_file_arg(arg);

    EXPECT_EQ(id, 5);
    EXPECT_TRUE(fs::exists(p, ec));
    RemoveIfExists(p);
}

// Observable behavior: if the filename does not match the expected pattern,
// the function throws std::domain_error. Note: The function creates the file
// before attempting to parse, so we verify the file side-effect too.
TEST_F(ParseLogFileArgTest_882, ThrowsWhenPatternNotFoundAndStillCreatesFile_882) {
    fs::path p = UniqueLogPath("not_a_match.txt");
    RemoveIfExists(p);

    const std::string arg = MakeArg(p.string());
    EXPECT_THROW({
        try {
            (void)parse_log_file_arg(arg);
        } catch (const std::domain_error&) {
            // Verify the file side effect occurred even on failure (observable behavior).
            std::error_code ec;
            EXPECT_TRUE(fs::exists(p, ec));
            // Re-throw to satisfy EXPECT_THROW
            throw;
        }
    }, std::domain_error);

    // Cleanup
    RemoveIfExists(p);
}

// Extra observable behavior: numeric id embedded within a larger name segment,
// still extracted because a regex *search* is used (not an anchored match).
TEST_F(ParseLogFileArgTest_882, ExtractsIdFromSubstringWithinFilename_882) {
    fs::path p = UniqueLogPath("prefix_MemoryChecker.901.log_suffix");
    RemoveIfExists(p);

    const std::string arg = MakeArg(p.string());
    int id = parse_log_file_arg(arg);

    EXPECT_EQ(id, 901);
    std::error_code ec;
    EXPECT_TRUE(fs::exists(p, ec));
    RemoveIfExists(p);
}
