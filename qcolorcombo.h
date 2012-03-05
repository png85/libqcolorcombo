#ifndef QCOLORCOMBO_H
#define QCOLORCOMBO_H 1

#include <QWidget>
#include <QFrame>
#include <QComboBox>

class QColorCombo : public QFrame {
  Q_OBJECT
 public:
  QColorCombo(QWidget* parent=0);

 protected:
  QComboBox* m_combo;

};

#endif // !QCOLORCOMBO_H

