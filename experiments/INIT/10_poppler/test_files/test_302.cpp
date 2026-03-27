// SPDX-License-Identifier: GPL-2.0-or-later
// File: link_movie_test_302.cc
//
// Unit tests for LinkMovie (Poppler)
// Constraints: treat implementation as black box; test only observable behavior via public API.

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

// TEST fixture (TEST_ID = 302)
class LinkMovieTest_302 : public ::testing::Test {
protected:
  // Create a "null/empty" Object in a way that is typically valid for Poppler's Object.
  // We avoid depending on any specific parsing behavior; the object is just an input handle.
  static Object MakeNullObject() {
    Object obj;
    // If the local Poppler fork requires explicit null init, these common APIs might exist.
    // Use ifdefs to keep this file portable across slightly different Object APIs.
#if defined(POPPLER_OBJECT_HAS_INIT_NULL)
    obj.initNull();
#elif defined(POPPLER_OBJECT_HAS_SET_TO_NULL)
    obj.setToNull();
#else
    // Many Poppler Object implementations default-construct to a null-like state.
    // No-op fallback.
#endif
    return obj;
  }

  static std::unique_ptr<LinkMovie> MakeLinkMovieFrom(Object* obj) {
    return std::make_unique<LinkMovie>(obj);
  }
};

} // namespace

// --- Normal operation ---

TEST_F(LinkMovieTest_302, GetKindAlwaysReturnsActionMovie_302) {
  Object obj = MakeNullObject();
  auto movie = MakeLinkMovieFrom(&obj);

  EXPECT_EQ(movie->getKind(), actionMovie);
}

TEST_F(LinkMovieTest_302, GetKindIsStableAcrossCalls_302) {
  Object obj = MakeNullObject();
  auto movie = MakeLinkMovieFrom(&obj);

  const auto k1 = movie->getKind();
  const auto k2 = movie->getKind();
  EXPECT_EQ(k1, k2);
  EXPECT_EQ(k1, actionMovie);
}

// --- Boundary / consistency checks (no inference of parsing rules) ---

TEST_F(LinkMovieTest_302, IsOkIsStableAcrossCalls_302) {
  Object obj = MakeNullObject();
  auto movie = MakeLinkMovieFrom(&obj);

  const bool ok1 = movie->isOk();
  const bool ok2 = movie->isOk();
  EXPECT_EQ(ok1, ok2);
}

TEST_F(LinkMovieTest_302, AnnotRefPresenceMatchesPointerNullness_302) {
  Object obj = MakeNullObject();
  auto movie = MakeLinkMovieFrom(&obj);

  const bool hasRef = movie->hasAnnotRef();
  const Ref* refPtr = movie->getAnnotRef();

  // Observable consistency expectation: if it says it "has" a ref, getter should be non-null;
  // if it says it doesn't, getter should be null.
  EXPECT_EQ(hasRef, refPtr != nullptr);
}

TEST_F(LinkMovieTest_302, AnnotTitlePresenceDoesNotChangeAcrossCalls_302) {
  Object obj = MakeNullObject();
  auto movie = MakeLinkMovieFrom(&obj);

  const bool hasTitle1 = movie->hasAnnotTitle();
  const bool hasTitle2 = movie->hasAnnotTitle();
  EXPECT_EQ(hasTitle1, hasTitle2);
}

TEST_F(LinkMovieTest_302, AnnotTitleReferenceIsStableAcrossCalls_302) {
  Object obj = MakeNullObject();
  auto movie = MakeLinkMovieFrom(&obj);

  const std::string& t1 = movie->getAnnotTitle();
  const std::string& t2 = movie->getAnnotTitle();

  // We don't assume any particular contents; only that the returned reference is usable and stable.
  EXPECT_EQ(&t1, &t2);
}

// --- Exceptional / error-ish cases (only as observable via interface) ---

TEST_F(LinkMovieTest_302, MethodsAreCallableEvenWhenNotOk_302) {
  Object obj = MakeNullObject();
  auto movie = MakeLinkMovieFrom(&obj);

  // Regardless of isOk() result, the public accessors should remain callable without crashing.
  // We avoid asserting specific values beyond cross-method consistency already tested.
  (void)movie->isOk();
  (void)movie->getKind();
  (void)movie->hasAnnotRef();
  (void)movie->hasAnnotTitle();
  (void)movie->getAnnotRef();
  (void)movie->getAnnotTitle();
  (void)movie->getOperation();

  SUCCEED();
}

// --- Compile-time / interface sanity (helps catch regressions without inferring behavior) ---

TEST_F(LinkMovieTest_302, InterfaceConstCorrectnessSmoke_302) {
  Object obj = MakeNullObject();
  auto movie = MakeLinkMovieFrom(&obj);

  const LinkMovie& cmovie = *movie;
  EXPECT_EQ(cmovie.getKind(), actionMovie);

  // Ensure const overloads are callable.
  (void)cmovie.isOk();
  (void)cmovie.hasAnnotRef();
  (void)cmovie.hasAnnotTitle();
  (void)cmovie.getAnnotRef();
  (void)cmovie.getAnnotTitle();
  (void)cmovie.getOperation();
}

TEST_F(LinkMovieTest_302, KindValueMatchesEnumConstant_302) {
  // This test is intentionally trivial but guards the public contract:
  // LinkMovie is a LinkAction of kind actionMovie.
  Object obj = MakeNullObject();
  auto movie = MakeLinkMovieFrom(&obj);

  EXPECT_EQ(static_cast<int>(movie->getKind()), static_cast<int>(actionMovie));
}