#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <gmock/gmock.h>



using namespace tinyxml2;

using ::testing::MockFunction;



class XMLPrinterTest : public ::testing::Test {

protected:

    void SetUp() override {

        file = fopen("test_output.xml", "w+");

        printer = new XMLPrinter(file, true, 0);

    }



    void TearDown() override {

        delete printer;

        fclose(file);

        remove("test_output.xml");

    }



    FILE* file;

    XMLPrinter* printer;

};



TEST_F(XMLPrinterTest_313, PushComment_NormalOperation_313) {

    const char* comment = "This is a comment";

    printer->PushComment(comment);



    rewind(file);

    char buffer[256];

    fgets(buffer, sizeof(buffer), file);

    EXPECT_STREQ("<!--This is a comment-->", buffer);

}



TEST_F(XMLPrinterTest_313, PushComment_EmptyString_313) {

    const char* comment = "";

    printer->PushComment(comment);



    rewind(file);

    char buffer[256];

    fgets(buffer, sizeof(buffer), file);

    EXPECT_STREQ("<!---->", buffer);

}



TEST_F(XMLPrinterTest_313, PushComment_SpecialCharacters_313) {

    const char* comment = "<>&\"";

    printer->PushComment(comment);



    rewind(file);

    char buffer[256];

    fgets(buffer, sizeof(buffer), file);

    EXPECT_STREQ("<!--&lt;&gt;&amp;&quot;-->", buffer);

}



TEST_F(XMLPrinterTest_313, PushComment_NullPointer_313) {

    const char* comment = nullptr;

    printer->PushComment(comment);



    rewind(file);

    char buffer[256];

    fgets(buffer, sizeof(buffer), file);

    EXPECT_STREQ("<!--(null)-->", buffer);

}
