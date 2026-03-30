#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "absl/strings/string_view.h"

#include "./TestProjects/re2/re2/prog.h"



namespace re2 {



class BeginPtrTest_133 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(BeginPtrTest_133, NonEmptyStringView_133) {

    absl::string_view s = "hello";

    EXPECT_EQ(BeginPtr(s), s.data());

}



TEST_F(BeginPtrTest_133, EmptyStringView_133) {

    absl::string_view s = "";

    EXPECT_EQ(BeginPtr(s), s.data());

}



TEST_F(BeginPtrTest_133, SingleCharacterStringView_133) {

    absl::string_view s = "a";

    EXPECT_EQ(BeginPtr(s), s.data());

}



} // namespace re2
