#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpTest_159 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any state here if needed

    }



    void TearDown() override {

        // Teardown any state here if needed

    }

};



TEST_F(RegexpTest_159, NameReturnsNullptrForNonCaptureOp_159) {

    Regexp* regexp = new Regexp(kRegexpLiteral, 0);

    EXPECT_EQ(nullptr, regexp->name());

    regexp->Decref();

}



TEST_F(RegexpTest_159, NameReturnsValidPointerForCaptureOp_159) {

    std::string name("capture_name");

    Regexp* regexp = new Regexp(kRegexpCapture, 0);

    regexp->cap_ = 1;

    regexp->name_ = &name;



    EXPECT_EQ(&name, regexp->name());



    regexp->Decref();

}



TEST_F(RegexpTest_159, NameReturnsNullptrForUnsetCaptureName_159) {

    Regexp* regexp = new Regexp(kRegexpCapture, 0);

    regexp->cap_ = 1;

    regexp->name_ = nullptr;



    EXPECT_EQ(nullptr, regexp->name());



    regexp->Decref();

}



TEST_F(RegexpTest_159, RefIncrementsReferenceCount_159) {

    Regexp* regexp = new Regexp(kRegexpLiteral, 0);

    int initial_ref_count = regexp->Ref();



    EXPECT_EQ(1, initial_ref_count);



    regexp->Incref();

    EXPECT_EQ(2, regexp->Ref());



    regexp->Decref(); // Decrement to avoid memory leak

    regexp->Decref();

}



TEST_F(RegexpTest_159, DecrefDecrementsReferenceCount_159) {

    Regexp* regexp = new Regexp(kRegexpLiteral, 0);

    regexp->Incref();



    EXPECT_EQ(2, regexp->Ref());



    regexp->Decref();

    EXPECT_EQ(1, regexp->Ref());



    regexp->Decref(); // Decrement to avoid memory leak

}
