#include <gtest/gtest.h>

#include "compile.cc"

#include "prog.h"



using namespace re2;



class CompilerTest_293 : public ::testing::Test {

protected:

    Compiler compiler;

};



TEST_F(CompilerTest_293, Alt_ReturnsSecondFragmentIfFirstIsNoMatch_293) {

    Frag no_match = compiler.NoMatch();

    Frag frag_b(1, PatchList::Mk(2), true);

    Frag result = compiler.Alt(no_match, frag_b);

    EXPECT_EQ(result.begin, frag_b.begin);

    EXPECT_EQ(result.end.head, frag_b.end.head);

    EXPECT_EQ(result.nullable, frag_b.nullable);

}



TEST_F(CompilerTest_293, Alt_ReturnsFirstFragmentIfSecondIsNoMatch_293) {

    Frag no_match = compiler.NoMatch();

    Frag frag_a(1, PatchList::Mk(2), true);

    Frag result = compiler.Alt(frag_a, no_match);

    EXPECT_EQ(result.begin, frag_a.begin);

    EXPECT_EQ(result.end.head, frag_a.end.head);

    EXPECT_EQ(result.nullable, frag_a.nullable);

}



TEST_F(CompilerTest_293, Alt_CreatesNewFragmentIfNeitherIsNoMatch_293) {

    Frag frag_a(1, PatchList::Mk(2), false);

    Frag frag_b(3, PatchList::Mk(4), true);

    Frag result = compiler.Alt(frag_a, frag_b);



    // Verify that a new instruction is created

    EXPECT_NE(result.begin, frag_a.begin);

    EXPECT_NE(result.begin, frag_b.begin);



    // Verify nullable flag

    EXPECT_TRUE(result.nullable);

}



TEST_F(CompilerTest_293, Alt_PatchListIsCorrectlyAppended_293) {

    Frag frag_a(1, PatchList::Mk(2), false);

    Frag frag_b(3, PatchList::Mk(4), true);

    Frag result = compiler.Alt(frag_a, frag_b);



    // Assuming PatchList::Append creates a new PatchList with the heads and tails

    EXPECT_EQ(result.end.head, 2);

    EXPECT_EQ(result.end.tail, 4);

}



TEST_F(CompilerTest_293, Alt_HandlesAllocInstFailure_293) {

    Frag frag_a(1, PatchList::Mk(2), false);

    Frag frag_b(3, PatchList::Mk(4), true);



    // Mocking the behavior of AllocInst to return -1

    compiler.max_ninst_ = 0; // This will cause AllocInst to fail as it tries to allocate more than max_ninst_



    Frag result = compiler.Alt(frag_a, frag_b);

    EXPECT_EQ(result.begin, frag_a.begin); // Should return NoMatch()

    EXPECT_TRUE(result.nullable); // NoMatch().nullable is true

}
