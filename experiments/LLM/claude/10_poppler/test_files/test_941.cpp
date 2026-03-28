#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OptionalContent.h"
#include "Object.h"
#include "Array.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class OCGsTest_941 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test getRBGroupsArray when rbgroups is not an array (default/null Object)
// We need to construct OCGs from an OCG object. We'll create minimal valid structures.

TEST_F(OCGsTest_941, GetRBGroupsArray_NullWhenNoRBGroups_941) {
    // Create a minimal OCG dictionary object with no RBGroups
    // The OCGs constructor expects an object with "OCGs" array and optional "D" dict
    
    // Build a minimal catalog OCProperties-like object
    // { "OCGs": [], "D": { "Order": [], "RBGroups": null } }
    // Since we can't easily construct XRef, we test with nullptr xref and minimal object
    
    // Create empty OCGs array
    auto ocgsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    
    // Create D dictionary without RBGroups
    auto dDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    // Build the top-level object
    auto topDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    topDict->add("OCGs", Object(ocgsArray.release()));
    topDict->add("D", Object(dDict.release()));
    
    Object ocgObject(topDict.release());
    
    OCGs ocgs(&ocgObject, nullptr);
    
    // When there are no RBGroups, getRBGroupsArray should return nullptr
    const Array *rbArray = ocgs.getRBGroupsArray();
    EXPECT_EQ(rbArray, nullptr);
}

TEST_F(OCGsTest_941, GetRBGroupsArray_NullWhenEmptyArray_941) {
    // Create an OCG object where RBGroups is an empty array
    auto ocgsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    
    auto rbGroupsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    // Empty array - length is 0
    
    auto dDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    dDict->add("RBGroups", Object(rbGroupsArray.release()));
    
    auto topDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    topDict->add("OCGs", Object(ocgsArray.release()));
    topDict->add("D", Object(dDict.release()));
    
    Object ocgObject(topDict.release());
    
    OCGs ocgs(&ocgObject, nullptr);
    
    // Empty array should return nullptr because arrayGetLength() == 0
    const Array *rbArray = ocgs.getRBGroupsArray();
    EXPECT_EQ(rbArray, nullptr);
}

TEST_F(OCGsTest_941, GetRBGroupsArray_ReturnsArrayWhenNonEmpty_941) {
    // Create an OCG object where RBGroups is a non-empty array
    auto ocgsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    
    auto innerArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    innerArray->add(Object(1)); // Add a dummy element
    
    auto rbGroupsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    rbGroupsArray->add(Object(innerArray.release()));
    
    auto dDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    dDict->add("RBGroups", Object(rbGroupsArray.release()));
    
    auto topDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    topDict->add("OCGs", Object(ocgsArray.release()));
    topDict->add("D", Object(dDict.release()));
    
    Object ocgObject(topDict.release());
    
    OCGs ocgs(&ocgObject, nullptr);
    
    // Non-empty array should return a valid pointer
    const Array *rbArray = ocgs.getRBGroupsArray();
    EXPECT_NE(rbArray, nullptr);
    if (rbArray) {
        EXPECT_GE(rbArray->getLength(), 1);
    }
}

TEST_F(OCGsTest_941, HasOCGs_ReturnsFalseWhenEmpty_941) {
    auto ocgsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    
    auto dDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    auto topDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    topDict->add("OCGs", Object(ocgsArray.release()));
    topDict->add("D", Object(dDict.release()));
    
    Object ocgObject(topDict.release());
    
    OCGs ocgs(&ocgObject, nullptr);
    
    EXPECT_FALSE(ocgs.hasOCGs());
}

TEST_F(OCGsTest_941, GetOCGs_EmptyWhenNoOCGsDefined_941) {
    auto ocgsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    
    auto dDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    auto topDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    topDict->add("OCGs", Object(ocgsArray.release()));
    topDict->add("D", Object(dDict.release()));
    
    Object ocgObject(topDict.release());
    
    OCGs ocgs(&ocgObject, nullptr);
    
    const auto &ocgMap = ocgs.getOCGs();
    EXPECT_TRUE(ocgMap.empty());
}

TEST_F(OCGsTest_941, GetOrderArray_NullWhenNoOrder_941) {
    auto ocgsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    
    auto dDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    auto topDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    topDict->add("OCGs", Object(ocgsArray.release()));
    topDict->add("D", Object(dDict.release()));
    
    Object ocgObject(topDict.release());
    
    OCGs ocgs(&ocgObject, nullptr);
    
    const Array *orderArray = ocgs.getOrderArray();
    EXPECT_EQ(orderArray, nullptr);
}

TEST_F(OCGsTest_941, FindOcgByRef_ReturnsNullForNonexistentRef_941) {
    auto ocgsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    
    auto dDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    
    auto topDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    topDict->add("OCGs", Object(ocgsArray.release()));
    topDict->add("D", Object(dDict.release()));
    
    Object ocgObject(topDict.release());
    
    OCGs ocgs(&ocgObject, nullptr);
    
    Ref testRef = {99, 0};
    const OptionalContentGroup *result = ocgs.findOcgByRef(testRef);
    EXPECT_EQ(result, nullptr);
}

TEST_F(OCGsTest_941, GetRBGroupsArray_MultipleElements_941) {
    // Test with multiple elements in RBGroups array
    auto ocgsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    
    auto rbGroupsArray = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    
    auto group1 = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    group1->add(Object(1));
    rbGroupsArray->add(Object(group1.release()));
    
    auto group2 = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    group2->add(Object(2));
    rbGroupsArray->add(Object(group2.release()));
    
    auto dDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    dDict->add("RBGroups", Object(rbGroupsArray.release()));
    
    auto topDict = std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    topDict->add("OCGs", Object(ocgsArray.release()));
    topDict->add("D", Object(dDict.release()));
    
    Object ocgObject(topDict.release());
    
    OCGs ocgs(&ocgObject, nullptr);
    
    const Array *rbArray = ocgs.getRBGroupsArray();
    EXPECT_NE(rbArray, nullptr);
    if (rbArray) {
        EXPECT_EQ(rbArray->getLength(), 2);
    }
}
