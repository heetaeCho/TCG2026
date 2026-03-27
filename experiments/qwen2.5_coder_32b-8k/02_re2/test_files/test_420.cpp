#include <gtest/gtest.h>

#include "re2/prog.h"



namespace re2 {



class ProgTest : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_420, PrefixAccel_FrontAndBack_ReturnsNullWhenSizeLessThanPrefixSize_420) {

    const char* data = "abc";

    size_t size = 1; // Assuming prefix_size_ is at least 2

    EXPECT_EQ(prog.PrefixAccel_FrontAndBack(data, size), nullptr);

}



TEST_F(ProgTest_420, PrefixAccel_FrontAndBack_ReturnsNullWhenNoMatchFound_420) {

    const char* data = "abc";

    size_t size = 3; // Assuming prefix_size_ is at least 2

    EXPECT_EQ(prog.PrefixAccel_FrontAndBack(data, size), nullptr);

}



TEST_F(ProgTest_420, PrefixAccel_FrontAndBack_ReturnsPointerToMatch_420) {

    const char* data = "abcba";

    size_t size = 5; // Assuming prefix_size_ is at least 2

    prog.prefix_front_ = 'a';

    prog.prefix_back_ = 'a';

    EXPECT_NE(prog.PrefixAccel_FrontAndBack(data, size), nullptr);

}



TEST_F(ProgTest_420, PrefixAccel_FrontAndBack_ReturnsPointerToFirstMatch_420) {

    const char* data = "abcbaabca";

    size_t size = 9; // Assuming prefix_size_ is at least 2

    prog.prefix_front_ = 'a';

    prog.prefix_back_ = 'a';

    EXPECT_EQ(prog.PrefixAccel_FrontAndBack(data, size), reinterpret_cast<const void*>(data));

}



TEST_F(ProgTest_420, PrefixAccel_FrontAndBack_HandlesPrefixSizeEqualToDataSize_420) {

    const char* data = "ab";

    size_t size = 2; // Assuming prefix_size_ is at least 2

    prog.prefix_front_ = 'a';

    prog.prefix_back_ = 'b';

    EXPECT_EQ(prog.PrefixAccel_FrontAndBack(data, size), reinterpret_cast<const void*>(data));

}



TEST_F(ProgTest_420, PrefixAccel_FrontAndBack_HandlesPrefixSizeGreaterThanDataSize_420) {

    const char* data = "a";

    size_t size = 1; // Assuming prefix_size_ is at least 2

    prog.prefix_front_ = 'a';

    prog.prefix_back_ = 'b';

    EXPECT_EQ(prog.PrefixAccel_FrontAndBack(data, size), nullptr);

}



TEST_F(ProgTest_420, PrefixAccel_FrontAndBack_BoundaryConditionsWithPrefixSizeTwo_420) {

    const char* data = "aa";

    size_t size = 2; // Assuming prefix_size_ is at least 2

    prog.prefix_front_ = 'a';

    prog.prefix_back_ = 'a';

    EXPECT_EQ(prog.PrefixAccel_FrontAndBack(data, size), reinterpret_cast<const void*>(data));

}



TEST_F(ProgTest_420, PrefixAccel_FrontAndBack_BoundaryConditionsWithPrefixSizeGreaterThanTwo_420) {

    const char* data = "abcba";

    size_t size = 5; // Assuming prefix_size_ is at least 3

    prog.prefix_front_ = 'a';

    prog.prefix_back_ = 'a';

    prog.prefix_size_ = 3;

    EXPECT_NE(prog.PrefixAccel_FrontAndBack(data, size), nullptr);

}



} // namespace re2
