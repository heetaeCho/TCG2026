#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "line_printer.h"



class LinePrinterTest_111 : public ::testing::Test {

protected:

    LinePrinter printer_;

};



TEST_F(LinePrinterTest_111, PrintDoesNotThrowOnNormalInput_111) {

    EXPECT_NO_THROW(printer_.Print("Hello, world!", LineType::kDefault));

}



TEST_F(LinePrinterTest_111, PrintOnNewLineDoesNotThrowOnNormalInput_111) {

    EXPECT_NO_THROW(printer_.PrintOnNewLine("Hello, world!"));

}



TEST_F(LinePrinterTest_111, SetConsoleLockedDoesNotThrowOnNormalInput_111) {

    EXPECT_NO_THROW(printer_.SetConsoleLocked(true));

    EXPECT_NO_THROW(printer_.SetConsoleLocked(false));

}



TEST_F(LinePrinterTest_111, IsSmartTerminalReturnsConsistentValues_111) {

    printer_.set_smart_terminal(true);

    EXPECT_TRUE(printer_.is_smart_terminal());

    printer_.set_smart_terminal(false);

    EXPECT_FALSE(printer_.is_smart_terminal());

}



TEST_F(LinePrinterTest_111, SupportsColorInitiallyFalse_111) {

    EXPECT_FALSE(printer_.supports_color());

}



TEST_F(LinePrinterTest_111, SetSmartTerminalBoundaryCondition_111) {

    printer_.set_smart_terminal(true);

    EXPECT_TRUE(printer_.is_smart_terminal());

    printer_.set_smart_terminal(false);

    EXPECT_FALSE(printer_.is_smart_terminal());

}
