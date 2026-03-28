#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/prog.h"

#include "./TestProjects/re2/re2/sparse_array.h"

#include "./TestProjects/re2/re2/sparse_set.h"



using namespace re2;



class ProgTest_415 : public ::testing::Test {

protected:

    Prog* prog;

    

    void SetUp() override {

        prog = new Prog();

    }

    

    void TearDown() override {

        delete prog;

    }

};



TEST_F(ProgTest_415, EmitList_NormalOperation_415) {

    SparseArray<int> rootmap(10);

    std::vector<Inst> flat;

    SparseSet reachable;

    std::vector<int> stk;



    // Assuming some valid setup for rootmap and other parameters

    prog->EmitList(0, &rootmap, &flat, &reachable, &stk);



    EXPECT_FALSE(flat.empty());

}



TEST_F(ProgTest_415, EmitList_RootNotReachable_415) {

    SparseArray<int> rootmap(10);

    std::vector<Inst> flat;

    SparseSet reachable;

    std::vector<int> stk;



    prog->EmitList(999, &rootmap, &flat, &reachable, &stk);



    EXPECT_TRUE(flat.empty());

}



TEST_F(ProgTest_415, EmitList_BoundaryConditions_415) {

    SparseArray<int> rootmap(0);

    std::vector<Inst> flat;

    SparseSet reachable;

    std::vector<int> stk;



    prog->EmitList(0, &rootmap, &flat, &reachable, &stk);



    EXPECT_TRUE(flat.empty());

}



TEST_F(ProgTest_415, EmitList_ExceptionalCases_415) {

    SparseArray<int> rootmap(-1); // Invalid size

    std::vector<Inst> flat;

    SparseSet reachable;

    std::vector<int> stk;



    EXPECT_THROW(prog->EmitList(0, &rootmap, &flat, &reachable, &stk), std::exception);

}



TEST_F(ProgTest_415, EmitList_ReachableContainsRoot_415) {

    SparseArray<int> rootmap(10);

    std::vector<Inst> flat;

    SparseSet reachable;

    std::vector<int> stk;



    // Assuming some valid setup for rootmap and other parameters

    prog->EmitList(0, &rootmap, &flat, &reachable, &stk);



    EXPECT_TRUE(reachable.contains(0));

}



TEST_F(ProgTest_415, EmitList_ReachableContainsMultipleIds_415) {

    SparseArray<int> rootmap(10);

    std::vector<Inst> flat;

    SparseSet reachable;

    std::vector<int> stk;



    // Assuming some valid setup for rootmap and other parameters

    prog->EmitList(0, &rootmap, &flat, &reachable, &stk);



    EXPECT_TRUE(reachable.size() > 1);

}



TEST_F(ProgTest_415, EmitList_SparseArrayHasIndex_415) {

    SparseArray<int> rootmap(10);

    std::vector<Inst> flat;

    SparseSet reachable;

    std::vector<int> stk;



    // Assuming some valid setup for rootmap and other parameters

    prog->EmitList(0, &rootmap, &flat, &reachable, &stk);



    EXPECT_TRUE(rootmap.has_index(0));

}



TEST_F(ProgTest_415, EmitList_SparseArrayNoIndex_415) {

    SparseArray<int> rootmap(10);

    std::vector<Inst> flat;

    SparseSet reachable;

    std::vector<int> stk;



    // Assuming some valid setup for rootmap and other parameters

    prog->EmitList(999, &rootmap, &flat, &reachable, &stk);



    EXPECT_FALSE(rootmap.has_index(999));

}
