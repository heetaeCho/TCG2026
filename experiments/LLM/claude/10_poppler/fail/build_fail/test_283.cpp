#include <gtest/gtest.h>
#include <memory>
#include "Link.h"
#include "Object.h"
#include "GooString.h"

// Test that getKind() returns actionGoTo
TEST(LinkGoToTest_283, GetKindReturnsActionGoTo_283) {
    // Create a null object to pass to the constructor
    Object obj;
    obj.initNull();
    LinkGoTo linkGoTo(&obj);
    EXPECT_EQ(linkGoTo.getKind(), actionGoTo);
}

// Test that LinkGoTo with null object is not ok
TEST(LinkGoToTest_283, NullObjectIsNotOk_283) {
    Object obj;
    obj.initNull();
    LinkGoTo linkGoTo(&obj);
    // With a null object, there's no valid destination
    EXPECT_FALSE(linkGoTo.isOk());
}

// Test that getDest returns nullptr when constructed with null object
TEST(LinkGoToTest_283, GetDestReturnsNullForNullObject_283) {
    Object obj;
    obj.initNull();
    LinkGoTo linkGoTo(&obj);
    EXPECT_EQ(linkGoTo.getDest(), nullptr);
}

// Test that getNamedDest returns nullptr when constructed with null object
TEST(LinkGoToTest_283, GetNamedDestReturnsNullForNullObject_283) {
    Object obj;
    obj.initNull();
    LinkGoTo linkGoTo(&obj);
    EXPECT_EQ(linkGoTo.getNamedDest(), nullptr);
}

// Test with a named destination (string object)
TEST(LinkGoToTest_283, NamedDestFromStringObject_283) {
    Object obj;
    obj.initString(new GooString("Chapter1"));
    LinkGoTo linkGoTo(&obj);
    
    if (linkGoTo.isOk()) {
        EXPECT_NE(linkGoTo.getNamedDest(), nullptr);
        EXPECT_EQ(linkGoTo.getKind(), actionGoTo);
    }
}

// Test with a name object as named destination
TEST(LinkGoToTest_283, NamedDestFromNameObject_283) {
    Object obj;
    obj.initName("Chapter2");
    LinkGoTo linkGoTo(&obj);
    
    if (linkGoTo.isOk()) {
        EXPECT_NE(linkGoTo.getNamedDest(), nullptr);
        EXPECT_EQ(linkGoTo.getKind(), actionGoTo);
    }
}

// Test that getKind always returns actionGoTo regardless of construction
TEST(LinkGoToTest_283, GetKindAlwaysReturnsActionGoTo_283) {
    Object obj1;
    obj1.initNull();
    LinkGoTo linkGoTo1(&obj1);
    EXPECT_EQ(linkGoTo1.getKind(), actionGoTo);
    
    Object obj2;
    obj2.initString(new GooString("test"));
    LinkGoTo linkGoTo2(&obj2);
    EXPECT_EQ(linkGoTo2.getKind(), actionGoTo);
}

// Test that actionGoTo enum value is 0
TEST(LinkActionKindTest_283, ActionGoToValueIsZero_283) {
    EXPECT_EQ(actionGoTo, 0);
}

// Test with an array object (could represent a direct destination)
TEST(LinkGoToTest_283, ArrayObjectDestination_283) {
    Object obj;
    obj.initArray(nullptr); // This may not create a valid destination without proper xref
    LinkGoTo linkGoTo(&obj);
    // Just verify it doesn't crash and getKind is correct
    EXPECT_EQ(linkGoTo.getKind(), actionGoTo);
}

// Test that dest and namedDest are mutually exclusive or both can be null
TEST(LinkGoToTest_283, DestAndNamedDestConsistency_283) {
    Object obj;
    obj.initNull();
    LinkGoTo linkGoTo(&obj);
    
    // When not ok, both should be null
    if (!linkGoTo.isOk()) {
        EXPECT_EQ(linkGoTo.getDest(), nullptr);
        EXPECT_EQ(linkGoTo.getNamedDest(), nullptr);
    }
}
