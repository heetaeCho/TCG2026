#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "NameToCharCode.h"



class NameToCharCodeTest_1501 : public ::testing::Test {

protected:

    NameToCharCode::string_hasher hasher;

};



TEST_F(NameToCharCodeTest_1501, HashOfEmptyString_1501) {

    EXPECT_EQ(hasher(""), std::hash<std::string>{}(""));

}



TEST_F(NameToCharCodeTest_1501, HashOfString_ReturnsConsistentValue_1501) {

    const std::string testString = "test";

    EXPECT_EQ(hasher(testString), std::hash<std::string>{}(testString));

}



TEST_F(NameToCharCodeTest_1501, HashOfDifferentStrings_AreDifferent_1501) {

    const std::string string1 = "hello";

    const std::string string2 = "world";

    EXPECT_NE(hasher(string1), hasher(string2));

}



TEST_F(NameToCharCodeTest_1501, HashOfLongString_ReturnsConsistentValue_1501) {

    const std::string longString(1000, 'a');

    EXPECT_EQ(hasher(longString), std::hash<std::string>{}(longString));

}



TEST_F(NameToCharCodeTest_1501, HashOfSameString_MultipleTimes_AreEqual_1501) {

    const std::string testString = "consistent";

    EXPECT_EQ(hasher(testString), hasher(testString));

}
