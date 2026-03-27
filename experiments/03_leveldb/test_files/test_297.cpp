#include <gtest/gtest.h>

#include "db/db_impl.cc"  // Include the file containing the class definition



using namespace leveldb;



class DBImplTest_297 : public ::testing::Test {

protected:

    DBImpl db_impl;

    Compaction compaction;

    CompactionState* compaction_state;



    void SetUp() override {

        compaction_state = new CompactionState(&compaction);

    }



    void TearDown() override {

        delete compaction_state;

    }

};



TEST_F(DBImplTest_297, CurrentOutput_ReturnsLastOutput_297) {

    Output output1;

    Output output2;

    compaction_state->outputs.push_back(output1);

    compaction_state->outputs.push_back(output2);



    EXPECT_EQ(&output2, compaction_state->current_output());

}



TEST_F(DBImplTest_297, CurrentOutput_ThrowsOnEmptyOutputs_297) {

    // Assuming current_output() would throw an exception if outputs is empty

    // This test checks the boundary condition where outputs vector is empty.

    EXPECT_THROW(compaction_state->current_output(), std::exception);

}



TEST_F(DBImplTest_297, CurrentOutput_ReturnsSamePointerForMultipleCalls_297) {

    Output output;

    compaction_state->outputs.push_back(output);



    Output* first_call = compaction_state->current_output();

    Output* second_call = compaction_state->current_output();



    EXPECT_EQ(first_call, second_call);

}
