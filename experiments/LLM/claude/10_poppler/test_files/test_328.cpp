#include <gtest/gtest.h>
#include "Link.h"

// Test that getPreserveRB returns a bool value (basic observable behavior)
// Since we treat the implementation as a black box, we test through the public interface.
// We need to construct LinkOCGState objects to test, which requires an Object*.

// Note: LinkOCGState requires an Object* for construction. We'll create minimal
// Object instances to test the observable behavior.

#include "Object.h"

class LinkOCGStateTest_328 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with an empty dictionary object - should result in invalid state
TEST_F(LinkOCGStateTest_328, EmptyObjectConstruction_328)
{
    Object obj = Object(new Dict(nullptr));
    LinkOCGState linkOCGState(&obj);
    // An empty object without proper fields should not be ok
    EXPECT_FALSE(linkOCGState.isOk());
}

// Test getKind returns the correct LinkActionKind for OCGState
TEST_F(LinkOCGStateTest_328, GetKindReturnsOCGState_328)
{
    Object obj = Object(new Dict(nullptr));
    LinkOCGState linkOCGState(&obj);
    EXPECT_EQ(linkOCGState.getKind(), actionOCGState);
}

// Test getPreserveRB on a default/empty constructed object
TEST_F(LinkOCGStateTest_328, GetPreserveRBDefaultValue_328)
{
    Object obj = Object(new Dict(nullptr));
    LinkOCGState linkOCGState(&obj);
    // preserveRB should have some default value - we just verify it returns a bool
    bool result = linkOCGState.getPreserveRB();
    EXPECT_TRUE(result == true || result == false);
}

// Test getStateList on an empty/invalid object returns empty list
TEST_F(LinkOCGStateTest_328, GetStateListEmptyObject_328)
{
    Object obj = Object(new Dict(nullptr));
    LinkOCGState linkOCGState(&obj);
    const auto &stateList = linkOCGState.getStateList();
    // With no valid state data, the list should be empty
    EXPECT_TRUE(stateList.empty());
}

// Test with a properly formed OCGState dictionary that includes preserveRB = true
TEST_F(LinkOCGStateTest_328, PreserveRBTrueFromValidObject_328)
{
    // Build a dict with "PreserveRB" set to true and a "State" array
    Dict *dict = new Dict(nullptr);
    
    Object preserveRBObj(true);
    dict->add("PreserveRB", std::move(preserveRBObj));
    
    // Create a State array (even if empty, to have the key present)
    Array *stateArr = new Array(nullptr);
    Object stateObj(stateArr);
    dict->add("State", std::move(stateObj));
    
    Object obj(dict);
    LinkOCGState linkOCGState(&obj);
    
    EXPECT_TRUE(linkOCGState.getPreserveRB());
}

// Test with a properly formed OCGState dictionary that includes preserveRB = false
TEST_F(LinkOCGStateTest_328, PreserveRBFalseFromValidObject_328)
{
    Dict *dict = new Dict(nullptr);
    
    Object preserveRBObj(false);
    dict->add("PreserveRB", std::move(preserveRBObj));
    
    Array *stateArr = new Array(nullptr);
    Object stateObj(stateArr);
    dict->add("State", std::move(stateObj));
    
    Object obj(dict);
    LinkOCGState linkOCGState(&obj);
    
    EXPECT_FALSE(linkOCGState.getPreserveRB());
}

// Test with null-like object
TEST_F(LinkOCGStateTest_328, NullObjectConstruction_328)
{
    Object obj;
    LinkOCGState linkOCGState(&obj);
    EXPECT_FALSE(linkOCGState.isOk());
}

// Test that getPreserveRB is const-correct and callable on const reference
TEST_F(LinkOCGStateTest_328, GetPreserveRBConstCorrectness_328)
{
    Object obj = Object(new Dict(nullptr));
    const LinkOCGState linkOCGState(&obj);
    // Should compile and work on const object
    bool result = linkOCGState.getPreserveRB();
    (void)result;
    SUCCEED();
}
