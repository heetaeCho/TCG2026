// File: ./TestProjects/ninja/tests/line_printer_test_112.cc

#include "gtest/gtest.h"
#include "line_printer.h"

#include <string>

class LinePrinterTest_112 : public ::testing::Test {
protected:
    LinePrinter printer_;
};

/**
 * Verify that set_smart_terminal(bool) is reflected by is_smart_terminal().
 */
TEST_F(LinePrinterTest_112, SmartTerminalSetterGetter_112) {
    // Set to true and verify getter.
    printer_.set_smart_terminal(true);
    EXPECT_TRUE(printer_.is_smart_terminal());

    // Set to false and verify getter.
    printer_.set_smart_terminal(false);
    EXPECT_FALSE(printer_.is_smart_terminal());
}

/**
 * Verify that multiple calls to set_smart_terminal behave consistently
 * and always reflect the last value passed in.
 */
TEST_F(LinePrinterTest_112, SmartTerminalMultipleChanges_112) {
    printer_.set_smart_terminal(true);
    EXPECT_TRUE(printer_.is_smart_terminal());

    printer_.set_smart_terminal(false);
    EXPECT_FALSE(printer_.is_smart_terminal());

    // Set back to true again to ensure it still works after toggling.
    printer_.set_smart_terminal(true);
    EXPECT_TRUE(printer_.is_smart_terminal());
}

/**
 * Verify that Print() accepts an empty string without throwing,
 * for both a normal line type and (if available) any other public LineType.
 * We treat LinePrinter as a black box and only assert that calls succeed.
 */
TEST_F(LinePrinterTest_112, PrintEmptyStringDoesNotThrow_112) {
    // We assume at least one valid LineType exists; use FULL if available.
    // If LineType has different enumerators in this codebase,
    // replace LinePrinter::FULL with an appropriate valid one.
    EXPECT_NO_THROW(printer_.Print(std::string(), LinePrinter::FULL));

    // Also try with a non-empty but minimal string, still focusing only
    // on "no exception" as observable behavior.
    EXPECT_NO_THROW(printer_.Print(std::string(""), LinePrinter::FULL));
}

/**
 * Verify that Print() and PrintOnNewLine() handle a long string and
 * different console lock states without throwing.
 *
 * We do NOT assume anything about where or how it prints (stdout/stderr/buffer),
 * only that the public functions are callable in these states.
 */
TEST_F(LinePrinterTest_112, PrintLongStringWithConsoleLockStates_112) {
    std::string large_text(10000, 'X');  // Boundary-like case: long string.

    // Default console lock state: should be callable.
    EXPECT_NO_THROW(printer_.Print(large_text, LinePrinter::FULL));
    EXPECT_NO_THROW(printer_.PrintOnNewLine(large_text));

    // When console is locked, calls should still be safe (no exceptions).
    printer_.SetConsoleLocked(true);
    EXPECT_NO_THROW(printer_.Print(large_text, LinePrinter::FULL));
    EXPECT_NO_THROW(printer_.PrintOnNewLine(large_text));

    // Unlock again and verify calls remain safe.
    printer_.SetConsoleLocked(false);
    EXPECT_NO_THROW(printer_.Print(large_text, LinePrinter::FULL));
    EXPECT_NO_THROW(printer_.PrintOnNewLine(large_text));
}

/**
 * Verify that supports_color() is callable and does not throw, and that
 * it remains callable after changing smart terminal and console lock states.
 *
 * We do NOT assert any specific value for supports_color(), since its
 * semantics may depend on environment or platform.
 */
TEST_F(LinePrinterTest_112, SupportsColorQueryInVariousStates_112) {
    // Default state.
    EXPECT_NO_THROW({
        (void)printer_.supports_color();
    });

    // After toggling smart terminal.
    printer_.set_smart_terminal(true);
    EXPECT_NO_THROW({
        (void)printer_.supports_color();
    });

    printer_.set_smart_terminal(false);
    EXPECT_NO_THROW({
        (void)printer_.supports_color();
    });

    // With console locked / unlocked.
    printer_.SetConsoleLocked(true);
    EXPECT_NO_THROW({
        (void)printer_.supports_color();
    });

    printer_.SetConsoleLocked(false);
    EXPECT_NO_THROW({
        (void)printer_.supports_color();
    });
}
