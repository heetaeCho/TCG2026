#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Sound.h"
#include "Object.h"
#include "Stream.h"
#include "Dict.h"
#include "PDFDoc.h"

#include <memory>
#include <string>

class SoundTest_1448 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that parseSound returns 0 for a non-sound object (e.g., null object)
TEST_F(SoundTest_1448, ParseSoundWithNullObject_1448) {
    Object obj;
    int result = Sound::parseSound(obj);
    // A null/invalid object should not parse as a valid sound
    EXPECT_EQ(result, 0);
}

// Test that parseSound returns 0 for an integer object (not a stream)
TEST_F(SoundTest_1448, ParseSoundWithIntObject_1448) {
    Object obj(42);
    int result = Sound::parseSound(obj);
    EXPECT_EQ(result, 0);
}

// Test that parseSound returns 0 for a string object
TEST_F(SoundTest_1448, ParseSoundWithStringObject_1448) {
    Object obj(GooString("not a sound"));
    int result = Sound::parseSound(obj);
    EXPECT_EQ(result, 0);
}

// Test that parseSound returns 0 for a boolean object
TEST_F(SoundTest_1448, ParseSoundWithBoolObject_1448) {
    Object obj(true);
    int result = Sound::parseSound(obj);
    EXPECT_EQ(result, 0);
}

// Test that parseSound returns 0 for a real number object
TEST_F(SoundTest_1448, ParseSoundWithRealObject_1448) {
    Object obj(3.14);
    int result = Sound::parseSound(obj);
    EXPECT_EQ(result, 0);
}

// Test that parseSound returns 0 for an array object (not a valid sound)
TEST_F(SoundTest_1448, ParseSoundWithArrayObject_1448) {
    Object obj(new Array(nullptr));
    int result = Sound::parseSound(obj);
    EXPECT_EQ(result, 0);
}

// Test that parseSound returns 0 for a dict object (not a stream)
TEST_F(SoundTest_1448, ParseSoundWithDictObject_1448) {
    Object obj(new Dict(nullptr));
    int result = Sound::parseSound(obj);
    EXPECT_EQ(result, 0);
}

// Test copy method returns a valid Sound pointer and preserves properties
// This requires a valid Sound object which needs a valid stream object with Sound dict
// We test with a constructed stream that has the proper Sound attributes
TEST_F(SoundTest_1448, ParseSoundReturnValueForInvalidInput_1448) {
    // Verify consistency: multiple calls with same invalid object yield same result
    Object obj;
    int result1 = Sound::parseSound(obj);
    int result2 = Sound::parseSound(obj);
    EXPECT_EQ(result1, result2);
}

// Test that parseSound handles a copied/moved object properly
TEST_F(SoundTest_1448, ParseSoundWithCopiedObject_1448) {
    Object obj1(100);
    Object obj2 = obj1.copy();
    int result = Sound::parseSound(obj2);
    EXPECT_EQ(result, 0);
}
