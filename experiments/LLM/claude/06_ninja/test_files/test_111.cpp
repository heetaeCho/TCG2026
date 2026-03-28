#include "gtest/gtest.h"
#include "line_printer.h"

// Test fixture for LinePrinter tests
class LinePrinterTest_111 : public ::testing::Test {
 protected:
  LinePrinter printer_;
};

// Test that is_smart_terminal returns a valid boolean after construction
TEST_F(LinePrinterTest_111, DefaultConstruction_111) {
  // After default construction, is_smart_terminal() should return some boolean value
  // (depends on whether the terminal is actually smart, but it should not crash)
  bool result = printer_.is_smart_terminal();
  EXPECT_TRUE(result == true || result == false);
}

// Test that set_smart_terminal(true) makes is_smart_terminal() return true
TEST_F(LinePrinterTest_111, SetSmartTerminalTrue_111) {
  printer_.set_smart_terminal(true);
  EXPECT_TRUE(printer_.is_smart_terminal());
}

// Test that set_smart_terminal(false) makes is_smart_terminal() return false
TEST_F(LinePrinterTest_111, SetSmartTerminalFalse_111) {
  printer_.set_smart_terminal(false);
  EXPECT_FALSE(printer_.is_smart_terminal());
}

// Test toggling smart terminal from true to false
TEST_F(LinePrinterTest_111, ToggleSmartTerminalTrueToFalse_111) {
  printer_.set_smart_terminal(true);
  EXPECT_TRUE(printer_.is_smart_terminal());
  printer_.set_smart_terminal(false);
  EXPECT_FALSE(printer_.is_smart_terminal());
}

// Test toggling smart terminal from false to true
TEST_F(LinePrinterTest_111, ToggleSmartTerminalFalseToTrue_111) {
  printer_.set_smart_terminal(false);
  EXPECT_FALSE(printer_.is_smart_terminal());
  printer_.set_smart_terminal(true);
  EXPECT_TRUE(printer_.is_smart_terminal());
}

// Test that setting smart terminal multiple times to the same value is stable
TEST_F(LinePrinterTest_111, SetSmartTerminalRepeatedTrue_111) {
  printer_.set_smart_terminal(true);
  printer_.set_smart_terminal(true);
  printer_.set_smart_terminal(true);
  EXPECT_TRUE(printer_.is_smart_terminal());
}

TEST_F(LinePrinterTest_111, SetSmartTerminalRepeatedFalse_111) {
  printer_.set_smart_terminal(false);
  printer_.set_smart_terminal(false);
  printer_.set_smart_terminal(false);
  EXPECT_FALSE(printer_.is_smart_terminal());
}

// Test supports_color returns a valid boolean
TEST_F(LinePrinterTest_111, SupportsColorReturnsBool_111) {
  bool result = printer_.supports_color();
  EXPECT_TRUE(result == true || result == false);
}

// Test that Print does not crash with an empty string
TEST_F(LinePrinterTest_111, PrintEmptyString_111) {
  printer_.set_smart_terminal(false);
  EXPECT_NO_FATAL_FAILURE(printer_.Print("", LinePrinter::FULL));
}

// Test that Print does not crash with a normal string
TEST_F(LinePrinterTest_111, PrintNormalString_111) {
  printer_.set_smart_terminal(false);
  EXPECT_NO_FATAL_FAILURE(printer_.Print("Hello World", LinePrinter::FULL));
}

// Test that Print with ELIDE type does not crash
TEST_F(LinePrinterTest_111, PrintElideType_111) {
  printer_.set_smart_terminal(false);
  EXPECT_NO_FATAL_FAILURE(printer_.Print("Some output", LinePrinter::ELIDE));
}

// Test that PrintOnNewLine does not crash with empty string
TEST_F(LinePrinterTest_111, PrintOnNewLineEmpty_111) {
  printer_.set_smart_terminal(false);
  EXPECT_NO_FATAL_FAILURE(printer_.PrintOnNewLine(""));
}

// Test that PrintOnNewLine does not crash with normal string
TEST_F(LinePrinterTest_111, PrintOnNewLineNormal_111) {
  printer_.set_smart_terminal(false);
  EXPECT_NO_FATAL_FAILURE(printer_.PrintOnNewLine("New line output\n"));
}

// Test that SetConsoleLocked does not crash
TEST_F(LinePrinterTest_111, SetConsoleLockedTrue_111) {
  EXPECT_NO_FATAL_FAILURE(printer_.SetConsoleLocked(true));
}

TEST_F(LinePrinterTest_111, SetConsoleLockedFalse_111) {
  EXPECT_NO_FATAL_FAILURE(printer_.SetConsoleLocked(false));
}

// Test that locking console and then printing does not crash
TEST_F(LinePrinterTest_111, PrintWhileConsoleLocked_111) {
  printer_.set_smart_terminal(false);
  printer_.SetConsoleLocked(true);
  EXPECT_NO_FATAL_FAILURE(printer_.Print("locked print", LinePrinter::FULL));
  printer_.SetConsoleLocked(false);
}

// Test that unlocking console flushes buffered output without crash
TEST_F(LinePrinterTest_111, UnlockConsoleAfterPrint_111) {
  printer_.set_smart_terminal(false);
  printer_.SetConsoleLocked(true);
  printer_.Print("buffered", LinePrinter::FULL);
  EXPECT_NO_FATAL_FAILURE(printer_.SetConsoleLocked(false));
}

// Test Print with smart terminal enabled
TEST_F(LinePrinterTest_111, PrintWithSmartTerminal_111) {
  printer_.set_smart_terminal(true);
  EXPECT_NO_FATAL_FAILURE(printer_.Print("smart output", LinePrinter::FULL));
}

// Test PrintOnNewLine with smart terminal enabled
TEST_F(LinePrinterTest_111, PrintOnNewLineSmartTerminal_111) {
  printer_.set_smart_terminal(true);
  EXPECT_NO_FATAL_FAILURE(printer_.PrintOnNewLine("smart new line\n"));
}

// Test Print with a very long string
TEST_F(LinePrinterTest_111, PrintLongString_111) {
  printer_.set_smart_terminal(false);
  std::string long_str(10000, 'x');
  EXPECT_NO_FATAL_FAILURE(printer_.Print(long_str, LinePrinter::FULL));
}

// Test Print with ELIDE on smart terminal (should elide long lines)
TEST_F(LinePrinterTest_111, PrintElideSmartTerminal_111) {
  printer_.set_smart_terminal(true);
  std::string long_str(10000, 'a');
  EXPECT_NO_FATAL_FAILURE(printer_.Print(long_str, LinePrinter::ELIDE));
}

// Test multiple sequential prints
TEST_F(LinePrinterTest_111, MultipleSequentialPrints_111) {
  printer_.set_smart_terminal(false);
  for (int i = 0; i < 100; ++i) {
    EXPECT_NO_FATAL_FAILURE(printer_.Print("line " + std::to_string(i), LinePrinter::FULL));
  }
}

// Test PrintOnNewLine after Print
TEST_F(LinePrinterTest_111, PrintOnNewLineAfterPrint_111) {
  printer_.set_smart_terminal(true);
  printer_.Print("first line", LinePrinter::FULL);
  EXPECT_NO_FATAL_FAILURE(printer_.PrintOnNewLine("second line\n"));
}
