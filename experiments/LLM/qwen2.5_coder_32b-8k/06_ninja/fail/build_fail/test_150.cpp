#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/ninja/src/util.cc"

#include "./TestProjects/ninja/src/string_piece.h"



using ::testing::ElementsAre;



class CGroupSubSysTest : public ::testing::Test {

protected:

    CGroupSubSys cgroupSubSys;

};



TEST_F(CGroupSubSysTest_150, ParseValidLine_150) {

    std::string line = "123:cpu,memory:test_name";

    EXPECT_TRUE(cgroupSubSys.parse(line));

    EXPECT_EQ(123, cgroupSubSys.id);

    EXPECT_EQ("test_name", cgroupSubSys.name);

    EXPECT_THAT(cgroupSubSys.subsystems, ElementsAre("cpu", "memory"));

}



TEST_F(CGroupSubSysTest_150, ParseLineWithoutSecondColon_150) {

    std::string line = "123:cpu,memory";

    EXPECT_FALSE(cgroupSubSys.parse(line));

}



TEST_F(CGroupSubSysTest_150, ParseLineWithoutFirstColon_150) {

    std::string line = "cpu,memory:test_name";

    EXPECT_FALSE(cgroupSubSys.parse(line));

}



TEST_F(CGroupSubSysTest_150, ParseEmptyString_150) {

    std::string line = "";

    EXPECT_FALSE(cgroupSubSys.parse(line));

}



TEST_F(CGroupSubSysTest_150, ParseLineWithNoSubsystems_150) {

    std::string line = "123::test_name";

    EXPECT_TRUE(cgroupSubSys.parse(line));

    EXPECT_EQ(123, cgroupSubSys.id);

    EXPECT_EQ("test_name", cgroupSubSys.name);

    EXPECT_THAT(cgroupSubSys.subsystems, ElementsAre(""));

}



TEST_F(CGroupSubSysTest_150, ParseLineWithSingleSubsystem_150) {

    std::string line = "456:cpu:test_single";

    EXPECT_TRUE(cgroupSubSys.parse(line));

    EXPECT_EQ(456, cgroupSubSys.id);

    EXPECT_EQ("test_single", cgroupSubSys.name);

    EXPECT_THAT(cgroupSubSys.subsystems, ElementsAre("cpu"));

}
