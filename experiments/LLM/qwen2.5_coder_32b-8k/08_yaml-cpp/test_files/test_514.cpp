#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



class EmitterTest_514 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_514, SizeInitiallyZero_514) {

    EXPECT_EQ(emitter.size(), 0);

}



TEST_F(EmitterTest_514, WriteStringIncreasesSize_514) {

    const std::string testString = "test";

    emitter.Write(testString);

    EXPECT_EQ(emitter.size(), testString.size());

}



TEST_F(EmitterTest_514, WriteCharIncreasesSizeByOne_514) {

    char testChar = 'a';

    emitter.Write(testChar);

    EXPECT_EQ(emitter.size(), 1);

}



TEST_F(EmitterTest_514, WriteMultipleStringsConcatenates_514) {

    const std::string str1 = "Hello";

    const std::string str2 = "World";

    emitter.Write(str1).Write(str2);

    EXPECT_EQ(emitter.size(), str1.size() + str2.size());

}



TEST_F(EmitterTest_514, WriteEmptyStringDoesNotChangeSize_514) {

    emitter.Write("");

    EXPECT_EQ(emitter.size(), 0);

}



TEST_F(EmitterTest_514, GoodInitiallyTrue_514) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_514, GetLastErrorInitiallyEmpty_514) {

    EXPECT_TRUE(emitter.GetLastError().empty());

}



TEST_F(EmitterTest_514, SetIndentReturnsTrue_514) {

    EXPECT_TRUE(emitter.SetIndent(2));

}



TEST_F(EmitterTest_514, WriteBoolIncreasesSizeByFour_514) {

    emitter.Write(true);

    EXPECT_EQ(emitter.size(), 4); // Assuming "true" is written

}



TEST_F(EmitterTest_514, WriteNullIncreasesSizeByFour_514) {

    emitter.Write(YAML::_Null());

    EXPECT_EQ(emitter.size(), 4); // Assuming "~" or "null" is written

}



TEST_F(EmitterTest_514, WriteCommentDoesNotChangeSize_514) {

    const std::string comment = "# This is a comment";

    emitter.Write(YAML::_Comment(comment));

    EXPECT_EQ(emitter.size(), 0); // Assuming comments are not counted in size

}
