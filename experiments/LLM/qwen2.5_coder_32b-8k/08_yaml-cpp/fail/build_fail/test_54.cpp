#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>

#include <sstream>



class EmitterTest_54 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_54, WriteIntegralType_NormalOperation_54) {

    long long value = 12345;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_54, WriteIntegralType_BoundaryCondition_Zero_54) {

    long long value = 0;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_54, WriteIntegralType_BoundaryCondition_MaxValue_54) {

    long long value = LLONG_MAX;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_54, WriteIntegralType_BoundaryCondition_MinValue_54) {

    long long value = LLONG_MIN;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_54, WriteIntegralType_ExceptionalCase_NotGoodState_54) {

    // Assuming there is a way to put the emitter in a bad state

    // This is a placeholder test as the actual conditions are not provided

    // For example, if writing to a closed stream causes bad state

    std::ostringstream oss;

    YAML::Emitter local_emitter(oss);

    local_emitter << YAML::EndSeq; // Force bad state

    EXPECT_FALSE(local_emitter.good());

}



TEST_F(EmitterTest_54, WriteOperator_NormalOperation_54) {

    emitter << "test string";

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_54, WriteOperator_BoundaryCondition_EmptyString_54) {

    emitter << "";

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_54, WriteOperator_ExceptionalCase_NotGoodState_54) {

    // Assuming there is a way to put the emitter in a bad state

    // This is a placeholder test as the actual conditions are not provided

    std::ostringstream oss;

    YAML::Emitter local_emitter(oss);

    local_emitter << YAML::EndSeq; // Force bad state

    EXPECT_FALSE(local_emitter.good());

}
