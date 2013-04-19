#include <QMessageBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QColorDialog>

#include "QColorCombo"


QColorCombo::QColorCombo(QWidget* parent) :
    QFrame(parent), m_combo(NULL), m_color("#000000"), m_showColorNames(true), m_allowCustomColors(true)
 {

    QHBoxLayout* hbox = NULL;
    try {
        hbox = new QHBoxLayout(this);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to create new QHBoxLayout in" << Q_FUNC_INFO << ":" << ex.what();
        QString message = tr("Caught exception when trying to allocate new QHBoxLayout in %1: %2").arg(Q_FUNC_INFO, ex.what());
        QMessageBox::critical(this, tr("Out of memory"), message, QMessageBox::Ok);
        throw;
    }

    try {
        m_combo = new QComboBox(this);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "QColorCombo::QColorCombo: "
                    << "Caught std::bad_alloc when trying to create "
                    << "new QComboBox: " << ex.what();
        QMessageBox::critical(this, tr("Fatal error!"),
                              tr("Unable to allocate memory for new QComboBox!"),
                              QMessageBox::Ok, QMessageBox::Ok);
        exit(1);
    }

    m_combo->setEditable(false);

    // add default colors to the combo box
    QList<QColor> colorList;
    colorList << "#000000" << "#FFFFFF" << "#808080" << "#800000"
              << "#804040" << "#FF8080" << "#FF0000" << "#FFFF80"
              << "#FFFF00" << "#FF8040" << "#FF8000" << "#80FF80"
              << "#80FF00" << "#00FF00" << "#80FFFF" << "#00FFFF"
              << "#004080" << "#0000FF" << "#0080FF" << "#0080C0";
    setColors(colorList);

    QObject::connect(m_combo, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(combo_currentIndexChanged(int)));

    hbox->addWidget(m_combo);

    QFrame::setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    QFrame::setLineWidth(1);
    setLayout(hbox);
}


/// \brief Create icon for a given color
///
/// Creates a 32x32 pixel icon for the given color name.
///
/// \param color Color name in the form of \a #RRGGBB
QIcon QColorCombo::createIcon(QString color) {
    QPixmap p(32, 32);

    p.fill(QColor(color));

    return QIcon(p);
}


/// \brief Handler for combo box selection changes
///
/// This gets executed when the user selects a new color from our
/// combo box. If the user selects the option to use a custom color
/// we show them a QColorDialog and add the custom color to the top
/// of our color list afterwards.
///
/// \param index Index of the currently selected color in m_combo
void QColorCombo::combo_currentIndexChanged(int index) {
    QString itemData = m_combo->itemData(index).toString();

    if (itemData == "[CUSTOM]") {
        QColor customColor = QColorDialog::getColor(Qt::white, this);
        if (customColor.isValid()) {
            m_color = customColor;
            m_colors << customColor;
            setColors(m_colors);
            setSelectedColor(customColor);
        }
    } else {
        QColor selectedColor = QColor(itemData);
        if (selectedColor.isValid())
            m_color = selectedColor;
    }

    emit colorChanged(m_color);
    emit colorChanged(m_color.name());
}



void QColorCombo::setColors(QList<QColor> colors)  {
    m_combo->clear();

    m_colors = colors;
    foreach (QColor color, m_colors)
        m_combo->addItem(createIcon(color.name()),
                         m_showColorNames == true ? color.name().toUpper() : QString(),
                         color.name());

    if (m_allowCustomColors)
        m_combo->addItem(QIcon::fromTheme("go-jump"), tr("Custom..."), "[CUSTOM]");

    setSelectedColor(m_color);
}


void QColorCombo::setSelectedColor(QColor color) {
    if (!m_colors.contains(color)) {
        if (!m_allowCustomColors)
            return;

        m_colors << color;
        setColors(m_colors);
    }

    m_combo->setCurrentIndex(m_colors.indexOf(color));
}


void QColorCombo::setShowColorNames(bool show) {
    if (show != m_showColorNames) {
        m_showColorNames = show;
        setColors(m_colors);
    }
}


void QColorCombo::setAllowCustomColors(bool allow) {
    if (allow != m_allowCustomColors) {
        m_allowCustomColors = allow;
        setColors(m_colors);
    }
}
