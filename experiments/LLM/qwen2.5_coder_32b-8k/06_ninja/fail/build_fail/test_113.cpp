#include <gtest/gtest.h>

#include "line_printer.h"



class LinePrinterTest_113 : public ::testing::Test {

protected:

    LinePrinter line_printer;

};



TEST_F(LinePrinterTest_113, SupportsColor_DefaultValue_113) {

    EXPECT_FALSE(line_printer.supports_color());

}



TEST_F(LinePrinterTest_113, PrintOnNewLine_NormalOperation_113) {

    // Since we cannot observe internal state directly, we can only test for interface compliance.

    line_printer.PrintOnNewLine("This is a test");

}



TEST_F(LinePrinterTest_113, SetConsoleLocked_UnlockedToLocked_113) {

    line_printer.SetConsoleLocked(true);

    // No observable behavior to verify, but the call should not cause issues

}



TEST_F(LinePrinterTest_113, SetConsoleLocked_LockedToUnlocked_113) {

    line_printer.SetConsoleLocked(false);

    // No observable behavior to verify, but the call should not cause issues

}



TEST_F(LinePrinterTest_113, Print_NormalOperation_113) {

    line_printer.Print("This is a test", LineType::kNormal);

    // No observable behavior to verify, but the call should not cause issues

}



TEST_F(LinePrinterTest_113, IsSmartTerminal_DefaultValue_113) {

    EXPECT_FALSE(line_printer.is_smart_terminal());

}



TEST_F(LinePrinterTest_113, SetSmartTerminal_SetTrue_113) {

    line_printer.set_smart_terminal(true);

    // No observable behavior to verify, but the call should not cause issues

}



TEST_F(LinePrinterTest_113, SetSmartTerminal_SetFalse_113) {

    line_printer.set_smart_terminal(false);

    // No observable behavior to verify, but the call should not cause issues

}
