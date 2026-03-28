#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/PageLabelInfo_p.h"

#include "./TestProjects/poppler/poppler/Error.h"



TEST(fromLatin_1935, SingleLowercaseLetter_1935) {

    const char* buffer = "a";

    EXPECT_EQ(PageLabelInfo::fromLatin(buffer), 1);

}



TEST(fromLatin_1935, MultipleSameLowercaseLetters_1935) {

    const char* buffer = "aaa";

    EXPECT_EQ(PageLabelInfo::fromLatin(buffer), 27); // 26*(3-1) + 'a' - 'a' + 1

}



TEST(fromLatin_1935, SingleUppercaseLetter_1935) {

    const char* buffer = "A";

    EXPECT_EQ(PageLabelInfo::fromLatin(buffer), 1);

}



TEST(fromLatin_1935, MultipleSameUppercaseLetters_1935) {

    const char* buffer = "AAA";

    EXPECT_EQ(PageLabelInfo::fromLatin(buffer), 27); // 26*(3-1) + 'A' - 'A' + 1

}



TEST(fromLatin_1935, MixedCaseLetters_1935) {

    const char* buffer = "aAbB";

    EXPECT_EQ(PageLabelInfo::fromLatin(buffer), -1);

}



TEST(fromLatin_1935, DifferentCharacters_1935) {

    const char* buffer = "abc";

    EXPECT_EQ(PageLabelInfo::fromLatin(buffer), -1);

}



TEST(fromLatin_1935, EmptyString_1935) {

    const char* buffer = "";

    EXPECT_EQ(PageLabelInfo::fromLatin(buffer), -1);

}



TEST(fromLatin_1935, LargeBufferExceedingIntMax_1935) {

    std::string largeBuffer((std::numeric_limits<int>::max() / 100 + 2), 'a');

    EXPECT_EQ(PageLabelInfo::fromLatin(largeBuffer.c_str()), -1);

}



TEST(fromLatin_1935, BoundaryConditionMaxIntDiv100_1935) {

    std::string largeBuffer((std::numeric_limits<int>::max() / 100), 'a');

    EXPECT_EQ(PageLabelInfo::fromLatin(largeBuffer.c_str()), 26 * (std::numeric_limits<int>::max() / 100 - 1) + 1);

}
