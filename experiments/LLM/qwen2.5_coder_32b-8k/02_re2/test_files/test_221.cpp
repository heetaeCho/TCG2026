#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/mimics_pcre.cc"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class MockRegexp : public Regexp {

public:

    MOCK_METHOD(int, Ref, (), (override));

    MOCK_METHOD(Regexp*, Incref, (), (override));

    MOCK_METHOD(void, Decref, (), (override));

    MOCK_METHOD(bool, MimicsPCRE, (), (const override));

    MOCK_METHOD(std::string, ToString, (), (const override));

    MOCK_METHOD(Prog*, CompileToProg, (int64_t max_mem), (override));

    MOCK_METHOD(Prog*, CompileToReverseProg, (int64_t max_mem), (override));

};



class EmptyStringWalkerTest_221 : public ::testing::Test {

protected:

    std::unique_ptr<EmptyStringWalker> walker;

    MockRegexp mock_regexp;



    void SetUp() override {

        walker = std::make_unique<EmptyStringWalker>();

    }

};



TEST_F(EmptyStringWalkerTest_221, ShortVisit_ReturnsInputValue_221) {

    bool input_value = true;

    EXPECT_CALL(mock_regexp, MimicsPCRE()).Times(0);  // Ensure no internal behavior is inferred

    EXPECT_EQ(walker->ShortVisit(&mock_regexp, input_value), input_value);

}



TEST_F(EmptyStringWalkerTest_221, ShortVisit_ReturnsFalseWhenInputIsFalse_221) {

    bool input_value = false;

    EXPECT_CALL(mock_regexp, MimicsPCRE()).Times(0);  // Ensure no internal behavior is inferred

    EXPECT_EQ(walker->ShortVisit(&mock_regexp, input_value), input_value);

}



TEST_F(EmptyStringWalkerTest_221, PostVisit_ReturnsParentArgWhenNoChildren_221) {

    bool parent_arg = true;

    bool pre_arg = false;

    int nchild_args = 0;

    bool* child_args = nullptr;



    EXPECT_CALL(mock_regexp, MimicsPCRE()).Times(0);  // Ensure no internal behavior is inferred

    EXPECT_EQ(walker->PostVisit(&mock_regexp, parent_arg, pre_arg, child_args, nchild_args), parent_arg);

}



TEST_F(EmptyStringWalkerTest_221, PostVisit_ReturnsFalseWhenAnyChildArgIsFalse_221) {

    bool parent_arg = true;

    bool pre_arg = false;

    int nchild_args = 2;

    bool child_args[] = {true, false};



    EXPECT_CALL(mock_regexp, MimicsPCRE()).Times(0);  // Ensure no internal behavior is inferred

    EXPECT_EQ(walker->PostVisit(&mock_regexp, parent_arg, pre_arg, child_args, nchild_args), false);

}



TEST_F(EmptyStringWalkerTest_221, PostVisit_ReturnsTrueWhenAllChildArgsAreTrue_221) {

    bool parent_arg = true;

    bool pre_arg = false;

    int nchild_args = 2;

    bool child_args[] = {true, true};



    EXPECT_CALL(mock_regexp, MimicsPCRE()).Times(0);  // Ensure no internal behavior is inferred

    EXPECT_EQ(walker->PostVisit(&mock_regexp, parent_arg, pre_arg, child_args, nchild_args), parent_arg);

}
