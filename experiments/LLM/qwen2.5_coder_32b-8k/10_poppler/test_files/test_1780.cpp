#include <gtest/gtest.h>

#include "StructElement.h"  // Assuming this header contains the declaration of Attribute::Owner and ownerToName function



// Define a test fixture for the tests related to StructElement

class StructElementTest_1780 : public ::testing::Test {

protected:

    // If needed, setup code can be placed here

};



// Test normal operation with a known valid attribute owner

TEST_F(StructElementTest_1780, ValidOwnerToNameConversion_1780) {

    const char* result = ownerToName(Attribute::Owner::Document);

    EXPECT_STREQ(result, "Document");

}



// Test boundary condition with the first possible enum value of Attribute::Owner

TEST_F(StructElementTest_1780, FirstEnumValueConversion_1780) {

    const char* result = ownerToName(static_cast<Attribute::Owner>(0));

    EXPECT_STREQ(result, "UnknownOwner");  // Assuming the map starts at a non-zero value and zero is not mapped

}



// Test boundary condition with an out-of-range enum value of Attribute::Owner

TEST_F(StructElementTest_1780, OutOfRangeEnumValueConversion_1780) {

    const char* result = ownerToName(static_cast<Attribute::Owner>(-1));

    EXPECT_STREQ(result, "UnknownOwner");

}



// Test exceptional case with the last possible enum value of Attribute::Owner

TEST_F(StructElementTest_1780, LastEnumValueConversion_1780) {

    const char* result = ownerToName(static_cast<Attribute::Owner>(10));  // Hypothetical last value

    EXPECT_STREQ(result, "UnknownOwner");

}



// Test exceptional case with an unknown or unassigned enum value of Attribute::Owner

TEST_F(StructElementTest_1780, UnknownEnumValueConversion_1780) {

    const char* result = ownerToName(static_cast<Attribute::Owner>(99));  // Hypothetical unknown value

    EXPECT_STREQ(result, "UnknownOwner");

}

```


