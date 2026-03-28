#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::detail;



TEST(bit_cast_test_268, NormalOperationForSameSizeTypes_268) {

    int original = 42;

    float result = bit_cast<float>(original);

    EXPECT_EQ(original, bit_cast<int>(result));

}



TEST(bit_cast_test_268, BoundaryConditionsWithZero_268) {

    int zero_int = 0;

    float zero_float = bit_cast<float>(zero_int);

    EXPECT_FLOAT_EQ(0.0f, zero_float);



    zero_float = 0.0f;

    zero_int = bit_cast<int>(zero_float);

    EXPECT_EQ(0, zero_int);

}



TEST(bit_cast_test_268, BoundaryConditionsWithMaxValues_268) {

    unsigned int max_uint = UINT_MAX;

    float result = bit_cast<float>(max_uint);

    unsigned int converted_back = bit_cast<unsigned int>(result);

    EXPECT_EQ(max_uint, converted_back);

}



TEST(bit_cast_test_268, ExceptionalCaseWithDifferentSizeTypes_268) {

    // This test case is not applicable as the static_assert would prevent compilation.

    // However, it's good to document this behavior.

}



TEST(bit_cast_test_268, VerifyNoChangeInTriviallyCopyableTypes_268) {

    struct TrivialStruct {

        int a;

        float b;

    };



    TrivialStruct original = {42, 3.14f};

    TrivialStruct result = bit_cast<TrivialStruct>(original);

    EXPECT_EQ(original.a, result.a);

    EXPECT_FLOAT_EQ(original.b, result.b);

}
