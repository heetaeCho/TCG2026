#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace re2 {



class MockRegexpStatus : public RegexpStatus {

public:

    MOCK_METHOD(void, SetError, (const std::string&), (override));

};



class ParseStateTest : public ::testing::Test {

protected:

    MockRegexpStatus mock_status;

    ParseState parse_state_with_oneline_flag{ParseFlags::OneLine, "test", &mock_status};

    ParseState parse_state_without_oneline_flag{ParseFlags::NoParseFlags, "test", &mock_status};



    static constexpr RegexpOp kRegexpBeginText = RegexpOp::kRegexpBeginText;

    static constexpr RegexpOp kRegexpBeginLine = RegexpOp::kRegexpBeginLine;

};



TEST_F(ParseStateTest_490, PushCaretWithOneLineFlag_ReturnsTrue_490) {

    EXPECT_CALL(mock_status, SetError(::testing::_)).Times(0);

    bool result = parse_state_with_oneline_flag.PushCaret();

    ASSERT_TRUE(result);

}



TEST_F(ParseStateTest_490, PushCaretWithoutOneLineFlag_ReturnsTrue_490) {

    EXPECT_CALL(mock_status, SetError(::testing::_)).Times(0);

    bool result = parse_state_without_oneline_flag.PushCaret();

    ASSERT_TRUE(result);

}



}  // namespace re2
