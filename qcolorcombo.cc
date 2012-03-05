#include <QMessageBox>
#include <QDebug>
#include <QHBoxLayout>

#include "QColorCombo"


QColorCombo::QColorCombo(QWidget* parent) :
  QFrame(parent), m_combo(NULL) {
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

  hbox->addWidget(m_combo);

  setLayout(hbox);
}

