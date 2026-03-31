#include "gtest/gtest.h"
#include "line_printer.h"

class LinePrinterTest_112 : public ::testing::Test {
 protected:
  LinePrinter printer_;
};

// Test default construction - smart_terminal state may vary by environment,
// but we can at least construct and query it.
TEST_F(LinePrinterTest_112, DefaultConstruction_112) {
  LinePrinter lp;
  // Just verify we can query these without crashing
  bool smart = lp.is_smart_terminal();
  bool color = lp.supports_color();
  (void)smart;
  (void)color;
}

// Test set_smart_terminal sets the value retrievable by is_smart_terminal
TEST_F(LinePrinterTest_112, SetSmartTerminalTrue_112) {
  printer_.set_smart_terminal(true);
  EXPECT_TRUE(printer_.is_smart_terminal());
}

TEST_F(LinePrinterTest_112, SetSmartTerminalFalse_112) {
  printer_.set_smart_terminal(false);
  EXPECT_FALSE(printer_.is_smart_terminal());
}

// Test toggling smart terminal back and forth
TEST_F(LinePrinterTest_112, ToggleSmartTerminal_112) {
  printer_.set_smart_terminal(true);
  EXPECT_TRUE(printer_.is_smart_terminal());
  printer_.set_smart_terminal(false);
  EXPECT_FALSE(printer_.is_smart_terminal());
  printer_.set_smart_terminal(true);
  EXPECT_TRUE(printer_.is_smart_terminal());
}

// Test supports_color is queryable (read-only, set at construction)
TEST_F(LinePrinterTest_112, SupportsColorQueryable_112) {
  // supports_color is determined at construction time; just verify it doesn't crash
  bool color = printer_.supports_color();
  (void)color;
}

// Test Print with empty string in non-smart terminal mode
TEST_F(LinePrinterTest_112, PrintEmptyStringNonSmart_112) {
  printer_.set_smart_terminal(false);
  // Should not crash
  printer_.Print("", LinePrinter::FULL);
}

// Test Print with a normal string in non-smart terminal mode
TEST_F(LinePrinterTest_112, PrintNormalStringNonSmart_112) {
  printer_.set_smart_terminal(false);
  printer_.Print("Building something...", LinePrinter::FULL);
}

// Test Print with ELIDE line type in non-smart terminal mode
TEST_F(LinePrinterTest_112, PrintElideNonSmart_112) {
  printer_.set_smart_terminal(false);
  printer_.Print("Building something...", LinePrinter::ELIDE);
}

// Test Print in smart terminal mode
TEST_F(LinePrinterTest_112, PrintSmartTerminal_112) {
  printer_.set_smart_terminal(true);
  printer_.Print("Building target...", LinePrinter::FULL);
}

// Test Print with ELIDE in smart terminal mode
TEST_F(LinePrinterTest_112, PrintElideSmartTerminal_112) {
  printer_.set_smart_terminal(true);
  printer_.Print("Building target...", LinePrinter::ELIDE);
}

// Test PrintOnNewLine with empty string
TEST_F(LinePrinterTest_112, PrintOnNewLineEmpty_112) {
  printer_.set_smart_terminal(false);
  printer_.PrintOnNewLine("");
}

// Test PrintOnNewLine with a normal string
TEST_F(LinePrinterTest_112, PrintOnNewLineNormal_112) {
  printer_.set_smart_terminal(false);
  printer_.PrintOnNewLine("Some output\n");
}

// Test PrintOnNewLine in smart terminal mode
TEST_F(LinePrinterTest_112, PrintOnNewLineSmartTerminal_112) {
  printer_.set_smart_terminal(true);
  printer_.PrintOnNewLine("Some output\n");
}

// Test SetConsoleLocked locks and unlocks
TEST_F(LinePrinterTest_112, SetConsoleLockedTrue_112) {
  printer_.set_smart_terminal(false);
  printer_.SetConsoleLocked(true);
  // While locked, Print should buffer output
  printer_.Print("Buffered output", LinePrinter::FULL);
}

TEST_F(LinePrinterTest_112, SetConsoleLockedFalse_112) {
  printer_.set_smart_terminal(false);
  printer_.SetConsoleLocked(true);
  printer_.Print("Buffered output", LinePrinter::FULL);
  // Unlocking should flush the buffer
  printer_.SetConsoleLocked(false);
}

// Test locking and unlocking with smart terminal
TEST_F(LinePrinterTest_112, SetConsoleLockedSmartTerminal_112) {
  printer_.set_smart_terminal(true);
  printer_.SetConsoleLocked(true);
  printer_.Print("Buffered smart", LinePrinter::ELIDE);
  printer_.SetConsoleLocked(false);
}

// Test multiple prints while console is locked
TEST_F(LinePrinterTest_112, MultiplePrintsWhileLocked_112) {
  printer_.set_smart_terminal(false);
  printer_.SetConsoleLocked(true);
  printer_.Print("First", LinePrinter::FULL);
  printer_.Print("Second", LinePrinter::FULL);
  printer_.PrintOnNewLine("Third\n");
  printer_.SetConsoleLocked(false);
}

// Test Print after PrintOnNewLine
TEST_F(LinePrinterTest_112, PrintAfterPrintOnNewLine_112) {
  printer_.set_smart_terminal(true);
  printer_.Print("First line", LinePrinter::ELIDE);
  printer_.PrintOnNewLine("New line content\n");
  printer_.Print("Second line", LinePrinter::ELIDE);
}

// Test sequential set_smart_terminal with same value
TEST_F(LinePrinterTest_112, SetSmartTerminalIdempotent_112) {
  printer_.set_smart_terminal(true);
  printer_.set_smart_terminal(true);
  EXPECT_TRUE(printer_.is_smart_terminal());
  printer_.set_smart_terminal(false);
  printer_.set_smart_terminal(false);
  EXPECT_FALSE(printer_.is_smart_terminal());
}

// Test Print with very long string
TEST_F(LinePrinterTest_112, PrintVeryLongString_112) {
  printer_.set_smart_terminal(true);
  std::string long_str(10000, 'x');
  printer_.Print(long_str, LinePrinter::ELIDE);
}

// Test PrintOnNewLine with string containing no newline
TEST_F(LinePrinterTest_112, PrintOnNewLineNoNewline_112) {
  printer_.set_smart_terminal(false);
  printer_.PrintOnNewLine("no newline at end");
}

// Test lock/unlock without any prints in between
TEST_F(LinePrinterTest_112, LockUnlockWithoutPrint_112) {
  printer_.SetConsoleLocked(true);
  printer_.SetConsoleLocked(false);
}

// Test Print with newline characters embedded
TEST_F(LinePrinterTest_112, PrintWithEmbeddedNewlines_112) {
  printer_.set_smart_terminal(false);
  printer_.Print("line1\nline2\nline3", LinePrinter::FULL);
}

// Test switching between smart and non-smart during operation
TEST_F(LinePrinterTest_112, SwitchSmartTerminalDuringOperation_112) {
  printer_.set_smart_terminal(true);
  printer_.Print("Smart print", LinePrinter::ELIDE);
  printer_.set_smart_terminal(false);
  printer_.Print("Non-smart print", LinePrinter::FULL);
  printer_.set_smart_terminal(true);
  printer_.PrintOnNewLine("Back to smart\n");
}
