#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "re2/prog.h"

#include "re2/sparse_set.h"

#include <absl/strings/string_view.h>

#include <string>



using namespace re2;

using ::testing::Return;



class ProgToStringTest_400 : public ::testing::Test {

protected:

    void SetUp() override {

        prog = new Prog();

        q = new Workq();

    }



    void TearDown() override {

        delete prog;

        delete q;

    }



    Prog* prog;

    Workq* q;

};



TEST_F(ProgToStringTest_400, EmptyQueue_400) {

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, "");

}



TEST_F(ProgToStringTest_400, SingleInstruction_400) {

    prog->inst(0)->InitNop(1);

    q->insert(0);

    std::string expected_output = "0. nop 1\n";

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, expected_output);

}



TEST_F(ProgToStringTest_400, MultipleInstructions_400) {

    prog->inst(0)->InitNop(1);

    prog->inst(1)->InitMatch(2);

    q->insert(0);

    q->insert(1);

    std::string expected_output = "0. nop 1\n"

                                  "1. match 2\n";

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, expected_output);

}



TEST_F(ProgToStringTest_400, AltInstruction_400) {

    prog->inst(0)->InitAlt(1, 2);

    q->insert(0);

    std::string expected_output = "0. alt 1 2\n";

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, expected_output);

}



TEST_F(ProgToStringTest_400, AltMatchInstruction_400) {

    prog->inst(0)->InitAltMatch(1, 2);

    q->insert(0);

    std::string expected_output = "0. altmatch 1 2\n";

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, expected_output);

}



TEST_F(ProgToStringTest_400, ByteRangeInstruction_400) {

    prog->inst(0)->InitByteRange('a', 'z', 0, 1);

    q->insert(0);

    std::string expected_output = "0. byterange a-z/0 1\n";

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, expected_output);

}



TEST_F(ProgToStringTest_400, CaptureInstruction_400) {

    prog->inst(0)->InitCapture(3, 1);

    q->insert(0);

    std::string expected_output = "0. capture 3 1\n";

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, expected_output);

}



TEST_F(ProgToStringTest_400, EmptyWidthInstruction_400) {

    prog->inst(0)->InitEmptyWidth(kEmptyWordBoundary, 1);

    q->insert(0);

    std::string expected_output = "0. emptywordboundary 1\n";

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, expected_output);

}



TEST_F(ProgToStringTest_400, MatchInstruction_400) {

    prog->inst(0)->InitMatch(2);

    q->insert(0);

    std::string expected_output = "0. match 2\n";

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, expected_output);

}



TEST_F(ProgToStringTest_400, FailInstruction_400) {

    prog->inst(0)->InitFail();

    q->insert(0);

    std::string expected_output = "0. fail\n";

    std::string result = ProgToString(prog, q);

    EXPECT_EQ(result, expected_output);

}
