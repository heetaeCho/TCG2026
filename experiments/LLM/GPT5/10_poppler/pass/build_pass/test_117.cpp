// Dict_setXRef_tests_117.cpp

#include <gtest/gtest.h>

#include "poppler/Dict.h"
#include "poppler/XRef.h"

class DictTest_117 : public ::testing::Test {};

TEST_F(DictTest_117, SetXRefUpdatesGetXRef_117) {
  XRef xref1;
  XRef xref2;

  Dict dict(&xref1);
  EXPECT_EQ(dict.getXRef(), &xref1);

  dict.setXRef(&xref2);
  EXPECT_EQ(dict.getXRef(), &xref2);
}

TEST_F(DictTest_117, SetXRefAllowsNullptr_117) {
  XRef xref;

  Dict dict(&xref);
  ASSERT_EQ(dict.getXRef(), &xref);

  dict.setXRef(nullptr);
  EXPECT_EQ(dict.getXRef(), nullptr);
}

TEST_F(DictTest_117, SetXRefIsIdempotentForSamePointer_117) {
  XRef xref;

  Dict dict(&xref);
  EXPECT_EQ(dict.getXRef(), &xref);

  dict.setXRef(&xref);
  EXPECT_EQ(dict.getXRef(), &xref);

  dict.setXRef(&xref);
  EXPECT_EQ(dict.getXRef(), &xref);
}

TEST_F(DictTest_117, SetXRefCanBeChangedMultipleTimes_117) {
  XRef xref1;
  XRef xref2;
  XRef xref3;

  Dict dict(&xref1);
  EXPECT_EQ(dict.getXRef(), &xref1);

  dict.setXRef(&xref2);
  EXPECT_EQ(dict.getXRef(), &xref2);

  dict.setXRef(&xref3);
  EXPECT_EQ(dict.getXRef(), &xref3);

  dict.setXRef(&xref1);
  EXPECT_EQ(dict.getXRef(), &xref1);
}

TEST_F(DictTest_117, SetXRefDoesNotAffectOtherInstances_117) {
  XRef xref1;
  XRef xref2;
  XRef xref3;

  Dict dictA(&xref1);
  Dict dictB(&xref2);

  ASSERT_EQ(dictA.getXRef(), &xref1);
  ASSERT_EQ(dictB.getXRef(), &xref2);

  dictA.setXRef(&xref3);

  EXPECT_EQ(dictA.getXRef(), &xref3);
  EXPECT_EQ(dictB.getXRef(), &xref2);
}