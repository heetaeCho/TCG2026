#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "StructElement.h"
#include "Object.h"

// Since StructElement has private constructors and complex dependencies,
// we need to test through the available construction paths.
// The key method under test is isObjectRef() which checks:
// 1. type == OBJR
// 2. c->ref != Ref::INVALID()

// We'll use the Ref-based constructor to create OBJR type elements
// and test isObjectRef behavior.

class StructElementTest_1692 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that an OBJR element with a valid Ref returns true for isObjectRef
TEST_F(StructElementTest_1692, IsObjectRefReturnsTrueForValidRef_1692)
{
    // Create a valid Ref (not INVALID)
    Ref validRef;
    validRef.num = 1;
    validRef.gen = 0;

    // Construct a StructElement using the Ref constructor (creates OBJR type)
    // Note: We need a StructTreeRoot and parent, using nullptr where possible
    StructElement elem(validRef, nullptr, nullptr);

    EXPECT_TRUE(elem.isObjectRef());
}

// Test that an OBJR element with INVALID ref returns false for isObjectRef
TEST_F(StructElementTest_1692, IsObjectRefReturnsFalseForInvalidRef_1692)
{
    Ref invalidRef = Ref::INVALID();

    StructElement elem(invalidRef, nullptr, nullptr);

    EXPECT_FALSE(elem.isObjectRef());
}

// Test that an MCID-based element (content, not OBJR) returns false for isObjectRef
TEST_F(StructElementTest_1692, IsObjectRefReturnsFalseForMCIDElement_1692)
{
    // MCID constructor creates a non-OBJR (MCR type) element
    StructElement elem(0, nullptr, nullptr);

    EXPECT_FALSE(elem.isObjectRef());
}

// Test isObjectRef with various valid ref numbers
TEST_F(StructElementTest_1692, IsObjectRefWithVariousValidRefs_1692)
{
    Ref ref1;
    ref1.num = 100;
    ref1.gen = 0;
    StructElement elem1(ref1, nullptr, nullptr);
    EXPECT_TRUE(elem1.isObjectRef());

    Ref ref2;
    ref2.num = 0;
    ref2.gen = 0;
    StructElement elem2(ref2, nullptr, nullptr);
    // Ref(0,0) may or may not be INVALID depending on implementation
    // We test the observable behavior
    if (ref2.num != Ref::INVALID().num || ref2.gen != Ref::INVALID().gen) {
        EXPECT_TRUE(elem2.isObjectRef());
    }
}

// Test that getObjectRef returns the ref that was used to construct the OBJR element
TEST_F(StructElementTest_1692, GetObjectRefReturnsCorrectRef_1692)
{
    Ref validRef;
    validRef.num = 42;
    validRef.gen = 3;

    StructElement elem(validRef, nullptr, nullptr);

    Ref result = elem.getObjectRef();
    EXPECT_EQ(result.num, 42);
    EXPECT_EQ(result.gen, 3);
}

// Test isContent for MCID-based element
TEST_F(StructElementTest_1692, IsContentReturnsTrueForMCIDElement_1692)
{
    StructElement elem(5, nullptr, nullptr);
    // MCR type elements should be content
    EXPECT_TRUE(elem.isContent());
}

// Test isContent for OBJR element
TEST_F(StructElementTest_1692, IsContentReturnsTrueForOBJRElement_1692)
{
    Ref validRef;
    validRef.num = 10;
    validRef.gen = 0;
    StructElement elem(validRef, nullptr, nullptr);
    // OBJR elements are also considered content
    EXPECT_TRUE(elem.isContent());
}

// Test getMCID for MCID-based element
TEST_F(StructElementTest_1692, GetMCIDReturnsCorrectValue_1692)
{
    StructElement elem(7, nullptr, nullptr);
    EXPECT_EQ(elem.getMCID(), 7);
}

// Test getMCID boundary - zero
TEST_F(StructElementTest_1692, GetMCIDWithZero_1692)
{
    StructElement elem(0, nullptr, nullptr);
    EXPECT_EQ(elem.getMCID(), 0);
}

// Test that getParent returns the parent passed during construction
TEST_F(StructElementTest_1692, GetParentReturnsCorrectParent_1692)
{
    Ref ref;
    ref.num = 1;
    ref.gen = 0;
    StructElement parent(ref, nullptr, nullptr);
    
    Ref childRef;
    childRef.num = 2;
    childRef.gen = 0;
    StructElement child(childRef, nullptr, &parent);

    EXPECT_EQ(child.getParent(), &parent);
}

// Test getParent returns nullptr when no parent
TEST_F(StructElementTest_1692, GetParentReturnsNullWhenNoParent_1692)
{
    StructElement elem(0, nullptr, nullptr);
    EXPECT_EQ(elem.getParent(), nullptr);
}
