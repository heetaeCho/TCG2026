// File: test_richmediaannotation_2772.cc
//
// Unit tests for Poppler::RichMediaAnnotation (Qt5)
// Focus: constructor robustness with various QDomNode shapes + observable public API behavior
//
// Constraints respected:
// - Treat implementation as black box
// - No private/internal state access
// - Only observable behavior via public interface (store/subType/settings/content)
// - Boundary/error-like inputs via unusual DOM node structures

#include <gtest/gtest.h>

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <QtCore/QString>

// Poppler Qt5 public header (expected in Poppler Qt5 build)
#include "poppler-annotation.h"

namespace {

class RichMediaAnnotationTest_2772 : public ::testing::Test {
protected:
    static QDomElement MakeElement(QDomDocument &doc, const QString &tag)
    {
        return doc.createElement(tag);
    }

    static void AppendText(QDomDocument &doc, QDomNode &parent, const QString &text)
    {
        parent.appendChild(doc.createTextNode(text));
    }

    static void AppendElement(QDomNode &parent, const QDomElement &elem)
    {
        parent.appendChild(elem);
    }
};

TEST_F(RichMediaAnnotationTest_2772, ConstructWithElementNoChildren_DoesNotCrashAndCanStore_2772)
{
    QDomDocument inDoc(QStringLiteral("in"));
    QDomElement inRoot = inDoc.createElement(QStringLiteral("annot"));
    inDoc.appendChild(inRoot);

    Poppler::RichMediaAnnotation ann(inRoot);

    QDomDocument outDoc(QStringLiteral("out"));
    QDomElement outRoot = outDoc.createElement(QStringLiteral("annot"));
    outDoc.appendChild(outRoot);

    QDomNode outNode(outRoot);
    EXPECT_NO_THROW(ann.store(outNode, outDoc));

    // Observable: store should not leave document in a totally empty / invalid state.
    // We avoid asserting exact XML structure (black-box).
    EXPECT_TRUE(outDoc.documentElement().isElement());
}

TEST_F(RichMediaAnnotationTest_2772, ConstructSkipsNonRichMediaElements_DoesNotCrash_2772)
{
    QDomDocument doc(QStringLiteral("in"));
    QDomElement root = doc.createElement(QStringLiteral("annot"));
    doc.appendChild(root);

    // Child elements that are NOT "richMedia"
    AppendElement(root, MakeElement(doc, QStringLiteral("foo")));
    AppendElement(root, MakeElement(doc, QStringLiteral("bar")));
    AppendElement(root, MakeElement(doc, QStringLiteral("baz")));

    EXPECT_NO_THROW({
        Poppler::RichMediaAnnotation ann(root);

        QDomDocument outDoc(QStringLiteral("out"));
        QDomElement outRoot = outDoc.createElement(QStringLiteral("annot"));
        outDoc.appendChild(outRoot);
        QDomNode outNode(outRoot);
        ann.store(outNode, outDoc);
    });
}

TEST_F(RichMediaAnnotationTest_2772, ConstructWithRichMediaAmongSiblings_DoesNotCrash_2772)
{
    QDomDocument doc(QStringLiteral("in"));
    QDomElement root = doc.createElement(QStringLiteral("annot"));
    doc.appendChild(root);

    // Mix in text nodes and multiple element siblings.
    AppendText(doc, root, QStringLiteral("leading text"));

    AppendElement(root, MakeElement(doc, QStringLiteral("notRichMedia")));
    AppendElement(root, MakeElement(doc, QStringLiteral("richMedia"))); // target tag
    AppendElement(root, MakeElement(doc, QStringLiteral("afterRichMedia")));

    EXPECT_NO_THROW({
        Poppler::RichMediaAnnotation ann(root);

        // Exercise additional observable API without asserting internals.
        (void)ann.subType();

        QDomDocument outDoc(QStringLiteral("out"));
        QDomElement outRoot = outDoc.createElement(QStringLiteral("annot"));
        outDoc.appendChild(outRoot);
        QDomNode outNode(outRoot);
        ann.store(outNode, outDoc);
    });
}

TEST_F(RichMediaAnnotationTest_2772, ConstructWithTextNodeAsInput_DoesNotCrash_2772)
{
    QDomDocument doc(QStringLiteral("in"));
    QDomText textNode = doc.createTextNode(QStringLiteral("just text"));

    // Passing a non-element QDomNode exercises an error-ish input shape.
    EXPECT_NO_THROW({
        Poppler::RichMediaAnnotation ann(textNode);

        QDomDocument outDoc(QStringLiteral("out"));
        QDomElement outRoot = outDoc.createElement(QStringLiteral("annot"));
        outDoc.appendChild(outRoot);
        QDomNode outNode(outRoot);
        ann.store(outNode, outDoc);
    });
}

TEST_F(RichMediaAnnotationTest_2772, SetSettingsNullptr_RoundTripsAsNull_2772)
{
    QDomDocument doc(QStringLiteral("in"));
    QDomElement root = doc.createElement(QStringLiteral("annot"));
    doc.appendChild(root);

    Poppler::RichMediaAnnotation ann(root);

    ann.setSettings(nullptr);
    EXPECT_EQ(ann.settings(), nullptr);
}

TEST_F(RichMediaAnnotationTest_2772, SetContentNullptr_RoundTripsAsNull_2772)
{
    QDomDocument doc(QStringLiteral("in"));
    QDomElement root = doc.createElement(QStringLiteral("annot"));
    doc.appendChild(root);

    Poppler::RichMediaAnnotation ann(root);

    ann.setContent(nullptr);
    EXPECT_EQ(ann.content(), nullptr);
}

TEST_F(RichMediaAnnotationTest_2772, StoreWithFreshDocumentNode_DoesNotInvalidateRoot_2772)
{
    QDomDocument inDoc(QStringLiteral("in"));
    QDomElement inRoot = inDoc.createElement(QStringLiteral("annot"));
    inDoc.appendChild(inRoot);

    // Include a "richMedia" child to cover that parsing path (still black-box).
    AppendElement(inRoot, MakeElement(inDoc, QStringLiteral("richMedia")));

    Poppler::RichMediaAnnotation ann(inRoot);

    QDomDocument outDoc(QStringLiteral("out"));
    QDomElement outRoot = outDoc.createElement(QStringLiteral("annot"));
    outDoc.appendChild(outRoot);

    QDomNode outNode(outRoot);
    EXPECT_NO_THROW(ann.store(outNode, outDoc));

    // Observable sanity checks: document root remains the same element and is still attached.
    EXPECT_TRUE(outDoc.documentElement().isElement());
    EXPECT_EQ(outDoc.documentElement().tagName(), QStringLiteral("annot"));
}

} // namespace