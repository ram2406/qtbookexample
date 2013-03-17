#ifndef ICONEDITORPLUGINPLUGIN_H
#define ICONEDITORPLUGINPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class IconEditorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
    IconEditorPlugin(QObject *parent = 0);
    
    bool isContainer() const;

    QIcon icon() const;

    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);

    
private:

};

#endif
