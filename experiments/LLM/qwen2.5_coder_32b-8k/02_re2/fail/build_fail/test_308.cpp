#include <gtest/gtest.h>

#include "re2/compile.cc"



namespace re2 {



class CompilerTest_308 : public ::testing::Test {

protected:

    Compiler* compiler;



    void SetUp() override {

        compiler = new Compiler();

    }



    void TearDown() override {

        delete compiler;

    }

};



TEST_F(CompilerTest_308, AddSuffixInitialValue_308) {

    int id = 1;

    compiler->AddSuffix(id);

    EXPECT_EQ(compiler->rune_range_.begin, id);

}



TEST_F(CompilerTest_308, AddSuffixUTF8Encoding_308) {

    compiler->encoding_ = kEncodingUTF8;

    compiler->rune_range_.begin = 1;

    int new_id = 2;

    compiler->AddSuffix(new_id);

    // Assuming AddSuffixRecursive returns a valid value, we can't predict it exactly.

    EXPECT_NE(compiler->rune_range_.begin, 0);

}



TEST_F(CompilerTest_308, AddSuffixNonUTF8Encoding_308) {

    compiler->encoding_ = kEncodingLatin1;

    compiler->rune_range_.begin = 1;

    int new_id = 2;

    compiler->AddSuffix(new_id);

    EXPECT_NE(compiler->rune_range_.begin, 1);

}



TEST_F(CompilerTest_308, AddSuffixFailedState_308) {

    compiler->failed_ = true;

    compiler->rune_range_.begin = 1;

    int new_id = 2;

    compiler->AddSuffix(new_id);

    EXPECT_EQ(compiler->rune_range_.begin, 1); // Should not change due to failed state

}



TEST_F(CompilerTest_308, AddSuffixInstAllocationFailure_308) {

    // Mocking AllocInst to return -1 to simulate allocation failure

    compiler->encoding_ = kEncodingLatin1;

    compiler->rune_range_.begin = 1;

    int new_id = 2;

    EXPECT_CALL(*compiler, AllocInst(1)).WillOnce(testing::Return(-1));

    compiler->AddSuffix(new_id);

    EXPECT_EQ(compiler->rune_range_.begin, 0); // Should reset to 0 due to allocation failure

}



} // namespace re2
