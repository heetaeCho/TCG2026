#include <gtest/gtest.h>

#include "poppler/utils/pdfinfo.cc"

#include "poppler/poppler/Object.h"

#include "poppler/poppler/Dict.h"

#include "poppler/poppler/UnicodeMap.h"



class PrintInfoStringTest : public ::testing::Test {

protected:

    Dict infoDict;

    UnicodeMap uMap;



    void SetUp() override {

        // Initialize the Dict and UnicodeMap objects

        // Assuming default constructor initializes them correctly for testing purposes.

    }

};



TEST_F(PrintInfoStringTest_2664, KeyNotFound_2664) {

    const char* key = "NonExistentKey";

    const char* text = "Text: ";

    testing::internal::CaptureStdout();

    printInfoString(&infoDict, key, text, &uMap);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, ""); // No output expected if the key is not found

}



TEST_F(PrintInfoStringTest_2664, NormalOperation_2664) {

    const char* key = "Title";

    const char* text = "Title: ";

    std::unique_ptr<GooString> title(new GooString("Sample Document"));

    infoDict.dictAdd(key, Object(std::move(title)));



    testing::internal::CaptureStdout();

    printInfoString(&infoDict, key, text, &uMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Title: Sample Document\n");

}



TEST_F(PrintInfoStringTest_2664, EmptyString_2664) {

    const char* key = "Author";

    const char* text = "Author: ";

    std::unique_ptr<GooString> author(new GooString(""));

    infoDict.dictAdd(key, Object(std::move(author)));



    testing::internal::CaptureStdout();

    printInfoString(&infoDict, key, text, &uMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, "Author: \n");

}



TEST_F(PrintInfoStringTest_2664, NonStringType_2664) {

    const char* key = "PageCount";

    const char* text = "Page Count: ";

    infoDict.dictAdd(key, Object(5)); // Adding an integer instead of a string



    testing::internal::CaptureStdout();

    printInfoString(&infoDict, key, text, &uMap);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(output, ""); // No output expected if the value is not a string

}
