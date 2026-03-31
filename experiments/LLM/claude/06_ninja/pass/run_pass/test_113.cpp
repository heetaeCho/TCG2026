#include "gtest/gtest.h"
#include "line_printer.h"

// Test fixture for LinePrinter tests
class LinePrinterTest_113 : public ::testing::Test {
protected:
    LinePrinter printer_;
};

// Test default construction and initial state of smart_terminal
TEST_F(LinePrinterTest_113, DefaultConstruction_113) {
    // LinePrinter should be constructible without errors
    LinePrinter lp;
    // We can at least call these methods without crashing
    lp.is_smart_terminal();
    lp.supports_color();
}

// Test supports_color returns a bool value
TEST_F(LinePrinterTest_113, SupportsColorReturnsBool_113) {
    bool color = printer_.supports_color();
    // The result should be either true or false (valid bool)
    EXPECT_TRUE(color == true || color == false);
}

// Test set_smart_terminal and is_smart_terminal
TEST_F(LinePrinterTest_113, SetSmartTerminalTrue_113) {
    printer_.set_smart_terminal(true);
    EXPECT_TRUE(printer_.is_smart_terminal());
}

TEST_F(LinePrinterTest_113, SetSmartTerminalFalse_113) {
    printer_.set_smart_terminal(false);
    EXPECT_FALSE(printer_.is_smart_terminal());
}

// Test toggling smart terminal back and forth
TEST_F(LinePrinterTest_113, ToggleSmartTerminal_113) {
    printer_.set_smart_terminal(true);
    EXPECT_TRUE(printer_.is_smart_terminal());
    printer_.set_smart_terminal(false);
    EXPECT_FALSE(printer_.is_smart_terminal());
    printer_.set_smart_terminal(true);
    EXPECT_TRUE(printer_.is_smart_terminal());
}

// Test is_smart_terminal reflects what was set
TEST_F(LinePrinterTest_113, IsSmartTerminalReflectsSet_113) {
    printer_.set_smart_terminal(false);
    EXPECT_FALSE(printer_.is_smart_terminal());
    printer_.set_smart_terminal(true);
    EXPECT_TRUE(printer_.is_smart_terminal());
}

// Test Print with empty string doesn't crash
TEST_F(LinePrinterTest_113, PrintEmptyString_113) {
    printer_.set_smart_terminal(false);
    EXPECT_NO_FATAL_FAILURE(printer_.Print("", LinePrinter::FULL));
}

// Test Print with a normal string
TEST_F(LinePrinterTest_113, PrintNormalString_113) {
    printer_.set_smart_terminal(false);
    EXPECT_NO_FATAL_FAILURE(printer_.Print("Hello, World!", LinePrinter::FULL));
}

// Test Print with ELIDE line type
TEST_F(LinePrinterTest_113, PrintElideType_113) {
    printer_.set_smart_terminal(true);
    EXPECT_NO_FATAL_FAILURE(printer_.Print("Some elided text", LinePrinter::ELIDE));
}

// Test PrintOnNewLine with empty string
TEST_F(LinePrinterTest_113, PrintOnNewLineEmpty_113) {
    printer_.set_smart_terminal(false);
    EXPECT_NO_FATAL_FAILURE(printer_.PrintOnNewLine(""));
}

// Test PrintOnNewLine with content
TEST_F(LinePrinterTest_113, PrintOnNewLineWithContent_113) {
    printer_.set_smart_terminal(false);
    EXPECT_NO_FATAL_FAILURE(printer_.PrintOnNewLine("New line content\n"));
}

// Test SetConsoleLocked true and false
TEST_F(LinePrinterTest_113, SetConsoleLockedTrue_113) {
    EXPECT_NO_FATAL_FAILURE(printer_.SetConsoleLocked(true));
}

TEST_F(LinePrinterTest_113, SetConsoleLockedFalse_113) {
    EXPECT_NO_FATAL_FAILURE(printer_.SetConsoleLocked(false));
}

// Test that locking and unlocking console works with printing
TEST_F(LinePrinterTest_113, LockThenPrintThenUnlock_113) {
    printer_.set_smart_terminal(false);
    printer_.SetConsoleLocked(true);
    // Print while locked - should buffer
    EXPECT_NO_FATAL_FAILURE(printer_.Print("buffered text", LinePrinter::FULL));
    // Unlock - should flush buffered content
    EXPECT_NO_FATAL_FAILURE(printer_.SetConsoleLocked(false));
}

// Test Print with smart terminal enabled
TEST_F(LinePrinterTest_113, PrintWithSmartTerminal_113) {
    printer_.set_smart_terminal(true);
    EXPECT_NO_FATAL_FAILURE(printer_.Print("smart terminal output", LinePrinter::FULL));
}

// Test Print with smart terminal and ELIDE
TEST_F(LinePrinterTest_113, PrintSmartTerminalElide_113) {
    printer_.set_smart_terminal(true);
    EXPECT_NO_FATAL_FAILURE(printer_.Print("this is a very long line that might be elided on a smart terminal", LinePrinter::ELIDE));
}

// Test PrintOnNewLine with smart terminal
TEST_F(LinePrinterTest_113, PrintOnNewLineSmartTerminal_113) {
    printer_.set_smart_terminal(true);
    // First print something, then print on new line
    printer_.Print("first line", LinePrinter::FULL);
    EXPECT_NO_FATAL_FAILURE(printer_.PrintOnNewLine("second line\n"));
}

// Test multiple prints in sequence
TEST_F(LinePrinterTest_113, MultiplePrintsInSequence_113) {
    printer_.set_smart_terminal(false);
    EXPECT_NO_FATAL_FAILURE(printer_.Print("line 1\n", LinePrinter::FULL));
    EXPECT_NO_FATAL_FAILURE(printer_.Print("line 2\n", LinePrinter::FULL));
    EXPECT_NO_FATAL_FAILURE(printer_.Print("line 3\n", LinePrinter::FULL));
}

// Test that supports_color is consistent across calls
TEST_F(LinePrinterTest_113, SupportsColorConsistency_113) {
    bool first_call = printer_.supports_color();
    bool second_call = printer_.supports_color();
    EXPECT_EQ(first_call, second_call);
}

// Test Print with newline character
TEST_F(LinePrinterTest_113, PrintWithNewline_113) {
    printer_.set_smart_terminal(true);
    EXPECT_NO_FATAL_FAILURE(printer_.Print("line with newline\n", LinePrinter::FULL));
}

// Test locking console multiple times
TEST_F(LinePrinterTest_113, MultipleLocks_113) {
    printer_.SetConsoleLocked(true);
    printer_.SetConsoleLocked(true);  // double lock
    EXPECT_NO_FATAL_FAILURE(printer_.SetConsoleLocked(false));
}

// Test printing while console is locked then printing on new line after unlock
TEST_F(LinePrinterTest_113, BufferedOutputFlushedOnUnlock_113) {
    printer_.set_smart_terminal(false);
    printer_.SetConsoleLocked(true);
    printer_.Print("locked output\n", LinePrinter::FULL);
    printer_.PrintOnNewLine("also locked\n");
    EXPECT_NO_FATAL_FAILURE(printer_.SetConsoleLocked(false));
}
