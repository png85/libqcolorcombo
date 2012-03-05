#ifndef QCOLORCOMBO_H
#define QCOLORCOMBO_H 1

#include <QWidget>
#include <QFrame>
#include <QComboBox>
#include <QColor>
#include <QIcon>

class QColorCombo : public QFrame {
  Q_OBJECT
 public:
  QColorCombo(QWidget* parent=0);

 protected:
  QComboBox* m_combo;
  QString m_colorName;
  QColor m_color;

  QIcon createIcon(QString color);

 protected slots:
  void combo_currentIndexChanged(int index);

 signals:
  void colorChanged(QString colorName);
  void colorChanged(QColor color);

};

#endif // !QCOLORCOMBO_H

