#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/stlemitter.h"



using namespace YAML;



class EmitterTest_656 : public ::testing::Test {

protected:

    std::ostringstream stream;

    Emitter emitter;



    EmitterTest_656() : emitter(stream) {}

};



TEST_F(EmitterTest_656, WriteStringNormalOperation_656) {

    emitter << "test_string";

    EXPECT_EQ(emitter.c_str(), "test_string");

}



TEST_F(EmitterTest_656, WriteEmptyString_656) {

    emitter << "";

    EXPECT_EQ(emitter.c_str(), "");

}



TEST_F(EmitterTest_656, WriteBooleanTrue_656) {

    emitter << true;

    EXPECT_EQ(emitter.c_str(), "true");

}



TEST_F(EmitterTest_656, WriteBooleanFalse_656) {

    emitter << false;

    EXPECT_EQ(emitter.c_str(), "false");

}



TEST_F(EmitterTest_656, WriteCharNormalOperation_656) {

    emitter << 'a';

    EXPECT_EQ(emitter.c_str(), "a");

}



TEST_F(EmitterTest_656, WriteListIntegers_656) {

    std::list<int> numbers = {1, 2, 3};

    emitter << numbers;

    EXPECT_EQ(emitter.c_str(), "- 1\n- 2\n- 3\n");

}



TEST_F(EmitterTest_656, WriteEmptyList_656) {

    std::list<int> empty_list;

    emitter << empty_list;

    EXPECT_EQ(emitter.c_str(), "");

}



TEST_F(EmitterTest_656, GoodStatusAfterWriting_656) {

    emitter << "test_string";

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_656, GoodStatusWithEmptyWrite_656) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_656, GetLastErrorInitiallyEmpty_656) {

    EXPECT_EQ(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_656, SetIndentValidValue_656) {

    EXPECT_TRUE(emitter.SetIndent(2));

}



TEST_F(EmitterTest_656, SetIndentZero_656) {

    EXPECT_FALSE(emitter.SetIndent(0));

}



TEST_F(EmitterTest_656, SetIndentMax_656) {

    EXPECT_TRUE(emitter.SetIndent(10));

}



TEST_F(EmitterTest_656, WriteAfterSetSeqFormat_656) {

    emitter.SetSeqFormat(FmtFlow);

    std::list<int> numbers = {1, 2, 3};

    emitter << numbers;

    EXPECT_EQ(emitter.c_str(), "[1, 2, 3]");

}



TEST_F(EmitterTest_656, SetInvalidManipulator_656) {

    EXPECT_FALSE(emitter.SetOutputCharset(static_cast<EMITTER_MANIP>(-1)));

}
