#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "value.cpp"  // Assuming this file includes necessary Exiv2 headers



using namespace Exiv2;

using namespace testing;



class XmpValueTest_831 : public Test {

protected:

    XmpValue xmpValue;

};



TEST_F(XmpValueTest_831, CopyToBufferNormalOperation_831) {

    const std::string expected = "SampleXMPData";

    xmpValue.write = [&]() { return expected; };



    byte buffer[1024];

    size_t resultSize = xmpValue.copy(buffer, ByteOrder::big);



    EXPECT_EQ(resultSize, expected.size());

    EXPECT_STREQ(reinterpret_cast<char*>(buffer), expected.c_str());

}



TEST_F(XmpValueTest_831, CopyToBufferEmptyString_831) {

    const std::string emptyExpected = "";

    xmpValue.write = [&]() { return emptyExpected; };



    byte buffer[1024];

    size_t resultSize = xmpValue.copy(buffer, ByteOrder::big);



    EXPECT_EQ(resultSize, 0);

}



TEST_F(XmpValueTest_831, CopyToBufferBoundaryConditionSmallBuffer_831) {

    const std::string expected = "LargeXMPData";

    xmpValue.write = [&]() { return expected; };



    byte buffer[5]; // Smaller than the size of expected string

    size_t resultSize = xmpValue.copy(buffer, ByteOrder::big);



    EXPECT_EQ(resultSize, expected.size());

    EXPECT_STRNE(reinterpret_cast<char*>(buffer), expected.c_str()); // Only partial data should be copied

}



TEST_F(XmpValueTest_831, CopyToBufferBoundaryConditionExactFit_831) {

    const std::string expected = "ExactXMP";

    xmpValue.write = [&]() { return expected; };



    byte buffer[expected.size()];

    size_t resultSize = xmpValue.copy(buffer, ByteOrder::big);



    EXPECT_EQ(resultSize, expected.size());

    EXPECT_STREQ(reinterpret_cast<char*>(buffer), expected.c_str()); // Exact fit should copy all data

}



// Mocking not required for this specific interface as there are no external collaborators or callbacks involved.

```


