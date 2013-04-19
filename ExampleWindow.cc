#include <QMessageBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

#include "QColorCombo.h"
#include "ExampleWindow.h"

ExampleWindow::ExampleWindow(QWidget* parent) :
  QFrame(parent), m_label(NULL) {
  setWindowTitle("QColorCombo example");

  try {
    QHBoxLayout* hbox = new QHBoxLayout(this);

    m_label = new QLabel("#000000");
    hbox->addWidget(m_label);

    QColorCombo* colorCombo = new QColorCombo(this);
    QObject::connect(colorCombo, SIGNAL(colorChanged(QString)),
		     this, SLOT(colorChanged(QString)));

    hbox->addWidget(colorCombo);
  }

  catch (std::bad_alloc& ex) {
    QMessageBox::critical(this, tr("Fatal error"),
			  tr("Caught std::bad_alloc when trying "
			     "to create widgets!"),
			  QMessageBox::Ok, QMessageBox::Ok);
  exit(1);
  }
}

void ExampleWindow::colorChanged(QString colorName) {
  m_label->setText(colorName);
  m_label->setStyleSheet("QLabel { background-color: " + colorName + "; }");
}
