#include <gtest/gtest.h>

#include "re2/prog.h"



namespace re2 {

class ProgTest : public ::testing::Test {

protected:

    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }



    Prog* prog;

};



TEST_F(ProgTest_131, PrefixAccel_NoPrefixConfigured_ReturnsNull_131) {

    const char data[] = "test";

    size_t size = sizeof(data);

    EXPECT_EQ(prog->PrefixAccel(data, size), nullptr);

}



TEST_F(ProgTest_131, PrefixAccel_SingleCharacterPrefix_MatchesFound_131) {

    prog->ConfigurePrefixAccel("a", false);

    const char data[] = "abcd";

    size_t size = sizeof(data);

    EXPECT_EQ(prog->PrefixAccel(data, size), static_cast<const void*>(data));

}



TEST_F(ProgTest_131, PrefixAccel_SingleCharacterPrefix_MatchesNotFound_131) {

    prog->ConfigurePrefixAccel("a", false);

    const char data[] = "bcd";

    size_t size = sizeof(data);

    EXPECT_EQ(prog->PrefixAccel(data, size), nullptr);

}



TEST_F(ProgTest_131, PrefixAccel_MultiCharacterPrefixWithoutFoldCase_MatchesFound_131) {

    prog->ConfigurePrefixAccel("abc", false);

    const char data[] = "abcdef";

    size_t size = sizeof(data);

    EXPECT_EQ(prog->PrefixAccel(data, size), static_cast<const void*>(data));

}



TEST_F(ProgTest_131, PrefixAccel_MultiCharacterPrefixWithoutFoldCase_MatchesNotFound_131) {

    prog->ConfigurePrefixAccel("abc", false);

    const char data[] = "def";

    size_t size = sizeof(data);

    EXPECT_EQ(prog->PrefixAccel(data, size), nullptr);

}



TEST_F(ProgTest_131, PrefixAccel_MultiCharacterPrefixWithFoldCase_MatchesFound_131) {

    prog->ConfigurePrefixAccel("abc", true);

    const char data[] = "ABCdef";

    size_t size = sizeof(data);

    EXPECT_EQ(prog->PrefixAccel(data, size), static_cast<const void*>(data));

}



TEST_F(ProgTest_131, PrefixAccel_MultiCharacterPrefixWithFoldCase_MatchesNotFound_131) {

    prog->ConfigurePrefixAccel("abc", true);

    const char data[] = "def";

    size_t size = sizeof(data);

    EXPECT_EQ(prog->PrefixAccel(data, size), nullptr);

}



TEST_F(ProgTest_131, PrefixAccel_EmptyData_ReturnsNull_131) {

    prog->ConfigurePrefixAccel("abc", false);

    const char data[] = "";

    size_t size = 0;

    EXPECT_EQ(prog->PrefixAccel(data, size), nullptr);

}



TEST_F(ProgTest_131, PrefixAccel_DataSizeExceedsPrefixSize_ReturnsMatch_131) {

    prog->ConfigurePrefixAccel("abc", false);

    const char data[] = "abcdef";

    size_t size = 6; // sizeof(data) - 1 to exclude null terminator

    EXPECT_EQ(prog->PrefixAccel(data, size), static_cast<const void*>(data));

}



TEST_F(ProgTest_131, PrefixAccel_DataSizeEqualsPrefixSize_ReturnsMatch_131) {

    prog->ConfigurePrefixAccel("abc", false);

    const char data[] = "abc";

    size_t size = 3; // sizeof(data) - 1 to exclude null terminator

    EXPECT_EQ(prog->PrefixAccel(data, size), static_cast<const void*>(data));

}



TEST_F(ProgTest_131, PrefixAccel_DataSizeLessThanPrefixSize_ReturnsNull_131) {

    prog->ConfigurePrefixAccel("abc", false);

    const char data[] = "ab";

    size_t size = 2; // sizeof(data) - 1 to exclude null terminator

    EXPECT_EQ(prog->PrefixAccel(data, size), nullptr);

}



} // namespace re2
