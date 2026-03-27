#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/impl.h"



using namespace YAML;



// Mock class to simulate types that are streamable

class StreamableType {

public:

    friend std::ostream& operator<<(std::ostream& os, const StreamableType& obj) {

        os << "Streamable";

        return os;

    }

};



TEST_F(YamlKeyToStringTest_571, NormalOperation_StreamableType_571) {

    StreamableType key;

    EXPECT_EQ(key_to_string(key), "Streamable");

}



TEST_F(YamlKeyToStringTest_571, NormalOperation_StringLiteral_571) {

    const char* key = "test";

    EXPECT_EQ(key_to_string(key), "test");

}



TEST_F(YamlKeyToStringTest_571, NormalOperation_StringObject_571) {

    std::string key = "example";

    EXPECT_EQ(key_to_string(key), "example");

}



TEST_F(YamlKeyToStringTest_571, BoundaryCondition_EmptyStringLiteral_571) {

    const char* key = "";

    EXPECT_EQ(key_to_string(key), "");

}



TEST_F(YamlKeyToStringTest_571, BoundaryCondition_EmptyStringObject_571) {

    std::string key = "";

    EXPECT_EQ(key_to_string(key), "");

}



TEST_F(YamlKeyToStringTest_571, ExceptionalCase_NonStreamableType_571) {

    int nonStreamableKey = 42;

    EXPECT_THROW(key_to_string(nonStreamableKey), std::exception);

}

```


