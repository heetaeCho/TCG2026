#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include the necessary Poppler Qt5 headers
#include "poppler-annotation.h"
#include "poppler-qt5.h"

namespace {

// Test fixture for SoundAnnotation tests
class SoundAnnotationTest_1415 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a SoundAnnotation can be created without crashing
TEST_F(SoundAnnotationTest_1415, DefaultConstruction_1415) {
    Poppler::SoundAnnotation annot;
    // Should be able to create a SoundAnnotation without issues
    EXPECT_EQ(annot.subType(), Poppler::Annotation::ASound);
}

// Test that the default icon is "Speaker"
TEST_F(SoundAnnotationTest_1415, DefaultIconIsSpeaker_1415) {
    Poppler::SoundAnnotation annot;
    EXPECT_EQ(annot.soundIconName(), QStringLiteral("Speaker"));
}

// Test setting and getting the sound icon name
TEST_F(SoundAnnotationTest_1415, SetAndGetSoundIconName_1415) {
    Poppler::SoundAnnotation annot;
    annot.setSoundIconName(QStringLiteral("Mic"));
    EXPECT_EQ(annot.soundIconName(), QStringLiteral("Mic"));
}

// Test setting icon name to empty string
TEST_F(SoundAnnotationTest_1415, SetEmptyIconName_1415) {
    Poppler::SoundAnnotation annot;
    annot.setSoundIconName(QStringLiteral(""));
    EXPECT_EQ(annot.soundIconName(), QStringLiteral(""));
}

// Test that sound() returns nullptr by default (no sound object attached)
TEST_F(SoundAnnotationTest_1415, DefaultSoundIsNull_1415) {
    Poppler::SoundAnnotation annot;
    EXPECT_EQ(annot.sound(), nullptr);
}

// Test that subType returns ASound
TEST_F(SoundAnnotationTest_1415, SubTypeIsASound_1415) {
    Poppler::SoundAnnotation annot;
    EXPECT_EQ(annot.subType(), Poppler::Annotation::ASound);
}

// Test that destruction of SoundAnnotation does not crash
TEST_F(SoundAnnotationTest_1415, DestructionDoesNotCrash_1415) {
    auto annot = std::make_unique<Poppler::SoundAnnotation>();
    annot->setSoundIconName(QStringLiteral("TestIcon"));
    // Explicit destruction should not crash
    annot.reset();
    SUCCEED();
}

// Test setting icon name with special characters
TEST_F(SoundAnnotationTest_1415, SetIconNameWithSpecialChars_1415) {
    Poppler::SoundAnnotation annot;
    QString specialName = QStringLiteral("Icon_With-Special.Chars!@#");
    annot.setSoundIconName(specialName);
    EXPECT_EQ(annot.soundIconName(), specialName);
}

// Test setting icon name with unicode characters
TEST_F(SoundAnnotationTest_1415, SetIconNameWithUnicode_1415) {
    Poppler::SoundAnnotation annot;
    QString unicodeName = QStringLiteral("スピーカー");
    annot.setSoundIconName(unicodeName);
    EXPECT_EQ(annot.soundIconName(), unicodeName);
}

// Test that multiple set calls to icon name work correctly (last one wins)
TEST_F(SoundAnnotationTest_1415, MultipleSetIconNameCalls_1415) {
    Poppler::SoundAnnotation annot;
    annot.setSoundIconName(QStringLiteral("First"));
    annot.setSoundIconName(QStringLiteral("Second"));
    annot.setSoundIconName(QStringLiteral("Third"));
    EXPECT_EQ(annot.soundIconName(), QStringLiteral("Third"));
}

// Test that SoundAnnotation inherits from Annotation properly
TEST_F(SoundAnnotationTest_1415, InheritsFromAnnotation_1415) {
    Poppler::SoundAnnotation annot;
    // Test base class functionality - boundary/flags
    annot.setBoundary(QRectF(0.0, 0.0, 1.0, 1.0));
    EXPECT_EQ(annot.boundary(), QRectF(0.0, 0.0, 1.0, 1.0));
}

// Test setting author through base class interface
TEST_F(SoundAnnotationTest_1415, SetAuthorFromBaseClass_1415) {
    Poppler::SoundAnnotation annot;
    annot.setAuthor(QStringLiteral("TestAuthor"));
    EXPECT_EQ(annot.author(), QStringLiteral("TestAuthor"));
}

// Test setting contents through base class interface
TEST_F(SoundAnnotationTest_1415, SetContentsFromBaseClass_1415) {
    Poppler::SoundAnnotation annot;
    annot.setContents(QStringLiteral("TestContents"));
    EXPECT_EQ(annot.contents(), QStringLiteral("TestContents"));
}

} // anonymous namespace
