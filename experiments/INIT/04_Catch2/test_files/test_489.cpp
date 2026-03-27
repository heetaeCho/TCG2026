// tests/source_line_info_ostream_tests_489.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <limits>

// Include the provided interface
#include "catch2/internal/catch_source_line_info.hpp"

namespace {

// Helper to build the expected string depending on platform formatting
static std::string ExpectedFormatted(const char* file, std::size_t line) {
    std::ostringstream oss;
#ifndef __GNUG__
    // Non-GNUC format: file(line)
    oss << file << '(' << line << ')';
#else
    // GNUC format: file:line
    oss << file << ':' << line;
#endif
    return oss.str();
}

} // namespace

// 1) Normal operation: basic file + line formatting
TEST(SourceLineInfoOstreamTest_489, FormatsFileAndLine_489) {
    const char* file = "path/to/file.cpp";
    const std::size_t line = 42;
    Catch::SourceLineInfo info{file, line};

    std::ostringstream oss;
    oss << info;

    EXPECT_EQ(oss.str(), ExpectedFormatted(file, line));
}

// 2) Normal operation: returned stream reference supports chaining
TEST(SourceLineInfoOstreamTest_489, SupportsChainedInsertion_489) {
    const char* file = "main.cc";
    const std::size_t line = 7;
    Catch::SourceLineInfo info{file, line};

    std::ostringstream oss;
    // Validate that we can immediately chain more output after inserting info
    oss << info << " [end]";

    std::ostringstream expected;
#ifndef __GNUG__
    expected << file << '(' << line << ')' << " [end]";
#else
    expected << file << ':' << line << " [end]";
#endif

    EXPECT_EQ(oss.str(), expected.str());
}

// 3) Boundary condition: empty filename should still format correctly
TEST(SourceLineInfoOstreamTest_489, HandlesEmptyFilename_489) {
    const char* file = "";   // empty but valid C-string
    const std::size_t line = 1;
    Catch::SourceLineInfo info{file, line};

    std::ostringstream oss;
    oss << info;

    EXPECT_EQ(oss.str(), ExpectedFormatted(file, line));
}

// 4) Boundary condition: very large line number is streamed as-is
TEST(SourceLineInfoOstreamTest_489, HandlesLargeLineNumber_489) {
    const char* file = "big.cpp";
    const std::size_t line = std::numeric_limits<std::size_t>::max();
    Catch::SourceLineInfo info{file, line};

    std::ostringstream oss;
    oss << info;

    EXPECT_EQ(oss.str(), ExpectedFormatted(file, line));
}
