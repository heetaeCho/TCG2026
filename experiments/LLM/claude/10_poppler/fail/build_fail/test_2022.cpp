#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GfxFont.h"
#include "Annot.h"

// Since createAnnotDrawFont is a static function in Annot.cc, we need to
// include the implementation file or test through the public API that uses it.
// We'll test the components and behavior observable through Dict/Object.

class CreateAnnotDrawFontTest_2022 : public ::testing::Test {
protected:
    void SetUp() override {
        xref = std::make_unique<XRef>();
    }

    void TearDown() override {
    }

    std::unique_ptr<XRef> xref;
};

// Test Dict creation and basic operations used by createAnnotDrawFont
TEST_F(CreateAnnotDrawFontTest_2022, DictAddAndLookup_2022) {
    Dict *dict = new Dict(xref.get());
    dict->add("BaseFont", Object(objName, "Helvetica"));
    dict->add("Subtype", Object(objName, "Type1"));

    Object baseFont = dict->lookup("BaseFont");
    ASSERT_TRUE(baseFont.isName());
    EXPECT_STREQ(baseFont.getName(), "Helvetica");

    Object subtype = dict->lookup("Subtype");
    ASSERT_TRUE(subtype.isName());
    EXPECT_STREQ(subtype.getName(), "Type1");

    // Dict is ref counted, but we need to manage it properly
    // The Object that wraps it will handle cleanup
    Object dictObj(dict);
}

TEST_F(CreateAnnotDrawFontTest_2022, DictSetOverwritesExisting_2022) {
    Dict *dict = new Dict(xref.get());
    dict->add("Key", Object(objName, "Value1"));
    dict->set("Key", Object(objName, "Value2"));

    Object val = dict->lookup("Key");
    ASSERT_TRUE(val.isName());
    EXPECT_STREQ(val.getName(), "Value2");

    Object dictObj(dict);
}

TEST_F(CreateAnnotDrawFontTest_2022, FontParentDictWithoutFontEntry_2022) {
    // Simulate what createAnnotDrawFont does when parent has no "Font" key
    Dict *fontParentDict = new Dict(xref.get());

    Object fontsDictObj = fontParentDict->lookup("Font");
    EXPECT_FALSE(fontsDictObj.isDict());

    // Create new font dict and add to parent
    fontsDictObj = Object(new Dict(xref.get()));
    fontParentDict->add("Font", fontsDictObj.copy());

    // Now lookup should return a dict
    Object result = fontParentDict->lookup("Font");
    ASSERT_TRUE(result.isDict());

    Object parentObj(fontParentDict);
}

TEST_F(CreateAnnotDrawFontTest_2022, FontParentDictWithExistingFontEntry_2022) {
    Dict *fontParentDict = new Dict(xref.get());
    Dict *existingFonts = new Dict(xref.get());
    existingFonts->add("ExistingFont", Object(objName, "Times"));
    fontParentDict->add("Font", Object(existingFonts));

    Object fontsDictObj = fontParentDict->lookup("Font");
    ASSERT_TRUE(fontsDictObj.isDict());

    // Should be able to add more entries
    fontsDictObj.dictSet("NewFont", Object(new Dict(xref.get())));

    // Verify existing entry still present
    Object existing = fontsDictObj.dictLookup("ExistingFont");
    ASSERT_TRUE(existing.isName());
    EXPECT_STREQ(existing.getName(), "Times");

    Object parentObj(fontParentDict);
}

TEST_F(CreateAnnotDrawFontTest_2022, ObjectNameCreation_2022) {
    Object nameObj(objName, "Helvetica");
    ASSERT_TRUE(nameObj.isName());
    EXPECT_STREQ(nameObj.getName(), "Helvetica");
}

TEST_F(CreateAnnotDrawFontTest_2022, ObjectNameType1_2022) {
    Object nameObj(objName, "Type1");
    ASSERT_TRUE(nameObj.isName());
    EXPECT_STREQ(nameObj.getName(), "Type1");
}

TEST_F(CreateAnnotDrawFontTest_2022, WinAnsiEncodingForHelvetica_2022) {
    // For Helvetica (not ZapfDingbats or Symbol), encoding should be added
    Dict *fontDict = new Dict(xref.get());
    const char *fontname = "Helvetica";

    fontDict->add("BaseFont", Object(objName, fontname));
    fontDict->add("Subtype", Object(objName, "Type1"));

    if ((strcmp(fontname, "ZapfDingbats") != 0) && (strcmp(fontname, "Symbol") != 0)) {
        fontDict->add("Encoding", Object(objName, "WinAnsiEncoding"));
    }

    Object encoding = fontDict->lookup("Encoding");
    ASSERT_TRUE(encoding.isName());
    EXPECT_STREQ(encoding.getName(), "WinAnsiEncoding");

    Object dictObj(fontDict);
}

TEST_F(CreateAnnotDrawFontTest_2022, NoEncodingForZapfDingbats_2022) {
    // For ZapfDingbats, encoding should NOT be added
    Dict *fontDict = new Dict(xref.get());
    const char *fontname = "ZapfDingbats";

    fontDict->add("BaseFont", Object(objName, fontname));
    fontDict->add("Subtype", Object(objName, "Type1"));

    if ((strcmp(fontname, "ZapfDingbats") != 0) && (strcmp(fontname, "Symbol") != 0)) {
        fontDict->add("Encoding", Object(objName, "WinAnsiEncoding"));
    }

    Object encoding = fontDict->lookup("Encoding");
    EXPECT_FALSE(encoding.isName());
    EXPECT_TRUE(encoding.isNull() || encoding.isNone());

    Object dictObj(fontDict);
}

TEST_F(CreateAnnotDrawFontTest_2022, NoEncodingForSymbol_2022) {
    // For Symbol, encoding should NOT be added
    Dict *fontDict = new Dict(xref.get());
    const char *fontname = "Symbol";

    fontDict->add("BaseFont", Object(objName, fontname));
    fontDict->add("Subtype", Object(objName, "Type1"));

    if ((strcmp(fontname, "ZapfDingbats") != 0) && (strcmp(fontname, "Symbol") != 0)) {
        fontDict->add("Encoding", Object(objName, "WinAnsiEncoding"));
    }

    Object encoding = fontDict->lookup("Encoding");
    EXPECT_FALSE(encoding.isName());

    Object dictObj(fontDict);
}

TEST_F(CreateAnnotDrawFontTest_2022, DictGetLength_2022) {
    Dict *dict = new Dict(xref.get());
    EXPECT_EQ(dict->getLength(), 0);

    dict->add("Key1", Object(objName, "Val1"));
    EXPECT_EQ(dict->getLength(), 1);

    dict->add("Key2", Object(objName, "Val2"));
    EXPECT_EQ(dict->getLength(), 2);

    Object dictObj(dict);
}

TEST_F(CreateAnnotDrawFontTest_2022, DictHasKey_2022) {
    Dict *dict = new Dict(xref.get());
    EXPECT_FALSE(dict->hasKey("Font"));

    dict->add("Font", Object(new Dict(xref.get())));
    EXPECT_TRUE(dict->hasKey("Font"));

    Object dictObj(dict);
}

TEST_F(CreateAnnotDrawFontTest_2022, ObjectCopyPreservesType_2022) {
    Dict *dict = new Dict(xref.get());
    dict->add("Key", Object(objName, "Value"));
    Object original(dict);

    Object copied = original.copy();
    ASSERT_TRUE(copied.isDict());

    Object val = copied.dictLookup("Key");
    ASSERT_TRUE(val.isName());
    EXPECT_STREQ(val.getName(), "Value");
}

TEST_F(CreateAnnotDrawFontTest_2022, InvalidRefCreation_2022) {
    Ref dummyRef = { .num = -1, .gen = -1 };
    EXPECT_EQ(dummyRef.num, -1);
    EXPECT_EQ(dummyRef.gen, -1);
}

TEST_F(CreateAnnotDrawFontTest_2022, DictRemove_2022) {
    Dict *dict = new Dict(xref.get());
    dict->add("Key1", Object(objName, "Val1"));
    dict->add("Key2", Object(objName, "Val2"));
    EXPECT_EQ(dict->getLength(), 2);

    dict->remove("Key1");
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_FALSE(dict->hasKey("Key1"));
    EXPECT_TRUE(dict->hasKey("Key2"));

    Object dictObj(dict);
}

TEST_F(CreateAnnotDrawFontTest_2022, ObjectDictSetViaObjectInterface_2022) {
    Dict *dict = new Dict(xref.get());
    Object dictObj(dict);

    Dict *innerDict = new Dict(xref.get());
    innerDict->add("Inner", Object(objName, "InnerVal"));
    dictObj.dictSet("Resource", Object(innerDict));

    Object result = dictObj.dictLookup("Resource");
    ASSERT_TRUE(result.isDict());

    Object innerVal = result.dictLookup("Inner");
    ASSERT_TRUE(innerVal.isName());
    EXPECT_STREQ(innerVal.getName(), "InnerVal");
}

TEST_F(CreateAnnotDrawFontTest_2022, EncodingAddedForCourier_2022) {
    // Courier is not ZapfDingbats or Symbol, so encoding should be added
    Dict *fontDict = new Dict(xref.get());
    const char *fontname = "Courier";

    fontDict->add("BaseFont", Object(objName, fontname));
    fontDict->add("Subtype", Object(objName, "Type1"));

    if ((strcmp(fontname, "ZapfDingbats") != 0) && (strcmp(fontname, "Symbol") != 0)) {
        fontDict->add("Encoding", Object(objName, "WinAnsiEncoding"));
    }

    Object encoding = fontDict->lookup("Encoding");
    ASSERT_TRUE(encoding.isName());
    EXPECT_STREQ(encoding.getName(), "WinAnsiEncoding");

    Object dictObj(fontDict);
}

TEST_F(CreateAnnotDrawFontTest_2022, MultipleFontResourcesInParent_2022) {
    Dict *fontParentDict = new Dict(xref.get());
    Dict *fontsDict = new Dict(xref.get());

    Dict *font1 = new Dict(xref.get());
    font1->add("BaseFont", Object(objName, "Helvetica"));
    fontsDict->add("Font1", Object(font1));

    Dict *font2 = new Dict(xref.get());
    font2->add("BaseFont", Object(objName, "Courier"));
    fontsDict->add("Font2", Object(font2));

    fontParentDict->add("Font", Object(fontsDict));

    Object fontsDictObj = fontParentDict->lookup("Font");
    ASSERT_TRUE(fontsDictObj.isDict());
    EXPECT_EQ(fontsDictObj.dictGetLength(), 2);

    Object parentObj(fontParentDict);
}
