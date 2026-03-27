#include <gtest/gtest.h>

#include "re2/re2.h"

#include <string>



namespace {



class RE2Test_237 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed (for this case, no setup is necessary)

    }



    void TearDown() override {

        // Teardown if needed (for this case, no teardown is necessary)

    }

};



TEST_F(RE2Test_237, EmptyString_ReturnsValidPointer_237) {

    std::string* empty_str = re2::empty_string();

    EXPECT_NE(empty_str, nullptr);

}



TEST_F(RE2Test_237, EmptyString_PointerConsistency_237) {

    std::string* empty_str1 = re2::empty_string();

    std::string* empty_str2 = re2::empty_string();

    EXPECT_EQ(empty_str1, empty_str2);

}



TEST_F(RE2Test_237, EmptyString_DefaultValue_237) {

    const std::string* empty_str = re2::empty_string();

    EXPECT_TRUE(empty_str->empty());

}



}  // namespace
