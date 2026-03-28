#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include <sstream>



using namespace YAML;



class EmitterTest_526 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_526, SetPostCommentIndent_ValidValue_ReturnsTrue_526) {

    EXPECT_TRUE(emitter.SetPostCommentIndent(1));

}



TEST_F(EmitterTest_526, SetPostCommentIndent_Zero_ReturnsFalse_526) {

    EXPECT_FALSE(emitter.SetPostCommentIndent(0));

}



TEST_F(EmitterTest_526, SetPostCommentIndent_MaxValue_ReturnsTrue_526) {

    EXPECT_TRUE(emitter.SetPostCommentIndent(std::numeric_limits<std::size_t>::max()));

}



TEST_F(EmitterTest_526, SetPostCommentIndent_NormalOperation_NoException_526) {

    EXPECT_NO_THROW(emitter.SetPostCommentIndent(4));

}



TEST_F(EmitterTest_526, SetPostCommentIndent_GoodAfterSet_ReturnsTrue_526) {

    emitter.SetPostCommentIndent(3);

    EXPECT_TRUE(emitter.good());

}
