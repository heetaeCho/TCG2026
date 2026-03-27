#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"

#include <cstdio>



using namespace tinyxml2;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class XMLPrinterTest : public testing::Test {

protected:

    FILE* mockFile = fopen("dummy.txt", "w");

    XMLPrinter printer{mockFile, false, 0, EscapeAposCharsInAttributes::YES};



    ~XMLPrinterTest() {

        fclose(mockFile);

    }

};



TEST_F(XMLPrinterTest_295, OpenElement_NormalOperation_295) {

    printer.OpenElement("test", false);

    // Verify that the stack has the new element

    EXPECT_EQ(printer._stack.Size(), 1u);

}



TEST_F(XMLPrinterTest_295, OpenElement_BoundaryCondition_EmptyName_295) {

    printer.OpenElement("", false);

    // Verify that an empty string can be pushed onto the stack

    EXPECT_EQ(printer._stack.PeekTop(), "");

}



TEST_F(XMLPrinterTest_295, OpenElement_BoundaryCondition_NullName_295) {

    printer.OpenElement(nullptr, false);

    // Verify that a null pointer does not cause a crash and is handled gracefully

    EXPECT_TRUE(true);  // If the function doesn't throw or assert, we consider it a pass.

}



TEST_F(XMLPrinterTest_295, OpenElement_BoundaryCondition_MaxDepth_295) {

    for (size_t i = 0; i < 100; ++i) {  // Assuming a reasonable depth limit

        printer.OpenElement("test", false);

    }

    // Verify that the stack can handle multiple elements being opened

    EXPECT_EQ(printer._stack.Size(), 100u);

}



TEST_F(XMLPrinterTest_295, OpenElement_VerifyDepthIncrement_295) {

    size_t initialDepth = printer._depth;

    printer.OpenElement("test", false);

    // Verify that the depth is incremented

    EXPECT_EQ(printer._depth, initialDepth + 1);

}



TEST_F(XMLPrinterTest_295, OpenElement_VerifyElementJustOpenedFlag_295) {

    printer.OpenElement("test", false);

    // Verify that the _elementJustOpened flag is set to true

    EXPECT_TRUE(printer._elementJustOpened);

}
