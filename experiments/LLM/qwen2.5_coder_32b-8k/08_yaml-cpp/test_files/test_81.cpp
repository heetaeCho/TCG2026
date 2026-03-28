#include <gtest/gtest.h>

#include "yaml-cpp/exceptions.h"



// Assuming there's a class that uses ErrorMsg::KEY_NOT_FOUND_WITH_KEY for testing purposes.

// Since we don't have such a class, let's assume a hypothetical one for demonstration.



class HypotheticalYamlParser {

public:

    std::string getKeyNotFoundMessage(const std::string& key) const {

        return YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key);

    }

};



class YamlCppExceptionsTest_81 : public ::testing::Test {

protected:

    HypotheticalYamlParser parser;

};



TEST_F(YamlCppExceptionsTest_81, KeyNotFoundWithKey_NormalOperation_81) {

    std::string key = "test_key";

    EXPECT_EQ(parser.getKeyNotFoundMessage(key), YAML::ErrorMsg::KEY_NOT_FOUND);

}



TEST_F(YamlCppExceptionsTest_81, KeyNotFoundWithKey_EmptyKey_81) {

    std::string key = "";

    EXPECT_EQ(parser.getKeyNotFoundMessage(key), YAML::ErrorMsg::KEY_NOT_FOUND);

}



TEST_F(YamlCppExceptionsTest_81, KeyNotFoundWithKey_LongKey_81) {

    std::string key = "a_very_long_key_that_might_test_boundary_conditions_and_other_things";

    EXPECT_EQ(parser.getKeyNotFoundMessage(key), YAML::ErrorMsg::KEY_NOT_FOUND);

}

```


