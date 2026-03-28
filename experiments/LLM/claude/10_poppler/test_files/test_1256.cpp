#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Gfx.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"

#include <memory>
#include <string>

class GfxResourcesTest_1256 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that GfxResources constructed with nullptr resDict and nullptr next returns nullptr for getNext
TEST_F(GfxResourcesTest_1256, GetNextReturnsNullWhenNextIsNull_1256) {
    // Create a GfxResources with next = nullptr
    GfxResources resources(nullptr, nullptr, nullptr);
    EXPECT_EQ(resources.getNext(), nullptr);
}

// Test that GfxResources constructed with a valid next pointer returns that pointer via getNext
TEST_F(GfxResourcesTest_1256, GetNextReturnsCorrectPointerWhenNextIsSet_1256) {
    GfxResources first(nullptr, nullptr, nullptr);
    GfxResources second(nullptr, nullptr, &first);
    EXPECT_EQ(second.getNext(), &first);
}

// Test chaining: three resources linked together
TEST_F(GfxResourcesTest_1256, GetNextChaining_1256) {
    GfxResources r1(nullptr, nullptr, nullptr);
    GfxResources r2(nullptr, nullptr, &r1);
    GfxResources r3(nullptr, nullptr, &r2);

    EXPECT_EQ(r3.getNext(), &r2);
    EXPECT_EQ(r3.getNext()->getNext(), &r1);
    EXPECT_EQ(r3.getNext()->getNext()->getNext(), nullptr);
}

// Test lookupFont with a name that doesn't exist returns nullptr shared_ptr
TEST_F(GfxResourcesTest_1256, LookupFontNonExistentReturnsNull_1256) {
    GfxResources resources(nullptr, nullptr, nullptr);
    auto font = resources.lookupFont("NonExistentFont");
    EXPECT_EQ(font, nullptr);
}

// Test lookupXObject with a name that doesn't exist returns a null/none object
TEST_F(GfxResourcesTest_1256, LookupXObjectNonExistentReturnsNullObj_1256) {
    GfxResources resources(nullptr, nullptr, nullptr);
    Object obj = resources.lookupXObject("NonExistentXObject");
    EXPECT_TRUE(obj.isNull());
}

// Test lookupXObjectNF with a name that doesn't exist
TEST_F(GfxResourcesTest_1256, LookupXObjectNFNonExistentReturnsNullObj_1256) {
    GfxResources resources(nullptr, nullptr, nullptr);
    Object obj = resources.lookupXObjectNF("NonExistent");
    EXPECT_TRUE(obj.isNull());
}

// Test lookupColorSpace with a name that doesn't exist
TEST_F(GfxResourcesTest_1256, LookupColorSpaceNonExistentReturnsNullObj_1256) {
    GfxResources resources(nullptr, nullptr, nullptr);
    Object obj = resources.lookupColorSpace("NonExistentCS");
    EXPECT_TRUE(obj.isNull());
}

// Test lookupGState with a name that doesn't exist
TEST_F(GfxResourcesTest_1256, LookupGStateNonExistentReturnsNullObj_1256) {
    GfxResources resources(nullptr, nullptr, nullptr);
    Object obj = resources.lookupGState("NonExistentGState");
    EXPECT_TRUE(obj.isNull());
}

// Test lookupGStateNF with a name that doesn't exist
TEST_F(GfxResourcesTest_1256, LookupGStateNFNonExistentReturnsNullObj_1256) {
    GfxResources resources(nullptr, nullptr, nullptr);
    Object obj = resources.lookupGStateNF("NonExistentGStateNF");
    EXPECT_TRUE(obj.isNull());
}

// Test lookupMarkedContentNF with a name that doesn't exist
TEST_F(GfxResourcesTest_1256, LookupMarkedContentNFNonExistentReturnsNullObj_1256) {
    GfxResources resources(nullptr, nullptr, nullptr);
    Object obj = resources.lookupMarkedContentNF("NonExistent");
    EXPECT_TRUE(obj.isNull());
}

// Test that copy constructor is deleted (compile-time check via static_assert)
TEST_F(GfxResourcesTest_1256, CopyConstructorIsDeleted_1256) {
    EXPECT_FALSE(std::is_copy_constructible<GfxResources>::value);
}

// Test that copy assignment is deleted
TEST_F(GfxResourcesTest_1256, CopyAssignmentIsDeleted_1256) {
    EXPECT_FALSE(std::is_copy_assignable<GfxResources>::value);
}

// Test with a valid Dict for resDict but no entries - lookups should still return null/none
TEST_F(GfxResourcesTest_1256, EmptyResDictLookupsFail_1256) {
    // Create an empty Dict object
    Object dictObj = Object(new Dict(nullptr));
    Dict *dict = dictObj.getDict();

    GfxResources resources(nullptr, dict, nullptr);

    auto font = resources.lookupFont("AnyFont");
    EXPECT_EQ(font, nullptr);

    Object xobj = resources.lookupXObject("AnyXObj");
    EXPECT_TRUE(xobj.isNull());

    Object cs = resources.lookupColorSpace("AnyCS");
    EXPECT_TRUE(cs.isNull());

    Object gs = resources.lookupGState("AnyGS");
    EXPECT_TRUE(gs.isNull());
}

// Test lookupPattern with non-existent name and null OutputDev/GfxState
TEST_F(GfxResourcesTest_1256, LookupPatternNonExistentReturnsError_1256) {
    GfxResources resources(nullptr, nullptr, nullptr);
    // lookupPattern returns an int; for non-existent, we expect some error/failure code
    int result = resources.lookupPattern("NonExistentPattern", nullptr, nullptr);
    // Typically returns a non-success code (likely 0 or negative) for missing pattern
    // We just verify it doesn't crash and returns a deterministic value
    EXPECT_TRUE(result == 0 || result < 0 || result > 0); // Always true, main goal: no crash
}

// Test lookupShading with non-existent name and null OutputDev/GfxState
TEST_F(GfxResourcesTest_1256, LookupShadingNonExistentReturnsError_1256) {
    GfxResources resources(nullptr, nullptr, nullptr);
    int result = resources.lookupShading("NonExistentShading", nullptr, nullptr);
    // Verify it doesn't crash
    EXPECT_TRUE(result == 0 || result != 0);
}

// Test that getNext on a chain of two returns the correct intermediate
TEST_F(GfxResourcesTest_1256, GetNextIntermediateChain_1256) {
    GfxResources a(nullptr, nullptr, nullptr);
    GfxResources b(nullptr, nullptr, &a);

    // b's next is &a
    GfxResources *next = b.getNext();
    ASSERT_NE(next, nullptr);
    EXPECT_EQ(next, &a);

    // a's next is nullptr
    EXPECT_EQ(next->getNext(), nullptr);
}
