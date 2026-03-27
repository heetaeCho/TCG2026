// File: link_rendition_getScript_ut_314.cpp
// Unit tests for LinkRendition::getScript()
// The TEST_ID is 314

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class LinkRenditionTest_314 : public ::testing::Test {
protected:
    // Poppler's Object default-constructs to a null object in most builds.
    // We avoid assuming any particular parsing/behavior beyond "it is a valid Object instance".
    static Object MakeNullObject()
    {
        return Object();
    }
};

TEST_F(LinkRenditionTest_314, GetScript_ReturnsStableReferenceAcrossCalls_314)
{
    Object obj = MakeNullObject();
    LinkRendition action(&obj);

    const std::string& s1 = action.getScript();
    const std::string& s2 = action.getScript();

    // Observable: getScript returns a const std::string&; repeated calls should be consistent.
    EXPECT_EQ(&s1, &s2);
    EXPECT_EQ(s1, s2);
}

TEST_F(LinkRenditionTest_314, GetScript_ReturnedReferenceUsableAsStringViewLike_314)
{
    Object obj = MakeNullObject();
    LinkRendition action(&obj);

    const std::string& s = action.getScript();

    // Boundary/robustness: should be safe to query basic string properties.
    // (No assumptions about whether it is empty or non-empty.)
    EXPECT_LE(0u, s.size());
    EXPECT_EQ(s.size(), s.length());
}

TEST_F(LinkRenditionTest_314, GetScript_CopyIsIndependentFromReturnedReference_314)
{
    Object obj = MakeNullObject();
    LinkRendition action(&obj);

    const std::string& s = action.getScript();
    std::string copy = s;

    // Mutating the copy must not affect the original reference (original is const anyway).
    copy.push_back('X');
    EXPECT_NE(copy, s);
}

TEST_F(LinkRenditionTest_314, GetScript_CanBeCalledOnConstObject_314)
{
    Object obj = MakeNullObject();
    const LinkRendition action(&obj);

    const std::string& s = action.getScript();

    // Minimal observable checks: valid reference and consistent value.
    EXPECT_EQ(s, action.getScript());
    EXPECT_EQ(&s, &action.getScript());
}

} // namespace