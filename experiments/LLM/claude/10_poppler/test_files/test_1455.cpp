#include <gtest/gtest.h>
#include "poppler-qt5.h"

// Include necessary headers for the Poppler Sound/SoundData types
// We need access to the SoundData class which appears to be internal
// but has public members according to the known dependencies

namespace Poppler {

// Test fixture for SoundData
class SoundDataTest_1455 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that SoundObject can be created via the public API
// Since SoundData appears to be an internal implementation detail,
// we test through the Sound public interface if available

// Testing Sound class which is the public-facing class
class SoundTest_1455 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test Sound object type enumeration
TEST_F(SoundTest_1455, SoundTypeEnumExists_1455) {
    // Verify that Sound::SoundType enum values exist
    Poppler::SoundObject::SoundType embedded = Poppler::SoundObject::Embedded;
    Poppler::SoundObject::SoundType external = Poppler::SoundObject::External;
    EXPECT_NE(embedded, external);
}

// Test Sound encoding enumeration
TEST_F(SoundTest_1455, SoundEncodingEnumExists_1455) {
    Poppler::SoundObject::SoundEncoding raw = Poppler::SoundObject::Raw;
    Poppler::SoundObject::SoundEncoding signed_enc = Poppler::SoundObject::Signed;
    Poppler::SoundObject::SoundEncoding muLaw = Poppler::SoundObject::muLaw;
    Poppler::SoundObject::SoundEncoding aLaw = Poppler::SoundObject::ALaw;
    
    // All encodings should be distinct
    EXPECT_NE(raw, signed_enc);
    EXPECT_NE(raw, muLaw);
    EXPECT_NE(raw, aLaw);
    EXPECT_NE(signed_enc, muLaw);
    EXPECT_NE(signed_enc, aLaw);
    EXPECT_NE(muLaw, aLaw);
}

} // namespace Poppler

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>

// Attempt to include the relevant poppler headers
#include "poppler-qt5.h"

namespace {

class SoundDataTest_1455 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that SoundObject type enum values are distinct
TEST_F(SoundDataTest_1455, SoundTypeEnumValues_1455) {
    EXPECT_EQ(static_cast<int>(Poppler::SoundObject::Embedded), 0);
    EXPECT_EQ(static_cast<int>(Poppler::SoundObject::External), 1);
}

// Test that SoundEncoding enum values are distinct
TEST_F(SoundDataTest_1455, SoundEncodingEnumValues_1455) {
    Poppler::SoundObject::SoundEncoding raw = Poppler::SoundObject::Raw;
    Poppler::SoundObject::SoundEncoding sig = Poppler::SoundObject::Signed;
    Poppler::SoundObject::SoundEncoding mu = Poppler::SoundObject::muLaw;
    Poppler::SoundObject::SoundEncoding al = Poppler::SoundObject::ALaw;
    
    EXPECT_NE(raw, sig);
    EXPECT_NE(raw, mu);
    EXPECT_NE(raw, al);
}

} // anonymous namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
