#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "xmp_exiv2.hpp"
#include "error.hpp"

namespace Exiv2 {

class MockHandler : public IHandler {
public:
    MOCK_METHOD(void, handleError, (const Error&), (override));
};

// TEST_ID: 1297
TEST_F(XmpdatumTest_1297, ValueThrowsErrorIfNotSet_1297) {
    // Given: Xmpdatum without a value set
    XmpKey key;
    Xmpdatum datum(key, nullptr); // pValue is null
    
    // When: Trying to access the value
    // Then: It should throw an Error with the ErrorCode::kerValueNotSet
    EXPECT_THROW(datum.value(), Error);
}

// TEST_ID: 1298
TEST_F(XmpdatumTest_1298, ValueReturnsCorrectValueWhenSet_1298) {
    // Given: Xmpdatum with a value set
    XmpKey key;
    Value val("SomeValue");
    Xmpdatum datum(key, &val); // pValue is set

    // When: Accessing the value
    // Then: It should return the correct value
    EXPECT_EQ(datum.value(), val);
}

// TEST_ID: 1299
TEST_F(XmpdatumTest_1299, CopyConstructorWorks_1299) {
    // Given: An Xmpdatum with a value
    XmpKey key;
    Value val("SomeValue");
    Xmpdatum datum1(key, &val);
    
    // When: Copying the Xmpdatum
    Xmpdatum datum2(datum1);
    
    // Then: The copied datum should have the same value
    EXPECT_EQ(datum1.value(), datum2.value());
}

// TEST_ID: 1300
TEST_F(XmpdatumTest_1300, CopyAssignmentOperatorWorks_1300) {
    // Given: An Xmpdatum with a value
    XmpKey key;
    Value val("SomeValue");
    Xmpdatum datum1(key, &val);
    
    // When: Assigning one Xmpdatum to another
    Xmpdatum datum2(key, nullptr); // Initially null
    datum2 = datum1;
    
    // Then: The assigned datum should have the same value
    EXPECT_EQ(datum1.value(), datum2.value());
}

// TEST_ID: 1301
TEST_F(XmpdatumTest_1301, SetValueSetsCorrectValue_1301) {
    // Given: An Xmpdatum
    XmpKey key;
    Xmpdatum datum(key, nullptr);
    
    // When: Setting a value
    Value val("NewValue");
    datum.setValue(&val);
    
    // Then: The value should be correctly set
    EXPECT_EQ(datum.value(), val);
}

// TEST_ID: 1302
TEST_F(XmpdatumTest_1302, SetValueThrowsErrorWhenValueNotSet_1302) {
    // Given: An Xmpdatum without a valid value
    XmpKey key;
    Xmpdatum datum(key, nullptr);
    
    // When: Trying to access the value after setting an invalid one
    Value invalidVal("");
    datum.setValue(&invalidVal);
    
    // Then: It should throw an Error with the ErrorCode::kerValueNotSet
    EXPECT_THROW(datum.value(), Error);
}

// TEST_ID: 1303
TEST_F(XmpdatumTest_1303, ValueNullptrDoesNotCrash_1303) {
    // Given: Xmpdatum with a null value
    XmpKey key;
    Xmpdatum datum(key, nullptr); 
    
    // When: Accessing the value (should not crash, but may throw)
    // Then: It should throw an error if the value is null
    EXPECT_THROW(datum.value(), Error);
}

}  // namespace Exiv2