#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/dfa.h"

#include "absl/strings/string_view.h"



using namespace re2;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class DFAInterfaceTest_605 : public ::testing::Test {

protected:

    Prog* mock_prog_;

    DFA dfa_;



    DFAInterfaceTest_605() : mock_prog_(nullptr), dfa_(mock_prog_, Prog::MatchKind::kLongestMatch, 1024) {}



    virtual ~DFAInterfaceTest_605() {}

};



TEST_F(DFAInterfaceTest_605, OkReturnsTrueInitially_605) {

    EXPECT_TRUE(dfa_.ok());

}



TEST_F(DFAInterfaceTest_605, KindReturnsExpectedValue_605) {

    EXPECT_EQ(dfa_.kind(), Prog::MatchKind::kLongestMatch);

}



class MockDFAStateCallback : public Prog::DFAStateCallback {

public:

    MOCK_METHOD(void, Call, (State*, const std::string&), (override));

};



TEST_F(DFAInterfaceTest_605, BuildAllStatesCallsCallback_605) {

    MockDFAStateCallback mock_callback;

    EXPECT_CALL(mock_callback, Call(_, _)).Times(1);

    dfa_.BuildAllStates(mock_callback);

}



TEST_F(DFAInterfaceTest_605, PossibleMatchRangeReturnsFalseOnEmptyBounds_605) {

    std::string min, max;

    EXPECT_FALSE(dfa_.PossibleMatchRange(&min, &max, 0));

}



TEST_F(DFAInterfaceTest_605, SearchWithEmptyTextDoesNotCrash_605) {

    absl::string_view text = "";

    absl::string_view context = "";

    bool failed = false;

    const char* epp = nullptr;

    SparseSet matches;

    EXPECT_NO_THROW(dfa_.Search(text, context, false, false, true, &failed, &epp, &matches));

}



TEST_F(DFAInterfaceTest_605, SearchWithNullFailedPointerDoesNotCrash_605) {

    absl::string_view text = "test";

    absl::string_view context = "context";

    const char* epp = nullptr;

    SparseSet matches;

    EXPECT_NO_THROW(dfa_.Search(text, context, false, false, true, nullptr, &epp, &matches));

}



TEST_F(DFAInterfaceTest_605, SearchWithNullEppPointerDoesNotCrash_605) {

    absl::string_view text = "test";

    absl::string_view context = "context";

    bool failed = false;

    SparseSet matches;

    EXPECT_NO_THROW(dfa_.Search(text, context, false, false, true, &failed, nullptr, &matches));

}



TEST_F(DFAInterfaceTest_605, SearchWithNullMatchesPointerDoesNotCrash_605) {

    absl::string_view text = "test";

    absl::string_view context = "context";

    bool failed = false;

    const char* epp = nullptr;

    EXPECT_NO_THROW(dfa_.Search(text, context, false, false, true, &failed, &epp, nullptr));

}
