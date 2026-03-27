#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>



using namespace YAML;



// Test fixture for the convert<bool>::decode function

class ConvertBoolDecodeTest_623 : public ::testing::Test {

protected:

    Node node;

    bool result;

};



// Normal operation: Testing with "true" values

TEST_F(ConvertBoolDecodeTest_623, DecodeTrueValues_623) {

    for (const auto& trueValue : {"y", "Y", "yes", "YES", "true", "TRUE", "on", "ON"}) {

        node = Node(trueValue);

        EXPECT_TRUE(convert<bool>::decode(node, result));

        EXPECT_TRUE(result);

    }

}



// Normal operation: Testing with "false" values

TEST_F(ConvertBoolDecodeTest_623, DecodeFalseValues_623) {

    for (const auto& falseValue : {"n", "N", "no", "NO", "false", "FALSE", "off", "OFF"}) {

        node = Node(falseValue);

        EXPECT_TRUE(convert<bool>::decode(node, result));

        EXPECT_FALSE(result);

    }

}



// Boundary condition: Testing with an empty string

TEST_F(ConvertBoolDecodeTest_623, DecodeEmptyString_623) {

    node = Node("");

    EXPECT_FALSE(convert<bool>::decode(node, result));

}



// Boundary condition: Testing with non-boolean strings

TEST_F(ConvertBoolDecodeTest_623, DecodeNonBooleanStrings_623) {

    for (const auto& nonBoolValue : {"maybe", "unknown", "1", "0"}) {

        node = Node(nonBoolValue);

        EXPECT_FALSE(convert<bool>::decode(node, result));

    }

}



// Boundary condition: Testing with a scalar containing spaces

TEST_F(ConvertBoolDecodeTest_623, DecodeScalarWithSpaces_623) {

    for (const auto& spacedValue : {" y ", " yes ", " true ", " on ", " n ", " no ", " false ", " off "}) {

        node = Node(spacedValue);

        EXPECT_FALSE(convert<bool>::decode(node, result));

    }

}



// Exceptional case: Testing with a non-scalar node

TEST_F(ConvertBoolDecodeTest_623, DecodeNonScalarNode_623) {

    node = Node(NodeType::Map); // Example of a non-scalar node

    EXPECT_FALSE(convert<bool>::decode(node, result));

}
