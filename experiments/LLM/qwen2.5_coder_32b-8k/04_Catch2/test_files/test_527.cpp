#include <gtest/gtest.h>

#include <sstream>

#include "catch_jsonwriter.hpp"



using namespace Catch;



class JsonUtilsTest_527 : public ::testing::Test {

protected:

    std::ostringstream oss;

};



TEST_F(JsonUtilsTest_527, IndentZeroLevel_527) {

    JsonUtils::indent(oss, 0);

    EXPECT_EQ(oss.str(), "");

}



TEST_F(JsonUtilsTest_527, IndentOneLevel_527) {

    JsonUtils::indent(oss, 1);

    EXPECT_EQ(oss.str(), " ");

}



TEST_F(JsonUtilsTest_527, IndentMultipleLevels_527) {

    JsonUtils::indent(oss, 4);

    EXPECT_EQ(oss.str(), "    ");

}



TEST_F(JsonUtilsTest_527, IndentMaxLevel_527) {

    JsonUtils::indent(oss, std::numeric_limits<std::uint64_t>::max());

    // Since we're using a stringstream and assuming it can handle large numbers of spaces,

    // the test checks for no crash or exception.

    EXPECT_EQ(oss.tellp(), static_cast<std::streampos>(std::numeric_limits<std::uint64_t>::max()));

}
