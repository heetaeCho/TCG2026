#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/emittermanip.h"



class EmitterTest_60 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_60, SetLocalPrecision_NormalOperation_60) {

    YAML::_Precision precision(5, 10);

    emitter << precision;



    // We can't directly verify the internal state, but we can check if it returns a reference to itself

    EXPECT_EQ(&emitter, &(emitter << precision));

}



TEST_F(EmitterTest_60, SetLocalPrecision_BoundaryConditions_60) {

    YAML::_Precision min_precision(0, 0);

    YAML::_Precision max_precision(std::numeric_limits<std::size_t>::max(), std::numeric_limits<std::size_t>::max());



    emitter << min_precision;

    emitter << max_precision;



    EXPECT_EQ(&emitter, &(emitter << min_precision));

    EXPECT_EQ(&emitter, &(emitter << max_precision));

}



TEST_F(EmitterTest_60, SetFloatPrecision_NormalOperation_60) {

    bool result = emitter.SetFloatPrecision(5);

    EXPECT_TRUE(result);  // Assuming valid precision values return true

}



TEST_F(EmitterTest_60, SetDoublePrecision_NormalOperation_60) {

    bool result = emitter.SetDoublePrecision(10);

    EXPECT_TRUE(result);  // Assuming valid precision values return true

}



TEST_F(EmitterTest_60, SetIndent_NormalOperation_60) {

    bool result = emitter.SetIndent(4);

    EXPECT_TRUE(result);  // Assuming valid indent values return true

}



TEST_F(EmitterTest_60, WriteString_NormalOperation_60) {

    emitter.Write("test");

    EXPECT_EQ(&emitter, &(emitter.Write("test")));

}



TEST_F(EmitterTest_60, WriteBool_NormalOperation_60) {

    emitter.Write(true);

    emitter.Write(false);

    EXPECT_EQ(&emitter, &(emitter.Write(true)));

    EXPECT_EQ(&emitter, &(emitter.Write(false)));

}



TEST_F(EmitterTest_60, WriteChar_NormalOperation_60) {

    emitter.Write('a');

    EXPECT_EQ(&emitter, &(emitter.Write('a')));

}



TEST_F(EmitterTest_60, GoodState_Default_60) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_60, GetLastError_EmptyInitially_60) {

    EXPECT_EQ("", emitter.GetLastError());

}
