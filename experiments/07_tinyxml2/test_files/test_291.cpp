#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"

#include <cstdio>



using namespace tinyxml2;

using ::testing::_;

using ::testing::NiceMock;



class MockFILE {

public:

    MOCK_METHOD3(fwrite, size_t(const void* ptr, size_t size, size_t nmemb));

};



TEST_F(XMLPrinterTest_291, WriteToFile_NormalOperation_291) {

    FILE* mockFile = reinterpret_cast<FILE*>(new NiceMock<MockFILE>());

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::eNoEscape);



    const char* data = "Hello, World!";

    size_t dataSize = strlen(data);



    EXPECT_CALL(*reinterpret_cast<NiceMock<MockFILE>*>(mockFile), fwrite(data, sizeof(char), dataSize, mockFile))

        .Times(1)

        .WillOnce(::testing::Return(dataSize));



    printer.Write(data, dataSize);

}



TEST_F(XMLPrinterTest_291, WriteToFile_BoundaryCondition_EmptyData_291) {

    FILE* mockFile = reinterpret_cast<FILE*>(new NiceMock<MockFILE>());

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::eNoEscape);



    const char* data = "";

    size_t dataSize = strlen(data);



    EXPECT_CALL(*reinterpret_cast<NiceMock<MockFILE>*>(mockFile), fwrite(_, _, _, _))

        .Times(0);



    printer.Write(data, dataSize);

}



TEST_F(XMLPrinterTest_291, WriteToBuffer_NormalOperation_291) {

    FILE* mockFile = nullptr;

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::eNoEscape);



    const char* data = "Hello, World!";

    size_t dataSize = strlen(data);



    printer.Write(data, dataSize);

    const char* bufferContent = printer.CStr();



    EXPECT_STREQ(bufferContent, "Hello, World!");

}



TEST_F(XMLPrinterTest_291, WriteToBuffer_BoundaryCondition_EmptyData_291) {

    FILE* mockFile = nullptr;

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::eNoEscape);



    const char* data = "";

    size_t dataSize = strlen(data);



    printer.Write(data, dataSize);

    const char* bufferContent = printer.CStr();



    EXPECT_STREQ(bufferContent, "");

}



TEST_F(XMLPrinterTest_291, WriteToFile_ExceptionalCase_NullData_291) {

    FILE* mockFile = reinterpret_cast<FILE*>(new NiceMock<MockFILE>());

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::eNoEscape);



    const char* data = nullptr;

    size_t dataSize = 10;



    EXPECT_CALL(*reinterpret_cast<NiceMock<MockFILE>*>(mockFile), fwrite(_, _, _, _))

        .Times(0);



    printer.Write(data, dataSize);

}



TEST_F(XMLPrinterTest_291, WriteToBuffer_ExceptionalCase_NullData_291) {

    FILE* mockFile = nullptr;

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::eNoEscape);



    const char* data = nullptr;

    size_t dataSize = 10;



    printer.Write(data, dataSize);

    const char* bufferContent = printer.CStr();



    EXPECT_STREQ(bufferContent, "");

}
