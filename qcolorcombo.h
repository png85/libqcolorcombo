#ifndef QCOLORCOMBO_H
#define QCOLORCOMBO_H 1

#include <QWidget>
#include <QFrame>
#include <QComboBox>
#include <QColor>
#include <QIcon>

class QColorCombo : public QFrame {
    Q_OBJECT

    Q_PROPERTY(QString colorName READ getColorName)
    Q_PROPERTY(QColor selectedColor READ getColor)

public:
    QColorCombo(QWidget* parent=0);

protected:
    QComboBox* m_combo;
    QString m_colorName;
    QColor m_color;
    bool m_showColorNames;

    static QIcon createIcon(QString color);
    void addColor(QColor color);
    void addColor(QString colorName);

public:
    QString getColorName();
    void setColorName(QString colorName);

    QColor getColor();
    void setColor(QColor color);

protected slots:
    void combo_currentIndexChanged(int index);

signals:
    void colorChanged(QString colorName);
    void colorChanged(QColor color);

};

#endif // !QCOLORCOMBO_H

