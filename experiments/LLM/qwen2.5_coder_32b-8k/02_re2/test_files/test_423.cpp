#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class ChildArgsChangedTest_423 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or states before each test.

    }



    void TearDown() override {

        // Clean up any resources after each test.

    }

};



TEST_F(ChildArgsChangedTest_423, NormalOperation_NoChange_423) {

    Regexp* re = Regexp::LiteralString(nullptr, 0, 0);

    Regexp** child_args = new Regexp*[re->nsub()];

    for (int i = 0; i < re->nsub(); i++) {

        child_args[i] = re->sub()[i];

    }

    

    EXPECT_FALSE(ChildArgsChanged(re, child_args));

    

    delete[] child_args;

    re->Decref();

}



TEST_F(ChildArgsChangedTest_423, NormalOperation_ChangeDetected_423) {

    Regexp* re = Regexp::LiteralString(nullptr, 0, 0);

    Regexp** child_args = new Regexp*[re->nsub()];

    for (int i = 0; i < re->nsub(); i++) {

        child_args[i] = Regexp::LiteralString(nullptr, 0, 0); // New sub expression

    }

    

    EXPECT_TRUE(ChildArgsChanged(re, child_args));

    

    for (int i = 0; i < re->nsub(); i++) {

        child_args[i]->Decref();

    }

    delete[] child_args;

    re->Decref();

}



TEST_F(ChildArgsChangedTest_423, Boundary_NoSubExpressions_423) {

    Regexp* re = Regexp::LiteralString(nullptr, 0, 0); // No sub expressions

    Regexp** child_args = new Regexp*[re->nsub()]; // nsub should be 0

    

    EXPECT_FALSE(ChildArgsChanged(re, child_args));

    

    delete[] child_args;

    re->Decref();

}



TEST_F(ChildArgsChangedTest_423, Exceptional_NullSubExpressions_423) {

    Regexp* re = Regexp::LiteralString(nullptr, 0, 0);

    Regexp** child_args = nullptr; // Nullptr for child arguments

    

    EXPECT_DEATH(ChildArgsChanged(re, child_args), "");

    

    re->Decref();

}



TEST_F(ChildArgsChangedTest_423, ExternalInteraction_DecrefCalled_423) {

    Regexp* re = Regexp::LiteralString(nullptr, 0, 0);

    Regexp** child_args = new Regexp*[re->nsub()];

    for (int i = 0; i < re->nsub(); i++) {

        child_args[i] = Regexp::LiteralString(nullptr, 0, 0); // New sub expression

    }

    

    EXPECT_TRUE(ChildArgsChanged(re, child_args));

    

    delete[] child_args;

    re->Decref();

}
