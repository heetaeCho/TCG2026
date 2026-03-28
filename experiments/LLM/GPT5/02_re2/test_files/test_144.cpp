// File: charclass_end_tests_144.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using namespace re2;

class CharClassTest_144 : public ::testing::Test {
protected:
    CharClass* Make(size_t maxranges = 0) {
        return CharClass::New(maxranges);
    }
    void Cleanup(CharClass* cc) {
        if (cc) cc->Delete();
    }
};

// [144] end() is callable on a freshly-created (presumably empty) CharClass.
TEST_F(CharClassTest_144, EndCallableOnFreshInstance_144) {
    CharClass* cc = Make(0);
    ASSERT_NE(cc, nullptr);

    auto it = cc->end();
    // Just ensure we can obtain and hold an iterator (no deref, no assumptions).
    (void)it;

    Cleanup(cc);
}

// [144] For an empty CharClass, begin() == end().
TEST_F(CharClassTest_144, BeginEqualsEndWhenEmpty_144) {
    CharClass* cc = Make(0);
    ASSERT_NE(cc, nullptr);

    EXPECT_EQ(cc->begin(), cc->end());

    Cleanup(cc);
}

// [144] Multiple calls to end() return comparable/equal iterators.
TEST_F(CharClassTest_144, EndIsStableAcrossCalls_144) {
    CharClass* cc = Make(0);
    ASSERT_NE(cc, nullptr);

    auto e1 = cc->end();
    auto e2 = cc->end();
    EXPECT_EQ(e1, e2);

    Cleanup(cc);
}

// [144] begin()/end() are obtainable before deletion; we do not touch them after Delete().
TEST_F(CharClassTest_144, EndObtainBeforeDelete_NoUseAfter_144) {
    CharClass* cc = Make(0);
    ASSERT_NE(cc, nullptr);

    auto b = cc->begin();
    auto e = cc->end();
    // Only compare prior to delete; ensures no crash on simple use.
    EXPECT_EQ(b, e);

    Cleanup(cc);
}
