#ifndef QCOLORCOMBODESIGNERFACTORY_H
#define QCOLORCOMBODESIGNERFACTORY_H

#include <QObject>
#include <QtDeclarative/QDeclarativeItem>
#include <QtDesigner/QDesignerCustomWidgetInterface>

class QColorComboDesignerFactory : public QObject,
                                   public QDesignerCustomWidgetInterface {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
#if (QT_VERSION >= 0x050000)
    Q_PLUGIN_METADATA(IID "de.das-system-networks.QColorCombo.DesignerPlugin")
#endif
public:
    explicit QColorComboDesignerFactory(QDeclarativeItem* parent = 0);

    virtual QWidget* createWidget(QWidget* parent);
    virtual QString group() const;
    virtual QIcon icon() const;
    virtual QString includeFile() const;
    virtual bool isContainer() const;
    virtual QString name() const;
    virtual QString toolTip() const;
    virtual QString whatsThis() const;

signals:

public slots:
};

#endif // QCOLORCOMBODESIGNERFACTORY_H
