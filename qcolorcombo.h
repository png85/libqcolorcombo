#ifndef QCOLORCOMBO_H
#define QCOLORCOMBO_H 1

#include <QWidget>
#include <QFrame>
#include <QComboBox>
#include <QColor>
#include <QIcon>

class QColorCombo : public QFrame {
    Q_OBJECT

    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
    Q_PROPERTY(QList<QColor> colors READ colors WRITE setColors)

public:
    QColorCombo(QWidget* parent=0);

    QList<QColor> colors() const { return m_colors; }
    QColor selectedColor();

protected:
    QComboBox* m_combo;
    QColor m_color;

    QList<QColor> m_colors;

    static QIcon createIcon(QString color);

public slots:
    void setColors(QList<QColor> colors);
    void setSelectedColor(QColor color);

protected slots:
    void combo_currentIndexChanged(int index);

signals:
    void colorChanged(QString colorName);
    void colorChanged(QColor color);

};

#endif // !QCOLORCOMBO_H

