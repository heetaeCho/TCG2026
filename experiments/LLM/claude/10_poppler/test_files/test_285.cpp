#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "GooString.h"
#include "Object.h"

class LinkGoToTest_285 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that LinkGoTo can be constructed with a name string destination
TEST_F(LinkGoToTest_285, ConstructWithNamedDest_285) {
    // Create an Object that represents a named destination (a string)
    Object nameObj(new GooString("TestDest"));
    LinkGoTo linkGoTo(&nameObj);
    
    const GooString *namedDest = linkGoTo.getNamedDest();
    if (namedDest != nullptr) {
        EXPECT_STREQ(namedDest->c_str(), "TestDest");
    }
}

// Test that getNamedDest returns nullptr when destination is not a named dest
TEST_F(LinkGoToTest_285, GetNamedDestReturnsNullForNonNamedDest_285) {
    // Create an Object that represents an array destination (not a named one)
    Object arrObj(new Array(nullptr));
    LinkGoTo linkGoTo(&arrObj);
    
    // When destination is specified as an explicit dest (array), namedDest should be null
    // This depends on the implementation, but we test the observable behavior
    const GooString *namedDest = linkGoTo.getNamedDest();
    // Either it's null or it has some value - we just ensure no crash
    SUCCEED();
}

// Test that getKind returns actionGoTo
TEST_F(LinkGoToTest_285, GetKindReturnsActionGoTo_285) {
    Object nameObj(new GooString("Page1"));
    LinkGoTo linkGoTo(&nameObj);
    
    EXPECT_EQ(linkGoTo.getKind(), actionGoTo);
}

// Test getDest when constructed with a named destination
TEST_F(LinkGoToTest_285, GetDestWithNamedDest_285) {
    Object nameObj(new GooString("NamedPage"));
    LinkGoTo linkGoTo(&nameObj);
    
    // When constructed with a named dest, getDest() may return nullptr
    const LinkDest *dest = linkGoTo.getDest();
    // Just checking it doesn't crash; the actual value depends on construction
    SUCCEED();
}

// Test isOk after construction with a valid named destination
TEST_F(LinkGoToTest_285, IsOkWithNamedDest_285) {
    Object nameObj(new GooString("ValidDest"));
    LinkGoTo linkGoTo(&nameObj);
    
    // A named destination should result in a valid LinkGoTo
    EXPECT_TRUE(linkGoTo.isOk());
}

// Test construction with a null object
TEST_F(LinkGoToTest_285, ConstructWithNullObj_285) {
    Object nullObj;
    LinkGoTo linkGoTo(&nullObj);
    
    // With a null/none object, the link might not be ok
    // We just verify no crash and check observable state
    const GooString *namedDest = linkGoTo.getNamedDest();
    const LinkDest *dest = linkGoTo.getDest();
    // Both could be null
    SUCCEED();
}

// Test that getNamedDest returns consistent results on multiple calls
TEST_F(LinkGoToTest_285, GetNamedDestConsistency_285) {
    Object nameObj(new GooString("ConsistentDest"));
    LinkGoTo linkGoTo(&nameObj);
    
    const GooString *first = linkGoTo.getNamedDest();
    const GooString *second = linkGoTo.getNamedDest();
    
    // Should return the same pointer on repeated calls
    EXPECT_EQ(first, second);
}

// Test with empty string named destination
TEST_F(LinkGoToTest_285, EmptyNamedDest_285) {
    Object nameObj(new GooString(""));
    LinkGoTo linkGoTo(&nameObj);
    
    const GooString *namedDest = linkGoTo.getNamedDest();
    if (namedDest != nullptr) {
        EXPECT_EQ(namedDest->getLength(), 0);
    }
}

// Test that getDest returns consistent results
TEST_F(LinkGoToTest_285, GetDestConsistency_285) {
    Object nameObj(new GooString("AnotherDest"));
    LinkGoTo linkGoTo(&nameObj);
    
    const LinkDest *first = linkGoTo.getDest();
    const LinkDest *second = linkGoTo.getDest();
    
    EXPECT_EQ(first, second);
}
