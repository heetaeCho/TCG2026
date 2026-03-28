#include <gtest/gtest.h>

#include "re2/prog.h"

#include <string>



using namespace re2;



class ProgTest : public ::testing::Test {

protected:

    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }



    Prog* prog;

};



TEST_F(ProgTest_402, DumpReturnsNonEmptyStringWhenNotFlattened_402) {

    EXPECT_FALSE(prog->Dump().empty());

}



TEST_F(ProgTest_402, DumpReturnsSameStringAfterFlatten_402) {

    std::string before = prog->Dump();

    prog->Flatten();

    std::string after = prog->Dump();

    EXPECT_EQ(before, after);

}



TEST_F(ProgTest_402, DumpUsesFlattenedProgToStringWhenDidFlattenIsTrue_402) {

    prog->did_flatten_ = true;

    std::string result = prog->Dump();

    // Assuming FlattenedProgToString returns a non-empty string when did_flatten_ is true

    EXPECT_FALSE(result.empty());

}



TEST_F(ProgTest_402, DumpUsesProgToStringWhenDidFlattenIsFalse_402) {

    prog->did_flatten_ = false;

    std::string result = prog->Dump();

    // Assuming ProgToString returns a non-empty string when did_flatten_ is false

    EXPECT_FALSE(result.empty());

}



TEST_F(ProgTest_402, DumpConsistentWithStartState_402) {

    int original_start = prog->start_;

    std::string dump_before_change = prog->Dump();

    prog->set_start(original_start + 1);

    std::string dump_after_change = prog->Dump();

    EXPECT_NE(dump_before_change, dump_after_change);

}



TEST_F(ProgTest_402, DumpUnanchoredReturnsNonEmptyString_402) {

    EXPECT_FALSE(prog->DumpUnanchored().empty());

}



TEST_F(ProgTest_402, DumpByteMapReturnsNonEmptyString_402) {

    prog->ComputeByteMap();

    EXPECT_FALSE(prog->DumpByteMap().empty());

}
