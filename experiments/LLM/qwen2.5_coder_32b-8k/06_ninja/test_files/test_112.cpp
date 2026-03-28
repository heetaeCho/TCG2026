#include <gtest/gtest.h>

#include "line_printer.h"



class LinePrinterTest_112 : public ::testing::Test {

protected:

    LinePrinter line_printer_;

};



TEST_F(LinePrinterTest_112, SetSmartTerminalAndGetSmartTerminal_NormalOperation_112) {

    // Test normal operation of set_smart_terminal and is_smart_terminal

    line_printer_.set_smart_terminal(true);

    EXPECT_TRUE(line_printer_.is_smart_terminal());

    

    line_printer_.set_smart_terminal(false);

    EXPECT_FALSE(line_printer_.is_smart_terminal());

}



TEST_F(LinePrinterTest_112, SetSmartTerminalBoundaryConditions_112) {

    // Test boundary conditions by setting the terminal state multiple times

    line_printer_.set_smart_terminal(true);

    line_printer_.set_smart_terminal(true);

    EXPECT_TRUE(line_printer_.is_smart_terminal());



    line_printer_.set_smart_terminal(false);

    line_printer_.set_smart_terminal(false);

    EXPECT_FALSE(line_printer_.is_smart_terminal());

}



TEST_F(LinePrinterTest_112, SupportsColor_DefaultValue_112) {

    // Test the default value of supports_color

    EXPECT_FALSE(line_printer_.supports_color());  // Assuming it returns false by default if not set otherwise

}
