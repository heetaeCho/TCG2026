#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_296 : public ::testing::Test {

protected:

    void SetUp() override {

        _buffer = new DynArray<char, 20>;

        _printer = new XMLPrinter(stdout, false, 0, eAposNever);

        static_cast<XMLPrinter*>(_printer)->_elementJustOpened = true;

        static_cast<XMLPrinter*>(_printer)->_buffer = _buffer;

    }



    void TearDown() override {

        delete _printer;

        delete _buffer;

    }



    FILE* stdoutCapture(FILE* newFile) {

        FILE* old = stdout;

        fflush(stdout);

        dup2(fileno(newFile), STDOUT_FILENO);

        setbuf(stdout, NULL);

        return old;

    }



    void restoreStdout(FILE* originalStdout) {

        fflush(stdout);

        dup2(fileno(originalStdout), STDOUT_FILENO);

        fclose(originalStdout);

    }



private:

    XMLPrinter* _printer = nullptr;

    DynArray<char, 20>* _buffer = nullptr;

};



TEST_F(XMLPrinterTest_296, PushAttribute_NormalOperation_296) {

    FILE *originalStdout = stdoutCapture(fopen("/dev/null", "w"));

    _printer->PushAttribute("name", "value");

    restoreStdout(originalStdout);



    EXPECT_EQ(_buffer->Size(), 13);

    EXPECT_STREQ(_buffer->Ptr(), " name=\"value\"");

}



TEST_F(XMLPrinterTest_296, PushAttribute_BoundaryCondition_EmptyName_296) {

    FILE *originalStdout = stdoutCapture(fopen("/dev/null", "w"));

    _printer->PushAttribute("", "value");

    restoreStdout(originalStdout);



    EXPECT_EQ(_buffer->Size(), 10);

    EXPECT_STREQ(_buffer->Ptr(), " \"value\"");

}



TEST_F(XMLPrinterTest_296, PushAttribute_BoundaryCondition_EmptyValue_296) {

    FILE *originalStdout = stdoutCapture(fopen("/dev/null", "w"));

    _printer->PushAttribute("name", "");

    restoreStdout(originalStdout);



    EXPECT_EQ(_buffer->Size(), 10);

    EXPECT_STREQ(_buffer->Ptr(), " name=\"\"");

}



TEST_F(XMLPrinterTest_296, PushAttribute_ExceptionalCase_NullName_296) {

    FILE *originalStdout = stdoutCapture(fopen("/dev/null", "w"));

    _printer->PushAttribute(nullptr, "value");

    restoreStdout(originalStdout);



    EXPECT_EQ(_buffer->Size(), 10);

    EXPECT_STREQ(_buffer->Ptr(), " \"value\"");

}



TEST_F(XMLPrinterTest_296, PushAttribute_ExceptionalCase_NullValue_296) {

    FILE *originalStdout = stdoutCapture(fopen("/dev/null", "w"));

    _printer->PushAttribute("name", nullptr);

    restoreStdout(originalStdout);



    EXPECT_EQ(_buffer->Size(), 10);

    EXPECT_STREQ(_buffer->Ptr(), " name=\"\"");

}



TEST_F(XMLPrinterTest_296, PushAttribute_ElementNotJustOpened_296) {

    static_cast<XMLPrinter*>(_printer)->_elementJustOpened = false;



    FILE *originalStdout = stdoutCapture(fopen("/dev/null", "w"));

    _printer->PushAttribute("name", "value");

    restoreStdout(originalStdout);



    EXPECT_EQ(_buffer->Size(), 0);

}
