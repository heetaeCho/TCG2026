#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/simplify.h"



namespace re2 {



class SimplifyWalkerTest : public ::testing::Test {

protected:

    SimplifyWalker simplify_walker_;

};



TEST_F(SimplifyWalkerTest, CopyReturnsSamePointer_427) {

    Regexp* original = Regexp::NewLiteral('a', 0);

    Regexp* copied = simplify_walker_.Copy(original);

    EXPECT_EQ(original, copied);

    original->Decref();

}



TEST_F(SimplifyWalkerTest, CopyIncreasesRefCounter_427) {

    Regexp* original = Regexp::NewLiteral('a', 0);

    int initial_ref_count = original->Ref();

    simplify_walker_.Copy(original);

    EXPECT_EQ(initial_ref_count + 1, original->Ref());

    original->Decref();

    original->Decref();

}



TEST_F(SimplifyWalkerTest, CopyOfNullRegexp_427) {

    Regexp* original = nullptr;

    Regexp* copied = simplify_walker_.Copy(original);

    EXPECT_EQ(nullptr, copied);

}



}  // namespace re2
