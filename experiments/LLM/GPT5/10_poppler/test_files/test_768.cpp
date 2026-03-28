#include <gtest/gtest.h>
#include <memory>

// Mock classes for dependencies
class AnnotColor {};
class GooString {};
class AnnotIconFit {};
class AnnotAppearanceCharacsTextPos {};
class Dict {};

// The class under test
class AnnotAppearanceCharacs {
public:
    explicit AnnotAppearanceCharacs(Dict *dict) {}
    void setBackColor(std::unique_ptr<AnnotColor> &&color) { backColor = std::move(color); }
    void setBorderColor(std::unique_ptr<AnnotColor> &&color) { borderColor = std::move(color); }
    const AnnotColor *getBackColor() const { return backColor.get(); }
    const AnnotColor *getBorderColor() const { return borderColor.get(); }
    const GooString *getNormalCaption() const { return normalCaption.get(); }
    const GooString *getRolloverCaption() { return rolloverCaption.get(); }
    const GooString *getAlternateCaption() { return alternateCaption.get(); }
    const AnnotIconFit *getIconFit() { return iconFit.get(); }
    AnnotAppearanceCharacsTextPos getPosition() const { return position; }

private:
    std::unique_ptr<AnnotColor> borderColor;
    std::unique_ptr<AnnotColor> backColor;
    std::unique_ptr<GooString> normalCaption;
    std::unique_ptr<GooString> rolloverCaption;
    std::unique_ptr<GooString> alternateCaption;
    std::unique_ptr<AnnotIconFit> iconFit;
    AnnotAppearanceCharacsTextPos position;
};

TEST_F(AnnotAppearanceCharacsTest_768, SetAndGetBackColor_768) {
    // Test setting and getting backColor
    auto color = std::make_unique<AnnotColor>();
    AnnotAppearanceCharacs annot(nullptr);
    annot.setBackColor(std::move(color));

    // Verifying the setter and getter behavior
    EXPECT_EQ(annot.getBackColor(), color.get());
}

TEST_F(AnnotAppearanceCharacsTest_769, SetAndGetBorderColor_769) {
    // Test setting and getting borderColor
    auto color = std::make_unique<AnnotColor>();
    AnnotAppearanceCharacs annot(nullptr);
    annot.setBorderColor(std::move(color));

    // Verifying the setter and getter behavior
    EXPECT_EQ(annot.getBorderColor(), color.get());
}

TEST_F(AnnotAppearanceCharacsTest_770, SetBackColorWithNullPointer_770) {
    // Test setting backColor with a nullptr
    AnnotAppearanceCharacs annot(nullptr);
    annot.setBackColor(nullptr);

    // Verifying the setter and getter behavior with nullptr
    EXPECT_EQ(annot.getBackColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_771, SetBorderColorWithNullPointer_771) {
    // Test setting borderColor with a nullptr
    AnnotAppearanceCharacs annot(nullptr);
    annot.setBorderColor(nullptr);

    // Verifying the setter and getter behavior with nullptr
    EXPECT_EQ(annot.getBorderColor(), nullptr);
}

TEST_F(AnnotAppearanceCharacsTest_772, GetNormalCaption_772) {
    // Test getting normalCaption
    auto caption = std::make_unique<GooString>();
    AnnotAppearanceCharacs annot(nullptr);
    annot.normalCaption = std::move(caption);

    // Verifying the getter for normalCaption
    EXPECT_EQ(annot.getNormalCaption(), caption.get());
}

TEST_F(AnnotAppearanceCharacsTest_773, GetRolloverCaption_773) {
    // Test getting rolloverCaption
    auto caption = std::make_unique<GooString>();
    AnnotAppearanceCharacs annot(nullptr);
    annot.rolloverCaption = std::move(caption);

    // Verifying the getter for rolloverCaption
    EXPECT_EQ(annot.getRolloverCaption(), caption.get());
}

TEST_F(AnnotAppearanceCharacsTest_774, GetAlternateCaption_774) {
    // Test getting alternateCaption
    auto caption = std::make_unique<GooString>();
    AnnotAppearanceCharacs annot(nullptr);
    annot.alternateCaption = std::move(caption);

    // Verifying the getter for alternateCaption
    EXPECT_EQ(annot.getAlternateCaption(), caption.get());
}

TEST_F(AnnotAppearanceCharacsTest_775, GetIconFit_775) {
    // Test getting iconFit
    auto iconFit = std::make_unique<AnnotIconFit>();
    AnnotAppearanceCharacs annot(nullptr);
    annot.iconFit = std::move(iconFit);

    // Verifying the getter for iconFit
    EXPECT_EQ(annot.getIconFit(), iconFit.get());
}

TEST_F(AnnotAppearanceCharacsTest_776, GetPosition_776) {
    // Test getting position
    AnnotAppearanceCharacs annot(nullptr);
    auto position = annot.getPosition();

    // Verifying the getter for position
    EXPECT_EQ(position, annot.getPosition());
}

TEST_F(AnnotAppearanceCharacsTest_777, CopyConstructor_777) {
    // Test that the copy constructor does not work (since it's deleted)
    AnnotAppearanceCharacs annot(nullptr);
    EXPECT_DEATH(AnnotAppearanceCharacs copy = annot, "");
}

TEST_F(AnnotAppearanceCharacsTest_778, AssignmentOperator_778) {
    // Test that the assignment operator does not work (since it's deleted)
    AnnotAppearanceCharacs annot(nullptr);
    AnnotAppearanceCharacs another(nullptr);
    EXPECT_DEATH(another = annot, "");
}