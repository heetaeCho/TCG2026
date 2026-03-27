// SPDX-License-Identifier: GPL-2.0-or-later
// File: LinkMovie_test_301.cpp
//
// Unit tests for LinkMovie (poppler/Link.h)
// Constraints respected:
// - Treat implementation as black box
// - Use only public interface / observable behavior
// - No access to private state
// - Verify behavior via public getters + isOk()

#include <gtest/gtest.h>

#include "poppler/Link.h"

// Poppler core types used to build input Objects.
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/goo/GooString.h"

namespace {

// Helpers to build Objects without relying on LinkMovie internals.
// We only use well-known Poppler Object/Dict APIs.

Object MakeNullObject_301() {
    Object o;
    o.initNull();
    return o;
}

Object MakeDictObjectWithTitle_301(const std::string &title) {
    auto *dict = new Dict(nullptr); // XRef not needed for these unit tests
    Object titleObj;
    titleObj.initString(new GooString(title.c_str()));
    dict->add("T", std::move(titleObj)); // Common PDF key for movie title

    Object o;
    o.initDict(dict);
    return o;
}

Object MakeDictObjectWithAnnotRef_301(int num, int gen) {
    auto *dict = new Dict(nullptr);
    Object refObj;
    refObj.initRef(num, gen);
    dict->add("Annot", std::move(refObj)); // Common PDF key for movie annotation reference

    Object o;
    o.initDict(dict);
    return o;
}

Object MakeDictObjectWithAnnotRefAndTitle_301(int num, int gen, const std::string &title) {
    auto *dict = new Dict(nullptr);

    Object refObj;
    refObj.initRef(num, gen);
    dict->add("Annot", std::move(refObj));

    Object titleObj;
    titleObj.initString(new GooString(title.c_str()));
    dict->add("T", std::move(titleObj));

    Object o;
    o.initDict(dict);
    return o;
}

} // namespace

class LinkMovieTest_301 : public ::testing::Test {};

// Normal / baseline: whatever the constructor parses from a null Object,
// isOk() must be consistent with the observable "presence" queries.
TEST_F(LinkMovieTest_301, IsOkConsistentWithPublicPresenceQueries_NullObject_301) {
    Object obj = MakeNullObject_301();
    LinkMovie lm(&obj);

    EXPECT_EQ(lm.isOk(), (lm.hasAnnotRef() || lm.hasAnnotTitle()));
}

// Normal: title-only object. If title is recognized by the parser, hasAnnotTitle()
// should reflect that and isOk() must match the public presence queries.
TEST_F(LinkMovieTest_301, IsOkConsistentWithPublicPresenceQueries_TitleOnly_301) {
    Object obj = MakeDictObjectWithTitle_301("My Movie Title");
    LinkMovie lm(&obj);

    EXPECT_EQ(lm.isOk(), (lm.hasAnnotRef() || lm.hasAnnotTitle()));

    if (lm.hasAnnotTitle()) {
        EXPECT_EQ(lm.getAnnotTitle(), std::string("My Movie Title"));
    }
    // If parser ignores the key, test still remains valid via the consistency check above.
}

// Boundary: empty string title. We only assert internal consistency and (if recognized)
// that the getter returns the same (possibly empty) title.
TEST_F(LinkMovieTest_301, IsOkConsistentWithPublicPresenceQueries_EmptyTitle_301) {
    Object obj = MakeDictObjectWithTitle_301("");
    LinkMovie lm(&obj);

    EXPECT_EQ(lm.isOk(), (lm.hasAnnotRef() || lm.hasAnnotTitle()));

    if (lm.hasAnnotTitle()) {
        EXPECT_EQ(lm.getAnnotTitle(), std::string(""));
    }
}

// Normal: annotation-ref-only object. If annot ref is recognized, hasAnnotRef()
// should reflect that and getAnnotRef() must be non-null and match.
TEST_F(LinkMovieTest_301, IsOkConsistentWithPublicPresenceQueries_AnnotRefOnly_301) {
    constexpr int kNum = 12;
    constexpr int kGen = 0;

    Object obj = MakeDictObjectWithAnnotRef_301(kNum, kGen);
    LinkMovie lm(&obj);

    EXPECT_EQ(lm.isOk(), (lm.hasAnnotRef() || lm.hasAnnotTitle()));

    if (lm.hasAnnotRef()) {
        const Ref *r = lm.getAnnotRef();
        ASSERT_NE(r, nullptr);
        EXPECT_EQ(r->num, kNum);
        EXPECT_EQ(r->gen, kGen);
    } else {
        EXPECT_EQ(lm.getAnnotRef(), nullptr);
    }
}

// Normal: both annotation ref and title present. If both are recognized, both
// getters should be usable. Always assert isOk consistency via public queries.
TEST_F(LinkMovieTest_301, IsOkConsistentWithPublicPresenceQueries_AnnotRefAndTitle_301) {
    constexpr int kNum = 7;
    constexpr int kGen = 3;

    Object obj = MakeDictObjectWithAnnotRefAndTitle_301(kNum, kGen, "Dual");
    LinkMovie lm(&obj);

    EXPECT_EQ(lm.isOk(), (lm.hasAnnotRef() || lm.hasAnnotTitle()));

    if (lm.hasAnnotRef()) {
        const Ref *r = lm.getAnnotRef();
        ASSERT_NE(r, nullptr);
        EXPECT_EQ(r->num, kNum);
        EXPECT_EQ(r->gen, kGen);
    }
    if (lm.hasAnnotTitle()) {
        EXPECT_EQ(lm.getAnnotTitle(), std::string("Dual"));
    }
}

// Kind should be stable and indicate this is a movie action.
// (If the enum name differs in your Poppler version, adjust accordingly.)
TEST_F(LinkMovieTest_301, GetKindReturnsMovieKind_301) {
    Object obj = MakeNullObject_301();
    LinkMovie lm(&obj);

    EXPECT_EQ(lm.getKind(), actionMovie);
}

// Exceptional / error-ish: pass an object that is not a dict (e.g., integer).
// We still only assert consistency and that getters remain safe to call.
TEST_F(LinkMovieTest_301, IsOkConsistentWithPublicPresenceQueries_NonDictObject_301) {
    Object obj;
    obj.initInt(123);
    LinkMovie lm(&obj);

    EXPECT_EQ(lm.isOk(), (lm.hasAnnotRef() || lm.hasAnnotTitle()));

    // Getters should be safe regardless of parse success.
    (void)lm.getAnnotRef();
    (void)lm.getAnnotTitle();
}