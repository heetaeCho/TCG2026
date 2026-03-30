#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/emitterutils.cpp"

#include "yaml-cpp/ostream_wrapper.h"



using namespace YAML::Utils;

using ::testing::_;



class OutputStreamMock : public YAML::ostream_wrapper {

public:

    MOCK_METHOD(void, write, (const std::string& str), (override));

    MOCK_METHOD(void, write, (const char* str, std::size_t size), (override));

};



TEST_F(WriteBatchTest_631, NormalOperation_631) {

    OutputStreamMock mockOut;

    const char* testStr = "Hello\nWorld";

    std::size_t size = 12;

    std::size_t indent = 4;



    EXPECT_CALL(mockOut, write("|\n")).Times(1);

    EXPECT_CALL(mockOut, write("\n")).Times(1);

    EXPECT_CALL(mockOut, write("    H")).Times(1);

    EXPECT_CALL(mockOut, write("e")).Times(1);

    EXPECT_CALL(mockOut, write("l")).Times(2);

    EXPECT_CALL(mockOut, write("o")).Times(1);

    EXPECT_CALL(mockOut, write("    W")).Times(1);

    EXPECT_CALL(mockOut, write("o")).Times(1);

    EXPECT_CALL(mockOut, write("r")).Times(1);

    EXPECT_CALL(mockOut, write("l")).Times(1);

    EXPECT_CALL(mockOut, write("d")).Times(1);



    bool result = WriteLiteralString(mockOut, testStr, size, indent);

    EXPECT_TRUE(result);

}



TEST_F(WriteBatchTest_631, EmptyString_631) {

    OutputStreamMock mockOut;

    const char* testStr = "";

    std::size_t size = 0;

    std::size_t indent = 4;



    EXPECT_CALL(mockOut, write("|\n")).Times(1);



    bool result = WriteLiteralString(mockOut, testStr, size, indent);

    EXPECT_TRUE(result);

}



TEST_F(WriteBatchTest_631, SingleNewline_631) {

    OutputStreamMock mockOut;

    const char* testStr = "\n";

    std::size_t size = 1;

    std::size_t indent = 4;



    EXPECT_CALL(mockOut, write("|\n")).Times(1);

    EXPECT_CALL(mockOut, write("\n")).Times(1);



    bool result = WriteLiteralString(mockOut, testStr, size, indent);

    EXPECT_TRUE(result);

}



TEST_F(WriteBatchTest_631, MultipleNewlines_631) {

    OutputStreamMock mockOut;

    const char* testStr = "\n\n";

    std::size_t size = 2;

    std::size_t indent = 4;



    EXPECT_CALL(mockOut, write("|\n")).Times(1);

    EXPECT_CALL(mockOut, write("\n")).Times(2);



    bool result = WriteLiteralString(mockOut, testStr, size, indent);

    EXPECT_TRUE(result);

}



TEST_F(WriteBatchTest_631, NoNewlines_631) {

    OutputStreamMock mockOut;

    const char* testStr = "HelloWorld";

    std::size_t size = 10;

    std::size_t indent = 4;



    EXPECT_CALL(mockOut, write("|\n")).Times(1);

    EXPECT_CALL(mockOut, write("\n")).Times(0);

    EXPECT_CALL(mockOut, write("    H")).Times(1);

    EXPECT_CALL(mockOut, write("e")).Times(1);

    EXPECT_CALL(mockOut, write("l")).Times(2);

    EXPECT_CALL(mockOut, write("o")).Times(1);

    EXPECT_CALL(mockOut, write("W")).Times(1);

    EXPECT_CALL(mockOut, write("o")).Times(1);

    EXPECT_CALL(mockOut, write("r")).Times(1);

    EXPECT_CALL(mockOut, write("l")).Times(1);

    EXPECT_CALL(mockOut, write("d")).Times(1);



    bool result = WriteLiteralString(mockOut, testStr, size, indent);

    EXPECT_TRUE(result);

}



TEST_F(WriteBatchTest_631, LargeIndent_631) {

    OutputStreamMock mockOut;

    const char* testStr = "Hello\nWorld";

    std::size_t size = 12;

    std::size_t indent = 20;



    EXPECT_CALL(mockOut, write("|\n")).Times(1);

    EXPECT_CALL(mockOut, write("\n")).Times(1);

    EXPECT_CALL(mockOut, write("                    H")).Times(1);

    EXPECT_CALL(mockOut, write("e")).Times(1);

    EXPECT_CALL(mockOut, write("l")).Times(2);

    EXPECT_CALL(mockOut, write("o")).Times(1);

    EXPECT_CALL(mockOut, write("                    W")).Times(1);

    EXPECT_CALL(mockOut, write("o")).Times(1);

    EXPECT_CALL(mockOut, write("r")).Times(1);

    EXPECT_CALL(mockOut, write("l")).Times(1);

    EXPECT_CALL(mockOut, write("d")).Times(1);



    bool result = WriteLiteralString(mockOut, testStr, size, indent);

    EXPECT_TRUE(result);

}
