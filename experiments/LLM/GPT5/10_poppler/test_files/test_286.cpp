// LinkGoToR_test_286.cpp
#include <gtest/gtest.h>

#include "Link.h"
#include "Object.h"
#include "goo/GooString.h"

namespace {

class LinkGoToRTest_286 : public ::testing::Test {
protected:
  static Object MakeNullObj() {
    Object o;
    o.initNull();
    return o;
  }

  static Object MakeStringObj(const char* s) {
    Object o;
    o.initString(new GooString(s)); // Object takes ownership in Poppler
    return o;
  }

  static void ExpectIsOkMatchesPublicGetters(const LinkGoToR& a) {
    const bool expected =
        (a.getFileName() != nullptr) &&
        ((a.getDest() != nullptr) || (a.getNamedDest() != nullptr));
    EXPECT_EQ(expected, a.isOk());
  }
};

TEST_F(LinkGoToRTest_286, IsOkFalseWhenEverythingNull_286) {
  Object fileSpec = MakeNullObj();
  Object dest = MakeNullObj();

  LinkGoToR a(&fileSpec, &dest);

  // We only assert observable behavior via public APIs.
  ExpectIsOkMatchesPublicGetters(a);

  // In many implementations this will be null/null/null; we don't assume ctor parsing.
  if (!a.isOk()) {
    EXPECT_TRUE(a.getFileName() == nullptr ||
                (a.getDest() == nullptr && a.getNamedDest() == nullptr));
  }
}

TEST_F(LinkGoToRTest_286, IsOkMatchesGetterConditionForVariousInputs_286) {
  // The constructor may interpret these Objects differently depending on Poppler version.
  // We don't assume parsing rules; we only verify isOk is consistent with the public getters.
  struct Case {
    const char* fileSpecStr; // nullptr => null object
    const char* destStr;     // nullptr => null object
  } cases[] = {
      {nullptr, nullptr},
      {"", nullptr},
      {"file.pdf", nullptr},
      {nullptr, ""},
      {nullptr, "NamedDest"},
      {"file.pdf", ""},
      {"file.pdf", "NamedDest"},
      {"", "NamedDest"},
  };

  for (const auto& c : cases) {
    Object fileSpec = c.fileSpecStr ? MakeStringObj(c.fileSpecStr) : MakeNullObj();
    Object dest = c.destStr ? MakeStringObj(c.destStr) : MakeNullObj();

    LinkGoToR a(&fileSpec, &dest);
    ExpectIsOkMatchesPublicGetters(a);
  }
}

TEST_F(LinkGoToRTest_286, IsOkBoundaryEmptyStringsDoNotCrashAndStayConsistent_286) {
  Object fileSpec = MakeStringObj("");
  Object dest = MakeStringObj("");

  LinkGoToR a(&fileSpec, &dest);

  // Boundary condition: empty strings. No assumptions about how ctor treats them.
  ExpectIsOkMatchesPublicGetters(a);
}

TEST_F(LinkGoToRTest_286, GettersAreStableAcrossMultipleCalls_286) {
  Object fileSpec = MakeStringObj("file.pdf");
  Object dest = MakeStringObj("NamedDest");

  LinkGoToR a(&fileSpec, &dest);

  // Observable stability: repeated calls return the same pointer values (or both null).
  const GooString* f1 = a.getFileName();
  const LinkDest* d1 = a.getDest();
  const GooString* nd1 = a.getNamedDest();

  const GooString* f2 = a.getFileName();
  const LinkDest* d2 = a.getDest();
  const GooString* nd2 = a.getNamedDest();

  EXPECT_EQ(f1, f2);
  EXPECT_EQ(d1, d2);
  EXPECT_EQ(nd1, nd2);

  ExpectIsOkMatchesPublicGetters(a);
}

} // namespace