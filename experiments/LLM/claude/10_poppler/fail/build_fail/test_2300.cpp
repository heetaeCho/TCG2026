#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler headers
#include "poppler-action.h"
#include "poppler-private.h"
#include "poppler-media.h"
#include "Link.h"
#include "Object.h"

// Since build_rendition is static in the .cc file, we need to include it
// or test through the public API that calls it.
// In poppler glib, _poppler_action_new is typically the public entry point.

using ::testing::Return;
using ::testing::_;

class BuildRenditionTest_2300 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that build_rendition correctly sets the operation from LinkRendition
TEST_F(BuildRenditionTest_2300, SetsOperationFromLink_2300)
{
    // Create a LinkRendition with a known operation
    // We test through _poppler_action_new or equivalent public interface
    // that internally calls build_rendition
    
    Object obj;
    obj.initDict(nullptr);
    
    // Build a rendition link action and convert it to PopplerAction
    // Testing through the public poppler glib action creation interface
    LinkRendition linkRendition(nullptr);
    
    PopplerAction action;
    memset(&action, 0, sizeof(PopplerAction));
    
    // The operation should be copied from the link
    RenditionOperation expectedOp = linkRendition.getOperation();
    
    // Since build_rendition is static, we test via _poppler_action_new
    // which is the glib-internal public function
    PopplerAction *pAction = _poppler_action_new(nullptr, static_cast<LinkAction*>(&linkRendition), nullptr);
    
    if (pAction) {
        EXPECT_EQ(pAction->rendition.op, static_cast<int>(expectedOp));
        poppler_action_free(pAction);
    }
}

// Test that when media is nullptr, rendition.media remains null
TEST_F(BuildRenditionTest_2300, NullMediaSetsNullMedia_2300)
{
    // Create a LinkRendition where getMedia() returns nullptr
    LinkRendition linkRendition(nullptr);
    
    if (linkRendition.getMedia() == nullptr) {
        PopplerAction *pAction = _poppler_action_new(nullptr, static_cast<LinkAction*>(&linkRendition), nullptr);
        if (pAction) {
            EXPECT_EQ(pAction->rendition.media, nullptr);
            poppler_action_free(pAction);
        }
    }
}

// Test that when media is present, rendition.media is created
TEST_F(BuildRenditionTest_2300, NonNullMediaCreatesMedia_2300)
{
    // Build a proper Object that has media rendition info
    // This requires constructing a valid LinkRendition with media
    Object mediaObj;
    Object renditionObj;
    
    // Construct with an object that has media rendition
    // The exact construction depends on the Object/Dict API
    LinkRendition linkRendition(&renditionObj);
    
    PopplerAction *pAction = _poppler_action_new(nullptr, static_cast<LinkAction*>(&linkRendition), nullptr);
    
    if (pAction) {
        if (linkRendition.getMedia() != nullptr) {
            EXPECT_NE(pAction->rendition.media, nullptr);
        } else {
            EXPECT_EQ(pAction->rendition.media, nullptr);
        }
        poppler_action_free(pAction);
    }
}

// Test operation values are correctly propagated
TEST_F(BuildRenditionTest_2300, OperationValuePreserved_2300)
{
    LinkRendition linkRendition(nullptr);
    
    PopplerAction *pAction = _poppler_action_new(nullptr, static_cast<LinkAction*>(&linkRendition), nullptr);
    
    if (pAction) {
        // The operation in the action should match the source
        EXPECT_EQ(pAction->rendition.op, static_cast<int>(linkRendition.getOperation()));
        poppler_action_free(pAction);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
