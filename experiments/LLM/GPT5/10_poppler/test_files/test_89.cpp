// Object_isName_unittest.cpp
// Unit tests for poppler::Object::isName(std::string_view)
//
// Constraints honored:
// - Treat Object as a black box; only use public interface/observable behavior.
// - Do not access private state.
// - No internal-logic reimplementation.
// - Include normal/boundary/error-ish cases as observable.
// - TEST_ID appended to every test name (TEST_ID = 89).

#include <gtest/gtest.h>

#include <string>
#include <string_view>

// Poppler header under test
#include "poppler/Object.h"

namespace {

class ObjectIsNameTest_89 : public ::testing::Test {};

TEST_F(ObjectIsNameTest_89, ReturnsTrueForMatchingName_89)
{
    // Create a name object using public ctor (ObjType + string_view).
    Object obj(objName, std::string_view("Author"));

    EXPECT_TRUE(obj.isName("Author"));
}

TEST_F(ObjectIsNameTest_89, ReturnsFalseForDifferentName_89)
{
    Object obj(objName, std::string_view("Author"));

    EXPECT_FALSE(obj.isName("Title"));
}

TEST_F(ObjectIsNameTest_89, ReturnsFalseWhenObjectIsNotNameType_89)
{
    // Non-name object should never match a name string.
    Object objInt(123);

    EXPECT_FALSE(objInt.isName("123"));
    EXPECT_FALSE(objInt.isName("Author"));
}

TEST_F(ObjectIsNameTest_89, EmptyStringMatchesOnlyEmptyName_89)
{
    Object emptyName(objName, std::string_view(""));

    EXPECT_TRUE(emptyName.isName(""));
    EXPECT_FALSE(emptyName.isName(" "));
    EXPECT_FALSE(emptyName.isName("A"));
}

TEST_F(ObjectIsNameTest_89, ComparisonIsCaseSensitive_89)
{
    Object obj(objName, std::string_view("Name"));

    EXPECT_TRUE(obj.isName("Name"));
    EXPECT_FALSE(obj.isName("name"));
    EXPECT_FALSE(obj.isName("NAME"));
}

TEST_F(ObjectIsNameTest_89, HandlesStringViewWithEmbeddedNulls_89)
{
    // Boundary case: string_view can include '\0' in the middle.
    const char raw[] = {'A', '\0', 'B', 'C'};
    std::string_view withNull(raw, sizeof(raw));

    Object obj(objName, withNull);

    EXPECT_TRUE(obj.isName(withNull));

    // Different length should not match (e.g., stops at '\0' if treated as C-string elsewhere).
    EXPECT_FALSE(obj.isName(std::string_view(raw, 1)));          // "A"
    EXPECT_FALSE(obj.isName(std::string_view(raw, 2)));          // "A\0"
    EXPECT_FALSE(obj.isName(std::string_view(raw, 3)));          // "A\0B"
}

TEST_F(ObjectIsNameTest_89, WorksAfterMoveConstruction_89)
{
    Object src(objName, std::string_view("Moved"));
    Object dst(std::move(src));

    EXPECT_TRUE(dst.isName("Moved"));
    EXPECT_FALSE(dst.isName("Other"));
}

TEST_F(ObjectIsNameTest_89, WorksAfterMoveAssignment_89)
{
    Object src(objName, std::string_view("Assigned"));
    Object dst(0); // start from a different type
    dst = std::move(src);

    EXPECT_TRUE(dst.isName("Assigned"));
    EXPECT_FALSE(dst.isName("assigned"));
}

TEST_F(ObjectIsNameTest_89, ReturnsFalseForNullEofErrorObjects_89)
{
    // "Exceptional/error-ish" objects as observable through factory functions.
    Object n = Object::null();
    Object e = Object::eof();
    Object err = Object::error();

    EXPECT_FALSE(n.isName(""));
    EXPECT_FALSE(n.isName("Any"));

    EXPECT_FALSE(e.isName(""));
    EXPECT_FALSE(e.isName("Any"));

    EXPECT_FALSE(err.isName(""));
    EXPECT_FALSE(err.isName("Any"));
}

TEST_F(ObjectIsNameTest_89, ReturnsFalseForDefaultConstructedObject_89)
{
    // Default ctor exists per header; it starts as objNone.
    Object obj;

    EXPECT_FALSE(obj.isName(""));
    EXPECT_FALSE(obj.isName("Anything"));
}

} // namespace