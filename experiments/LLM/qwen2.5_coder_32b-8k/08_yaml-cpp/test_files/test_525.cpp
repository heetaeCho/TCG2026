#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>



class EmitterTest_525 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_525, SetPreCommentIndent_ValidValue_ReturnsTrue_525) {

    EXPECT_TRUE(emitter.SetPreCommentIndent(4));

}



TEST_F(EmitterTest_525, SetPreCommentIndent_Zero_ReturnsTrue_525) {

    EXPECT_TRUE(emitter.SetPreCommentIndent(0));

}



TEST_F(EmitterTest_525, SetPreCommentIndent_MaxValue_ReturnsTrue_525) {

    EXPECT_TRUE(emitter.SetPreCommentIndent(std::numeric_limits<std::size_t>::max()));

}



TEST_F(EmitterTest_525, SetPreCommentIndent_AfterWrite_ReturnsTrue_525) {

    emitter.Write("key: value");

    EXPECT_TRUE(emitter.SetPreCommentIndent(4));

}
