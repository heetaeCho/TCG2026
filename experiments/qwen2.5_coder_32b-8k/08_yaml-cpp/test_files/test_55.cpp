#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>



class EmitterTest_55 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_55, WriteIntegralType_ValidValue_55) {

    unsigned long long value = 1234567890ULL;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_55, WriteIntegralType_Zero_55) {

    unsigned long long value = 0ULL;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_55, WriteIntegralType_MaxValue_55) {

    unsigned long long value = ULLONG_MAX;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_55, WriteIntegralType_AfterOtherWrites_55) {

    emitter << "test string";

    unsigned long long value = 1234567890ULL;

    emitter << value;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_55, WriteIntegralType_CheckOutput_55) {

    unsigned long long value = 1234567890ULL;

    emitter << value;

    std::string expected_output = "1234567890";

    EXPECT_EQ(expected_output, emitter.c_str());

}



TEST_F(EmitterTest_55, WriteIntegralType_CheckSize_55) {

    unsigned long long value = 1234567890ULL;

    emitter << value;

    std::size_t expected_size = 10; // Length of "1234567890"

    EXPECT_EQ(expected_size, emitter.size());

}
