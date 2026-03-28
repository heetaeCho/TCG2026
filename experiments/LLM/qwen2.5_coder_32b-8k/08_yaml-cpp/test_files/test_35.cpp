#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



using namespace YAML;

using ::testing::Return;



class EmitterTest_35 : public testing::Test {

protected:

    std::stringstream output_stream;

    Emitter emitter;



    EmitterTest_35() : emitter(output_stream) {}

};



TEST_F(EmitterTest_35, WriteStreamable_NormalOperation_Float_35) {

    emitter.WriteStreamable(123.456f);

    EXPECT_EQ(output_stream.str(), "123.456");

}



TEST_F(EmitterTest_35, WriteStreamable_BoundaryCondition_Zero_35) {

    emitter.WriteStreamable(0.0f);

    EXPECT_EQ(output_stream.str(), "0");

}



TEST_F(EmitterTest_35, WriteStreamable_Exceptional_NaN_35) {

    emitter.WriteStreamable(std::numeric_limits<float>::quiet_NaN());

    EXPECT_EQ(output_stream.str(), ".nan");

}



TEST_F(EmitterTest_35, WriteStreamable_Exceptional_InfinityPositive_35) {

    emitter.WriteStreamable(std::numeric_limits<float>::infinity());

    EXPECT_EQ(output_stream.str(), ".inf");

}



TEST_F(EmitterTest_35, WriteStreamable_Exceptional_InfinityNegative_35) {

    emitter.WriteStreamable(-std::numeric_limits<float>::infinity());

    EXPECT_EQ(output_stream.str(), "-.inf");

}



TEST_F(EmitterTest_35, WriteStreamable_NormalOperation_Double_35) {

    emitter.WriteStreamable(123.456789);

    EXPECT_EQ(output_stream.str(), "123.456789");

}



TEST_F(EmitterTest_35, WriteStreamable_Exceptional_NaNDouble_35) {

    emitter.WriteStreamable(std::numeric_limits<double>::quiet_NaN());

    EXPECT_EQ(output_stream.str(), ".nan");

}



TEST_F(EmitterTest_35, WriteStreamable_Exceptional_InfinityPositiveDouble_35) {

    emitter.WriteStreamable(std::numeric_limits<double>::infinity());

    EXPECT_EQ(output_stream.str(), ".inf");

}



TEST_F(EmitterTest_35, WriteStreamable_Exceptional_InfinityNegativeDouble_35) {

    emitter.WriteStreamable(-std::numeric_limits<double>::infinity());

    EXPECT_EQ(output_stream.str(), "-.inf");

}



TEST_F(EmitterTest_35, WriteStreamable_NormalOperation_Integer_35) {

    emitter.WriteStreamable(12345);

    EXPECT_EQ(output_stream.str(), "12345");

}



TEST_F(EmitterTest_35, WriteStreamable_BoundaryCondition_MinInt_35) {

    emitter.WriteStreamable(std::numeric_limits<int>::min());

    EXPECT_EQ(output_stream.str(), std::to_string(std::numeric_limits<int>::min()));

}



TEST_F(EmitterTest_35, WriteStreamable_BoundaryCondition_MaxInt_35) {

    emitter.WriteStreamable(std::numeric_limits<int>::max());

    EXPECT_EQ(output_stream.str(), std::to_string(std::numeric_limits<int>::max()));

}



TEST_F(EmitterTest_35, WriteStreamable_GoodFalse_ReturnsSelfReference_35) {

    Emitter badEmitter;

    auto& result = badEmitter.WriteStreamable(123.456f);

    EXPECT_EQ(&badEmitter, &result);

}



TEST_F(EmitterTest_35, WriteStreamable_UnaffectedByPreviousError_35) {

    Emitter badEmitter;

    badEmitter.SetOutputCharset(static_cast<EMITTER_MANIP>(-1)); // Assuming this sets an error state

    auto& result = emitter.WriteStreamable(123.456f);

    EXPECT_EQ(&emitter, &result);

    EXPECT_EQ(output_stream.str(), "123.456");

}
