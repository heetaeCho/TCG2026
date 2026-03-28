#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "Annot.h"

// We need to access the static function. Since it's static in Annot.cc, we need to
// either include it or declare it. Since it's a static (file-scope) function,
// we can't directly call it from outside. We'll need to work around this.
// 
// One approach: We can include the .cc file to get access to the static function.
// This is a common technique for testing static functions.

// Forward declare or include the static function
// Since the function is static in Annot.cc, we include it to access it
// We need to be careful about multiple definitions

// Let's declare the function signature we want to test
// Since it's static, we may need to include the source file
#include "Annot.cc"

class SetChildDictEntryValueTest_2026 : public ::testing::Test {
protected:
    void SetUp() override {
        xref = new XRef();
    }

    void TearDown() override {
        delete xref;
    }

    XRef *xref;
};

// Test: When child dict already exists, the entry should be set in the existing child dict
TEST_F(SetChildDictEntryValueTest_2026, SetEntryInExistingChildDict_2026) {
    Dict *parentDict = new Dict(xref);
    Dict *childDict = new Dict(xref);
    
    // Add child dict to parent
    parentDict->set("ChildDict", Object(childDict));
    
    Ref refValue;
    refValue.num = 10;
    refValue.gen = 0;
    
    setChildDictEntryValue(parentDict, "ChildDict", "EntryName", refValue, xref);
    
    // Verify the child dict now has the entry
    Object childObj = parentDict->lookup("ChildDict");
    ASSERT_TRUE(childObj.isDict());
    
    Object entryObj = childObj.dictLookup("EntryName");
    ASSERT_TRUE(entryObj.isRef());
    EXPECT_EQ(entryObj.getRefNum(), 10);
    EXPECT_EQ(entryObj.getRefGen(), 0);
    
    parentDict->decRef();
}

// Test: When child dict does not exist, a new dict should be created and entry set
TEST_F(SetChildDictEntryValueTest_2026, CreateChildDictWhenNotExists_2026) {
    Dict *parentDict = new Dict(xref);
    
    Ref refValue;
    refValue.num = 5;
    refValue.gen = 2;
    
    setChildDictEntryValue(parentDict, "NewChild", "SomeEntry", refValue, xref);
    
    // Verify a child dict was created
    Object childObj = parentDict->lookup("NewChild");
    ASSERT_TRUE(childObj.isDict());
    
    // Verify the entry exists in the new child dict
    Object entryObj = childObj.dictLookup("SomeEntry");
    ASSERT_TRUE(entryObj.isRef());
    EXPECT_EQ(entryObj.getRefNum(), 5);
    EXPECT_EQ(entryObj.getRefGen(), 2);
    
    parentDict->decRef();
}

// Test: When parent has a non-dict value for childDictName, it should be replaced with a new dict
TEST_F(SetChildDictEntryValueTest_2026, ReplaceNonDictChildWithNewDict_2026) {
    Dict *parentDict = new Dict(xref);
    
    // Set a non-dict value for the child name
    parentDict->set("ChildDict", Object(42));
    
    Ref refValue;
    refValue.num = 7;
    refValue.gen = 1;
    
    setChildDictEntryValue(parentDict, "ChildDict", "Key", refValue, xref);
    
    // Verify the child is now a dict
    Object childObj = parentDict->lookup("ChildDict");
    ASSERT_TRUE(childObj.isDict());
    
    // Verify the entry exists
    Object entryObj = childObj.dictLookup("Key");
    ASSERT_TRUE(entryObj.isRef());
    EXPECT_EQ(entryObj.getRefNum(), 7);
    EXPECT_EQ(entryObj.getRefGen(), 1);
    
    parentDict->decRef();
}

// Test: Setting multiple entries in the same child dict
TEST_F(SetChildDictEntryValueTest_2026, SetMultipleEntriesInChildDict_2026) {
    Dict *parentDict = new Dict(xref);
    Dict *childDict = new Dict(xref);
    parentDict->set("ChildDict", Object(childDict));
    
    Ref refValue1;
    refValue1.num = 1;
    refValue1.gen = 0;
    
    Ref refValue2;
    refValue2.num = 2;
    refValue2.gen = 0;
    
    setChildDictEntryValue(parentDict, "ChildDict", "Entry1", refValue1, xref);
    setChildDictEntryValue(parentDict, "ChildDict", "Entry2", refValue2, xref);
    
    Object childObj = parentDict->lookup("ChildDict");
    ASSERT_TRUE(childObj.isDict());
    
    Object entry1 = childObj.dictLookup("Entry1");
    ASSERT_TRUE(entry1.isRef());
    EXPECT_EQ(entry1.getRefNum(), 1);
    
    Object entry2 = childObj.dictLookup("Entry2");
    ASSERT_TRUE(entry2.isRef());
    EXPECT_EQ(entry2.getRefNum(), 2);
    
    parentDict->decRef();
}

// Test: Overwriting an existing entry in child dict
TEST_F(SetChildDictEntryValueTest_2026, OverwriteExistingEntryInChildDict_2026) {
    Dict *parentDict = new Dict(xref);
    Dict *childDict = new Dict(xref);
    parentDict->set("ChildDict", Object(childDict));
    
    Ref refValue1;
    refValue1.num = 100;
    refValue1.gen = 0;
    
    setChildDictEntryValue(parentDict, "ChildDict", "Entry", refValue1, xref);
    
    Ref refValue2;
    refValue2.num = 200;
    refValue2.gen = 3;
    
    setChildDictEntryValue(parentDict, "ChildDict", "Entry", refValue2, xref);
    
    Object childObj = parentDict->lookup("ChildDict");
    ASSERT_TRUE(childObj.isDict());
    
    Object entryObj = childObj.dictLookup("Entry");
    ASSERT_TRUE(entryObj.isRef());
    EXPECT_EQ(entryObj.getRefNum(), 200);
    EXPECT_EQ(entryObj.getRefGen(), 3);
    
    parentDict->decRef();
}

// Test: Using Ref::INVALID() as the entry value
TEST_F(SetChildDictEntryValueTest_2026, SetInvalidRefAsEntryValue_2026) {
    Dict *parentDict = new Dict(xref);
    
    Ref refValue = Ref::INVALID();
    
    setChildDictEntryValue(parentDict, "ChildDict", "Entry", refValue, xref);
    
    Object childObj = parentDict->lookup("ChildDict");
    ASSERT_TRUE(childObj.isDict());
    
    Object entryObj = childObj.dictLookup("Entry");
    ASSERT_TRUE(entryObj.isRef());
    EXPECT_EQ(entryObj.getRefNum(), refValue.num);
    EXPECT_EQ(entryObj.getRefGen(), refValue.gen);
    
    parentDict->decRef();
}

// Test: Zero ref values
TEST_F(SetChildDictEntryValueTest_2026, SetZeroRefValues_2026) {
    Dict *parentDict = new Dict(xref);
    
    Ref refValue;
    refValue.num = 0;
    refValue.gen = 0;
    
    setChildDictEntryValue(parentDict, "ChildDict", "ZeroEntry", refValue, xref);
    
    Object childObj = parentDict->lookup("ChildDict");
    ASSERT_TRUE(childObj.isDict());
    
    Object entryObj = childObj.dictLookup("ZeroEntry");
    ASSERT_TRUE(entryObj.isRef());
    EXPECT_EQ(entryObj.getRefNum(), 0);
    EXPECT_EQ(entryObj.getRefGen(), 0);
    
    parentDict->decRef();
}

// Test: Parent dict with null value for child dict name
TEST_F(SetChildDictEntryValueTest_2026, ParentHasNullChildValue_2026) {
    Dict *parentDict = new Dict(xref);
    parentDict->set("ChildDict", Object(objNull));
    
    Ref refValue;
    refValue.num = 42;
    refValue.gen = 0;
    
    setChildDictEntryValue(parentDict, "ChildDict", "Entry", refValue, xref);
    
    Object childObj = parentDict->lookup("ChildDict");
    ASSERT_TRUE(childObj.isDict());
    
    Object entryObj = childObj.dictLookup("Entry");
    ASSERT_TRUE(entryObj.isRef());
    EXPECT_EQ(entryObj.getRefNum(), 42);
    
    parentDict->decRef();
}

// Test: Large ref numbers
TEST_F(SetChildDictEntryValueTest_2026, LargeRefNumbers_2026) {
    Dict *parentDict = new Dict(xref);
    
    Ref refValue;
    refValue.num = 999999;
    refValue.gen = 65535;
    
    setChildDictEntryValue(parentDict, "ChildDict", "LargeRefEntry", refValue, xref);
    
    Object childObj = parentDict->lookup("ChildDict");
    ASSERT_TRUE(childObj.isDict());
    
    Object entryObj = childObj.dictLookup("LargeRefEntry");
    ASSERT_TRUE(entryObj.isRef());
    EXPECT_EQ(entryObj.getRefNum(), 999999);
    EXPECT_EQ(entryObj.getRefGen(), 65535);
    
    parentDict->decRef();
}

// Test: Different child dict names in same parent
TEST_F(SetChildDictEntryValueTest_2026, DifferentChildDictNames_2026) {
    Dict *parentDict = new Dict(xref);
    
    Ref refValue1;
    refValue1.num = 10;
    refValue1.gen = 0;
    
    Ref refValue2;
    refValue2.num = 20;
    refValue2.gen = 0;
    
    setChildDictEntryValue(parentDict, "Child1", "Entry", refValue1, xref);
    setChildDictEntryValue(parentDict, "Child2", "Entry", refValue2, xref);
    
    Object child1Obj = parentDict->lookup("Child1");
    ASSERT_TRUE(child1Obj.isDict());
    Object entry1 = child1Obj.dictLookup("Entry");
    ASSERT_TRUE(entry1.isRef());
    EXPECT_EQ(entry1.getRefNum(), 10);
    
    Object child2Obj = parentDict->lookup("Child2");
    ASSERT_TRUE(child2Obj.isDict());
    Object entry2 = child2Obj.dictLookup("Entry");
    ASSERT_TRUE(entry2.isRef());
    EXPECT_EQ(entry2.getRefNum(), 20);
    
    parentDict->decRef();
}
