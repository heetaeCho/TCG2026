#include <gtest/gtest.h>

#include "tinyxml2.h"



namespace tinyxml2 {



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* file = nullptr;

    std::string buffer;



    void SetUp() override {

        file = fmemopen(&buffer, 1024, "w+");

    }



    void TearDown() override {

        if (file) {

            fclose(file);

            file = nullptr;

        }

    }

};



TEST_F(XMLPrinterTest_292, PutcToFile_292) {

    XMLPrinter printer(file, false, 0, EscapeAposCharsInAttributes::eNoApostrophes);

    printer.Putc('a');

    rewind(file);

    char ch;

    fread(&ch, sizeof(char), 1, file);

    EXPECT_EQ(ch, 'a');

}



TEST_F(XMLPrinterTest_292, PutcToBuffer_292) {

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::eNoApostrophes);

    printer.Putc('b');

    EXPECT_STREQ(printer.CStr(), "b");

}



TEST_F(XMLPrinterTest_292, PutcMultipleCharactersToFile_292) {

    XMLPrinter printer(file, false, 0, EscapeAposCharsInAttributes::eNoApostrophes);

    printer.Putc('a');

    printer.Putc('b');

    printer.Putc('c');

    rewind(file);

    char buffer[4];

    fread(buffer, sizeof(char), 3, file);

    buffer[3] = '\0';

    EXPECT_STREQ(buffer, "abc");

}



TEST_F(XMLPrinterTest_292, PutcMultipleCharactersToBuffer_292) {

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::eNoApostrophes);

    printer.Putc('a');

    printer.Putc('b');

    printer.Putc('c');

    EXPECT_STREQ(printer.CStr(), "abc");

}



TEST_F(XMLPrinterTest_292, PutcNullCharacterToFile_292) {

    XMLPrinter printer(file, false, 0, EscapeAposCharsInAttributes::eNoApostrophes);

    printer.Putc('\0');

    rewind(file);

    char ch;

    size_t bytesRead = fread(&ch, sizeof(char), 1, file);

    EXPECT_EQ(bytesRead, 1);

    EXPECT_EQ(ch, '\0');

}



TEST_F(XMLPrinterTest_292, PutcNullCharacterToBuffer_292) {

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::eNoApostrophes);

    printer.Putc('\0');

    EXPECT_STREQ(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_292, PutcAfterClearingBuffer_292) {

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::eNoApostrophes);

    printer.Putc('a');

    printer.ClearBuffer();

    printer.Putc('b');

    EXPECT_STREQ(printer.CStr(), "b");

}



} // namespace tinyxml2
