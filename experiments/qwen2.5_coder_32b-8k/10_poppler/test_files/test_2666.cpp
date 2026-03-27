#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/pdfinfo.cc"

#include "TestProjects/poppler/poppler/Object.h"

#include "TestProjects/poppler/poppler/Dict.h"

#include "TestProjects/poppler/poppler/UnicodeMap.h"



using namespace testing;



class MockGooString : public GooString {

public:

    MOCK_METHOD(const char*, getCString, (), (const));

};



class MockUnicodeMap : public UnicodeMap {

public:

    MOCK_METHOD(int, mapUnicode, (Unicode u, char * buf, int bufSize), (override));

};



TEST(printISODateTest_2666, NormalOperation_2666) {

    Dict infoDict;

    UnicodeMap uMap("UTF-8", true, 1);



    MockGooString mockString;

    EXPECT_CALL(mockString, getCString())

        .WillOnce(Return("2023-10-05T14:48:30Z"));



    Object obj(std::make_unique<MockGooString>(mockString));

    infoDict.add("Date", std::move(obj));



    testing::internal::CaptureStdout();

    printISODate(&infoDict, "Date", "Date: ", &uMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Date: 2023-10-05T14:48:30Z\n");

}



TEST(printISODateTest_2666, BoundaryCondition_EmptyString_2666) {

    Dict infoDict;

    UnicodeMap uMap("UTF-8", true, 1);



    MockGooString mockString;

    EXPECT_CALL(mockString, getCString())

        .WillOnce(Return(""));



    Object obj(std::make_unique<MockGooString>(mockString));

    infoDict.add("Date", std::move(obj));



    testing::internal::CaptureStdout();

    printISODate(&infoDict, "Date", "Date: ", &uMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Date: \n");

}



TEST(printISODateTest_2666, ExceptionalCase_NotString_2666) {

    Dict infoDict;

    UnicodeMap uMap("UTF-8", true, 1);



    Object obj(42); // Int object

    infoDict.add("Date", std::move(obj));



    testing::internal::CaptureStdout();

    printISODate(&infoDict, "Date", "Date: ", &uMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "");

}



TEST(printISODateTest_2666, ExceptionalCase_NullObject_2666) {

    Dict infoDict;

    UnicodeMap uMap("UTF-8", true, 1);



    Object obj(Object::null());

    infoDict.add("Date", std::move(obj));



    testing::internal::CaptureStdout();

    printISODate(&infoDict, "Date", "Date: ", &uMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "");

}



TEST(printISODateTest_2666, ExternalInteraction_PrintTextStringCalled_2666) {

    Dict infoDict;

    UnicodeMap uMap("UTF-8", true, 1);



    MockGooString mockString;

    EXPECT_CALL(mockString, getCString())

        .WillOnce(Return("invalid-date"));



    Object obj(std::make_unique<MockGooString>(mockString));

    infoDict.add("Date", std::move(obj));



    testing::internal::CaptureStdout();

    printISODate(&infoDict, "Date", "Date: ", &uMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Date: \n");

}
