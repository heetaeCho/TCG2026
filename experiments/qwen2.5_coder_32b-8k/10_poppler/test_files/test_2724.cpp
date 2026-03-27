#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Object.h"

#include "poppler/Dict.h"



using namespace testing;



extern void printInfoDate(FILE *f, Dict *infoDict, const char *key, const char *text1, const char *text2);



class PrintInfoDateTest : public ::testing::Test {

protected:

    FILE* output;

    Dict infoDict;

    

    void SetUp() override {

        output = fopen("test_output.txt", "w");

    }



    void TearDown() override {

        fclose(output);

        remove("test_output.txt");

    }

};



TEST_F(PrintInfoDateTest_2724, NormalOperationValidDateString_2724) {

    Object dateObject(new GooString("D:20231015123456+02'00'"));

    infoDict.dictAdd("CreationDate", std::move(dateObject));



    printInfoDate(output, &infoDict, "CreationDate", "", "\n");



    FILE* readOutput = fopen("test_output.txt", "r");

    char buffer[100];

    fgets(buffer, sizeof(buffer), readOutput);

    fclose(readOutput);



    EXPECT_STREQ(buffer, "2023-10-15T12:34:56+02:00\n");

}



TEST_F(PrintInfoDateTest_2724, NormalOperationZuluTime_2724) {

    Object dateObject(new GooString("D:20231015123456Z"));

    infoDict.dictAdd("CreationDate", std::move(dateObject));



    printInfoDate(output, &infoDict, "CreationDate", "", "\n");



    FILE* readOutput = fopen("test_output.txt", "r");

    char buffer[100];

    fgets(buffer, sizeof(buffer), readOutput);

    fclose(readOutput);



    EXPECT_STREQ(buffer, "2023-10-15T12:34:56Z\n");

}



TEST_F(PrintInfoDateTest_2724, BoundaryConditionEmptyDateString_2724) {

    Object dateObject(new GooString(""));

    infoDict.dictAdd("CreationDate", std::move(dateObject));



    printInfoDate(output, &infoDict, "CreationDate", "", "\n");



    FILE* readOutput = fopen("test_output.txt", "r");

    char buffer[100];

    fgets(buffer, sizeof(buffer), readOutput);

    fclose(readOutput);



    EXPECT_STREQ(buffer, "");

}



TEST_F(PrintInfoDateTest_2724, BoundaryConditionNullObject_2724) {

    Object dateObject = Object::null();

    infoDict.dictAdd("CreationDate", std::move(dateObject));



    printInfoDate(output, &infoDict, "CreationDate", "", "\n");



    FILE* readOutput = fopen("test_output.txt", "r");

    char buffer[100];

    fgets(buffer, sizeof(buffer), readOutput);

    fclose(readOutput);



    EXPECT_STREQ(buffer, "");

}



TEST_F(PrintInfoDateTest_2724, BoundaryConditionNonDateString_2724) {

    Object dateObject(new GooString("NotADate"));

    infoDict.dictAdd("CreationDate", std::move(dateObject));



    printInfoDate(output, &infoDict, "CreationDate", "", "\n");



    FILE* readOutput = fopen("test_output.txt", "r");

    char buffer[100];

    fgets(buffer, sizeof(buffer), readOutput);

    fclose(readOutput);



    EXPECT_STREQ(buffer, "");

}



TEST_F(PrintInfoDateTest_2724, BoundaryConditionMissingKey_2724) {

    printInfoDate(output, &infoDict, "CreationDate", "", "\n");



    FILE* readOutput = fopen("test_output.txt", "r");

    char buffer[100];

    fgets(buffer, sizeof(buffer), readOutput);

    fclose(readOutput);



    EXPECT_STREQ(buffer, "");

}



TEST_F(PrintInfoDateTest_2724, ExceptionalCaseInvalidFormat_2724) {

    Object dateObject(new GooString("D:2023-10-15T12:34:56+02:00"));

    infoDict.dictAdd("CreationDate", std::move(dateObject));



    printInfoDate(output, &infoDict, "CreationDate", "", "\n");



    FILE* readOutput = fopen("test_output.txt", "r");

    char buffer[100];

    fgets(buffer, sizeof(buffer), readOutput);

    fclose(readOutput);



    EXPECT_STREQ(buffer, "");

}
