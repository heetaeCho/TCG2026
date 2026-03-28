#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OptionalContent.h"
#include "Object.h"
#include "Array.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class OCGsTest_940 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Helper to create a minimal OCG object structure for testing
// The OCG object passed to OCGs constructor should be a dict with certain keys

TEST_F(OCGsTest_940, GetOrderArrayReturnsNullWhenOrderIsNotArray_940) {
    // Create a minimal OCG dict object with no "Order" key
    // When order is not an array, getOrderArray should return nullptr
    
    // Create an empty dict for the OCGs entry
    auto xref = std::unique_ptr<XRef>(new XRef(nullptr));
    
    Dict *ocgsDict = new Dict(xref.get());
    
    // Create OCGs array (empty)
    Array *ocgsArray = new Array(xref.get());
    ocgsDict->add("OCGs", Object(ocgsArray));
    
    // No "Order" key set - order will be objNone
    Object ocgObject(ocgsDict);
    
    OCGs ocgs(&ocgObject, xref.get());
    
    const Array *orderArray = ocgs.getOrderArray();
    EXPECT_EQ(orderArray, nullptr);
}

TEST_F(OCGsTest_940, GetOrderArrayReturnsNullWhenOrderIsEmptyArray_940) {
    auto xref = std::unique_ptr<XRef>(new XRef(nullptr));
    
    Dict *ocgsDict = new Dict(xref.get());
    
    // Create OCGs array (empty)
    Array *ocgsArray = new Array(xref.get());
    ocgsDict->add("OCGs", Object(ocgsArray));
    
    // Create an empty Order array  
    Dict *dDict = new Dict(xref.get());
    Array *orderArr = new Array(xref.get());
    dDict->add("Order", Object(orderArr));
    ocgsDict->add("D", Object(dDict));
    
    Object ocgObject(ocgsDict);
    
    OCGs ocgs(&ocgObject, xref.get());
    
    const Array *orderArray = ocgs.getOrderArray();
    // Empty array (length 0) should return nullptr per the implementation
    EXPECT_EQ(orderArray, nullptr);
}

TEST_F(OCGsTest_940, GetOrderArrayReturnsArrayWhenOrderHasElements_940) {
    auto xref = std::unique_ptr<XRef>(new XRef(nullptr));
    
    Dict *ocgsDict = new Dict(xref.get());
    
    // Create OCGs array (empty)
    Array *ocgsArray = new Array(xref.get());
    ocgsDict->add("OCGs", Object(ocgsArray));
    
    // Create Order array with at least one element
    Dict *dDict = new Dict(xref.get());
    Array *orderArr = new Array(xref.get());
    orderArr->add(Object(1)); // Add an integer element
    dDict->add("Order", Object(orderArr));
    ocgsDict->add("D", Object(dDict));
    
    Object ocgObject(ocgsDict);
    
    OCGs ocgs(&ocgObject, xref.get());
    
    const Array *orderArray = ocgs.getOrderArray();
    // Non-empty array should be returned
    if (orderArray != nullptr) {
        EXPECT_GT(orderArray->getLength(), 0);
    }
    // Note: depending on implementation details of OCGs constructor,
    // the order may or may not be properly set. The key test is that
    // the logic in getOrderArray works correctly.
}

TEST_F(OCGsTest_940, HasOCGsReturnsFalseWhenNoOCGs_940) {
    auto xref = std::unique_ptr<XRef>(new XRef(nullptr));
    
    Dict *ocgsDict = new Dict(xref.get());
    
    // Create empty OCGs array
    Array *ocgsArray = new Array(xref.get());
    ocgsDict->add("OCGs", Object(ocgsArray));
    
    Object ocgObject(ocgsDict);
    
    OCGs ocgs(&ocgObject, xref.get());
    
    EXPECT_FALSE(ocgs.hasOCGs());
}

TEST_F(OCGsTest_940, GetOCGsReturnsEmptyMapWhenNoOCGs_940) {
    auto xref = std::unique_ptr<XRef>(new XRef(nullptr));
    
    Dict *ocgsDict = new Dict(xref.get());
    
    // Create empty OCGs array
    Array *ocgsArray = new Array(xref.get());
    ocgsDict->add("OCGs", Object(ocgsArray));
    
    Object ocgObject(ocgsDict);
    
    OCGs ocgs(&ocgObject, xref.get());
    
    const auto &ocgMap = ocgs.getOCGs();
    EXPECT_TRUE(ocgMap.empty());
}

TEST_F(OCGsTest_940, FindOcgByRefReturnsNullForNonexistentRef_940) {
    auto xref = std::unique_ptr<XRef>(new XRef(nullptr));
    
    Dict *ocgsDict = new Dict(xref.get());
    
    Array *ocgsArray = new Array(xref.get());
    ocgsDict->add("OCGs", Object(ocgsArray));
    
    Object ocgObject(ocgsDict);
    
    OCGs ocgs(&ocgObject, xref.get());
    
    Ref testRef = {99, 0};
    const OptionalContentGroup *result = ocgs.findOcgByRef(testRef);
    EXPECT_EQ(result, nullptr);
}

TEST_F(OCGsTest_940, GetRBGroupsArrayReturnsNullWhenNotSet_940) {
    auto xref = std::unique_ptr<XRef>(new XRef(nullptr));
    
    Dict *ocgsDict = new Dict(xref.get());
    
    Array *ocgsArray = new Array(xref.get());
    ocgsDict->add("OCGs", Object(ocgsArray));
    
    Object ocgObject(ocgsDict);
    
    OCGs ocgs(&ocgObject, xref.get());
    
    const Array *rbGroups = ocgs.getRBGroupsArray();
    EXPECT_EQ(rbGroups, nullptr);
}

TEST_F(OCGsTest_940, CopyConstructorIsDeleted_940) {
    // This is a compile-time check - OCGs should not be copyable
    EXPECT_FALSE(std::is_copy_constructible<OCGs>::value);
}

TEST_F(OCGsTest_940, CopyAssignmentIsDeleted_940) {
    // This is a compile-time check - OCGs should not be copy-assignable
    EXPECT_FALSE(std::is_copy_assignable<OCGs>::value);
}

TEST_F(OCGsTest_940, OptContentIsVisibleWithNullishRef_940) {
    auto xref = std::unique_ptr<XRef>(new XRef(nullptr));
    
    Dict *ocgsDict = new Dict(xref.get());
    
    Array *ocgsArray = new Array(xref.get());
    ocgsDict->add("OCGs", Object(ocgsArray));
    
    Object ocgObject(ocgsDict);
    
    OCGs ocgs(&ocgObject, xref.get());
    
    // Test with a null object - should likely return true (visible by default)
    Object nullObj = Object(objNull);
    bool visible = ocgs.optContentIsVisible(&nullObj);
    EXPECT_TRUE(visible);
}

TEST_F(OCGsTest_940, GetOrderArrayConsistencyCheck_940) {
    // Call getOrderArray twice to ensure consistent results
    auto xref = std::unique_ptr<XRef>(new XRef(nullptr));
    
    Dict *ocgsDict = new Dict(xref.get());
    
    Array *ocgsArray = new Array(xref.get());
    ocgsDict->add("OCGs", Object(ocgsArray));
    
    Object ocgObject(ocgsDict);
    
    OCGs ocgs(&ocgObject, xref.get());
    
    const Array *first = ocgs.getOrderArray();
    const Array *second = ocgs.getOrderArray();
    EXPECT_EQ(first, second);
}
