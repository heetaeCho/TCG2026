#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/NameToCharCode.h"



using namespace testing;



class NameToCharCodeTest_1500 : public ::testing::Test {

protected:

    NameToCharCode::string_hasher hasher;

};



TEST_F(NameToCharCodeTest_1500, HashingNullPointer_ReturnsZero_1500) {

    EXPECT_EQ(hasher(static_cast<const char*>(nullptr)), std::hash<std::string_view> {}(static_cast<const char*>(nullptr)));

}



TEST_F(NameToCharCodeTest_1500, HashingEmptyString_ReturnsExpectedValue_1500) {

    EXPECT_EQ(hasher(""), std::hash<std::string_view> {}(""));

}



TEST_F(NameToCharCodeTest_1500, HashingNonEmptyString_ReturnsConsistentValue_1500) {

    const char* testString = "test";

    EXPECT_EQ(hasher(testString), std::hash<std::string_view> {}(testString));

}



TEST_F(NameToCharCodeTest_1500, HashingSameString_MultipleTimes_ReturnsSameHash_1500) {

    const char* testString = "consistentHash";

    size_t hashValue = hasher(testString);

    EXPECT_EQ(hasher(testString), hashValue);

}



TEST_F(NameToCharCodeTest_1500, HashingDifferentStrings_ReturnsDifferentHashes_1500) {

    const char* string1 = "stringOne";

    const char* string2 = "stringTwo";

    EXPECT_NE(hasher(string1), hasher(string2));

}
