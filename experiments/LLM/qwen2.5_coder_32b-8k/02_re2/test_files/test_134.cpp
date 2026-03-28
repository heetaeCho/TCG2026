#include <gtest/gtest.h>

#include <absl/strings/string_view.h>

#include "./TestProjects/re2/re2/prog.h"



class EndPtrTest_134 : public ::testing::Test {

protected:

    // No need for setup or teardown as the function is stateless and static.

};



TEST_F(EndPtrTest_134, NormalOperation_134) {

    absl::string_view s = "Hello, World!";

    const char* expected_end = s.data() + s.size();

    EXPECT_EQ(re2::EndPtr(s), expected_end);

}



TEST_F(EndPtrTest_134, EmptyString_134) {

    absl::string_view s = "";

    const char* expected_end = s.data(); // Since size is 0, data pointer itself should be the end.

    EXPECT_EQ(re2::EndPtr(s), expected_end);

}



TEST_F(EndPtrTest_134, SingleCharacterString_134) {

    absl::string_view s = "A";

    const char* expected_end = s.data() + 1;

    EXPECT_EQ(re2::EndPtr(s), expected_end);

}

```



These tests cover:

- Normal operation with a typical string.

- Boundary condition with an empty string.
