#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/ninja/src/graph.h"



class EdgeTest : public ::testing::Test {

protected:

    Edge edge;

};



TEST_F(EdgeTest_55, SetCriticalPathWeight_SetsValueCorrectly_55) {

    int64_t test_value = 12345;

    edge.set_critical_path_weight(test_value);

    EXPECT_EQ(edge.critical_path_weight(), test_value);

}



TEST_F(EdgeTest_55, CriticalPathWeight_DefaultValueIsNegativeOne_55) {

    EXPECT_EQ(edge.critical_path_weight(), -1);

}



TEST_F(EdgeTest_55, Rule_ReturnsConstReferenceToRule_55) {

    const Rule& rule = edge.rule();

    // Since we have no way to set or modify the rule, we can't test much more than it returns a reference.

    EXPECT_EQ(&rule, &edge.rule_);

}



TEST_F(EdgeTest_55, Pool_ReturnsPointerToPool_55) {

    Pool* pool = edge.pool();

    // Since we have no way to set or modify the pool, we can't test much more than it returns a pointer.

    EXPECT_EQ(pool, edge.pool_);

}



TEST_F(EdgeTest_55, OutputsReady_DefaultValueIsFalse_55) {

    EXPECT_FALSE(edge.outputs_ready());

}
