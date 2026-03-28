#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// Forward declaration of the function under test
static size_t EstimateSizeForJPEG(const XMP_Node* xmpNode);

// We need to include the actual implementation since EstimateSizeForJPEG is a static function
// in XMPUtils.cpp. For testing purposes, we replicate the function here based on the provided code.
// In a real test environment, this would be linked or included appropriately.

// Macros that should be defined in the XMP SDK headers
#ifndef XMP_PropIsSimple
#define XMP_PropIsSimple(opt) (((opt) & kXMP_PropCompositeMask) == 0)
#endif

#ifndef XMP_PropIsArray
#define XMP_PropIsArray(opt) (((opt) & kXMP_PropValueIsArray) != 0)
#endif

// Redefine the static function for testing since it's static in the source file
static size_t EstimateSizeForJPEG(const XMP_Node* xmpNode)
{
    size_t estSize = 0;
    size_t nameSize = xmpNode->name.size();
    bool includeName = (!XMP_PropIsArray(xmpNode->parent->options));

    if (XMP_PropIsSimple(xmpNode->options)) {
        if (includeName) estSize += (nameSize + 3);
        estSize += xmpNode->value.size();
    } else if (XMP_PropIsArray(xmpNode->options)) {
        if (includeName) estSize += (2 * nameSize + 5);
        size_t arraySize = xmpNode->children.size();
        estSize += 9 + 10;
        estSize += arraySize * (8 + 9);
        for (size_t i = 0; i < arraySize; ++i) {
            estSize += EstimateSizeForJPEG(xmpNode->children[i]);
        }
    } else {
        // Struct
        if (includeName) estSize += (2 * nameSize + 5);
        estSize += 25;
        size_t fieldCount = xmpNode->children.size();
        for (size_t i = 0; i < fieldCount; ++i) {
            estSize += EstimateSizeForJPEG(xmpNode->children[i]);
        }
    }

    return estSize;
}

// Helper class to manage XMP_Node tree lifetime
class NodeManager {
public:
    ~NodeManager() {
        // Delete in reverse order to handle dependencies
        for (auto it = nodes_.rbegin(); it != nodes_.rend(); ++it) {
            // Clear children pointers to avoid double-delete since we manage all nodes
            (*it)->children.clear();
            (*it)->qualifiers.clear();
            delete *it;
        }
    }

    XMP_Node* createNode(XMP_Node* parent, const char* name, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, options);
        nodes_.push_back(node);
        return node;
    }

    XMP_Node* createNode(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options) {
        XMP_Node* node = new XMP_Node(parent, name, value, options);
        nodes_.push_back(node);
        return node;
    }

private:
    std::vector<XMP_Node*> nodes_;
};

class EstimateSizeForJPEGTest_1983 : public ::testing::Test {
protected:
    NodeManager mgr_;
};

// Test simple property where parent is NOT an array (includeName = true)
TEST_F(EstimateSizeForJPEGTest_1983, SimplePropertyWithName_1983) {
    // Parent is a struct (not an array), so includeName is true
    XMP_Node* parent = mgr_.createNode(nullptr, "parent", kXMP_PropValueIsStruct);
    XMP_Node* node = mgr_.createNode(parent, "propName", "value123", 0); // Simple property

    size_t result = EstimateSizeForJPEG(node);

    // nameSize = 8 ("propName"), valueSize = 8 ("value123")
    // includeName = true => estSize = (8 + 3) + 8 = 19
    size_t expected = (8 + 3) + 8;
    EXPECT_EQ(result, expected);
}

// Test simple property where parent IS an array (includeName = false)
TEST_F(EstimateSizeForJPEGTest_1983, SimplePropertyInArray_1983) {
    // Parent is an array, so includeName is false
    XMP_Node* parent = mgr_.createNode(nullptr, "parent", kXMP_PropValueIsArray);
    XMP_Node* node = mgr_.createNode(parent, "rdf:li", "someValue", 0); // Simple property

    size_t result = EstimateSizeForJPEG(node);

    // includeName = false => estSize = valueSize = 9 ("someValue")
    size_t expected = 9;
    EXPECT_EQ(result, expected);
}

// Test simple property with empty value
TEST_F(EstimateSizeForJPEGTest_1983, SimplePropertyEmptyValue_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "parent", kXMP_PropValueIsStruct);
    XMP_Node* node = mgr_.createNode(parent, "prop", "", 0);

    size_t result = EstimateSizeForJPEG(node);

    // nameSize = 4 ("prop"), valueSize = 0
    // estSize = (4 + 3) + 0 = 7
    size_t expected = 7;
    EXPECT_EQ(result, expected);
}

// Test simple property with empty name (parent is struct)
TEST_F(EstimateSizeForJPEGTest_1983, SimplePropertyEmptyName_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "parent", kXMP_PropValueIsStruct);
    XMP_Node* node = mgr_.createNode(parent, "", "val", 0);

    size_t result = EstimateSizeForJPEG(node);

    // nameSize = 0, valueSize = 3
    // includeName = true => estSize = (0 + 3) + 3 = 6
    size_t expected = 6;
    EXPECT_EQ(result, expected);
}

// Test array property with no children, parent is NOT array (includeName = true)
TEST_F(EstimateSizeForJPEGTest_1983, EmptyArrayWithName_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* arrayNode = mgr_.createNode(parent, "myArray", kXMP_PropValueIsArray);

    size_t result = EstimateSizeForJPEG(arrayNode);

    // nameSize = 7 ("myArray")
    // includeName = true => estSize = (2*7 + 5) = 19
    // estSize += 9 + 10 = 19 => total so far = 38
    // arraySize = 0 => no additional
    size_t expected = (2 * 7 + 5) + 9 + 10;
    EXPECT_EQ(result, expected);
}

// Test array property with children
TEST_F(EstimateSizeForJPEGTest_1983, ArrayWithChildren_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* arrayNode = mgr_.createNode(parent, "arr", kXMP_PropValueIsArray);

    // Add two simple children
    XMP_Node* child1 = mgr_.createNode(arrayNode, "rdf:li", "abc", 0);
    XMP_Node* child2 = mgr_.createNode(arrayNode, "rdf:li", "de", 0);
    arrayNode->children.push_back(child1);
    arrayNode->children.push_back(child2);

    size_t result = EstimateSizeForJPEG(arrayNode);

    // nameSize = 3 ("arr")
    // includeName = true (parent is struct) => (2*3 + 5) = 11
    // rdf:Xyz tags: 9 + 10 = 19
    // arraySize = 2 => 2 * (8+9) = 34
    // child1: parent is array, so includeName=false, simple: value.size()=3
    // child2: parent is array, so includeName=false, simple: value.size()=2
    // total = 11 + 19 + 34 + 3 + 2 = 69
    size_t expected = 11 + 19 + 34 + 3 + 2;
    EXPECT_EQ(result, expected);
}

// Test array in array (parent is also array, so includeName = false)
TEST_F(EstimateSizeForJPEGTest_1983, ArrayInArray_1983) {
    XMP_Node* grandparent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* outerArray = mgr_.createNode(grandparent, "outer", kXMP_PropValueIsArray);
    XMP_Node* innerArray = mgr_.createNode(outerArray, "rdf:li", kXMP_PropValueIsArray);
    outerArray->children.push_back(innerArray);

    size_t result = EstimateSizeForJPEG(innerArray);

    // Parent (outerArray) is array, so includeName = false
    // rdf:Xyz: 9 + 10 = 19
    // arraySize = 0
    size_t expected = 19;
    EXPECT_EQ(result, expected);
}

// Test struct property with no children, parent is NOT array
TEST_F(EstimateSizeForJPEGTest_1983, EmptyStructWithName_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* structNode = mgr_.createNode(parent, "myStruct", kXMP_PropValueIsStruct);

    size_t result = EstimateSizeForJPEG(structNode);

    // nameSize = 8 ("myStruct")
    // includeName = true => (2*8 + 5) = 21
    // parseType attribute: 25
    // fieldCount = 0
    size_t expected = 21 + 25;
    EXPECT_EQ(result, expected);
}

// Test struct property with children
TEST_F(EstimateSizeForJPEGTest_1983, StructWithChildren_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* structNode = mgr_.createNode(parent, "st", kXMP_PropValueIsStruct);

    XMP_Node* field1 = mgr_.createNode(structNode, "f1", "abc", 0);
    XMP_Node* field2 = mgr_.createNode(structNode, "field2", "xy", 0);
    structNode->children.push_back(field1);
    structNode->children.push_back(field2);

    size_t result = EstimateSizeForJPEG(structNode);

    // nameSize = 2 ("st")
    // includeName = true => (2*2 + 5) = 9
    // parseType: 25
    // field1: parent (structNode) is struct, includeName=true, nameSize=2, valueSize=3 => (2+3)+3 = 8
    // field2: parent (structNode) is struct, includeName=true, nameSize=6, valueSize=2 => (6+3)+2 = 11
    // total = 9 + 25 + 8 + 11 = 53
    size_t expected = 9 + 25 + 8 + 11;
    EXPECT_EQ(result, expected);
}

// Test struct property where parent IS an array (includeName = false)
TEST_F(EstimateSizeForJPEGTest_1983, StructInArray_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* arrayNode = mgr_.createNode(parent, "arr", kXMP_PropValueIsArray);
    XMP_Node* structChild = mgr_.createNode(arrayNode, "rdf:li", kXMP_PropValueIsStruct);
    arrayNode->children.push_back(structChild);

    size_t result = EstimateSizeForJPEG(structChild);

    // Parent is array, so includeName = false
    // parseType: 25
    // no children
    size_t expected = 25;
    EXPECT_EQ(result, expected);
}

// Test ordered array option
TEST_F(EstimateSizeForJPEGTest_1983, OrderedArray_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* arrayNode = mgr_.createNode(parent, "seq",
        kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered);

    size_t result = EstimateSizeForJPEG(arrayNode);

    // Same calculation as unordered array, since estimation doesn't distinguish
    // nameSize = 3 ("seq"), includeName = true
    // (2*3 + 5) + 9 + 10 = 30
    size_t expected = 11 + 19;
    EXPECT_EQ(result, expected);
}

// Test alternate array option
TEST_F(EstimateSizeForJPEGTest_1983, AlternateArray_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* arrayNode = mgr_.createNode(parent, "alt",
        kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered | kXMP_PropArrayIsAlternate);

    size_t result = EstimateSizeForJPEG(arrayNode);

    // nameSize = 3 ("alt"), includeName = true
    // (2*3 + 5) + 9 + 10 = 30
    size_t expected = 11 + 19;
    EXPECT_EQ(result, expected);
}

// Test deeply nested structure
TEST_F(EstimateSizeForJPEGTest_1983, DeeplyNested_1983) {
    XMP_Node* root = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* arr = mgr_.createNode(root, "a", kXMP_PropValueIsArray);

    // Array element is a struct
    XMP_Node* structInArr = mgr_.createNode(arr, "rdf:li", kXMP_PropValueIsStruct);
    arr->children.push_back(structInArr);

    // Struct has a simple field
    XMP_Node* field = mgr_.createNode(structInArr, "x", "y", 0);
    structInArr->children.push_back(field);

    size_t result = EstimateSizeForJPEG(arr);

    // arr: nameSize=1, parent is struct, includeName=true
    // (2*1+5) = 7
    // 9+10 = 19
    // arraySize=1 => 1*(8+9) = 17
    // structInArr: parent is array, includeName=false
    //   parseType: 25
    //   field: parent (structInArr) is struct, includeName=true
    //     nameSize=1, valueSize=1 => (1+3)+1 = 5
    //   structInArr total = 25 + 5 = 30
    // arr total = 7 + 19 + 17 + 30 = 73
    size_t expected = 7 + 19 + 17 + 30;
    EXPECT_EQ(result, expected);
}

// Test with a large value string
TEST_F(EstimateSizeForJPEGTest_1983, LargeValue_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    std::string largeValue(10000, 'x');
    XMP_Node* node = mgr_.createNode(parent, "p", largeValue.c_str(), 0);

    size_t result = EstimateSizeForJPEG(node);

    // nameSize = 1 ("p"), valueSize = 10000
    // includeName = true => (1+3) + 10000 = 10004
    size_t expected = 4 + 10000;
    EXPECT_EQ(result, expected);
}

// Test array with many children
TEST_F(EstimateSizeForJPEGTest_1983, ArrayWithManyChildren_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* arr = mgr_.createNode(parent, "big", kXMP_PropValueIsArray);

    const int numChildren = 100;
    for (int i = 0; i < numChildren; ++i) {
        XMP_Node* child = mgr_.createNode(arr, "rdf:li", "v", 0);
        arr->children.push_back(child);
    }

    size_t result = EstimateSizeForJPEG(arr);

    // nameSize = 3 ("big"), includeName = true
    // (2*3+5) = 11
    // 9+10 = 19
    // 100 * (8+9) = 1700
    // Each child: parent is array, includeName=false, simple: valueSize=1 => 1 each
    // children total = 100 * 1 = 100
    // total = 11 + 19 + 1700 + 100 = 1830
    size_t expected = 11 + 19 + 1700 + 100;
    EXPECT_EQ(result, expected);
}

// Test with long property name
TEST_F(EstimateSizeForJPEGTest_1983, LongPropertyName_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    std::string longName(500, 'n');
    XMP_Node* node = mgr_.createNode(parent, longName.c_str(), "val", 0);

    size_t result = EstimateSizeForJPEG(node);

    // nameSize = 500, valueSize = 3, includeName = true
    // (500 + 3) + 3 = 506
    size_t expected = 503 + 3;
    EXPECT_EQ(result, expected);
}

// Test struct with long name, in non-array parent
TEST_F(EstimateSizeForJPEGTest_1983, StructLongName_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    std::string longName(200, 's');
    XMP_Node* structNode = mgr_.createNode(parent, longName.c_str(), kXMP_PropValueIsStruct);

    size_t result = EstimateSizeForJPEG(structNode);

    // nameSize = 200, includeName = true
    // (2*200+5) = 405
    // parseType: 25
    // total = 430
    size_t expected = 405 + 25;
    EXPECT_EQ(result, expected);
}

// Test array with long name, in non-array parent
TEST_F(EstimateSizeForJPEGTest_1983, ArrayLongName_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    std::string longName(150, 'a');
    XMP_Node* arrayNode = mgr_.createNode(parent, longName.c_str(), kXMP_PropValueIsArray);

    size_t result = EstimateSizeForJPEG(arrayNode);

    // nameSize = 150, includeName = true
    // (2*150+5) = 305
    // 9+10 = 19
    // total = 324
    size_t expected = 305 + 19;
    EXPECT_EQ(result, expected);
}

// Test simple property with single character name and value
TEST_F(EstimateSizeForJPEGTest_1983, MinimalSimpleProperty_1983) {
    XMP_Node* parent = mgr_.createNode(nullptr, "r", kXMP_PropValueIsStruct);
    XMP_Node* node = mgr_.createNode(parent, "x", "y", 0);

    size_t result = EstimateSizeForJPEG(node);

    // nameSize=1, valueSize=1, includeName=true
    // (1+3)+1 = 5
    EXPECT_EQ(result, static_cast<size_t>(5));
}

// Test that parent being an array correctly suppresses name inclusion for struct child
TEST_F(EstimateSizeForJPEGTest_1983, StructChildNameNotIncludedWhenParentIsArray_1983) {
    XMP_Node* root = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* arrayParent = mgr_.createNode(root, "arr", kXMP_PropValueIsArray);
    XMP_Node* structChild = mgr_.createNode(arrayParent, "longStructName", kXMP_PropValueIsStruct);

    size_t resultInArray = EstimateSizeForJPEG(structChild);
    // Parent is array, includeName=false
    // Just parseType: 25
    EXPECT_EQ(resultInArray, static_cast<size_t>(25));

    // Now same struct under a struct parent
    XMP_Node* structParent = mgr_.createNode(root, "sp", kXMP_PropValueIsStruct);
    XMP_Node* structChild2 = mgr_.createNode(structParent, "longStructName", kXMP_PropValueIsStruct);

    size_t resultInStruct = EstimateSizeForJPEG(structChild2);
    // Parent is struct, includeName=true
    // nameSize=14 => (2*14+5) = 33
    // parseType: 25
    // total = 58
    EXPECT_EQ(resultInStruct, static_cast<size_t>(58));

    // Verify the difference is exactly the name contribution
    EXPECT_GT(resultInStruct, resultInArray);
}

// Test mixed children in a struct (simple + array + struct)
TEST_F(EstimateSizeForJPEGTest_1983, StructWithMixedChildren_1983) {
    XMP_Node* root = mgr_.createNode(nullptr, "root", kXMP_PropValueIsStruct);
    XMP_Node* structNode = mgr_.createNode(root, "st", kXMP_PropValueIsStruct);

    // Simple child
    XMP_Node* simpleChild = mgr_.createNode(structNode, "sc", "val", 0);
    structNode->children.push_back(simpleChild);

    // Array child with one simple element
    XMP_Node* arrayChild = mgr_.createNode(structNode, "ac", kXMP_PropValueIsArray);
    XMP_Node* arrayElem = mgr_.createNode(arrayChild, "rdf:li", "e", 0);
    arrayChild->children.push_back(arrayElem);
    structNode->children.push_back(arrayChild);

    // Nested struct child with one field
    XMP_Node* nestedStruct = mgr_.createNode(structNode, "ns", kXMP_PropValueIsStruct);
    XMP_Node* field = mgr_.createNode(nestedStruct, "f", "g", 0);
    nestedStruct->children.push_back(field);
    structNode->children.push_back(nestedStruct);

    size_t result = EstimateSizeForJPEG(structNode);

    // structNode: nameSize=2, parent=root (struct), includeName=true
    // (2*2+5)=9, +25 = 34 (base)
    //
    // simpleChild: parent is struct, includeName=true, nameSize=2, valueSize=3
    //   (2+3)+3 = 8
    //
    // arrayChild: parent is struct, includeName=true, nameSize=2
    //   (2*2+5)=9, +19=28, arraySize=1 => 1*17=17 => 28+17=45
    //   arrayElem: parent is array, includeName=false, valueSize=1 => 1
    //   arrayChild total = 45 + 1 = 46
    //
    // nestedStruct: parent is struct, includeName=true, nameSize=2
    //   (2*2+5)=9, +25=34
    //   field: parent is struct, includeName=true, nameSize=1, valueSize=1
    //     (1+3)+1 = 5
    //   nestedStruct total = 34 + 5 = 39
    //
    // total = 34 + 8 + 46 + 39 = 127
    size_t expected = 34 + 8 + 46 + 39;
    EXPECT_EQ(result, expected);
}
