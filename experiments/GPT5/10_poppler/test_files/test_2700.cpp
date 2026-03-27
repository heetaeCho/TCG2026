// doMergeFormDict_test_2700.cc
//
// Unit tests for static doMergeFormDict() in utils/pdfunite.cc
// Constraints:
// - Treat implementation as black box (no re-implementation / no private state access).
// - Test only via observable behavior (return value + public Object/Dict/Array APIs).
//
// NOTE: doMergeFormDict() is static in pdfunite.cc. We include that .cc directly so the
// symbol is visible in this test translation unit.

#include <gtest/gtest.h>

#include "poppler/Array.h"
#include "poppler/Dict.h"
#include "poppler/Object.h"

// Include the implementation file to access the static function under test.
#include "utils/pdfunite.cc"

namespace {

class DoMergeFormDictTest_2700 : public ::testing::Test {
protected:
  static Object MakeFieldsArrayObject(std::initializer_list<Ref> refs)
  {
    auto *arr = new Array(nullptr);
    Object arrObj(arr);

    for (const auto &r : refs) {
      arrObj.arrayAdd(Object(Ref{.num = r.num, .gen = r.gen}));
    }
    return arrObj;
  }

  static Object MakeFieldsArrayObjectWithNonRef(int value)
  {
    auto *arr = new Array(nullptr);
    Object arrObj(arr);
    arrObj.arrayAdd(Object(value)); // Non-ref element
    return arrObj;
  }

  static int GetFieldsLength(Dict *d)
  {
    Object fields = d->lookup("Fields");
    if (!fields.isArray()) {
      return -1;
    }
    return fields.arrayGetLength();
  }

  static Ref GetFieldsRefAt(Dict *d, int idx)
  {
    Object fields = d->lookup("Fields");
    EXPECT_TRUE(fields.isArray());
    EXPECT_GT(fields.arrayGetLength(), idx);
    const Object &o = fields.arrayGetNF(idx);
    EXPECT_TRUE(o.isRef());
    return o.getRef();
  }
};

TEST_F(DoMergeFormDictTest_2700, MergesRefsAndAppliesNumOffset_2700)
{
  Dict src(nullptr);
  Dict merge(nullptr);

  // src Fields: [ (1 0 R) ]
  src.add("Fields", MakeFieldsArrayObject({Ref{.num = 1, .gen = 0}}));

  // merge Fields: [ (10 2 R), (11 3 R) ]
  merge.add("Fields", MakeFieldsArrayObject({Ref{.num = 10, .gen = 2}, Ref{.num = 11, .gen = 3}}));

  ASSERT_EQ(GetFieldsLength(&src), 1);
  ASSERT_EQ(GetFieldsLength(&merge), 2);

  const int offset = 5;
  EXPECT_TRUE(doMergeFormDict(&src, &merge, offset));

  // Observable effect: src Fields length grows by merge Fields length.
  ASSERT_EQ(GetFieldsLength(&src), 3);

  // Existing first element unchanged
  {
    Ref r0 = GetFieldsRefAt(&src, 0);
    EXPECT_EQ(r0.num, 1);
    EXPECT_EQ(r0.gen, 0);
  }

  // New elements appended with num offset applied; gen preserved.
  {
    Ref r1 = GetFieldsRefAt(&src, 1);
    EXPECT_EQ(r1.num, 10 + offset);
    EXPECT_EQ(r1.gen, 2);
  }
  {
    Ref r2 = GetFieldsRefAt(&src, 2);
    EXPECT_EQ(r2.num, 11 + offset);
    EXPECT_EQ(r2.gen, 3);
  }
}

TEST_F(DoMergeFormDictTest_2700, ReturnsTrueWhenFieldsMissingOrNotArrays_2700)
{
  Dict src(nullptr);
  Dict merge(nullptr);

  // No "Fields" keys at all -> observable behavior should be: returns true (no error path hit).
  EXPECT_TRUE(doMergeFormDict(&src, &merge, /*numOffset=*/123));

  // Add a non-array "Fields" to src; merge still missing.
  src.add("Fields", Object(7));
  EXPECT_TRUE(doMergeFormDict(&src, &merge, /*numOffset=*/0));

  // Now make merge "Fields" non-array as well.
  merge.add("Fields", Object(false));
  EXPECT_TRUE(doMergeFormDict(&src, &merge, /*numOffset=*/0));
}

TEST_F(DoMergeFormDictTest_2700, EmptyMergeFieldsArrayMakesNoChanges_2700)
{
  Dict src(nullptr);
  Dict merge(nullptr);

  src.add("Fields", MakeFieldsArrayObject({Ref{.num = 3, .gen = 1}}));

  // merge Fields: empty array
  {
    auto *arr = new Array(nullptr);
    merge.add("Fields", Object(arr));
  }

  ASSERT_EQ(GetFieldsLength(&src), 1);
  ASSERT_EQ(GetFieldsLength(&merge), 0);

  EXPECT_TRUE(doMergeFormDict(&src, &merge, /*numOffset=*/999));

  // No additions expected
  ASSERT_EQ(GetFieldsLength(&src), 1);
  Ref r0 = GetFieldsRefAt(&src, 0);
  EXPECT_EQ(r0.num, 3);
  EXPECT_EQ(r0.gen, 1);
}

TEST_F(DoMergeFormDictTest_2700, NonRefElementInMergeFieldsReturnsFalseAndDoesNotAppend_2700)
{
  Dict src(nullptr);
  Dict merge(nullptr);

  src.add("Fields", MakeFieldsArrayObject({Ref{.num = 100, .gen = 0}}));

  // merge Fields contains a non-ref element -> should fail and return false.
  merge.add("Fields", MakeFieldsArrayObjectWithNonRef(/*value=*/42));

  ASSERT_EQ(GetFieldsLength(&src), 1);
  ASSERT_EQ(GetFieldsLength(&merge), 1);

  EXPECT_FALSE(doMergeFormDict(&src, &merge, /*numOffset=*/1));

  // Observable: src should not have appended anything (remains length 1).
  ASSERT_EQ(GetFieldsLength(&src), 1);
  Ref r0 = GetFieldsRefAt(&src, 0);
  EXPECT_EQ(r0.num, 100);
  EXPECT_EQ(r0.gen, 0);
}

TEST_F(DoMergeFormDictTest_2700, NegativeOffsetIsAppliedToRefNum_2700)
{
  Dict src(nullptr);
  Dict merge(nullptr);

  src.add("Fields", MakeFieldsArrayObject({Ref{.num = 1, .gen = 0}}));
  merge.add("Fields", MakeFieldsArrayObject({Ref{.num = 10, .gen = 7}}));

  const int offset = -3;
  EXPECT_TRUE(doMergeFormDict(&src, &merge, offset));

  ASSERT_EQ(GetFieldsLength(&src), 2);
  Ref r1 = GetFieldsRefAt(&src, 1);
  EXPECT_EQ(r1.num, 10 + offset);
  EXPECT_EQ(r1.gen, 7);
}

} // namespace