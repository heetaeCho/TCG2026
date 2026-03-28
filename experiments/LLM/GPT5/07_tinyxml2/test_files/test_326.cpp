// File: ./TestProjects/tinyxml2/tests/test_xmldocument_depthtracker_326.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class DepthTrackerTest_326 : public ::testing::Test {};

TEST_F(DepthTrackerTest_326, ConstructAndDestructWithValidDocument_326) {
    // The only observable behavior available through the public interface is that
    // construction/destruction should be safe for a valid XMLDocument pointer.
    tinyxml2::XMLDocument doc(/*processEntities=*/true, tinyxml2::PRESERVE_WHITESPACE);

    {
        tinyxml2::XMLDocument::DepthTracker tracker(&doc);
        (void)tracker;
    }

    SUCCEED();
}

TEST_F(DepthTrackerTest_326, NestedTrackersWithSameDocumentDoNotCrash_326) {
    tinyxml2::XMLDocument doc(/*processEntities=*/false, tinyxml2::PRESERVE_WHITESPACE);

    {
        tinyxml2::XMLDocument::DepthTracker outer(&doc);
        {
            tinyxml2::XMLDocument::DepthTracker inner(&doc);
            (void)inner;
        }
        (void)outer;
    }

    SUCCEED();
}

TEST_F(DepthTrackerTest_326, HeapAllocatedTrackerCanBeDeleted_326) {
    tinyxml2::XMLDocument doc(/*processEntities=*/true, tinyxml2::PRESERVE_WHITESPACE);

    auto* tracker = new tinyxml2::XMLDocument::DepthTracker(&doc);
    delete tracker;

    SUCCEED();
}

#if GTEST_HAS_DEATH_TEST
TEST_F(DepthTrackerTest_326, ConstructWithNullDocumentDies_326) {
    // The constructor takes a raw pointer and the partial implementation shows it dereferences
    // the pointer immediately. Passing nullptr is therefore expected to crash.
    EXPECT_DEATH(
        {
            tinyxml2::XMLDocument::DepthTracker tracker(nullptr);
            (void)tracker;
        },
        ".*");
}
#endif

}  // namespace
