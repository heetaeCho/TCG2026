#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/dfa.h"

#include "absl/strings/string_view.h"

#include "re2/sparse_set.h"



using ::testing::_;

using ::testing::MockFunction;

using ::testing::NotNull;



namespace re2 {



class MockProg : public Prog {

public:

    MOCK_METHOD(bool, SearchDFA, (absl::string_view text, absl::string_view context, Anchor anchor, MatchKind kind, absl::string_view* match0, bool* failed, SparseSet* matches), (override));

};



class DFA_Test_453 : public ::testing::Test {

protected:

    MockProg mock_prog;

    DFA dfa_under_test{&mock_prog, Prog::MatchKind::kFirstMatch, 1024};

};



TEST_F(DFA_Test_453, Search_ReturnsFalseWhenInitializationFails_453) {

    bool failed = false;

    const char* epp = nullptr;

    SparseSet matches;



    EXPECT_CALL(mock_prog, SearchDFA(_, _, _, Prog::MatchKind::kFirstMatch, NotNull(), &failed, NotNull()))

        .WillOnce([](absl::string_view text, absl::string_view context, Anchor anchor, MatchKind kind, absl::string_view* match0, bool* failed, SparseSet* matches) {

            *failed = true;

            return false;

        });



    EXPECT_FALSE(dfa_under_test.Search("test", "context", false, false, false, &failed, &epp, &matches));

    EXPECT_TRUE(failed);

}



TEST_F(DFA_Test_453, Search_ReturnsTrueForFullMatchStateAtStart_453) {

    bool failed = false;

    const char* epp = nullptr;

    SparseSet matches;



    EXPECT_CALL(mock_prog, SearchDFA(_, _, _, Prog::MatchKind::kFirstMatch, NotNull(), &failed, NotNull()))

        .WillOnce([](absl::string_view text, absl::string_view context, Anchor anchor, MatchKind kind, absl::string_view* match0, bool* failed, SparseSet* matches) {

            *failed = false;

            return true;

        });



    EXPECT_TRUE(dfa_under_test.Search("test", "context", false, false, false, &failed, &epp, &matches));

    EXPECT_EQ(epp, "test");

}



TEST_F(DFA_Test_453, Search_ReturnsTrueForFullMatchStateAtEnd_453) {

    bool failed = false;

    const char* epp = nullptr;

    SparseSet matches;



    EXPECT_CALL(mock_prog, SearchDFA(_, _, _, Prog::MatchKind::kFirstMatch, NotNull(), &failed, NotNull()))

        .WillOnce([](absl::string_view text, absl::string_view context, Anchor anchor, MatchKind kind, absl::string_view* match0, bool* failed, SparseSet* matches) {

            *failed = false;

            return true;

        });



    EXPECT_TRUE(dfa_under_test.Search("test", "context", false, true, false, &failed, &epp, &matches));

    EXPECT_EQ(epp, "test" + strlen("test"));

}



TEST_F(DFA_Test_453, Search_ReturnsFalseWhenAnalyzeSearchFails_453) {

    bool failed = false;

    const char* epp = nullptr;

    SparseSet matches;



    EXPECT_CALL(mock_prog, SearchDFA(_, _, _, Prog::MatchKind::kFirstMatch, NotNull(), &failed, NotNull()))

        .WillOnce([](absl::string_view text, absl::string_view context, Anchor anchor, MatchKind kind, absl::string_view* match0, bool* failed, SparseSet* matches) {

            *failed = true;

            return false;

        });



    EXPECT_FALSE(dfa_under_test.Search("test", "context", false, false, false, &failed, &epp, &matches));

    EXPECT_TRUE(failed);

}



TEST_F(DFA_Test_453, Search_ReturnsFalseWhenStartStateIsDeadState_453) {

    bool failed = false;

    const char* epp = nullptr;

    SparseSet matches;



    EXPECT_CALL(mock_prog, SearchDFA(_, _, _, Prog::MatchKind::kFirstMatch, NotNull(), &failed, NotNull()))

        .WillOnce([](absl::string_view text, absl::string_view context, Anchor anchor, MatchKind kind, absl::string_view* match0, bool* failed, SparseSet* matches) {

            *failed = false;

            return false;

        });



    EXPECT_FALSE(dfa_under_test.Search("test", "context", false, false, false, &failed, &epp, &matches));

}



TEST_F(DFA_Test_453, Search_ReturnsTrueWhenFastSearchLoopSucceeds_453) {

    bool failed = false;

    const char* epp = nullptr;

    SparseSet matches;



    EXPECT_CALL(mock_prog, SearchDFA(_, _, _, Prog::MatchKind::kFirstMatch, NotNull(), &failed, NotNull()))

        .WillOnce([](absl::string_view text, absl::string_view context, Anchor anchor, MatchKind kind, absl::string_view* match0, bool* failed, SparseSet* matches) {

            *failed = false;

            return true;

        });



    EXPECT_TRUE(dfa_under_test.Search("test", "context", false, false, false, &failed, &epp, &matches));

}



TEST_F(DFA_Test_453, Search_ReturnsFalseWhenFastSearchLoopFails_453) {

    bool failed = false;

    const char* epp = nullptr;

    SparseSet matches;



    EXPECT_CALL(mock_prog, SearchDFA(_, _, _, Prog::MatchKind::kFirstMatch, NotNull(), &failed, NotNull()))

        .WillOnce([](absl::string_view text, absl::string_view context, Anchor anchor, MatchKind kind, absl::string_view* match0, bool* failed, SparseSet* matches) {

            *failed = true;

            return false;

        });



    EXPECT_FALSE(dfa_under_test.Search("test", "context", false, false, false, &failed, &epp, &matches));

}



} // namespace re2
