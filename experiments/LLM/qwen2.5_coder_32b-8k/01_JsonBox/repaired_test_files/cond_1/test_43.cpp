#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_43 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialization code if needed

    }



    void TearDown() override {

        // Cleanup code if needed

    }

};



TEST_F(ValueTest_43, TryGetString_ReturnsDefaultValue_ForNonStringType_43) {

    Value value(123); // Initialize with an integer to ensure non-string type

    std::string defaultValue = "default";

    EXPECT_EQ(value.tryGetString(defaultValue), defaultValue);

}



TEST_F(ValueTest_43, TryGetString_ReturnsStoredString_ForStringType_43) {

    std::string testString = "test";

    Value value(testString);

    std::string defaultValue = "default";

    EXPECT_EQ(value.tryGetString(defaultValue), testString);

}



TEST_F(ValueTest_43, TryGetString_HandlesEmptyDefaultValue_43) {

    Value value(123); // Initialize with an integer to ensure non-string type

    std::string defaultValue = "";

    EXPECT_EQ(value.tryGetString(defaultValue), defaultValue);

}



TEST_F(ValueTest_43, TryGetString_ReturnsSameStringForEmptyStringType_43) {

    std::string testString = "";

    Value value(testString);

    std::string defaultValue = "default";

    EXPECT_EQ(value.tryGetString(defaultValue), testString);

}
