#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/compile.cc"

#include "./TestProjects/re2/re2/prog.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class CompilerTest : public ::testing::Test {

protected:

    Compiler compiler;



    void SetUp() override {

        // Setup any necessary state before tests

    }



    void TearDown() override {

        // Cleanup any necessary state after tests

    }

};



TEST_F(CompilerTest_AddSuffixRecursive_309, NormalOperation_309) {

    int root = 1;

    int id = 2;



    compiler.inst_.resize(5);

    compiler.inst_[root].InitAlt(root + 1, root + 2);



    EXPECT_CALL(compiler, AllocInst(_)).Times(0);

    EXPECT_CALL(compiler, IsNoMatch(_)).WillOnce(Return(false));

    EXPECT_CALL(compiler, IsCachedRuneByteSuffix(_)).WillOnce(Return(false));



    int result = compiler.AddSuffixRecursive(root, id);

    EXPECT_EQ(result, root);

}



TEST_F(CompilerTest_AddSuffixRecursive_309, NoMatchBranch_309) {

    int root = 1;

    int id = 2;



    compiler.inst_.resize(5);

    compiler.inst_[root].InitAlt(root + 1, root + 2);



    EXPECT_CALL(compiler, AllocInst(1)).WillOnce(Return(3));

    EXPECT_CALL(compiler, IsNoMatch(_)).WillOnce(Return(true));



    int result = compiler.AddSuffixRecursive(root, id);

    EXPECT_EQ(result, 3);

}



TEST_F(CompilerTest_AddSuffixRecursive_309, CachedRuneByteSuffix_309) {

    int root = 1;

    int id = 2;



    compiler.inst_.resize(5);

    compiler.inst_[root].InitAlt(root + 1, root + 2);



    EXPECT_CALL(compiler, AllocInst(1)).WillOnce(Return(3));

    EXPECT_CALL(compiler, IsNoMatch(_)).WillOnce(Return(false));

    EXPECT_CALL(compiler, IsCachedRuneByteSuffix(_)).WillOnce(Return(true));



    int result = compiler.AddSuffixRecursive(root, id);

    EXPECT_EQ(result, root);

}



TEST_F(CompilerTest_AddSuffixRecursive_309, OutOfMemoryAllocation_309) {

    int root = 1;

    int id = 2;



    compiler.inst_.resize(5);

    compiler.inst_[root].InitAlt(root + 1, root + 2);



    EXPECT_CALL(compiler, AllocInst(1)).WillOnce(Return(-1));

    EXPECT_CALL(compiler, IsNoMatch(_)).WillOnce(Return(true));



    int result = compiler.AddSuffixRecursive(root, id);

    EXPECT_EQ(result, 0);

}



TEST_F(CompilerTest_AddSuffixRecursive_309, RecursiveCallError_309) {

    int root = 1;

    int id = 2;



    compiler.inst_.resize(5);

    compiler.inst_[root].InitAlt(root + 1, root + 2);



    EXPECT_CALL(compiler, AllocInst(_)).Times(0);

    EXPECT_CALL(compiler, IsNoMatch(_)).WillOnce(Return(false));

    EXPECT_CALL(compiler, IsCachedRuneByteSuffix(_)).WillOnce(Return(false));



    // Mock the recursive call to return an error

    EXPECT_CALL(compiler, AddSuffixRecursive(_, _)).WillOnce(Return(0));



    int result = compiler.AddSuffixRecursive(root, id);

    EXPECT_EQ(result, 0);

}
