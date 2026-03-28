#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.hpp"

#include <string_view>



using namespace Exiv2::Internal;



class StringTagDetailsTest_177 : public ::testing::Test {

protected:

    std::string_view testKey = "test_key";

    StringTagDetails stringTagDetails;

    

    void SetUp() override {

        stringTagDetails.val_ = testKey;

    }

};



TEST_F(StringTagDetailsTest_177, OperatorEqualReturnsTrueForMatchingString_177) {

    EXPECT_TRUE(stringTagDetails == testKey);

}



TEST_F(StringTagDetailsTest_177, OperatorEqualReturnsFalseForNonMatchingString_177) {

    std::string_view nonMatchingKey = "non_matching_key";

    EXPECT_FALSE(stringTagDetails == nonMatchingKey);

}



TEST_F(StringTagDetailsTest_177, OperatorEqualBoundaryConditionEmptyStrings_177) {

    stringTagDetails.val_ = "";

    std::string_view emptyKey = "";

    EXPECT_TRUE(stringTagDetails == emptyKey);

}



TEST_F(StringTagDetailsTest_177, OperatorEqualBoundaryConditionEmptyAndNonEmptyString_177) {

    std::string_view nonEmptyKey = "non_empty";

    stringTagDetails.val_ = "";

    EXPECT_FALSE(stringTagDetails == nonEmptyKey);



    stringTagDetails.val_ = nonEmptyKey;

    std::string_view emptyKey = "";

    EXPECT_FALSE(stringTagDetails == emptyKey);

}
