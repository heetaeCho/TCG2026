#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>

#include <sstream>



using namespace YAML;



class EmitterTest_49 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_49, WriteIntegralType_NormalOperation_49) {

    unsigned int value = 123;

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "123");

}



TEST_F(EmitterTest_49, WriteIntegralType_BoundaryCondition_49) {

    unsigned int minValue = 0;

    unsigned int maxValue = UINT_MAX;

    emitter << minValue << maxValue;

    std::ostringstream expected;

    expected << minValue << "\n" << maxValue;

    EXPECT_EQ(emitter.c_str(), expected.str());

}



TEST_F(EmitterTest_49, WriteString_NormalOperation_49) {

    std::string value = "test";

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "test");

}



TEST_F(EmitterTest_49, WriteBool_NormalOperation_49) {

    bool value = true;

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "true");

}



TEST_F(EmitterTest_49, WriteChar_NormalOperation_49) {

    char value = 'a';

    emitter << value;

    EXPECT_EQ(emitter.c_str(), "a");

}



TEST_F(EmitterTest_49, SetIndent_ValidValue_49) {

    emitter.SetIndent(2);

    emitter << BeginSeq << 1 << EndSeq;

    EXPECT_EQ(emitter.c_str(), "- 1\n");

}



TEST_F(EmitterTest_49, SetIndent_BoundaryCondition_49) {

    emitter.SetIndent(0);

    emitter << BeginSeq << 1 << EndSeq;

    EXPECT_EQ(emitter.c_str(), "- 1\n");



    emitter.SetIndent(10);

    emitter << BeginSeq << 2 << EndSeq;

    EXPECT_EQ(emitter.c_str(), "- 1\n- 2\n");

}



TEST_F(EmitterTest_49, SetIndent_InvalidValue_49) {

    EXPECT_FALSE(emitter.SetIndent(UINT_MAX));

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_49, Good_ReturnsTrue_AfterValidOperations_49) {

    emitter << 123;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_49, GetLastError_ReturnsEmptyString_AfterGoodOperations_49) {

    emitter << 123;

    EXPECT_EQ(emitter.GetLastError(), "");

}



// Assuming that writing invalid data (e.g., null pointer for string) could cause an error

TEST_F(EmitterTest_49, WriteString_NullPointer_49) {

    const char* nullStr = nullptr;

    emitter << nullStr;

    EXPECT_FALSE(emitter.good());

    EXPECT_NE(emitter.GetLastError(), "");

}



TEST_F(EmitterTest_49, SetLocalIndent_ValidValue_49) {

    _Indent indent(2);

    emitter.SetLocalIndent(indent);

    emitter << BeginSeq << 1 << EndSeq;

    EXPECT_EQ(emitter.c_str(), "- 1\n");

}
