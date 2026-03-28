#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"

#include "re2/bitmap256.h"



using namespace re2;



class ProgTest : public ::testing::Test {

protected:

    std::vector<Inst> flat;

    Prog prog;



    void SetUp() override {

        // Setup any common state before tests (if needed)

    }



    void TearDown() override {

        // Clean-up after tests (if needed)

    }

};



TEST_F(ProgTest_416, ComputeHints_NormalOperation_416) {

    flat.resize(5);

    flat[0].InitByteRange('a', 'z', 0, 2);

    flat[1].InitByteRange('A', 'Z', 0, 3);

    flat[2].InitAlt(3, 4);

    flat[3].InitMatch(0);

    flat[4].InitFail();



    prog.ComputeHints(&flat, 0, 4);



    EXPECT_EQ(flat[0].hint(), 1); // hint_foldcase should be set to 1

    EXPECT_EQ(flat[1].hint(), 2); // hint_foldcase should be set to 2

}



TEST_F(ProgTest_416, ComputeHints_BoundaryConditions_416) {

    flat.resize(3);

    flat[0].InitByteRange('a', 'z', 0, 2);

    flat[1].InitAlt(2, 3); // out of bounds

    flat[2].InitMatch(0);



    prog.ComputeHints(&flat, 0, 2);



    EXPECT_EQ(flat[0].hint(), 1); // hint_foldcase should be set to 1

}



TEST_F(ProgTest_416, ComputeHints_NoByteRange_416) {

    flat.resize(3);

    flat[0].InitAlt(1, 2);

    flat[1].InitMatch(0);

    flat[2].InitFail();



    prog.ComputeHints(&flat, 0, 2);



    EXPECT_EQ(flat[0].hint(), 0); // No ByteRange instructions, hint should remain 0

}



TEST_F(ProgTest_416, ComputeHints_FoldCaseEdgeCases_416) {

    flat.resize(3);

    flat[0].InitByteRange('a', 'z', 1, 2);

    flat[1].InitAlt(2, 3); // out of bounds

    flat[2].InitMatch(0);



    prog.ComputeHints(&flat, 0, 2);



    EXPECT_EQ(flat[0].hint(), 1); // hint_foldcase should be set to 1



    flat.clear();

    flat.resize(3);

    flat[0].InitByteRange('A', 'Z', 1, 2);

    flat[1].InitAlt(2, 3); // out of bounds

    flat[2].InitMatch(0);



    prog.ComputeHints(&flat, 0, 2);



    EXPECT_EQ(flat[0].hint(), 2); // hint_foldcase should be set to 2



    flat.clear();

    flat.resize(3);

    flat[0].InitByteRange('a', 'Z', 1, 2);

    flat[1].InitAlt(2, 3); // out of bounds

    flat[2].InitMatch(0);



    prog.ComputeHints(&flat, 0, 2);



    EXPECT_EQ(flat[0].hint(), 1); // hint_foldcase should be set to 1

}



TEST_F(ProgTest_416, ComputeHints_LargeRange_416) {

    flat.resize(3);

    flat[0].InitByteRange('a', 'z', 1, 2);

    flat[1].InitAlt(2, 3); // out of bounds

    flat[2].InitMatch(0);



    prog.ComputeHints(&flat, 0, 2);



    EXPECT_EQ(flat[0].hint(), 1); // hint_foldcase should be set to 1



    flat.clear();

    flat.resize(4);

    flat[0].InitByteRange('a', 'm', 1, 2);

    flat[1].InitByteRange('n', 'z', 2, 3);

    flat[2].InitAlt(3, 4); // out of bounds

    flat[3].InitMatch(0);



    prog.ComputeHints(&flat, 0, 3);



    EXPECT_EQ(flat[0].hint(), 1); // hint_foldcase should be set to 1

    EXPECT_EQ(flat[1].hint(), 2); // hint_foldcase should be set to 2

}
