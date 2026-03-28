// optcontentmodel_unittest_2769.cpp
#include <gtest/gtest.h>

#include <QAbstractItemModel>
#include <QBuffer>
#include <QByteArray>
#include <QCoreApplication>
#include <QFile>
#include <QModelIndex>
#include <QTemporaryDir>
#include <QVariant>

#include <poppler-qt5.h>
#include <poppler-optcontent.h>

namespace {

class QtAppGuard_2769 {
public:
    QtAppGuard_2769()
    {
        if (QCoreApplication::instance())
            return;
        int argc = 0;
        app_ = new QCoreApplication(argc, nullptr);
    }
    ~QtAppGuard_2769()
    {
        // If we created it, we own it.
        delete app_;
    }

private:
    QCoreApplication *app_ = nullptr;
};

// Minimal PDF builder that produces a valid PDF with:
// - 1 page
// - Optional content groups (OCGs) with names
// - Optional /Order and /RBGroups entries in /OCProperties
//
// NOTE: This is *test data*, not Poppler logic.
QByteArray BuildPdfWithOCGs_2769(bool includeOrder, bool includeRBGroups)
{
    struct Obj_2769 {
        int num;
        QByteArray body; // content BETWEEN "n 0 obj\n" and "endobj\n"
    };

    QList<Obj_2769> objs;

    // OCG objects (4 and 5)
    objs.push_back({4, "<< /Type /OCG /Name (Layer 1) >>\n"});
    objs.push_back({5, "<< /Type /OCG /Name (Layer 2) >>\n"});

    // Contents stream (marked content is not required for the model, but harmless)
    const QByteArray contents =
        "q\n"
        "/OC /OCG1 BDC\n"
        "0 0 0 rg\n"
        "0 0 m 10 10 l S\n"
        "EMC\n"
        "Q\n";
    objs.push_back({6, QByteArray("<< /Length ") + QByteArray::number(contents.size()) + " >>\nstream\n" + contents +
                           "endstream\n"});

    // Page object (3)
    objs.push_back({3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 6 0 R >>\n"});

    // Pages tree (2)
    objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});

    // Build /OCProperties in catalog (1)
    QByteArray ocprops = "<< /OCGs [4 0 R 5 0 R] /D << ";

    // /Order: if present, getOrderArray() should be non-null and the private code path changes.
    if (includeOrder) {
        ocprops += "/Order [4 0 R 5 0 R] ";
    }

    // /RBGroups: radio-button groups. We also provide /ON and /OFF to stabilize initial states.
    if (includeRBGroups) {
        ocprops += "/RBGroups [ [4 0 R 5 0 R] ] ";
        ocprops += "/ON [4 0 R] /OFF [5 0 R] ";
    }

    ocprops += ">> >>";

    objs.push_back({1, QByteArray("<< /Type /Catalog /Pages 2 0 R /OCProperties ") + ocprops + " >>\n"});

    // Write PDF with xref
    QByteArray pdf;
    pdf += "%PDF-1.7\n";
    pdf += "%\xB5\xED\xAE\xFB\n";

    // Ensure objects are in ascending order for predictable xref.
    std::sort(objs.begin(), objs.end(), [](const Obj_2769 &a, const Obj_2769 &b) { return a.num < b.num; });

    // Offsets: index by object number (0..max)
    int maxObj = 0;
    for (const auto &o : objs)
        maxObj = std::max(maxObj, o.num);

    QVector<int> offsets(maxObj + 1, -1);

    // Object 0 is the free entry
    offsets[0] = 0;

    for (const auto &o : objs) {
        offsets[o.num] = pdf.size();
        pdf += QByteArray::number(o.num) + " 0 obj\n";
        pdf += o.body;
        pdf += "endobj\n";
    }

    const int xrefPos = pdf.size();
    pdf += "xref\n";
    pdf += "0 " + QByteArray::number(maxObj + 1) + "\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= maxObj; ++i) {
        // All objects we reference exist in this builder; still guard formatting.
        const int off = offsets[i] >= 0 ? offsets[i] : 0;
        QByteArray line = QByteArray("%1 00000 n \n").arg(off, 10, 10, QLatin1Char('0')).toLatin1();
        pdf += line;
    }

    pdf += "trailer\n";
    pdf += "<< /Size " + QByteArray::number(maxObj + 1) + " /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += QByteArray::number(xrefPos) + "\n";
    pdf += "%%EOF\n";
    return pdf;
}

Poppler::Document *LoadDocFromData_2769(const QByteArray &data)
{
    // Use loadFromData to avoid filesystem dependence.
    Poppler::Document *doc = Poppler::Document::loadFromData(data);
    return doc;
}

QModelIndex FindRowByDisplay_2769(QAbstractItemModel *model, const QString &text)
{
    if (!model)
        return QModelIndex();

    const int rows = model->rowCount(QModelIndex());
    for (int r = 0; r < rows; ++r) {
        QModelIndex idx = model->index(r, 0, QModelIndex());
        if (!idx.isValid())
            continue;
        if (model->data(idx, Qt::DisplayRole).toString() == text)
            return idx;
    }
    return QModelIndex();
}

} // namespace

class OptContentModelTest_2769 : public ::testing::Test {
protected:
    void SetUp() override { static QtAppGuard_2769 appGuard; }
};

TEST_F(OptContentModelTest_2769, OptionalContentModelNullOrEmptyWhenNoOCProperties_2769)
{
    // A minimal PDF without /OCProperties: optionalContentModel() may return nullptr or an empty model.
    const QByteArray pdf =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 10 10] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "180\n"
        "%%EOF\n";

    std::unique_ptr<Poppler::Document> doc(LoadDocFromData_2769(pdf));
    ASSERT_NE(doc, nullptr);

    Poppler::OptContentModel *model = doc->optionalContentModel();
    if (!model) {
        SUCCEED();
        return;
    }
    EXPECT_EQ(model->rowCount(QModelIndex()), 0);
}

TEST_F(OptContentModelTest_2769, BuildsFlatModelWhenOrderArrayAbsent_2769)
{
    std::unique_ptr<Poppler::Document> doc(LoadDocFromData_2769(BuildPdfWithOCGs_2769(/*includeOrder=*/false,
                                                                                    /*includeRBGroups=*/false)));
    ASSERT_NE(doc, nullptr);

    Poppler::OptContentModel *model = doc->optionalContentModel();
    ASSERT_NE(model, nullptr);

    // If /Order is absent, the private code path inserts all OCG nodes under the root.
    EXPECT_EQ(model->rowCount(QModelIndex()), 2);

    // Names should be exposed via DisplayRole.
    QModelIndex layer1 = FindRowByDisplay_2769(model, QStringLiteral("Layer 1"));
    QModelIndex layer2 = FindRowByDisplay_2769(model, QStringLiteral("Layer 2"));
    EXPECT_TRUE(layer1.isValid());
    EXPECT_TRUE(layer2.isValid());

    // Boundary: invalid index should behave safely.
    QModelIndex invalid;
    EXPECT_FALSE(model->setData(invalid, Qt::Checked, Qt::CheckStateRole));
    EXPECT_EQ(model->data(invalid, Qt::DisplayRole), QVariant());
}

TEST_F(OptContentModelTest_2769, BuildsModelWhenOrderArrayPresent_2769)
{
    std::unique_ptr<Poppler::Document> doc(
        LoadDocFromData_2769(BuildPdfWithOCGs_2769(/*includeOrder=*/true, /*includeRBGroups=*/false)));
    ASSERT_NE(doc, nullptr);

    Poppler::OptContentModel *model = doc->optionalContentModel();
    ASSERT_NE(model, nullptr);

    // With /Order present, the private constructor takes the parseOrderArray() path.
    // Observable: we still must be able to see the two layers in the model.
    EXPECT_EQ(model->rowCount(QModelIndex()), 2);

    QModelIndex layer1 = FindRowByDisplay_2769(model, QStringLiteral("Layer 1"));
    QModelIndex layer2 = FindRowByDisplay_2769(model, QStringLiteral("Layer 2"));
    EXPECT_TRUE(layer1.isValid());
    EXPECT_TRUE(layer2.isValid());
}

TEST_F(OptContentModelTest_2769, RBGroupsEnforcesSingleCheckedAfterToggle_2769)
{
    std::unique_ptr<Poppler::Document> doc(
        LoadDocFromData_2769(BuildPdfWithOCGs_2769(/*includeOrder=*/false, /*includeRBGroups=*/true)));
    ASSERT_NE(doc, nullptr);

    Poppler::OptContentModel *model = doc->optionalContentModel();
    ASSERT_NE(model, nullptr);
    ASSERT_EQ(model->rowCount(QModelIndex()), 2);

    QModelIndex layer1 = FindRowByDisplay_2769(model, QStringLiteral("Layer 1"));
    QModelIndex layer2 = FindRowByDisplay_2769(model, QStringLiteral("Layer 2"));
    ASSERT_TRUE(layer1.isValid());
    ASSERT_TRUE(layer2.isValid());

    // Initial state is stabilized by /ON and /OFF in our PDF builder.
    const QVariant s1 = model->data(layer1, Qt::CheckStateRole);
    const QVariant s2 = model->data(layer2, Qt::CheckStateRole);
    ASSERT_TRUE(s1.isValid());
    ASSERT_TRUE(s2.isValid());

    // Toggle Layer 2 to checked.
    EXPECT_TRUE(model->setData(layer2, Qt::Checked, Qt::CheckStateRole));

    const QVariant after1 = model->data(layer1, Qt::CheckStateRole);
    const QVariant after2 = model->data(layer2, Qt::CheckStateRole);
    ASSERT_TRUE(after1.isValid());
    ASSERT_TRUE(after2.isValid());

    // Radio-button behavior is observable through check states: at most one should be Checked.
    const int c1 = (after1.toInt() == Qt::Checked) ? 1 : 0;
    const int c2 = (after2.toInt() == Qt::Checked) ? 1 : 0;
    EXPECT_LE(c1 + c2, 1);
    EXPECT_EQ(after2.toInt(), static_cast<int>(Qt::Checked));
}

TEST_F(OptContentModelTest_2769, OutOfRangeIndexReturnsInvalidAndSafeFlags_2769)
{
    std::unique_ptr<Poppler::Document> doc(
        LoadDocFromData_2769(BuildPdfWithOCGs_2769(/*includeOrder=*/false, /*includeRBGroups=*/false)));
    ASSERT_NE(doc, nullptr);

    Poppler::OptContentModel *model = doc->optionalContentModel();
    ASSERT_NE(model, nullptr);

    // Boundary: row out of range -> invalid index.
    QModelIndex idx = model->index(/*row=*/999, /*column=*/0, QModelIndex());
    EXPECT_FALSE(idx.isValid());

    // Boundary: column out of range -> invalid index (or at least non-editable).
    QModelIndex colIdx = model->index(/*row=*/0, /*column=*/999, QModelIndex());
    if (colIdx.isValid()) {
        const Qt::ItemFlags f = model->flags(colIdx);
        // Should not crash; and typically shouldn't be user-checkable/editable in weird columns.
        EXPECT_FALSE(f.testFlag(Qt::ItemIsUserCheckable) && f.testFlag(Qt::ItemIsEditable));
    }
}