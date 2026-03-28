// File: ./TestProjects/ninja/tests/line_printer_test_111.cc

#include "gtest/gtest.h"
#include "line_printer.h"

class LinePrinterTest_111 : public ::testing::Test {
protected:
  LinePrinter printer_;
};

// Basic getter/setter behavior for smart terminal flag.
TEST_F(LinePrinterTest_111, SmartTerminalSetterGetter_111) {
  printer_.set_smart_terminal(true);
  EXPECT_TRUE(printer_.is_smart_terminal());

  printer_.set_smart_terminal(false);
  EXPECT_FALSE(printer_.is_smart_terminal());
}

// Printing should not change the smart terminal flag.
TEST_F(LinePrinterTest_111, SmartTerminalUnaffectedByPrint_111) {
  printer_.set_smart_terminal(true);
  LinePrinter::LineType type = static_cast<LinePrinter::LineType>(0);

  printer_.Print("some text", type);
  EXPECT_TRUE(printer_.is_smart_terminal());

  printer_.Print("", type);  // empty string boundary
  EXPECT_TRUE(printer_.is_smart_terminal());
}

// PrintOnNewLine should not change the smart terminal flag.
TEST_F(LinePrinterTest_111, SmartTerminalUnaffectedByPrintOnNewLine_111) {
  printer_.set_smart_terminal(false);

  printer_.PrintOnNewLine("line");
  EXPECT_FALSE(printer_.is_smart_terminal());

  printer_.PrintOnNewLine("");  // empty string boundary
  EXPECT_FALSE(printer_.is_smart_terminal());
}

// Locking/unlocking the console should not affect smart_terminal_.
TEST_F(LinePrinterTest_111, SetConsoleLockedDoesNotChangeSmartTerminal_111) {
  printer_.set_smart_terminal(true);

  printer_.SetConsoleLocked(true);
  EXPECT_TRUE(printer_.is_smart_terminal());

  printer_.SetConsoleLocked(false);
  EXPECT_TRUE(printer_.is_smart_terminal());
}

// supports_color() should be stable across multiple calls.
TEST_F(LinePrinterTest_111, SupportsColorIsStableAcrossCalls_111) {
  bool first = printer_.supports_color();
  bool second = printer_.supports_color();
  bool third = printer_.supports_color();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

// Changing smart terminal / printing should not change supports_color().
TEST_F(LinePrinterTest_111, SupportsColorUnaffectedBySmartTerminalAndPrint_111) {
  bool initial = printer_.supports_color();
  LinePrinter::LineType type = static_cast<LinePrinter::LineType>(0);

  // Change smart-terminal state and perform various prints.
  printer_.set_smart_terminal(true);
  printer_.Print("hello", type);
  printer_.PrintOnNewLine("world");

  printer_.set_smart_terminal(false);
  printer_.Print("", type);           // empty boundary
  printer_.PrintOnNewLine("");        // empty boundary

  EXPECT_EQ(initial, printer_.supports_color());
}

// Print and PrintOnNewLine should handle long strings without errors.
TEST_F(LinePrinterTest_111, HandlesLongStringsWithoutError_111) {
  LinePrinter::LineType type = static_cast<LinePrinter::LineType>(0);
  std::string long_text(4096, 'x');   // reasonably long line

  // If these calls throw or crash, the test will fail.
  printer_.Print(long_text, type);
  printer_.PrintOnNewLine(long_text);

  SUCCEED();  // Explicitly mark the test as passed if we got here.
}
