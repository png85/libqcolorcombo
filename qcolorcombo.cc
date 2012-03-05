#include <QMessageBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QColorDialog>

#include "QColorCombo"


QColorCombo::QColorCombo(QWidget* parent) :
  QFrame(parent), m_combo(NULL),
  m_colorName("#000000"), m_color("#00000") {
  setFrameShape(QFrame::StyledPanel);

  QHBoxLayout* hbox = NULL;
  try {
    hbox = new QHBoxLayout(this);
  }

  catch (std::bad_alloc& ex) {
    qCritical() << "QColorCombo::QColorCombo: "
		<< "Caught std::bad_alloc when trying to create "
		<< "new QHBoxLayout: " << ex.what();
    QMessageBox::critical(this, "Fatal error!",
			  "Unable to allocate memory for new QHBoxLayout!",
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
    QMessageBox::critical(this, "Fatal error!",
			  "Unable to allocate memory for new QComboBox!",
			  QMessageBox::Ok, QMessageBox::Ok);
    exit(1);
  }

  m_combo->addItem("Custom color...");

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


QIcon QColorCombo::createIcon(QString color) {
  QPixmap p(32, 32);

  p.fill(QColor(color));

  return QIcon(p);
}


void QColorCombo::combo_currentIndexChanged(int index) {
  if (index == 0) {
    // custom color option
    m_color = QColorDialog::getColor(m_color, this);
    m_colorName = m_color.name();
  } else {
    m_colorName = m_combo->itemText(index);
    m_color = m_combo->itemData(index).value<QColor>();
  }

  emit colorChanged(m_colorName);
  emit colorChanged(m_color);
}

