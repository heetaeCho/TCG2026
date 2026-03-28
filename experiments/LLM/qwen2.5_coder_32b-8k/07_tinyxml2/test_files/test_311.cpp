#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_311 : public ::testing::Test {

protected:

    void SetUp() override {

        _buffer = new DynArray<char, 20>;

        _printer = new XMLPrinter(stdout, false, 0, eNoAposInAttributes);

    }



    void TearDown() override {

        delete _printer;

        delete _buffer;

    }



    FILE* stdoutFile = stdout;

    bool compactMode = false;

    int depth = 0;

    EscapeAposCharsInAttributes aposInAttributes = eNoAposInAttributes;

    DynArray<char, 20>* _buffer;

    XMLPrinter* _printer;

};



TEST_F(XMLPrinterTest_311, PushTextFloatNormalOperation_311) {

    float value = 3.14f;

    _printer->PushText(value);

    // Assuming that the internal buffer is updated correctly and can be retrieved via CStr()

    std::string result(_printer->CStr());

    EXPECT_EQ(result.find("3.14"), 0); // Check if "3.14" is at the start of the string

}



TEST_F(XMLPrinterTest_311, PushTextFloatBoundaryCondition_311) {

    float value = std::numeric_limits<float>::max();

    _printer->PushText(value);

    std::string result(_printer->CStr());

    EXPECT_NE(result.find(std::to_string(value)), std::string::npos); // Check if the max float value is in the string



    _printer->ClearBuffer();

    value = std::numeric_limits<float>::lowest();

    _printer->PushText(value);

    result.assign(_printer->CStr());

    EXPECT_NE(result.find(std::to_string(value)), std::string::npos); // Check if the lowest float value is in the string

}



TEST_F(XMLPrinterTest_311, PushTextFloatExceptionalCase_311) {

    float value = std::numeric_limits<float>::quiet_NaN();

    _printer->PushText(value);

    std::string result(_printer->CStr());

    // The string representation of NaN can vary, but it should not be an empty string

    EXPECT_FALSE(result.empty());



    _printer->ClearBuffer();

    value = std::numeric_limits<float>::infinity();

    _printer->PushText(value);

    result.assign(_printer->CStr());

    EXPECT_NE(result.find("inf"), std::string::npos); // Check if "inf" is in the string

}



TEST_F(XMLPrinterTest_311, PushTextFloatExternalInteraction_311) {

    // Assuming we have a mock object to verify interactions (not applicable here as no external dependencies are mocked)

    // This test case can be omitted or adapted based on actual requirements and dependencies.

}
