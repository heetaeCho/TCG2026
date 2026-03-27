#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2/tinyxml2.h"



using namespace tinyxml2;



class MockXMLElement : public XMLElement {

    // No additional implementation needed for mocking purposes

};



class XMLPrinterTest_151 : public ::testing::Test {

protected:

    std::unique_ptr<XMLPrinter> printer;

    MockXMLElement mockElement;



    void SetUp() override {

        printer = std::make_unique<XMLPrinter>();

    }

};



TEST_F(XMLPrinterTest_151, CompactMode_ReturnsDefaultFalse_151) {

    EXPECT_FALSE(printer->CompactMode(mockElement));

}



// Assuming _compactMode can be set to true through some means (not shown in interface)

// For the sake of this exercise, we assume there's a way to set it to true

TEST_F(XMLPrinterTest_151, CompactMode_ReturnsTrue_WhenSet_151) {

    // If there were a setter or another way to modify _compactMode, it would be used here

    // Since the interface does not provide such functionality, this test assumes _compactMode is true

    printer->_compactMode = true; // Direct access for testing purposes only

    EXPECT_TRUE(printer->CompactMode(mockElement));

}



// Boundary conditions and exceptional/error cases are not clearly defined in the provided interface.

// Assuming no additional information, we focus on the observable behavior based on the given signature.

```


