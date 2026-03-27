#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking dependencies if necessary would go here.

// However, in this case, there are no external collaborators to mock.



// Including the header file for the class under test

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::detail;



struct DummyPolicy {

    using binary_to_decimal_rounding_policy = void;

};



TEST(is_binary_to_decimal_rounding_policy_422, TestValidPolicy_422) {

    is_binary_to_decimal_rounding_policy checker;

    EXPECT_TRUE(checker(dummy<DummyPolicy>{}));

}



// Boundary conditions and exceptional cases are not applicable for this template struct

// as it is a type trait-like structure without any runtime behavior or parameters.

```


