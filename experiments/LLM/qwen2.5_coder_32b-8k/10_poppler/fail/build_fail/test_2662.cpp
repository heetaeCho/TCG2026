#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/pdfinfo.cc"

#include "TestProjects/poppler/goo/GooString.h"

#include "TestProjects/poppler/poppler/UnicodeMap.h"



using namespace testing;



class MockUnicodeMap : public UnicodeMap {

public:

    MOCK_METHOD(void, printStdTextString, (const char* s), (override));

};



TEST(printTextStringTest_2662, NormalOperation_2662) {

    GooString gooStr("Hello, World!");

    MockUnicodeMap mockUMap;



    EXPECT_CALL(mockUMap, printStdTextString(StrEq("Hello, World!")));



    printTextString(&gooStr, &mockUMap);

}



TEST(printTextStringTest_2662, EmptyString_2662) {

    GooString gooStr("");

    MockUnicodeMap mockUMap;



    EXPECT_CALL(mockUMap, printStdTextString(StrEq("")));



    printTextString(&gooStr, &mockUMap);

}



TEST(printTextStringTest_2662, NullGooString_2662) {

    GooString* gooStr = nullptr;

    MockUnicodeMap mockUMap;



    EXPECT_CALL(mockUMap, printStdTextString(StrEq("")));



    printTextString(gooStr, &mockUMap);

}



TEST(printTextStringTest_2662, LargeString_2662) {

    std::string largeStr(1024, 'A'); // Large string of 1024 characters

    GooString gooStr(largeStr.c_str());

    MockUnicodeMap mockUMap;



    EXPECT_CALL(mockUMap, printStdTextString(StrEq(largeStr)));



    printTextString(&gooStr, &mockUMap);

}
