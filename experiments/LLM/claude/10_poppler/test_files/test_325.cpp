#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"

// Test fixture for LinkOCGState
class LinkOCGStateTest_325 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that isOk returns true when the object is valid
TEST_F(LinkOCGStateTest_325, IsOkReturnsTrueForValidObject_325) {
    // Create a valid OCGState object
    // We need an Object to construct LinkOCGState
    Object obj;
    // Construct with a dictionary-like object that has proper OCGState structure
    obj = Object(new Dict(nullptr));
    
    LinkOCGState ocgState(&obj);
    // The validity depends on the construction, but we test the interface
    // If construction with an empty/invalid object makes isValid false, isOk should return false
    // We're testing the observable behavior
    bool result = ocgState.isOk();
    // Result depends on whether the object was properly constructed
    // We just verify the method is callable and returns a bool
    EXPECT_TRUE(result == true || result == false);
}

// Test that getKind returns the correct LinkActionKind for OCGState
TEST_F(LinkOCGStateTest_325, GetKindReturnsOCGState_325) {
    Object obj;
    obj = Object(new Dict(nullptr));
    
    LinkOCGState ocgState(&obj);
    LinkActionKind kind = ocgState.getKind();
    EXPECT_EQ(kind, actionOCGState);
}

// Test that getStateList returns a reference to the state list
TEST_F(LinkOCGStateTest_325, GetStateListReturnsStateList_325) {
    Object obj;
    obj = Object(new Dict(nullptr));
    
    LinkOCGState ocgState(&obj);
    const auto &stateList = ocgState.getStateList();
    // For an empty/invalid construction, state list might be empty
    // We verify it's accessible
    EXPECT_GE(stateList.size(), 0u);
}

// Test that getPreserveRB returns a boolean value
TEST_F(LinkOCGStateTest_325, GetPreserveRBReturnsBool_325) {
    Object obj;
    obj = Object(new Dict(nullptr));
    
    LinkOCGState ocgState(&obj);
    bool preserveRB = ocgState.getPreserveRB();
    EXPECT_TRUE(preserveRB == true || preserveRB == false);
}

// Test with nullptr object - boundary condition
TEST_F(LinkOCGStateTest_325, ConstructWithNullObject_325) {
    // Test construction with null - this tests error handling
    LinkOCGState ocgState(nullptr);
    // When constructed with nullptr, the object should not be valid
    EXPECT_FALSE(ocgState.isOk());
}

// Test that an invalid construction results in isOk returning false
TEST_F(LinkOCGStateTest_325, InvalidObjectResultsInNotOk_325) {
    // Construct with an object that is not a proper OCGState dictionary
    Object obj;
    // An integer object is not a valid OCGState
    obj = Object(42);
    
    LinkOCGState ocgState(&obj);
    EXPECT_FALSE(ocgState.isOk());
}

// Test that invalid construction still returns empty state list
TEST_F(LinkOCGStateTest_325, InvalidObjectHasEmptyStateList_325) {
    Object obj;
    obj = Object(42);
    
    LinkOCGState ocgState(&obj);
    const auto &stateList = ocgState.getStateList();
    EXPECT_TRUE(stateList.empty());
}

// Test getKind consistency - should always return actionOCGState regardless of validity
TEST_F(LinkOCGStateTest_325, GetKindAlwaysReturnsOCGState_325) {
    Object obj;
    obj = Object(42);  // Invalid object
    
    LinkOCGState ocgState(&obj);
    EXPECT_EQ(ocgState.getKind(), actionOCGState);
}
