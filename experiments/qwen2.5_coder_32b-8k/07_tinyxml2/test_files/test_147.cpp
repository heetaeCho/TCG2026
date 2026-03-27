#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_147 : public ::testing::Test {

protected:

    XMLPrinter printer;

};



TEST_F(XMLPrinterTest_147, VisitExit_ReturnsTrue_147) {

    XMLDocument doc;

    EXPECT_TRUE(printer.VisitExit(doc));

}



// Since the function does not modify any observable state or interact with external components,

// there are no additional boundary conditions, exceptional cases, or external interactions to test.
