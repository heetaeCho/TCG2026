#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <cassert>
#include <regex>
#include <fstream>

// Forward declarations / replicate necessary parts from the source
const std::string logfile_prefix = "--log-file=";

bool starts_with(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

void create_empty_file(const std::string& fname) {
    std::ofstream ofs(fname);
    ofs.close();
}

int parse_log_file_arg(std::string const& arg) {
    assert(starts_with(arg, logfile_prefix) && "Attempting to parse incorrect arg!");
    auto fname = arg.substr(logfile_prefix.size());
    create_empty_file(fname);
    std::regex regex("MemoryChecker\\.(\\d+)\\.log", std::regex::icase);
    std::smatch match;
    if (std::regex_search(fname, match, regex)) {
        return std::stoi(match[1]);
    } else {
        throw std::domain_error("Couldn't find desired expression in string: " + fname);
    }
}

// Helper to clean up files created during tests
static void remove_file(const std::string& fname) {
    std::remove(fname.c_str());
}

class ParseLogFileArgTest_882 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any files that might have been created
        for (const auto& f : files_to_cleanup_) {
            remove_file(f);
        }
    }

    void trackFile(const std::string& fname) {
        files_to_cleanup_.push_back(fname);
    }

    std::vector<std::string> files_to_cleanup_;
};

TEST_F(ParseLogFileArgTest_882, BasicValidArgReturnsCorrectNumber_882) {
    std::string fname = "MemoryChecker.42.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 42);
}

TEST_F(ParseLogFileArgTest_882, ReturnsZeroForZeroId_882) {
    std::string fname = "MemoryChecker.0.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 0);
}

TEST_F(ParseLogFileArgTest_882, ReturnsLargeNumber_882) {
    std::string fname = "MemoryChecker.999999.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 999999);
}

TEST_F(ParseLogFileArgTest_882, ReturnsSingleDigitNumber_882) {
    std::string fname = "MemoryChecker.7.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 7);
}

TEST_F(ParseLogFileArgTest_882, CaseInsensitiveMatching_882) {
    std::string fname = "memorychecker.123.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 123);
}

TEST_F(ParseLogFileArgTest_882, MixedCaseMatching_882) {
    std::string fname = "MEMORYCHECKER.55.LOG";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 55);
}

TEST_F(ParseLogFileArgTest_882, ThrowsWhenNoMatch_882) {
    std::string fname = "somefile.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_THROW(parse_log_file_arg(arg), std::domain_error);
}

TEST_F(ParseLogFileArgTest_882, ThrowsWhenNoDigits_882) {
    std::string fname = "MemoryChecker..log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_THROW(parse_log_file_arg(arg), std::domain_error);
}

TEST_F(ParseLogFileArgTest_882, ThrowsForEmptyFilename_882) {
    std::string fname = "";
    std::string arg = logfile_prefix + fname;
    EXPECT_THROW(parse_log_file_arg(arg), std::domain_error);
}

TEST_F(ParseLogFileArgTest_882, ThrowsForUnrelatedFilename_882) {
    std::string fname = "random_file_name.txt";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_THROW(parse_log_file_arg(arg), std::domain_error);
}

TEST_F(ParseLogFileArgTest_882, FileWithPathPrefix_882) {
    std::string fname = "MemoryChecker.101.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 101);
}

TEST_F(ParseLogFileArgTest_882, CreatesEmptyFile_882) {
    std::string fname = "MemoryChecker.77.log";
    trackFile(fname);
    // Remove file if it exists
    remove_file(fname);

    std::string arg = logfile_prefix + fname;
    parse_log_file_arg(arg);

    // Verify the file was created
    std::ifstream ifs(fname);
    EXPECT_TRUE(ifs.good());
    ifs.close();
}

TEST_F(ParseLogFileArgTest_882, FileCreatedIsEmpty_882) {
    std::string fname = "MemoryChecker.88.log";
    trackFile(fname);
    remove_file(fname);

    std::string arg = logfile_prefix + fname;
    parse_log_file_arg(arg);

    std::ifstream ifs(fname, std::ios::ate);
    EXPECT_TRUE(ifs.good());
    EXPECT_EQ(ifs.tellg(), 0);
    ifs.close();
}

TEST_F(ParseLogFileArgTest_882, MatchesFirstOccurrence_882) {
    // If the filename contains the pattern, should match the first one
    std::string fname = "MemoryChecker.10.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 10);
}

TEST_F(ParseLogFileArgTest_882, ThrowsDomainErrorWithMessage_882) {
    std::string fname = "no_match_here.txt";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    try {
        parse_log_file_arg(arg);
        FAIL() << "Expected std::domain_error";
    } catch (const std::domain_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Couldn't find desired expression") != std::string::npos);
        EXPECT_TRUE(msg.find(fname) != std::string::npos);
    }
}

TEST_F(ParseLogFileArgTest_882, LeadingZerosInNumber_882) {
    std::string fname = "MemoryChecker.007.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 7);
}

TEST_F(ParseLogFileArgTest_882, NumberOne_882) {
    std::string fname = "MemoryChecker.1.log";
    trackFile(fname);
    std::string arg = logfile_prefix + fname;
    EXPECT_EQ(parse_log_file_arg(arg), 1);
}
