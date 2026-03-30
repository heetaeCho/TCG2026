#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/dfa.h"

#include "absl/strings/string_view.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class MockDFAStateCallback : public Prog::DFAStateCallback {

public:

    MOCK_METHOD(void, AddState, (const State* state), (override));

};



TEST_F(DFAConstructorTest_433, ConstructorWithValidParameters_433) {

    Prog prog;

    DFA dfa(&prog, Prog::MatchKind::kFullMatch, 1024);

    EXPECT_TRUE(dfa.ok());

}



TEST_F(DFASearchTest_433, SearchWithEmptyText_433) {

    Prog prog;

    DFA dfa(&prog, Prog::MatchKind::kFullMatch, 1024);

    bool failed = false;

    const char* ep = nullptr;

    SparseSet matches;



    EXPECT_FALSE(dfa.Search("", "", true, false, true, &failed, &ep, &matches));

}



TEST_F(DFASearchTest_433, SearchWithNullFailedPointer_433) {

    Prog prog;

    DFA dfa(&prog, Prog::MatchKind::kFullMatch, 1024);

    const char* ep = nullptr;

    SparseSet matches;



    EXPECT_DEATH({ dfa.Search("test", "", true, false, true, nullptr, &ep, &matches); }, ".*");

}



TEST_F(DFASearchTest_433, SearchWithNullEPPointer_433) {

    Prog prog;

    DFA dfa(&prog, Prog::MatchKind::kFullMatch, 1024);

    bool failed = false;

    SparseSet matches;



    EXPECT_DEATH({ dfa.Search("test", "", true, false, true, &failed, nullptr, &matches); }, ".*");

}



TEST_F(DFASearchTest_433, SearchWithNullMatchesPointer_433) {

    Prog prog;

    DFA dfa(&prog, Prog::MatchKind::kFullMatch, 1024);

    bool failed = false;

    const char* ep = nullptr;



    EXPECT_DEATH({ dfa.Search("test", "", true, false, true, &failed, &ep, nullptr); }, ".*");

}



TEST_F(DFAPossibleMatchRangeTest_433, PossibleMatchRangeWithNullMinPointer_433) {

    Prog prog;

    DFA dfa(&prog, Prog::MatchKind::kFullMatch, 1024);

    std::string max;

    

    EXPECT_DEATH({ dfa.PossibleMatchRange(nullptr, &max, 5); }, ".*");

}



TEST_F(DFAPossibleMatchRangeTest_433, PossibleMatchRangeWithNullMaxPointer_433) {

    Prog prog;

    DFA dfa(&prog, Prog::MatchKind::kFullMatch, 1024);

    std::string min;



    EXPECT_DEATH({ dfa.PossibleMatchRange(&min, nullptr, 5); }, ".*");

}



TEST_F(DFABuildAllStatesTest_433, BuildAllStatesWithValidCallback_433) {

    Prog prog;

    DFA dfa(&prog, Prog::MatchKind::kFullMatch, 1024);

    MockDFAStateCallback mock_callback;



    EXPECT_CALL(mock_callback, AddState(_)).Times(AtLeast(1));



    int result = dfa.BuildAllStates(mock_callback);

    EXPECT_GE(result, 0);

}



TEST_F(DFABuildAllStatesTest_433, BuildAllStatesWithNullCallback_433) {

    Prog prog;

    DFA dfa(&prog, Prog::MatchKind::kFullMatch, 1024);



    int result = dfa.BuildAllStates(nullptr);

    EXPECT_EQ(result, -1);

}
