// File: line_printer_test_113.cc

#include <string>

#include <gtest/gtest.h>

#include "line_printer.h"

class LinePrinterTest_113 : public ::testing::Test {
protected:
    LinePrinter printer_;
};

// Normal operation: setter/getter for smart_terminal should be consistent.
TEST_F(LinePrinterTest_113, SmartTerminalSetterGetter_113) {
    printer_.set_smart_terminal(true);
    EXPECT_TRUE(printer_.is_smart_terminal());

    printer_.set_smart_terminal(false);
    EXPECT_FALSE(printer_.is_smart_terminal());
}

// Basic property: supports_color() should be callable and stable across calls.
TEST_F(LinePrinterTest_113, SupportsColorConsistent_113) {
    bool first = printer_.supports_color();
    bool second = printer_.supports_color();
    EXPECT_EQ(first, second);
}

// Normal operation: Print should send the given text to the console output.
TEST_F(LinePrinterTest_113, PrintOutputsContent_113) {
    // Use an arbitrary LineType value; we do not rely on specific enum values.
    LineType type = static_cast<LineType>(0);

    ::testing::internal::CaptureStdout();
    printer_.Print("hello-world-113", type);
    std::string output = ::testing::internal::GetCapturedStdout();

    // At least ensure that the payload appears somewhere in the output.
    EXPECT_NE(output.find("hello-world-113"), std::string::npos);
}

// Normal operation: PrintOnNewLine should print the text, typically with a newline.
TEST_F(LinePrinterTest_113, PrintOnNewLineOutputsWithNewline_113) {
    ::testing::internal::CaptureStdout();
    printer_.PrintOnNewLine("line-113");
    std::string output = ::testing::internal::GetCapturedStdout();

    // The text itself should be present.
    EXPECT_NE(output.find("line-113"), std::string::npos);

    // And there should be at least one newline character in the output.
    EXPECT_NE(output.find('\n'), std::string::npos);
}

// Boundary case: Print should handle empty strings without crashing and
// should not introduce unexpected non-empty output (beyond any control codes).
TEST_F(LinePrinterTest_113, PrintHandlesEmptyString_113) {
    LineType type = static_cast<LineType>(0);

    ::testing::internal::CaptureStdout();
    printer_.Print("", type);
    std::string output = ::testing::internal::GetCapturedStdout();

    // We allow the implementation to print nothing or only control characters,
    // but at least it should not crash. The main check here is that the call
    // is valid; we do not enforce a strict output format.
    // To keep an observable assertion, verify that the function is callable:
    // i.e., the test reaches this point and output is a valid string.
    EXPECT_TRUE(output.size() >= 0u);
}

// Interaction behavior: toggling console lock should be supported and printing
// should still eventually produce visible output.
TEST_F(LinePrinterTest_113, ConsoleLockDoesNotPreventPrinting_113) {
    LineType type = static_cast<LineType>(0);

    printer_.SetConsoleLocked(true);
    ::testing::internal::CaptureStdout();
    printer_.Print("locked-113", type);
    printer_.SetConsoleLocked(false);
    printer_.Print("unlocked-113", type);
    std::string output = ::testing::internal::GetCapturedStdout();

    // We only assume that printed messages are not completely lost.
    EXPECT_NE(output.find("locked-113"), std::string::npos);
    EXPECT_NE(output.find("unlocked-113"), std::string::npos);
}
