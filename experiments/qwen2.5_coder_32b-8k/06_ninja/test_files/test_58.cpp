#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::Return;



class EdgeTest_58 : public ::testing::Test {

protected:

    Edge edge;

};



TEST_F(EdgeTest_58, WeightReturnsOne_58) {

    EXPECT_EQ(edge.weight(), 1);

}



TEST_F(EdgeTest_58, AllInputsReadyDefaultFalse_58) {

    EXPECT_FALSE(edge.AllInputsReady());

}



TEST_F(EdgeTest_58, CriticalPathWeightDefaultNegativeOne_58) {

    EXPECT_EQ(edge.critical_path_weight(), -1);

}



TEST_F(EdgeTest_58, SetCriticalPathWeightUpdatesValue_58) {

    int64_t new_weight = 10;

    edge.set_critical_path_weight(new_weight);

    EXPECT_EQ(edge.critical_path_weight(), new_weight);

}



TEST_F(EdgeTest_58, OutputsReadyDefaultFalse_58) {

    EXPECT_FALSE(edge.outputs_ready());

}



TEST_F(EdgeTest_58, IsPhonyDefaultFalse_58) {

    EXPECT_FALSE(edge.is_phony());

}



TEST_F(EdgeTest_58, UseConsoleDefaultFalse_58) {

    EXPECT_FALSE(edge.use_console());

}



TEST_F(EdgeTest_58, MaybePhonycycleDiagnosticDefaultFalse_58) {

    EXPECT_FALSE(edge.maybe_phonycycle_diagnostic());

}



TEST_F(EdgeTest_58, GetBindingEmptyStringForNonExistentKey_58) {

    std::string key = "non_existent_key";

    EXPECT_EQ(edge.GetBinding(key), "");

}



TEST_F(EdgeTest_58, GetBindingBoolFalseForNonExistentKey_58) {

    std::string key = "non_existent_key";

    EXPECT_FALSE(edge.GetBindingBool(key));

}



TEST_F(EdgeTest_58, EvaluateCommandEmptyStringDefault_58) {

    bool incl_rsp_file = false;

    EXPECT_EQ(edge.EvaluateCommand(incl_rsp_file), "");

}



TEST_F(EdgeTest_58, GetUnescapedDepfileEmptyStringDefault_58) {

    EXPECT_EQ(edge.GetUnescapedDepfile(), "");

}



TEST_F(EdgeTest_58, GetUnescapedDyndepEmptyStringDefault_58) {

    EXPECT_EQ(edge.GetUnescapedDyndep(), "");

}



TEST_F(EdgeTest_58, GetUnescapedRspfileEmptyStringDefault_58) {

    EXPECT_EQ(edge.GetUnescapedRspfile(), "");

}
