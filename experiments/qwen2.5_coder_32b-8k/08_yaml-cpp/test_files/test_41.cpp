#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>

#include <yaml-cpp/emittermanip.h>



class EmitterTest_41 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_41, WriteAlias_NormalOperation_41) {

    YAML::_Alias alias("test_alias");

    emitter << alias;

    EXPECT_EQ(emitter.c_str(), "*test_alias\n");

}



TEST_F(EmitterTest_41, WriteAlias_EmptyString_41) {

    YAML::_Alias alias("");

    emitter << alias;

    EXPECT_EQ(emitter.c_str(), "''\n"); // This is a bit of an assumption, as empty aliases are not typical

}



TEST_F(EmitterTest_41, WriteAlias_BoundaryCondition_41) {

    YAML::_Alias alias("a");

    emitter << alias;

    EXPECT_EQ(emitter.c_str(), "*a\n");

}



TEST_F(EmitterTest_41, WriteAlias_ErrorCase_41) {

    // Since the Emitter does not seem to handle errors for aliases directly,

    // we assume normal operation and no error state is expected.

    YAML::_Alias alias("test_alias");

    emitter << alias;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_41, WriteMultipleAliases_41) {

    YAML::_Alias alias1("alias1");

    YAML::_Alias alias2("alias2");

    emitter << alias1 << alias2;

    EXPECT_EQ(emitter.c_str(), "*alias1\n*alias2\n");

}
