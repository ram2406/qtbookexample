#include "iconeditorplugin.h"


#include <QtPlugin>
#include "../../../TestUi/UiTest/iconeditor.h"


IconEditorPlugin::IconEditorPlugin(QObject *parent)
    : QObject(parent)
{

}



QWidget *IconEditorPlugin::createWidget(QWidget *parent)
{
    //return new IconEditorPlugin(parent);
    return new IconEditor(parent);
}

QString IconEditorPlugin::name() const
{
    return QLatin1String("IconEditor");
}

QString IconEditorPlugin::group() const
{
    return QLatin1String("Image Manipulation Widget");
}

QIcon IconEditorPlugin::icon() const
{
    return QIcon(QLatin1String(":/Edit.png"));
}

QString IconEditorPlugin::toolTip() const
{
    return QLatin1String("An icon editor widget");
}

QString IconEditorPlugin::whatsThis() const
{
    return QLatin1String("This widget is presented in Chapter 5 of <i>C++ GUI"
                         "Programming with Qt 4</i> as an example of a custom Qt "
                         "widget.");
}

bool IconEditorPlugin::isContainer() const
{
    return false;
}

QString IconEditorPlugin::includeFile() const
{
    return QLatin1String("iconeditor.h");
}

Q_EXPORT_PLUGIN2(iconeditorplugin, IconEditorPlugin)
