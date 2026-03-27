// TEST_ID = 310
//
// Unit tests for LinkRendition::hasScreenAnnot()
// File under test: ./TestProjects/poppler/poppler/Link.h

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class LinkRenditionTest_310 : public ::testing::Test {};

TEST_F(LinkRenditionTest_310, HasScreenAnnot_DoesNotThrowOnDefaultObject_310)
{
    // We intentionally avoid assuming how LinkRendition parses the Object.
    // This is a black-box safety/smoke test: the public method should be callable.
    Object obj;

    ASSERT_NO_THROW({
        LinkRendition rendition(&obj);
        (void)rendition.hasScreenAnnot();
    });
}

TEST_F(LinkRenditionTest_310, HasScreenAnnot_IsConsistentAcrossMultipleCalls_310)
{
    Object obj;
    LinkRendition rendition(&obj);

    bool first = false;
    bool second = false;

    ASSERT_NO_THROW({ first = rendition.hasScreenAnnot(); });
    ASSERT_NO_THROW({ second = rendition.hasScreenAnnot(); });

    EXPECT_EQ(first, second);
}

TEST_F(LinkRenditionTest_310, HasScreenAnnot_ConsistentWithGetScreenAnnotInvalidness_310)
{
    // The interface exposes both hasScreenAnnot() and getScreenAnnot().
    // Observably, hasScreenAnnot() should match whether getScreenAnnot() equals Ref::INVALID().
    Object obj;
    LinkRendition rendition(&obj);

    ASSERT_NO_THROW({
        const bool has = rendition.hasScreenAnnot();
        const Ref r = rendition.getScreenAnnot();

        // Ref is expected to support != as used by LinkRendition::hasScreenAnnot().
        const bool nonInvalid = (r != Ref::INVALID());
        EXPECT_EQ(has, nonInvalid);
    });
}

TEST_F(LinkRenditionTest_310, HasScreenAnnot_WorksThroughConstReference_310)
{
    Object obj;
    LinkRendition rendition(&obj);
    const LinkRendition& cref = rendition;

    ASSERT_NO_THROW({
        const bool has1 = cref.hasScreenAnnot();
        const bool has2 = cref.hasScreenAnnot();
        EXPECT_EQ(has1, has2);
    });
}

} // namespace