#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/simplify.h"



namespace re2 {



class SimplifyWalkerTest_428 : public ::testing::Test {

protected:

    void SetUp() override {

        walker = new SimplifyWalker();

    }



    void TearDown() override {

        delete walker;

    }



    SimplifyWalker* walker;

};



TEST_F(SimplifyWalkerTest_428, ShortVisit_ReturnsIncref_Regexp_428) {

    Regexp *regexp = Regexp::NewLiteral('a', 0);

    Regexp *parent_arg = nullptr;



    Regexp *result = walker->ShortVisit(regexp, parent_arg);



    EXPECT_EQ(result, regexp->Incref());

    result->Decref();

    regexp->Decref();

}



TEST_F(SimplifyWalkerTest_428, ShortVisit_IncreasesReferenceCount_428) {

    Regexp *regexp = Regexp::NewLiteral('a', 0);

    Regexp *parent_arg = nullptr;



    int initial_ref_count = regexp->Ref();

    walker->ShortVisit(regexp, parent_arg);



    EXPECT_EQ(regexp->Ref(), initial_ref_count + 1);

    regexp->Decref(); // Decrement for ShortVisit

    regexp->Decref(); // Decrement for the original reference

}



} // namespace re2
