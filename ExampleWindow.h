#ifndef EXAMPLEWINDOW_H
#define EXAMPLEWINDOW_H 1

#include <QLabel>
#include <QFrame>

class ExampleWindow : public QFrame {
  Q_OBJECT
 public:
  ExampleWindow(QWidget* parent=0);

 protected slots:
  void colorChanged(QString colorName);

 protected:
  QLabel* m_label;
};

#endif // !EXAMPLEWINDOW_H
