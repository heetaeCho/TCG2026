#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::_;

using ::testing::InSequence;



class XMLPrinterTest : public ::testing::Test {

protected:

    std::stringstream bufferStream;

    FILE* bufferFile = fdopen(bufferStream.rdbuf()->fd(), "w");

    XMLPrinter printer{bufferFile, false, 0, EscapeAposCharsInAttributes::YES};



    ~XMLPrinterTest() override {

        fclose(bufferFile);

    }

};



TEST_F(XMLPrinterTest_308, PushText_Integer_NormalOperation_308) {

    int value = 42;

    printer.PushText(value);



    EXPECT_EQ(bufferStream.str(), "42");

}



TEST_F(XMLPrinterTest_308, PushText_Integer_BoundaryCondition_MinInt_308) {

    int minValue = INT_MIN;

    printer.PushText(minValue);



    EXPECT_EQ(bufferStream.str(), "-2147483648"); // Assuming 32-bit integer

}



TEST_F(XMLPrinterTest_308, PushText_Integer_BoundaryCondition_MaxInt_308) {

    int maxValue = INT_MAX;

    printer.PushText(maxValue);



    EXPECT_EQ(bufferStream.str(), "2147483647"); // Assuming 32-bit integer

}



TEST_F(XMLPrinterTest_308, PushText_Integer_ExceptionalCase_Zero_308) {

    int zero = 0;

    printer.PushText(zero);



    EXPECT_EQ(bufferStream.str(), "0");

}
