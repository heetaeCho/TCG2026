#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/pdfdetach.cc"

#include "TestProjects/poppler/goo/GooString.h"

#include "TestProjects/poppler/poppler/UnicodeMap.h"



using namespace testing;



class UnicodeMapMock : public UnicodeMap {

public:

    MOCK_METHOD(int, mapUnicode, (Unicode u, char *buf, int bufSize), (override));

};



TEST(getFileNameTest_2719, NormalOperationASCII_2719) {

    GooString gooStr("example.txt");

    UnicodeMapMock mockUnicodeMap;

    EXPECT_CALL(mockUnicodeMap, mapUnicode(_, _, _)).WillRepeatedly(Invoke([](Unicode u, char *buf, int bufSize) {

        buf[0] = static_cast<char>(u);

        return 1;

    }));



    std::string result = getFileName(gooStr, mockUnicodeMap);

    EXPECT_EQ(result, "example.txt");

}



TEST(getFileNameTest_2719, NormalOperationUnicode_2719) {

    GooString gooStr("\xFEFF6578616D706C652E747874"); // Unicode byte order mark followed by ASCII values

    UnicodeMapMock mockUnicodeMap;

    EXPECT_CALL(mockUnicodeMap, mapUnicode(_, _, _)).WillRepeatedly(Invoke([](Unicode u, char *buf, int bufSize) {

        buf[0] = static_cast<char>(u);

        return 1;

    }));



    std::string result = getFileName(gooStr, mockUnicodeMap);

    EXPECT_EQ(result, "example.txt");

}



TEST(getFileNameTest_2719, BoundaryConditionEmptyString_2719) {

    GooString gooStr("");

    UnicodeMapMock mockUnicodeMap;



    std::string result = getFileName(gooStr, mockUnicodeMap);

    EXPECT_EQ(result, "");

}



TEST(getFileNameTest_2719, ExceptionalCaseInvalidUnicode_2719) {

    GooString gooStr("\xFEFF"); // Only BOM without characters

    UnicodeMapMock mockUnicodeMap;

    EXPECT_CALL(mockUnicodeMap, mapUnicode(_, _, _)).WillRepeatedly(Return(0)); // Simulate invalid unicode mapping



    std::string result = getFileName(gooStr, mockUnicodeMap);

    EXPECT_EQ(result, "");

}



TEST(getFileNameTest_2719, ExternalInteractionMockVerification_2719) {

    GooString gooStr("example.txt");

    UnicodeMapMock mockUnicodeMap;

    EXPECT_CALL(mockUnicodeMap, mapUnicode(_, _, _)).Times(11); // 10 characters + BOM check



    getFileName(gooStr, mockUnicodeMap);

}
