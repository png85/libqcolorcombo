#include <QMessageBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QColorDialog>

#include "QColorCombo"


QColorCombo::QColorCombo(QWidget* parent) :
  QFrame(parent), m_combo(NULL),
  m_colorName("#000000"), m_color("#00000") {

  QHBoxLayout* hbox = NULL;
  try {
    hbox = new QHBoxLayout(this);
  }

  catch (std::bad_alloc& ex) {
    qCritical() << "QColorCombo::QColorCombo: "
		<< "Caught std::bad_alloc when trying to create "
		<< "new QHBoxLayout: " << ex.what();
    QMessageBox::critical(this, tr("Fatal error!"),
			  tr("Unable to allocate memory for new QHBoxLayout!"),
			  QMessageBox::Ok, QMessageBox::Ok);
    exit(1);
  }

  try {
    m_combo = new QComboBox(this);

    m_combo->setEditable(false);
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

  m_combo->addItem(tr("Custom color..."));

  // add default colors to the combo box
  QStringList colorList;
  colorList << "#000000" << "#FFFFFF" << "#808080" << "#800000"
	    << "#804040" << "#FF8080" << "#FF0000" << "#FFFF80"
	    << "#FFFF00" << "#FF8040" << "#FF8000" << "#80FF80"
	    << "#80FF00" << "#00FF00" << "#80FFFF" << "#00FFFF"
	    << "#004080" << "#0000FF" << "#0080FF" << "#0080C0";
  for (QStringList::iterator i=colorList.begin(); i!=colorList.end(); ++i) {
    QString colorName = (*i);
    m_combo->addItem(createIcon(colorName), colorName, QColor(colorName));
  }

  m_combo->setCurrentIndex(1);
  QObject::connect(m_combo, SIGNAL(currentIndexChanged(int)),
		   this, SLOT(combo_currentIndexChanged(int)));

  hbox->addWidget(m_combo);

  setLayout(hbox);
}


/// \brief Create icon for a given color
///
/// Creates a 32x32 pixel icon for the given color name.
///
/// \param color Color name in the form of '#RRGGBB'
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
  if (index == 0) {
    // custom color option
    m_color = QColorDialog::getColor(m_color, this);
    m_colorName = m_color.name();
    addColor(m_color);
  } else {
    m_colorName = m_combo->itemText(index);
    m_color = m_combo->itemData(index).value<QColor>();
  }

  emit colorChanged(m_colorName);
  emit colorChanged(m_color);
}


/// \brief Add color to m_combo
void QColorCombo::addColor(QColor color) {
  int index = m_combo->findData(color);

  if (index == -1) {
    // color doesn't exist in our dropdown list; create new entry
    QString colorName = color.name().toUpper();
    m_combo->insertItem(1, createIcon(colorName), colorName, color);
    m_combo->setCurrentIndex(1);
  } else {
    // color already exists in our dropdown list
    m_combo->setCurrentIndex(index);
  }
}


/// \brief Add color to m_combo
void QColorCombo::addColor(QString colorName) {
  colorName = colorName.toUpper();

  int index = m_combo->findText(colorName);

  if (index == -1) {
    // color doesn't exist in our dropdown list; create new entry
    m_combo->insertItem(1, createIcon(colorName), colorName, QColor(colorName));
    m_combo->setCurrentIndex(1);
  } else {
    // color already exists in our dropdown list
    m_combo->setCurrentIndex(index);
  }
}


/// \brief Get name of currently selected color
QString QColorCombo::getColorName() {
  return m_colorName;
}


/// \brief Set currently selected color
void QColorCombo::setColorName(QString colorName) {
  if (!colorName.isEmpty()) {
    if (QColor(colorName).isValid()) {
      m_colorName = colorName;
      m_color = QColor(colorName);
      addColor(colorName);
    }
  }
}


/// \brief Get currently selected color
QColor QColorCombo::getColor() {
  return m_color;
}


/// \brief Set currently selected color
void QColorCombo::setColor(QColor color) {
  if (color.isValid()) {
    m_colorName = color.name();
    m_color = color;
    addColor(color);
  }
}

