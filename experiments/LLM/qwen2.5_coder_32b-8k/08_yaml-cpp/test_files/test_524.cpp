#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"



using namespace YAML;



class EmitterTest_524 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_524, SetIndent_DefaultValue_ReturnsTrue_524) {

    EXPECT_TRUE(emitter.SetIndent(0));

}



TEST_F(EmitterTest_524, SetIndent_ValidRange_ReturnsTrue_524) {

    EXPECT_TRUE(emitter.SetIndent(1));

    EXPECT_TRUE(emitter.SetIndent(2));

    EXPECT_TRUE(emitter.SetIndent(10));

}



TEST_F(EmitterTest_524, SetIndent_MaxValue_ReturnsTrue_524) {

    EXPECT_TRUE(emitter.SetIndent(std::numeric_limits<std::size_t>::max()));

}



TEST_F(EmitterTest_524, SetIndent_Zero_ReturnsTrue_524) {

    EXPECT_TRUE(emitter.SetIndent(0));

}



TEST_F(EmitterTest_524, SetIndent_AfterWriting_ReturnsTrue_524) {

    emitter.Write("test");

    EXPECT_TRUE(emitter.SetIndent(2));

}



// Assuming that setting an indent does not change the state of good()

TEST_F(EmitterTest_524, SetIndent_EmitterGood_ReturnsTrue_524) {

    EXPECT_TRUE(emitter.good());

    EXPECT_TRUE(emitter.SetIndent(2));

    EXPECT_TRUE(emitter.good());

}
