#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"

#include <memory>



using ::testing::_;

using ::testing::Return;



class MockXRef : public XRef {

public:

    MOCK_METHOD(std::unique_ptr<GfxFont>, makeFont, (const char *tagA, Ref idA, Dict *fontDict), (override));

};



TEST_F(GfxFontTest_1157, GetFontBBox_ReturnsValidArray_1157) {

    std::array<double, 4> expected = {0.0, 1.0, 2.0, 3.0};

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    const auto& bbox = font->getFontBBox();



    EXPECT_EQ(bbox.size(), expected.size());

    for (size_t i = 0; i < bbox.size(); ++i) {

        EXPECT_DOUBLE_EQ(bbox[i], expected[i]);

    }

}



TEST_F(GfxFontTest_1157, GetTag_ReturnsCorrectValue_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("expectedTag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_EQ(font->getTag(), "expectedTag");

}



TEST_F(GfxFontTest_1157, GetID_ReturnsCorrectValue_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    Ref expectedRef(1234, 0);

    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([expectedRef](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", expectedRef, "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", expectedRef, fontDictMock.get());

    EXPECT_EQ(*font->getID(), expectedRef);

}



TEST_F(GfxFontTest_1157, IsSubset_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->isSubset());

}



TEST_F(GfxFontTest_1157, GetNameWithoutSubsetTag_ReturnsCorrectValue_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "nameSubset", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_EQ(font->getNameWithoutSubsetTag(), "name");

}



TEST_F(GfxFontTest_1157, IsCIDFont_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->isCIDFont());

}



TEST_F(GfxFontTest_1157, GetEmbeddedFontID_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;

    Ref embID;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->getEmbeddedFontID(&embID));

}



TEST_F(GfxFontTest_1157, InvalidateEmbeddedFont_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1157, GetEmbeddedFontName_ReturnsNullByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_EQ(font->getEmbeddedFontName(), nullptr);

}



TEST_F(GfxFontTest_1157, GetFlags_ReturnsZeroByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_EQ(font->getFlags(), 0);

}



TEST_F(GfxFontTest_1157, IsFixedWidth_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->isFixedWidth());

}



TEST_F(GfxFontTest_1157, IsSerif_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->isSerif());

}



TEST_F(GfxFontTest_1157, IsSymbolic_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->isSymbolic());

}



TEST_F(GfxFontTest_1157, IsItalic_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->isItalic());

}



TEST_F(GfxFontTest_1157, IsBold_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->isBold());

}



TEST_F(GfxFontTest_1157, GetFontMatrix_ReturnsValidArray_1157) {

    std::array<double, 6> expected = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    const auto& matrix = font->getFontMatrix();



    EXPECT_EQ(matrix.size(), expected.size());

    for (size_t i = 0; i < matrix.size(); ++i) {

        EXPECT_DOUBLE_EQ(matrix[i], expected[i]);

    }

}



TEST_F(GfxFontTest_1157, GetAscent_ReturnsDefaultValue_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_DOUBLE_EQ(font->getAscent(), 0.0);

}



TEST_F(GfxFontTest_1157, GetDescent_ReturnsDefaultValue_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_DOUBLE_EQ(font->getDescent(), 0.0);

}



TEST_F(GfxFontTest_1157, GetWMode_ReturnsDefaultValue_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_EQ(font->getWMode(), WritingMode::Horizontal);

}



TEST_F(GfxFontTest_1157, HasToUnicodeCMap_ReturnsFalseByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_FALSE(font->hasToUnicodeCMap());

}



TEST_F(GfxFontTest_1157, GetEncodingName_ReturnsEmptyStringByDefault_1157) {

    auto fontDictMock = std::make_unique<Dict>();

    MockXRef xrefMock;



    EXPECT_CALL(xrefMock, makeFont(_, _, _))

        .WillOnce([](const char*, Ref, Dict*) {

            return std::unique_ptr<GfxFont>(new GfxFont("tag", Ref(), "name", GfxFontType::Unknown, Ref()));

        });



    auto font = xrefMock.makeFont("tag", Ref(), fontDictMock.get());

    EXPECT_EQ(font->getEncodingName(), "");

}



TEST_F(GfxFontTest_1157, IsBase14Font_String_ReturnsFalseForNonBase14_1157) {

    EXPECT_FALSE(GfxFont::isBase14Font("SomeRandomFont", "Normal"));

}



TEST_F(GfxFontTest_1157, IsBase14Font_String_ReturnsTrueForBase14_1157) {

    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Bold"));

}



TEST_F(GfxFontTest_1157, IsBase14Font_Int_ReturnsFalseForNonBase14_1157) {

    EXPECT_FALSE(GfxFont::isBase14Font(9999, 0));

}



// Assuming some mapping from family and style to known Base14 fonts

TEST_F(GfxFontTest_1157, IsBase14Font_Int_ReturnsTrueForBase14_1157) {

    EXPECT_TRUE(GfxFont::isBase14Font(3, 0)); // Example values mapping to a Base14 font

}
