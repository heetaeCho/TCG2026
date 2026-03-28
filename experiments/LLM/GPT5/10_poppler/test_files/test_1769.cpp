// isTableScopeName_tests_1769.cc
#include <gtest/gtest.h>

#include "Object.h"

// NOTE:
// The function under test is declared `static` in StructElement.cc, so it has internal linkage.
// To test it as a black box through its real implementation, we include the .cc here so the
// function is part of this test translation unit.
//
// If your build already compiles/links StructElement.cc into the test binary, ensure your test
// target does NOT also compile StructElement.cc separately to avoid ODR/link issues.
#include "StructElement.cc"

namespace {

TEST(IsTableScopeNameTest_1769, ReturnsTrueForRowColumnBoth_1769)
{
    Object row(objName, "Row");
    Object column(objName, "Column");
    Object both(objName, "Both");

    EXPECT_TRUE(isTableScopeName(&row));
    EXPECT_TRUE(isTableScopeName(&column));
    EXPECT_TRUE(isTableScopeName(&both));
}

TEST(IsTableScopeNameTest_1769, ReturnsFalseForOtherNameValues_1769)
{
    Object other(objName, "Other");
    Object empty(objName, "");
    Object lowercase(objName, "row");
    Object whitespace(objName, " Row");
    Object suffix(objName, "Row ");

    EXPECT_FALSE(isTableScopeName(&other));
    EXPECT_FALSE(isTableScopeName(&empty));
    EXPECT_FALSE(isTableScopeName(&lowercase));
    EXPECT_FALSE(isTableScopeName(&whitespace));
    EXPECT_FALSE(isTableScopeName(&suffix));
}

TEST(IsTableScopeNameTest_1769, ReturnsFalseForNonNameTypes_1769)
{
    Object b(true);
    Object i(1);
    Object r(3.14);
    Object n = Object::null();
    Object e = Object::error();
    Object eof = Object::eof();

    EXPECT_FALSE(isTableScopeName(&b));
    EXPECT_FALSE(isTableScopeName(&i));
    EXPECT_FALSE(isTableScopeName(&r));
    EXPECT_FALSE(isTableScopeName(&n));
    EXPECT_FALSE(isTableScopeName(&e));
    EXPECT_FALSE(isTableScopeName(&eof));
}

TEST(IsTableScopeNameTest_1769, DoesNotMutateObjectObservableTypeOrName_1769)
{
    Object row(objName, "Row");
    ASSERT_TRUE(row.isName("Row"));

    const bool result = isTableScopeName(&row);

    EXPECT_TRUE(result);
    // Observable property should remain consistent after the call.
    EXPECT_TRUE(row.isName("Row"));
    EXPECT_TRUE(row.isName());
}

TEST(IsTableScopeNameTest_1769, BoundaryLongNameStillFalseUnlessExactMatch_1769)
{
    std::string longName(4096, 'A');
    Object longObj(objName, std::string_view(longName));

    EXPECT_FALSE(isTableScopeName(&longObj));

    Object rowWithExtra(objName, "RowX");
    Object prefixRow(objName, "XRow");
    Object embeddedRow(objName, "XRowX");

    EXPECT_FALSE(isTableScopeName(&rowWithExtra));
    EXPECT_FALSE(isTableScopeName(&prefixRow));
    EXPECT_FALSE(isTableScopeName(&embeddedRow));
}

} // namespace