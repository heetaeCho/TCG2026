#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterutils.cpp"

#include "yaml-cpp/ostream_wrapper.h"



using namespace YAML;

using namespace Utils;



class WriteBatchTest_629 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper out{oss};

};



TEST_F(WriteBatchTest_629, PutSimpleString_629) {

    const char* str = "hello";

    std::size_t size = 5;

    bool result = WriteSingleQuotedString(out, str, size);

    EXPECT_TRUE(result);

    EXPECT_EQ("'hello'", oss.str());

}



TEST_F(WriteBatchTest_629, PutEmptyString_629) {

    const char* str = "";

    std::size_t size = 0;

    bool result = WriteSingleQuotedString(out, str, size);

    EXPECT_TRUE(result);

    EXPECT_EQ("''", oss.str());

}



TEST_F(WriteBatchTest_629, PutStringWithSingleQuote_629) {

    const char* str = "hello'world";

    std::size_t size = 11;

    bool result = WriteSingleQuotedString(out, str, size);

    EXPECT_TRUE(result);

    EXPECT_EQ("'hello''world'", oss.str());

}



TEST_F(WriteBatchTest_629, PutStringWithNewLine_629) {

    const char* str = "hello\nworld";

    std::size_t size = 11;

    bool result = WriteSingleQuotedString(out, str, size);

    EXPECT_FALSE(result);

    EXPECT_EQ("'", oss.str());

}



TEST_F(WriteBatchTest_629, PutBoundaryConditionMaxSize_629) {

    const char* str = "a";

    std::size_t size = 1;

    bool result = WriteSingleQuotedString(out, str, size);

    EXPECT_TRUE(result);

    EXPECT_EQ("'a'", oss.str());

}



TEST_F(WriteBatchTest_629, PutBoundaryConditionEmptySize_629) {

    const char* str = "a";

    std::size_t size = 0;

    bool result = WriteSingleQuotedString(out, str, size);

    EXPECT_TRUE(result);

    EXPECT_EQ("''", oss.str());

}
