#include <gtest/gtest.h>

#include <sstream>



using namespace Catch;



class JsonUtilsTest : public ::testing::Test {

protected:

    std::ostringstream os;

    bool should_comma;

    std::uint64_t level;

};



TEST_F(JsonUtilsTest_528, AppendCommaNewline_NoCommaInitially_528) {

    should_comma = false;

    level = 0;

    JsonUtils::appendCommaNewline(os, should_comma, level);

    EXPECT_EQ(os.str(), "\n");

}



TEST_F(JsonUtilsTest_528, AppendCommaNewline_CommaInitially_528) {

    should_comma = true;

    level = 0;

    JsonUtils::appendCommaNewline(os, should_comma, level);

    EXPECT_EQ(os.str(), ",\n");

}



TEST_F(JsonUtilsTest_528, AppendCommaNewline_LevelGreaterThanZero_528) {

    should_comma = false;

    level = 3;

    JsonUtils::appendCommaNewline(os, should_comma, level);

    EXPECT_EQ(os.str(), "\n   ");

}



TEST_F(JsonUtilsTest_528, AppendCommaNewline_LevelAndCommaInitiallyTrue_528) {

    should_comma = true;

    level = 3;

    JsonUtils::appendCommaNewline(os, should_comma, level);

    EXPECT_EQ(os.str(), ",\n   ");

}



TEST_F(JsonUtilsTest_528, AppendCommaNewline_ShouldCommaSetToTrue_528) {

    should_comma = false;

    level = 0;

    JsonUtils::appendCommaNewline(os, should_comma, level);

    EXPECT_TRUE(should_comma);

}



TEST_F(JsonUtilsTest_528, AppendCommaNewline_ShouldCommaRemainsTrue_528) {

    should_comma = true;

    level = 0;

    JsonUtils::appendCommaNewline(os, should_comma, level);

    EXPECT_TRUE(should_comma);

}
