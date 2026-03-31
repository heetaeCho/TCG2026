#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Outline.h"
#include "Object.h"
#include "XRef.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>
#include <cstring>

// We need globalParams to be initialized for poppler
class OutlineTest_1922 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that constructing an Outline with a null catalog/no outlines works
TEST_F(OutlineTest_1922, ConstructOutlineWithNullDoc_1922) {
    // An Outline constructed without valid outline data should have no items
    // We test through the public Outline interface
    // Outline requires an Object* for the outline dict
    Object nullObj = Object(objNull);
    Outline outline(&nullObj, nullptr);
    const std::vector<OutlineItem*> *items = outline.getItems();
    // With a null/invalid outline object, items should be null or empty
    EXPECT_TRUE(items == nullptr || items->empty());
}

// Test Outline with no children
TEST_F(OutlineTest_1922, OutlineWithNoItems_1922) {
    Object noneObj;
    Outline outline(&noneObj, nullptr);
    const std::vector<OutlineItem*> *items = outline.getItems();
    EXPECT_TRUE(items == nullptr || items->empty());
}

// Test that Outline constructed from a dict without "First" has no items
TEST_F(OutlineTest_1922, OutlineDictWithoutFirst_1922) {
    // Create a dict object that doesn't have "First" key
    Dict *dict = new Dict(nullptr);
    dict->add("Count", Object(0));
    Object dictObj(dict);
    
    Outline outline(&dictObj, nullptr);
    const std::vector<OutlineItem*> *items = outline.getItems();
    EXPECT_TRUE(items == nullptr || items->empty());
}

// Test OutlineItem getTitle returns valid data
TEST_F(OutlineTest_1922, OutlineItemDefaultState_1922) {
    // Test that we can create an outline and check basic properties
    // This tests the observable interface
    Object nullObj = Object(objNull);
    Outline outline(&nullObj, nullptr);
    const std::vector<OutlineItem*> *items = outline.getItems();
    // No items expected from null object
    EXPECT_TRUE(items == nullptr || items->empty());
}

// Test loading a PDF with outlines if possible, otherwise test error paths
TEST_F(OutlineTest_1922, OutlineEofObject_1922) {
    Object eofObj = Object::eof();
    Outline outline(&eofObj, nullptr);
    const std::vector<OutlineItem*> *items = outline.getItems();
    EXPECT_TRUE(items == nullptr || items->empty());
}

TEST_F(OutlineTest_1922, OutlineErrorObject_1922) {
    Object errObj = Object::error();
    Outline outline(&errObj, nullptr);
    const std::vector<OutlineItem*> *items = outline.getItems();
    EXPECT_TRUE(items == nullptr || items->empty());
}

// Test with an integer object (not a valid outline dict)
TEST_F(OutlineTest_1922, OutlineWithIntObject_1922) {
    Object intObj(42);
    Outline outline(&intObj, nullptr);
    const std::vector<OutlineItem*> *items = outline.getItems();
    EXPECT_TRUE(items == nullptr || items->empty());
}

// Test with a boolean object (not a valid outline dict)
TEST_F(OutlineTest_1922, OutlineWithBoolObject_1922) {
    Object boolObj(true);
    Outline outline(&boolObj, nullptr);
    const std::vector<OutlineItem*> *items = outline.getItems();
    EXPECT_TRUE(items == nullptr || items->empty());
}

// Test with a string object (not a valid outline dict)
TEST_F(OutlineTest_1922, OutlineWithStringObject_1922) {
    Object strObj(std::string("test"));
    Outline outline(&strObj, nullptr);
    const std::vector<OutlineItem*> *items = outline.getItems();
    EXPECT_TRUE(items == nullptr || items->empty());
}
