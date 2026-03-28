#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"
#include "Object.h"

class LinkOCGStateTest_327 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getStateList returns a reference to the state list vector
TEST_F(LinkOCGStateTest_327, GetStateListReturnsVector_327) {
    // Create an Object that represents an OCGState action
    // We need to construct a valid OCG state object
    Object obj;
    
    // Construct with a null/empty object - may result in invalid state
    obj = Object(new Dict(nullptr));
    LinkOCGState ocgState(&obj);
    
    // getStateList should return a reference to a vector (possibly empty if invalid)
    const std::vector<LinkOCGState::StateList> &stateList = ocgState.getStateList();
    // If the object was not properly formed, the state list may be empty
    // We just verify we can call the method without crashing
    EXPECT_GE(stateList.size(), 0u);
}

// Test that getKind returns appropriate LinkActionKind for OCGState
TEST_F(LinkOCGStateTest_327, GetKindReturnsOCGState_327) {
    Object obj;
    obj = Object(new Dict(nullptr));
    LinkOCGState ocgState(&obj);
    
    EXPECT_EQ(ocgState.getKind(), actionOCGState);
}

// Test isOk with an invalid/empty object
TEST_F(LinkOCGStateTest_327, IsOkWithInvalidObject_327) {
    Object obj;
    obj = Object(new Dict(nullptr));
    LinkOCGState ocgState(&obj);
    
    // With an improperly formed object, isOk might return false
    // We just verify the method is callable
    bool ok = ocgState.isOk();
    // The result depends on internal validation; we just check it doesn't crash
    (void)ok;
}

// Test getPreserveRB
TEST_F(LinkOCGStateTest_327, GetPreserveRB_327) {
    Object obj;
    obj = Object(new Dict(nullptr));
    LinkOCGState ocgState(&obj);
    
    // getPreserveRB should return a bool without crashing
    bool preserveRB = ocgState.getPreserveRB();
    // Default behavior with empty dict - just verify no crash
    (void)preserveRB;
}

// Test that getStateList returns a const reference (compile-time check essentially)
TEST_F(LinkOCGStateTest_327, GetStateListReturnsConstReference_327) {
    Object obj;
    obj = Object(new Dict(nullptr));
    LinkOCGState ocgState(&obj);
    
    const auto &stateList1 = ocgState.getStateList();
    const auto &stateList2 = ocgState.getStateList();
    
    // Both calls should return a reference to the same underlying vector
    EXPECT_EQ(&stateList1, &stateList2);
}

// Test constructing with a properly structured OCGState dictionary
TEST_F(LinkOCGStateTest_327, ConstructWithValidDict_327) {
    // Build a dict that has "State" array with proper entries
    // This tests the normal operation path
    
    Dict *dict = new Dict(nullptr);
    
    // Create the State array
    Object stateArray = Object(new Array(nullptr));
    
    dict->add("State", std::move(stateArray));
    
    Object obj(dict);
    LinkOCGState ocgState(&obj);
    
    // With a State array but no valid entries, stateList may be empty
    const auto &stateList = ocgState.getStateList();
    EXPECT_GE(stateList.size(), 0u);
}

// Test that multiple calls to getStateList are consistent
TEST_F(LinkOCGStateTest_327, GetStateListConsistency_327) {
    Object obj;
    obj = Object(new Dict(nullptr));
    LinkOCGState ocgState(&obj);
    
    const auto &list1 = ocgState.getStateList();
    size_t size1 = list1.size();
    
    const auto &list2 = ocgState.getStateList();
    size_t size2 = list2.size();
    
    EXPECT_EQ(size1, size2);
}
