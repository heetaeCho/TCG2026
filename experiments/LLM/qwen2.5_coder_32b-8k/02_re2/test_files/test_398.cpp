#include <gtest/gtest.h>

#include "re2/prog.h"

#include <string>



using namespace re2;



class ProgTest_398 : public ::testing::Test {

protected:

    Prog* prog;

    virtual void SetUp() {

        prog = new Prog();

    }



    virtual void TearDown() {

        delete prog;

    }

};



TEST_F(ProgTest_398, ConfigurePrefixAccel_NormalOperation_398) {

    std::string prefix = "test";

    bool prefix_foldcase = true;

    prog->ConfigurePrefixAccel(prefix, prefix_foldcase);

}



TEST_F(ProgTest_398, ConfigurePrefixAccel_EmptyString_398) {

    std::string prefix = "";

    bool prefix_foldcase = false;

    prog->ConfigurePrefixAccel(prefix, prefix_foldcase);

}



TEST_F(ProgTest_398, PrefixAccel_ShiftDFA_NormalOperation_398) {

    const char data[] = "test";

    size_t size = sizeof(data) - 1; // Exclude null terminator

    prog->ConfigurePrefixAccel("test", true);

    const void* result = prog->PrefixAccel_ShiftDFA(data, size);

}



TEST_F(ProgTest_398, PrefixAccel_ShiftDFA_EmptyData_398) {

    const char data[] = "";

    size_t size = sizeof(data) - 1; // Exclude null terminator

    prog->ConfigurePrefixAccel("test", true);

    const void* result = prog->PrefixAccel_ShiftDFA(data, size);

}



TEST_F(ProgTest_398, PrefixAccel_FrontAndBack_NormalOperation_398) {

    const char data[] = "test";

    size_t size = sizeof(data) - 1; // Exclude null terminator

    prog->ConfigurePrefixAccel("test", true);

    const void* result = prog->PrefixAccel_FrontAndBack(data, size);

}



TEST_F(ProgTest_398, PrefixAccel_FrontAndBack_EmptyData_398) {

    const char data[] = "";

    size_t size = sizeof(data) - 1; // Exclude null terminator

    prog->ConfigurePrefixAccel("test", true);

    const void* result = prog->PrefixAccel_FrontAndBack(data, size);

}



TEST_F(ProgTest_398, Dump_NormalOperation_398) {

    std::string dump = prog->Dump();

    EXPECT_FALSE(dump.empty());

}



TEST_F(ProgTest_398, DumpUnanchored_NormalOperation_398) {

    std::string dump_unanchored = prog->DumpUnanchored();

    EXPECT_FALSE(dump_unanchored.empty());

}



TEST_F(ProgTest_398, DumpByteMap_NormalOperation_398) {

    prog->ComputeByteMap();

    std::string dump_byte_map = prog->DumpByteMap();

    EXPECT_FALSE(dump_byte_map.empty());

}



TEST_F(ProgTest_398, Optimize_NormalOperation_398) {

    prog->Optimize();

}



TEST_F(ProgTest_398, IsOnePass_NormalOperation_398) {

    bool is_one_pass = prog->IsOnePass();

}



TEST_F(ProgTest_398, SearchNFA_NormalOperation_398) {

    absl::string_view text("test");

    absl::string_view context;

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NOMATCH;

    absl::string_view match;

    int nmatch = 1;

    bool result = prog->SearchNFA(text, context, anchor, kind, &match, nmatch);

}



TEST_F(ProgTest_398, SearchDFA_NormalOperation_398) {

    absl::string_view text("test");

    absl::string_view context;

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NOMATCH;

    absl::string_view match0;

    bool failed;

    SparseSet matches;

    bool result = prog->SearchDFA(text, context, anchor, kind, &match0, &failed, &matches);

}



TEST_F(ProgTest_398, BuildEntireDFA_NormalOperation_398) {

    MatchKind kind = MATCH_NOMATCH;

    DFAStateCallback cb;

    int result = prog->BuildEntireDFA(kind, cb);

}



TEST_F(ProgTest_398, ComputeByteMap_NormalOperation_398) {

    prog->ComputeByteMap();

}



TEST_F(ProgTest_398, Flatten_NormalOperation_398) {

    prog->Flatten();

}



TEST_F(ProgTest_398, SearchOnePass_NormalOperation_398) {

    absl::string_view text("test");

    absl::string_view context;

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NOMATCH;

    absl::string_view match;

    int nmatch = 1;

    bool result = prog->SearchOnePass(text, context, anchor, kind, &match, nmatch);

}



TEST_F(ProgTest_398, SearchBitState_NormalOperation_398) {

    absl::string_view text("test");

    absl::string_view context;

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NOMATCH;

    absl::string_view match;

    int nmatch = 1;

    bool result = prog->SearchBitState(text, context, anchor, kind, &match, nmatch);

}



TEST_F(ProgTest_398, SearchNFA_EmptyText_398) {

    absl::string_view text("");

    absl::string_view context;

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NOMATCH;

    absl::string_view match;

    int nmatch = 1;

    bool result = prog->SearchNFA(text, context, anchor, kind, &match, nmatch);

}



TEST_F(ProgTest_398, SearchDFA_EmptyText_398) {

    absl::string_view text("");

    absl::string_view context;

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NOMATCH;

    absl::string_view match0;

    bool failed;

    SparseSet matches;

    bool result = prog->SearchDFA(text, context, anchor, kind, &match0, &failed, &matches);

}



TEST_F(ProgTest_398, SearchOnePass_EmptyText_398) {

    absl::string_view text("");

    absl::string_view context;

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NOMATCH;

    absl::string_view match;

    int nmatch = 1;

    bool result = prog->SearchOnePass(text, context, anchor, kind, &match, nmatch);

}



TEST_F(ProgTest_398, SearchBitState_EmptyText_398) {

    absl::string_view text("");

    absl::string_view context;

    Anchor anchor = ANCHOR_BOTH;

    MatchKind kind = MATCH_NOMATCH;

    absl::string_view match;

    int nmatch = 1;

    bool result = prog->SearchBitState(text, context, anchor, kind, &match, nmatch);

}



TEST_F(ProgTest_398, PossibleMatchRange_NormalOperation_398) {

    std::string min, max;

    int maxlen = 10;

    bool result = prog->PossibleMatchRange(&min, &max, maxlen);

}
