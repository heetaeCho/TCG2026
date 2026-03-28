#include <gtest/gtest.h>

#include "re2/prog.h"



namespace re2 {



class ProgTest : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_403, DumpUnanchored_ReturnsFlattenedStringWhenDidFlattenIsTrue_403) {

    prog.did_flatten_ = true; // Simulate the state where did_flatten_ is true

    std::string result = prog.DumpUnanchored();

    EXPECT_EQ(result, FlattenedProgToString(&prog, prog.start_unanchored_));

}



TEST_F(ProgTest_403, DumpUnanchored_ReturnsNormalStringWhenDidFlattenIsFalse_403) {

    prog.did_flatten_ = false; // Simulate the state where did_flatten_ is false

    std::string result = prog.DumpUnanchored();

    Workq q(prog.size_);

    prog.AddToQueue(&q, prog.start_unanchored_);

    EXPECT_EQ(result, ProgToString(&prog, &q));

}



TEST_F(ProgTest_403, DumpUnanchored_HandlesZeroSizeCorrectly_403) {

    prog.did_flatten_ = false;

    prog.size_ = 0;

    std::string result = prog.DumpUnanchored();

    EXPECT_EQ(result, ProgToString(&prog, nullptr));

}



TEST_F(ProgTest_403, DumpUnanchored_HandlesNonZeroSizeCorrectly_403) {

    prog.did_flatten_ = false;

    prog.size_ = 10; // Simulate a non-zero size

    std::string result = prog.DumpUnanchored();

    Workq q(prog.size_);

    prog.AddToQueue(&q, prog.start_unanchored_);

    EXPECT_EQ(result, ProgToString(&prog, &q));

}



} // namespace re2
