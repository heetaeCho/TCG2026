#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emittermanip.h"



using namespace YAML;

using ::testing::Eq;



class EmitterManipTest_13 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(EmitterManipTest_13, AliasCreationWithValidString_13) {

    std::string content = "example";

    _Alias alias = Alias(content);

    EXPECT_EQ(alias.m_value, content);

}



TEST_F(EmitterManipTest_13, AliasCreationWithEmptyString_13) {

    std::string content = "";

    _Alias alias = Alias(content);

    EXPECT_EQ(alias.m_value, content);

}



TEST_F(EmitterManipTest_13, AliasCreationWithLongString_13) {

    std::string content = "a very long string that might test the boundaries of the implementation";

    _Alias alias = Alias(content);

    EXPECT_EQ(alias.m_value, content);

}

```


