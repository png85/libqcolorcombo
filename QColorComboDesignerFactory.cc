#include <QDebug>
#include <QMessageBox>
#include <QtPlugin>

#include "nullptr.h"
#include "QColorCombo.h"
#include "QColorComboDesignerFactory.h"

QColorComboDesignerFactory::QColorComboDesignerFactory(QDeclarativeItem* parent)
    : QObject(parent)
{
    // ... nothing ...
}

QWidget* QColorComboDesignerFactory::createWidget(QWidget* parent)
{
    QColorCombo* widget = nullptr;
    try {
        widget = new QColorCombo(parent);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocat new QColorCombo in" << Q_FUNC_INFO << ":" << ex.what();
        QString message = tr("Caught exception when trying to create new QColorCombo"
                             "instance in %1: %2").arg(Q_FUNC_INFO, ex.what());
        QMessageBox::critical(parent, tr("Out of memory"), message, QMessageBox::Ok);
        throw;
    }

    return reinterpret_cast<QWidget*>(widget);
}

QString QColorComboDesignerFactory::group() const
{
    return "#das-system";
}

QIcon QColorComboDesignerFactory::icon() const
{
    return QIcon::fromTheme("video-display");
}

QString QColorComboDesignerFactory::includeFile() const
{
    return "QColorCombo.h";
}

QString QColorComboDesignerFactory::toolTip() const
{
    return tr("Color combo box");
}

QString QColorComboDesignerFactory::whatsThis() const
{
    return tr("QComboBox that can be used to select QColor values");
}

bool QColorComboDesignerFactory::isContainer() const
{
    return false;
}

QString QColorComboDesignerFactory::name() const
{
    return "QColorCombo";
}

Q_EXPORT_PLUGIN2(QColorComboDesignerPlugin, QColorComboDesignerFactory)
