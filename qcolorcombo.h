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
    Q_PROPERTY(bool showColorNames READ showColorNames WRITE setShowColorNames)
    Q_PROPERTY(bool allowCustomColors READ allowCustomColors WRITE setAllowCustomColors)

public:
    QColorCombo(QWidget* parent=0);

    QColor selectedColor() const { return m_color; }
    QList<QColor> colors() const { return m_colors; }
    bool showColorNames() const { return m_showColorNames; }
    bool allowCustomColors() const { return m_allowCustomColors; }

protected:
    QComboBox* m_combo;
    QColor m_color;
    QList<QColor> m_colors;
    bool m_showColorNames;
    bool m_allowCustomColors;

    static QIcon createIcon(QString color);

public slots:
    void setColors(QList<QColor> colors);
    void setSelectedColor(QColor color);
    void setShowColorNames(bool show);
    void setAllowCustomColors(bool allow);

protected slots:
    void combo_currentIndexChanged(int index);

signals:
    void colorChanged(QString colorName);
    void colorChanged(QColor color);

};

#endif // !QCOLORCOMBO_H

