#include <gtest/gtest.h>

#include "catch2/internal/catch_stringref.hpp"

#include <string>



using namespace Catch;



class StringRefTest_682 : public ::testing::Test {

protected:

    const char* testString1 = "hello";

    const char* testString2 = "world";

    const char* testString3 = "hello";



    StringRef stringRef1;

    StringRef stringRef2;

    StringRef stringRef3;



    void SetUp() override {

        stringRef1 = StringRef(testString1);

        stringRef2 = StringRef(testString2);

        stringRef3 = StringRef(testString3);

    }

};



TEST_F(StringRefTest_682, CompareEqualStrings_682) {

    EXPECT_EQ(stringRef1.compare(stringRef3), 0);

}



TEST_F(StringRefTest_682, CompareDifferentStrings_682) {

    EXPECT_LT(stringRef1.compare(stringRef2), 0);

    EXPECT_GT(stringRef2.compare(stringRef1), 0);

}



TEST_F(StringRefTest_682, CompareEmptyStrings_682) {

    StringRef emptyStringRef;

    EXPECT_EQ(emptyStringRef.compare(emptyStringRef), 0);

}



TEST_F(StringRefTest_682, CompareWithEmptyString_682) {

    StringRef emptyStringRef;

    EXPECT_GT(stringRef1.compare(emptyStringRef), 0);

    EXPECT_LT(emptyStringRef.compare(stringRef1), 0);

}



TEST_F(StringRefTest_682, ComparePrefixStrings_682) {

    const char* prefix = "he";

    StringRef stringRefPrefix(prefix);

    EXPECT_EQ(stringRef1.compare(stringRefPrefix), 1);

    EXPECT_EQ(stringRefPrefix.compare(stringRef1), -1);

}



TEST_F(StringRefTest_682, CompareSamePrefixStrings_682) {

    const char* prefix = "hel";

    StringRef stringRefPrefix(prefix);

    EXPECT_EQ(stringRef1.compare(stringRefPrefix), 0);

    EXPECT_EQ(stringRefPrefix.compare(stringRef1), 0);

}



TEST_F(StringRefTest_682, CompareLongerString_682) {

    const char* longerString = "hellooo";

    StringRef stringRefLonger(longerString);

    EXPECT_LT(stringRef1.compare(stringRefLonger), 0);

    EXPECT_GT(stringRefLonger.compare(stringRef1), 0);

}



TEST_F(StringRefTest_682, CompareShorterString_682) {

    const char* shorterString = "he";

    StringRef stringRefShorter(shorterString);

    EXPECT_EQ(stringRef1.compare(stringRefShorter), 1);

    EXPECT_EQ(stringRefShorter.compare(stringRef1), -1);

}
