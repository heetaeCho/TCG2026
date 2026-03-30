#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/binary.h"



class EmitterTest_46 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_46, WriteBinary_NormalOperation_46) {

    unsigned char data[] = {0x01, 0x02, 0x03};

    YAML::Binary binary(data, sizeof(data));

    emitter << binary;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_46, WriteBinary_EmptyData_46) {

    unsigned char data[] = {};

    YAML::Binary binary(data, sizeof(data));

    emitter << binary;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_46, WriteBinary_LargeData_46) {

    std::vector<unsigned char> largeData(1024, 0xFF);

    YAML::Binary binary(largeData.data(), largeData.size());

    emitter << binary;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_46, WriteBinary_ErrorHandling_46) {

    // Assuming there is no observable error condition for writing binary data,

    // this test would be more relevant if there were a known failure mode.

    unsigned char data[] = {0x01};

    YAML::Binary binary(data, sizeof(data));

    emitter << binary;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_46, WriteBinary_OwnedData_46) {

    std::vector<unsigned char> ownedData = {0x0A, 0x0B};

    YAML::Binary binary(ownedData.data(), ownedData.size());

    emitter << binary;

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_46, WriteBinary_UnownedData_46) {

    unsigned char unownedData[] = {0x1A, 0x1B};

    YAML::Binary binary(unownedData, sizeof(unownedData));

    emitter << binary;

    EXPECT_TRUE(emitter.good());

}
