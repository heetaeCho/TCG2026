#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class ConvertIntoTest_654 : public ::testing::Test {

protected:

    bool target;

};



TEST_F(ConvertIntoTest_654, PutTrueValues_654) {

    std::string source = "true";

    auto result = convertInto(source, target);

    EXPECT_TRUE(target);

    EXPECT_TRUE(result);

    EXPECT_EQ(ParseResultType::Matched, result.type());

}



TEST_F(ConvertIntoTest_654, PutFalseValues_654) {

    std::string source = "false";

    auto result = convertInto(source, target);

    EXPECT_FALSE(target);

    EXPECT_TRUE(result);

    EXPECT_EQ(ParseResultType::Matched, result.type());

}



TEST_F(ConvertIntoTest_654, PutYesNoValues_654) {

    std::string source1 = "yes";

    std::string source2 = "no";

    auto result1 = convertInto(source1, target);

    auto result2 = convertInto(source2, target);

    EXPECT_TRUE(target);

    EXPECT_FALSE(result1.errorMessage().empty());

    EXPECT_TRUE(result1);

    EXPECT_EQ(ParseResultType::Matched, result1.type());



    EXPECT_FALSE(target);

    EXPECT_FALSE(result2.errorMessage().empty());

    EXPECT_TRUE(result2);

    EXPECT_EQ(ParseResultType::Matched, result2.type());

}



TEST_F(ConvertIntoTest_654, PutOnOffValues_654) {

    std::string source1 = "on";

    std::string source2 = "off";

    auto result1 = convertInto(source1, target);

    auto result2 = convertInto(source2, target);

    EXPECT_TRUE(target);

    EXPECT_TRUE(result1);

    EXPECT_EQ(ParseResultType::Matched, result1.type());



    EXPECT_FALSE(target);

    EXPECT_TRUE(result2);

    EXPECT_EQ(ParseResultType::Matched, result2.type());

}



TEST_F(ConvertIntoTest_654, PutNumericValues_654) {

    std::string source1 = "1";

    std::string source2 = "0";

    auto result1 = convertInto(source1, target);

    auto result2 = convertInto(source2, target);

    EXPECT_TRUE(target);

    EXPECT_TRUE(result1);

    EXPECT_EQ(ParseResultType::Matched, result1.type());



    EXPECT_FALSE(target);

    EXPECT_TRUE(result2);

    EXPECT_EQ(ParseResultType::Matched, result2.type());

}



TEST_F(ConvertIntoTest_654, PutInvalidValues_654) {

    std::string source = "invalid";

    auto result = convertInto(source, target);

    EXPECT_FALSE(result);

    EXPECT_FALSE(target);

    EXPECT_EQ("Expected a boolean value but did not recognise: 'invalid'", result.errorMessage());

}
