#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Poppler core headers
#include "poppler/Link.h"
#include "poppler/PDFDoc.h"
#include "poppler/Array.h"
#include "poppler/Object.h"

// Poppler glib headers
extern "C" {
#include "glib/poppler.h"
#include "glib/poppler-private.h"
}

// Declaration of the function under test
extern "C" {
PopplerDest *_poppler_dest_new_goto(PopplerDocument *document, LinkDest *link_dest);
}

class PopplerDestNewGotoTest_2304 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing a nullptr LinkDest returns nullptr or handles gracefully
TEST_F(PopplerDestNewGotoTest_2304, NullLinkDestReturnsNull_2304)
{
    PopplerDest *dest = _poppler_dest_new_goto(nullptr, nullptr);
    // With null link_dest, function should return nullptr
    EXPECT_EQ(dest, nullptr);
}

// Test that passing a nullptr document with nullptr link_dest handles gracefully
TEST_F(PopplerDestNewGotoTest_2304, NullDocumentAndNullLinkDest_2304)
{
    PopplerDest *dest = _poppler_dest_new_goto(nullptr, nullptr);
    EXPECT_EQ(dest, nullptr);
}

// Test with a valid LinkDest that is not OK (invalid dest)
TEST_F(PopplerDestNewGotoTest_2304, InvalidLinkDestReturnsUnknownType_2304)
{
    // Create an empty array which should produce an invalid LinkDest
    auto xref = std::make_unique<XRef>();
    Array arr(xref.get());
    LinkDest linkDest(&arr);
    
    // linkDest.isOk() should be false for an empty array
    EXPECT_FALSE(linkDest.isOk());
    
    PopplerDest *dest = _poppler_dest_new_goto(nullptr, &linkDest);
    if (dest != nullptr) {
        // If it returns something, the type should indicate unknown
        EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);
        poppler_dest_free(dest);
    }
}

// Test creating a LinkDest with a valid Fit destination
TEST_F(PopplerDestNewGotoTest_2304, FitDestinationWithNullDocument_2304)
{
    // Build an array representing /Fit destination: [pageRef /Fit]
    auto xref = std::make_unique<XRef>();
    Array arr(xref.get());
    
    // Page number (integer, not a ref)
    arr.add(Object(1));
    // Destination type
    arr.add(Object(objName, "Fit"));
    
    LinkDest linkDest(&arr);
    
    if (linkDest.isOk()) {
        PopplerDest *dest = _poppler_dest_new_goto(nullptr, &linkDest);
        ASSERT_NE(dest, nullptr);
        EXPECT_EQ(dest->type, POPPLER_DEST_FIT);
        poppler_dest_free(dest);
    }
}

// Test creating a LinkDest with XYZ destination type
TEST_F(PopplerDestNewGotoTest_2304, XYZDestinationWithNullDocument_2304)
{
    auto xref = std::make_unique<XRef>();
    Array arr(xref.get());
    
    // Page number
    arr.add(Object(1));
    // Destination type XYZ
    arr.add(Object(objName, "XYZ"));
    // left, top, zoom
    arr.add(Object(100.0));
    arr.add(Object(200.0));
    arr.add(Object(1.5));
    
    LinkDest linkDest(&arr);
    
    if (linkDest.isOk()) {
        PopplerDest *dest = _poppler_dest_new_goto(nullptr, &linkDest);
        ASSERT_NE(dest, nullptr);
        EXPECT_EQ(dest->type, POPPLER_DEST_XYZ);
        EXPECT_DOUBLE_EQ(dest->left, 100.0);
        EXPECT_DOUBLE_EQ(dest->top, 200.0);
        EXPECT_DOUBLE_EQ(dest->zoom, 1.5);
        poppler_dest_free(dest);
    }
}

// Test FitH destination
TEST_F(PopplerDestNewGotoTest_2304, FitHDestinationWithNullDocument_2304)
{
    auto xref = std::make_unique<XRef>();
    Array arr(xref.get());
    
    arr.add(Object(1));
    arr.add(Object(objName, "FitH"));
    arr.add(Object(300.0)); // top
    
    LinkDest linkDest(&arr);
    
    if (linkDest.isOk()) {
        PopplerDest *dest = _poppler_dest_new_goto(nullptr, &linkDest);
        ASSERT_NE(dest, nullptr);
        EXPECT_EQ(dest->type, POPPLER_DEST_FITH);
        EXPECT_DOUBLE_EQ(dest->top, 300.0);
        poppler_dest_free(dest);
    }
}

// Test FitV destination
TEST_F(PopplerDestNewGotoTest_2304, FitVDestinationWithNullDocument_2304)
{
    auto xref = std::make_unique<XRef>();
    Array arr(xref.get());
    
    arr.add(Object(1));
    arr.add(Object(objName, "FitV"));
    arr.add(Object(150.0)); // left
    
    LinkDest linkDest(&arr);
    
    if (linkDest.isOk()) {
        PopplerDest *dest = _poppler_dest_new_goto(nullptr, &linkDest);
        ASSERT_NE(dest, nullptr);
        EXPECT_EQ(dest->type, POPPLER_DEST_FITV);
        EXPECT_DOUBLE_EQ(dest->left, 150.0);
        poppler_dest_free(dest);
    }
}

// Test FitR destination
TEST_F(PopplerDestNewGotoTest_2304, FitRDestinationWithNullDocument_2304)
{
    auto xref = std::make_unique<XRef>();
    Array arr(xref.get());
    
    arr.add(Object(1));
    arr.add(Object(objName, "FitR"));
    arr.add(Object(10.0));  // left
    arr.add(Object(20.0));  // bottom
    arr.add(Object(30.0));  // right
    arr.add(Object(40.0));  // top
    
    LinkDest linkDest(&arr);
    
    if (linkDest.isOk()) {
        PopplerDest *dest = _poppler_dest_new_goto(nullptr, &linkDest);
        ASSERT_NE(dest, nullptr);
        EXPECT_EQ(dest->type, POPPLER_DEST_FITR);
        EXPECT_DOUBLE_EQ(dest->left, 10.0);
        EXPECT_DOUBLE_EQ(dest->bottom, 20.0);
        EXPECT_DOUBLE_EQ(dest->right, 30.0);
        EXPECT_DOUBLE_EQ(dest->top, 40.0);
        poppler_dest_free(dest);
    }
}

// Test page number is set for non-ref page destinations
TEST_F(PopplerDestNewGotoTest_2304, PageNumberIsSetCorrectly_2304)
{
    auto xref = std::make_unique<XRef>();
    Array arr(xref.get());
    
    arr.add(Object(5)); // page 5
    arr.add(Object(objName, "Fit"));
    
    LinkDest linkDest(&arr);
    
    if (linkDest.isOk() && !linkDest.isPageRef()) {
        PopplerDest *dest = _poppler_dest_new_goto(nullptr, &linkDest);
        ASSERT_NE(dest, nullptr);
        EXPECT_EQ(dest->page_num, linkDest.getPageNum());
        poppler_dest_free(dest);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
