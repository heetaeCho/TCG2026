#include <gtest/gtest.h>

#include "prog.h"

#include "sparse_array.h"

#include "sparse_set.h"



using namespace re2;



class ProgTest_413 : public ::testing::Test {

protected:

    Prog prog;

    SparseArray<int> rootmap;

    SparseArray<int> predmap;

    std::vector<std::vector<int>> predvec;

    SparseSet reachable;

    std::vector<int> stk;



    void SetUp() override {

        // Initialize any necessary data for the tests

        prog.set_start(1);

        prog.set_start_unanchored(2);



        // Mocking or setting up external collaborators if needed

    }

};



TEST_F(ProgTest_413, MarkSuccessors_NormalOperation_413) {

    prog.MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

    

    EXPECT_TRUE(rootmap.has_index(0));

    EXPECT_TRUE(rootmap.has_index(prog.start_unanchored()));

    EXPECT_TRUE(rootmap.has_index(prog.start()));

    EXPECT_EQ(reachable.size(), 1); // start_unanchored is the only element in reachable set

}



TEST_F(ProgTest_413, MarkSuccessors_BoundaryConditions_413) {

    prog.set_start(0);

    prog.set_start_unanchored(0);



    prog.MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);



    EXPECT_TRUE(rootmap.has_index(0));

    EXPECT_EQ(reachable.size(), 1); // start_unanchored is the only element in reachable set

}



TEST_F(ProgTest_413, MarkSuccessors_ExceptionalCases_413) {

    // Assuming there are no exceptional cases directly observable from the interface.

    // If there were, they would be handled here.

}



TEST_F(ProgTest_413, MarkSuccessors_VerifyExternalInteractions_413) {

    // Since we do not mock internal behavior, we cannot verify interactions with internal objects.

    // However, we can verify that the method does not crash or cause any observable issues.

    prog.MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);

}



TEST_F(ProgTest_413, MarkSuccessors_EmptyStack_413) {

    stk.clear();

    prog.MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);



    EXPECT_TRUE(rootmap.has_index(0));

    EXPECT_TRUE(rootmap.has_index(prog.start_unanchored()));

    EXPECT_TRUE(rootmap.has_index(prog.start()));

    EXPECT_EQ(reachable.size(), 1); // start_unanchored is the only element in reachable set

}



TEST_F(ProgTest_413, MarkSuccessors_StartMatchesStartUnanchored_413) {

    prog.set_start(2);

    prog.set_start_unanchored(2);



    prog.MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);



    EXPECT_TRUE(rootmap.has_index(0));

    EXPECT_TRUE(rootmap.has_index(prog.start_unanchored()));

    EXPECT_EQ(reachable.size(), 1); // start_unanchored is the only element in reachable set

}



TEST_F(ProgTest_413, MarkSuccessors_StartDoesNotMatchStartUnanchored_413) {

    prog.set_start(1);

    prog.set_start_unanchored(2);



    prog.MarkSuccessors(&rootmap, &predmap, &predvec, &reachable, &stk);



    EXPECT_TRUE(rootmap.has_index(0));

    EXPECT_TRUE(rootmap.has_index(prog.start_unanchored()));

    EXPECT_TRUE(rootmap.has_index(prog.start()));

    EXPECT_EQ(reachable.size(), 1); // start_unanchored is the only element in reachable set

}
