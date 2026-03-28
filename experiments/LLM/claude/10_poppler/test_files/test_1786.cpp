#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler/StructElement.h"
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/Error.h"

// Since roleMapResolve is a static function in the .cc file, we need to
// include the .cc to access it for unit testing purposes.
// We declare nameToType as it's used by roleMapResolve
#include "poppler/StructElement.cc"

class RoleMapResolveTest_1786 : public ::testing::Test {
protected:
    void SetUp() override {
        // Dict requires an XRef, but for testing we can pass nullptr
        // if the dict operations we use don't need it
        roleMap = new Dict(static_cast<XRef *>(nullptr));
    }

    void TearDown() override {
        delete roleMap;
    }

    Dict *roleMap;
};

// Test: Direct resolution of a known standard structure type
TEST_F(RoleMapResolveTest_1786, DirectResolutionOfKnownType_1786) {
    // Map "MyParagraph" -> "P" (which is a known StructElement type)
    roleMap->add("MyParagraph", Object(objName, "P"));
    StructElement::Type result = roleMapResolve(roleMap, "MyParagraph");
    EXPECT_EQ(result, StructElement::P);
}

// Test: Direct resolution of another known type "Div"
TEST_F(RoleMapResolveTest_1786, DirectResolutionOfDiv_1786) {
    roleMap->add("CustomDiv", Object(objName, "Div"));
    StructElement::Type result = roleMapResolve(roleMap, "CustomDiv");
    EXPECT_EQ(result, StructElement::Div);
}

// Test: Direct resolution of "Document" type
TEST_F(RoleMapResolveTest_1786, DirectResolutionOfDocument_1786) {
    roleMap->add("MyDoc", Object(objName, "Document"));
    StructElement::Type result = roleMapResolve(roleMap, "MyDoc");
    EXPECT_EQ(result, StructElement::Document);
}

// Test: Direct resolution of "Span" type
TEST_F(RoleMapResolveTest_1786, DirectResolutionOfSpan_1786) {
    roleMap->add("MySpan", Object(objName, "Span"));
    StructElement::Type result = roleMapResolve(roleMap, "MySpan");
    EXPECT_EQ(result, StructElement::Span);
}

// Test: Name not found in roleMap returns Unknown
TEST_F(RoleMapResolveTest_1786, NameNotFoundReturnsUnknown_1786) {
    // roleMap is empty, so lookup returns null object
    StructElement::Type result = roleMapResolve(roleMap, "NonExistent");
    EXPECT_EQ(result, StructElement::Unknown);
}

// Test: Indirect resolution through chain (A -> B -> known type)
TEST_F(RoleMapResolveTest_1786, IndirectResolutionThroughChain_1786) {
    // "CustomRole" -> "MyParagraph" -> "P"
    roleMap->add("CustomRole", Object(objName, "MyParagraph"));
    roleMap->add("MyParagraph", Object(objName, "P"));
    StructElement::Type result = roleMapResolve(roleMap, "CustomRole");
    EXPECT_EQ(result, StructElement::P);
}

// Test: Circular reference detection (A -> B -> A)
TEST_F(RoleMapResolveTest_1786, CircularReferenceDetection_1786) {
    roleMap->add("RoleA", Object(objName, "RoleB"));
    roleMap->add("RoleB", Object(objName, "RoleA"));
    StructElement::Type result = roleMapResolve(roleMap, "RoleA");
    EXPECT_EQ(result, StructElement::Unknown);
}

// Test: Self-referencing circular reference (A -> A)
TEST_F(RoleMapResolveTest_1786, SelfReferenceCircularDetection_1786) {
    roleMap->add("RoleA", Object(objName, "RoleA"));
    StructElement::Type result = roleMapResolve(roleMap, "RoleA");
    EXPECT_EQ(result, StructElement::Unknown);
}

// Test: Longer circular chain (A -> B -> C -> A)
TEST_F(RoleMapResolveTest_1786, LongerCircularChainDetection_1786) {
    roleMap->add("RoleA", Object(objName, "RoleB"));
    roleMap->add("RoleB", Object(objName, "RoleC"));
    roleMap->add("RoleC", Object(objName, "RoleA"));
    StructElement::Type result = roleMapResolve(roleMap, "RoleA");
    EXPECT_EQ(result, StructElement::Unknown);
}

// Test: Wrong type in roleMap entry (e.g., integer instead of name)
TEST_F(RoleMapResolveTest_1786, WrongTypeEntryReturnsUnknown_1786) {
    roleMap->add("BadEntry", Object(42));
    StructElement::Type result = roleMapResolve(roleMap, "BadEntry");
    EXPECT_EQ(result, StructElement::Unknown);
}

// Test: Wrong type - boolean entry
TEST_F(RoleMapResolveTest_1786, BooleanEntryReturnsUnknown_1786) {
    roleMap->add("BoolEntry", Object(true));
    StructElement::Type result = roleMapResolve(roleMap, "BoolEntry");
    EXPECT_EQ(result, StructElement::Unknown);
}

// Test: Wrong type - string entry instead of name
TEST_F(RoleMapResolveTest_1786, StringEntryReturnsUnknown_1786) {
    roleMap->add("StringEntry", Object(std::string("P")));
    StructElement::Type result = roleMapResolve(roleMap, "StringEntry");
    EXPECT_EQ(result, StructElement::Unknown);
}

// Test: Chain that resolves to unknown name (no mapping found at end)
TEST_F(RoleMapResolveTest_1786, ChainResolvesToUnknownName_1786) {
    roleMap->add("RoleA", Object(objName, "RoleB"));
    // RoleB is not in the map, so lookup returns null
    StructElement::Type result = roleMapResolve(roleMap, "RoleA");
    EXPECT_EQ(result, StructElement::Unknown);
}

// Test: Known type "Table"
TEST_F(RoleMapResolveTest_1786, DirectResolutionOfTable_1786) {
    roleMap->add("MyTable", Object(objName, "Table"));
    StructElement::Type result = roleMapResolve(roleMap, "MyTable");
    EXPECT_EQ(result, StructElement::Table);
}

// Test: Known type "H1" (heading)
TEST_F(RoleMapResolveTest_1786, DirectResolutionOfH1_1786) {
    roleMap->add("MyHeading", Object(objName, "H1"));
    StructElement::Type result = roleMapResolve(roleMap, "MyHeading");
    EXPECT_EQ(result, StructElement::H1);
}

// Test: Known type "L" (list)
TEST_F(RoleMapResolveTest_1786, DirectResolutionOfList_1786) {
    roleMap->add("MyList", Object(objName, "L"));
    StructElement::Type result = roleMapResolve(roleMap, "MyList");
    EXPECT_EQ(result, StructElement::L);
}

// Test: Chain where intermediate is wrong type
TEST_F(RoleMapResolveTest_1786, ChainWithWrongTypeIntermediateReturnsUnknown_1786) {
    // "RoleA" -> "RoleB", but "RoleB" maps to an integer
    roleMap->add("RoleA", Object(objName, "RoleB"));
    roleMap->add("RoleB", Object(123));
    StructElement::Type result = roleMapResolve(roleMap, "RoleA");
    EXPECT_EQ(result, StructElement::Unknown);
}

// Test: Multiple entries, only one resolves correctly
TEST_F(RoleMapResolveTest_1786, MultipleEntriesCorrectResolution_1786) {
    roleMap->add("Role1", Object(objName, "P"));
    roleMap->add("Role2", Object(objName, "Div"));
    roleMap->add("Role3", Object(objName, "Span"));

    EXPECT_EQ(roleMapResolve(roleMap, "Role1"), StructElement::P);
    EXPECT_EQ(roleMapResolve(roleMap, "Role2"), StructElement::Div);
    EXPECT_EQ(roleMapResolve(roleMap, "Role3"), StructElement::Span);
}

// Test: Deep chain resolution (A -> B -> C -> P)
TEST_F(RoleMapResolveTest_1786, DeepChainResolution_1786) {
    roleMap->add("RoleA", Object(objName, "RoleB"));
    roleMap->add("RoleB", Object(objName, "RoleC"));
    roleMap->add("RoleC", Object(objName, "P"));
    StructElement::Type result = roleMapResolve(roleMap, "RoleA");
    EXPECT_EQ(result, StructElement::P);
}

// Test: Known type "Figure"
TEST_F(RoleMapResolveTest_1786, DirectResolutionOfFigure_1786) {
    roleMap->add("MyFigure", Object(objName, "Figure"));
    StructElement::Type result = roleMapResolve(roleMap, "MyFigure");
    EXPECT_EQ(result, StructElement::Figure);
}

// Test: Real number entry returns Unknown
TEST_F(RoleMapResolveTest_1786, RealNumberEntryReturnsUnknown_1786) {
    roleMap->add("RealEntry", Object(3.14));
    StructElement::Type result = roleMapResolve(roleMap, "RealEntry");
    EXPECT_EQ(result, StructElement::Unknown);
}
