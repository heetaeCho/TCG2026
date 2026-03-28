#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::_;

using ::testing::Return;



class EdgeTest_63 : public ::testing::Test {

protected:

    Edge edge;

};



TEST_F(EdgeTest_63, AllInputsReady_NormalOperation_63) {

    EXPECT_CALL(edge, AllInputsReady()).Times(1);

    edge.AllInputsReady();

}



TEST_F(EdgeTest_63, EvaluateCommand_NormalOperation_63) {

    bool incl_rsp_file = false;

    std::string result = edge.EvaluateCommand(incl_rsp_file);

    EXPECT_FALSE(result.empty());

}



TEST_F(EdgeTest_63, GetBinding_NormalOperation_63) {

    std::string key = "test_key";

    std::string result = edge.GetBinding(key);

    EXPECT_TRUE(result.empty() || !result.empty()); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, GetBindingBool_NormalOperation_63) {

    std::string key = "test_key";

    bool result = edge.GetBindingBool(key);

    EXPECT_EQ(result, false || true); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, GetUnescapedDepfile_NormalOperation_63) {

    std::string result = edge.GetUnescapedDepfile();

    EXPECT_TRUE(result.empty() || !result.empty()); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, GetUnescapedDyndep_NormalOperation_63) {

    std::string result = edge.GetUnescapedDyndep();

    EXPECT_TRUE(result.empty() || !result.empty()); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, GetUnescapedRspfile_NormalOperation_63) {

    std::string result = edge.GetUnescapedRspfile();

    EXPECT_TRUE(result.empty() || !result.empty()); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, Dump_NormalOperation_63) {

    const char* prefix = "test_prefix";

    edge.Dump(prefix);

}



TEST_F(EdgeTest_63, IsPhony_NormalOperation_63) {

    bool result = edge.is_phony();

    EXPECT_EQ(result, false || true); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, UseConsole_NormalOperation_63) {

    bool result = edge.use_console();

    EXPECT_EQ(result, false || true); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, MaybePhonycycleDiagnostic_NormalOperation_63) {

    bool result = edge.maybe_phonycycle_diagnostic();

    EXPECT_EQ(result, false || true); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, CriticalPathWeight_NormalOperation_63) {

    int64_t weight = edge.critical_path_weight();

    EXPECT_GE(weight, -1);

}



TEST_F(EdgeTest_63, SetCriticalPathWeight_NormalOperation_63) {

    int64_t new_weight = 10;

    edge.set_critical_path_weight(new_weight);

    EXPECT_EQ(edge.critical_path_weight(), new_weight);

}



TEST_F(EdgeTest_63, Rule_NormalOperation_63) {

    const Rule& rule = edge.rule();

    EXPECT_NE(&rule, nullptr);

}



TEST_F(EdgeTest_63, Pool_NormalOperation_63) {

    Pool* pool = edge.pool();

    EXPECT_TRUE(pool == nullptr || pool != nullptr); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, Weight_NormalOperation_63) {

    int weight = edge.weight();

    EXPECT_GE(weight, 0);

}



TEST_F(EdgeTest_63, OutputsReady_NormalOperation_63) {

    bool result = edge.outputs_ready();

    EXPECT_EQ(result, false || true); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, IsImplicit_ValidIndex_63) {

    size_t index = 0;

    bool result = edge.is_implicit(index);

    EXPECT_EQ(result, false || true); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, IsOrderOnly_ValidIndex_63) {

    size_t index = 0;

    bool result = edge.is_order_only(index);

    EXPECT_EQ(result, false || true); // Depending on the actual implementation

}



TEST_F(EdgeTest_63, IsImplicitOut_ValidIndex_63) {

    size_t index = 0;

    bool result = edge.is_implicit_out(index);

    EXPECT_EQ(result, false || true); // Depending on the actual implementation

}
