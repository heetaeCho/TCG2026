#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitter.h"

#include "yaml-cpp/binary.h"



using namespace YAML;



class EmitterTest_543 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_543, WriteBinary_NormalOperation_543) {

    Binary binary(reinterpret_cast<const unsigned char*>("test"), 4);

    Emitter& result = emitter.Write(binary);

    EXPECT_EQ(&result, &emitter); // Check if the returned reference is correct

}



TEST_F(EmitterTest_543, WriteBinary_EmptyBinary_543) {

    Binary binary;

    Emitter& result = emitter.Write(binary);

    EXPECT_EQ(&result, &emitter); // Check if the returned reference is correct

}



TEST_F(EmitterTest_543, WriteBinary_BoundaryCondition_LargeSize_543) {

    std::vector<unsigned char> largeData(1024 * 1024, 'A'); // 1MB of data

    Binary binary(largeData.data(), largeData.size());

    Emitter& result = emitter.Write(binary);

    EXPECT_EQ(&result, &emitter); // Check if the returned reference is correct

}



TEST_F(EmitterTest_543, WriteBinary_ExceptionalCase_EmptyEmitterStream_543) {

    std::ostringstream nullStream;

    nullStream.clear(std::ios_base::badbit); // Set bad bit to simulate a broken stream

    Emitter badEmitter(nullStream);

    Binary binary(reinterpret_cast<const unsigned char*>("test"), 4);

    Emitter& result = badEmitter.Write(binary);

    EXPECT_EQ(&result, &badEmitter); // Check if the returned reference is correct

    EXPECT_FALSE(badEmitter.good()); // Check if the emitter is not good after writing to a bad stream

}



TEST_F(EmitterTest_543, WriteBinary_VerificationOfGoodState_543) {

    Binary binary(reinterpret_cast<const unsigned char*>("test"), 4);

    Emitter& result = emitter.Write(binary);

    EXPECT_TRUE(emitter.good()); // Check if the emitter is still in a good state after writing

}



TEST_F(EmitterTest_543, WriteBinary_VerificationOfGoodState_AfterFailure_543) {

    std::ostringstream nullStream;

    nullStream.clear(std::ios_base::badbit); // Set bad bit to simulate a broken stream

    Emitter badEmitter(nullStream);

    Binary binary(reinterpret_cast<const unsigned char*>("test"), 4);

    badEmitter.Write(binary);

    EXPECT_FALSE(badEmitter.good()); // Check if the emitter is not in a good state after writing to a bad stream

}
