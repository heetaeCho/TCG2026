#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



class DragonboxDetailTest_426 : public ::testing::Test {

protected:

    using Policy = struct {

        using preferred_integer_types_policy = void;

    };

};



TEST_F(DragonboxDetailTest_426, TestOperatorReturnsTrueForValidPolicy_426) {

    is_preferred_integer_types_policy checker;

    EXPECT_TRUE(checker(dummy<Policy>{}));

}



// No observable boundary conditions or exceptional cases are present in the given function signature.

// The function is a template that checks for the presence of a specific type alias within the provided policy,

// and it always returns true if that type alias exists. Therefore, only one test case is necessary.



}}}}
