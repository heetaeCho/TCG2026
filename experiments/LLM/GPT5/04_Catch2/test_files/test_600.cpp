// tests/write_to_debug_console_test_600.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <string>

// Forward declare the function under test from the provided partial code.
namespace Catch {
    void writeToDebugConsole(std::string const& text);
}

// RAII helper to redirect std::cout to a stringstream during a test.
class CoutCapture {
public:
    CoutCapture() : oldBuf_(std::cout.rdbuf(ss_.rdbuf())) {}
    ~CoutCapture() { std::cout.rdbuf(oldBuf_); }

    std::string str() const { return ss_.str(); }
private:
    std::ostringstream ss_;
    std::streambuf* oldBuf_;
};

// Normal operation: writing plain text appears on the debug console.
TEST(WriteToDebugConsoleTest_600, WritesTextToConsole_600) {
    CoutCapture cap;
    const std::string msg = "hello, debug!";
    Catch::writeToDebugConsole(msg);
    EXPECT_EQ(cap.str(), msg);
}

// Boundary: empty string should not write anything.
TEST(WriteToDebugConsoleTest_600, EmptyStringProducesNoOutput_600) {
    CoutCapture cap;
    const std::string msg = "";
    Catch::writeToDebugConsole(msg);
    EXPECT_EQ(cap.str(), "");
}

// Formatting preservation: newlines and spaces are preserved as-is.
TEST(WriteToDebugConsoleTest_600, PreservesNewlinesAndSpaces_600) {
    CoutCapture cap;
    const std::string msg = "line 1\n  line 2\nline 3  ";
    Catch::writeToDebugConsole(msg);
    EXPECT_EQ(cap.str(), msg);
}

// Sequential calls: outputs are appended in order.
TEST(WriteToDebugConsoleTest_600, MultipleWritesAppend_600) {
    CoutCapture cap;
    const std::string first = "first";
    const std::string second = " second";
    Catch::writeToDebugConsole(first);
    Catch::writeToDebugConsole(second);
    EXPECT_EQ(cap.str(), first + second);
}

// Large input: sufficiently large text is written completely.
TEST(WriteToDebugConsoleTest_600, LargeInputIsFullyWritten_600) {
    CoutCapture cap;
    const size_t N = 100000; // 100k chars
    std::string big(N, 'x');
    Catch::writeToDebugConsole(big);
    const std::string out = cap.str();
    ASSERT_EQ(out.size(), N);
    // Spot-check a few positions to avoid O(N) compare costs beyond size check
    EXPECT_EQ(out.front(), 'x');
    EXPECT_EQ(out.back(), 'x');
    EXPECT_EQ(out.substr(0, 10), std::string(10, 'x'));
}
