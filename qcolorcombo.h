#ifndef QCOLORCOMBO_H
#define QCOLORCOMBO_H 1

#include <QWidget>
#include <QFrame>
#include <QComboBox>
#include <QColor>
#include <QIcon>


/** \brief Color selection combo box
 *
 * This widget provides a \a QComboBox that can be filled with a list of \a QColor variants
 * and supports custom color selection.
 *
 * \author Peter 'png' Hille <peter@das-system-networks.de>
 *
 * \version 1.0 Initial implementation
 */
class QColorCombo : public QFrame {
    Q_OBJECT

    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor)
    Q_PROPERTY(QList<QColor> colors READ colors WRITE setColors)
    Q_PROPERTY(bool showColorNames READ showColorNames WRITE setShowColorNames)
    Q_PROPERTY(bool allowCustomColors READ allowCustomColors WRITE setAllowCustomColors)

public:
    QColorCombo(QWidget* parent=0);

    /** \brief Get currently selected color
     *
     * \see m_color
     * \see setSelectedColor
     */
    QColor selectedColor() const { return m_color; }

    /** \brief Get list of selectable colors
     *
     * \see m_colors
     * \see setColors
     */
    QList<QColor> colors() const { return m_colors; }

    /** \brief Check if color names are shown
     *
     * \see m_showColorNames
     * \see setShowColorNames
     */
    bool showColorNames() const { return m_showColorNames; }

    /** \brief Check if custom colors are allowed
     *
     * \see m_allowCustomColors
     * \see setAllowCustomColors
     */
    bool allowCustomColors() const { return m_allowCustomColors; }

private:
    /** \brief Combo box for color selection
     *
     * \internal This widget is used to display a list of selectable colors as well
     * as an entry to define a custom colors (if \a m_allowCustomColors is true).
     */
    QComboBox* m_combo;

    /** \brief Currently selected color
     *
     * \internal Holds the color that is currently selected in \a m_combo.
     */
    QColor m_color;

    /** \brief List of selectable colors
     *
     * Holds the list of available \a QColor variants that are selectable from \a m_combo.
     */
    QList<QColor> m_colors;

    /** \brief Show color names?
     *
     * If this property is set to true the combo box will show the color names in the form
     * of '#RRGGBB'.
     */
    bool m_showColorNames;

    /** \brief Allow custom colors?
     *
     * If this property is set to true the combo box will contain an entry to select an
     * user-defined custom color via a \a QColorDialog and add it to the list of selectable
     * colors.
     */
    bool m_allowCustomColors;

protected:
    static QIcon createIcon(QString color);

public slots:
    void setColors(QList<QColor> colors);
    void setSelectedColor(QColor color);
    void setShowColorNames(bool show);
    void setAllowCustomColors(bool allow);

protected slots:
    void combo_currentIndexChanged(int index);

signals:
    /** \brief User selected new color
     *
     * This signal is emitted whenever the user has selected a new color from the combo box.
     *
     * \param colorName Name of the color as returned by \a QColor::name();
     */
    void colorChanged(QString colorName);

    /** \brief User selected new color
     *
     * This signal is emitted whenever the user has selected a new color from the combo box.
     *
     * \param color \a QColor that was selected by the user
     */
    void colorChanged(QColor color);

};

#endif // !QCOLORCOMBO_H

