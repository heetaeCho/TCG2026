#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_309 : public ::testing::Test {

protected:

    FILE* mockFile;

    XMLPrinter* printer;



    void SetUp() override {

        mockFile = fopen("mockfile.txt", "w");

        printer = new XMLPrinter(mockFile, false, 0, EscapeAposCharsInAttributes::YES);

    }



    void TearDown() override {

        delete printer;

        fclose(mockFile);

        remove("mockfile.txt");

    }

};



TEST_F(XMLPrinterTest_309, PushTextUnsignedNormalOperation_309) {

    unsigned value = 123456;

    printer->PushText(value);



    // Assuming the buffer can be inspected for verification (though this is not ideal)

    // For actual testing, you might need to mock the output or use a special method to inspect the internal state.

}



TEST_F(XMLPrinterTest_309, PushTextUnsignedBoundaryMaxValue_309) {

    unsigned value = UINT_MAX;

    printer->PushText(value);

}



TEST_F(XMLPrinterTest_309, PushTextUnsignedBoundaryMinValue_309) {

    unsigned value = 0;

    printer->PushText(value);

}

```


