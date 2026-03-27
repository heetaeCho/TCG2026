#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/simplify.cc"



using namespace re2;



class CoalesceWalkerTest_425 : public ::testing::Test {

protected:

    CoalesceWalker walker;

};



TEST_F(CoalesceWalkerTest_425, ShortVisit_Incref_ReturnsSameRegexp_425) {

    Regexp* regexp = Regexp::NewLiteral('a', 0);

    EXPECT_EQ(regexp, walker.ShortVisit(regexp, nullptr));

    regexp->Decref();

}



TEST_F(CoalesceWalkerTest_425, ShortVisit_Incref_IncreasesRef_425) {

    Regexp* regexp = Regexp::NewLiteral('a', 0);

    int initial_ref_count = regexp->Ref();

    walker.ShortVisit(regexp, nullptr);

    EXPECT_EQ(initial_ref_count + 1, regexp->Ref());

    regexp->Decref(); // Decrement twice to balance the incref from ShortVisit

    regexp->Decref();

}



// Since ShortVisit is a black box and does not have observable side effects other than Incref,

// we do not need additional boundary or error cases for it.
