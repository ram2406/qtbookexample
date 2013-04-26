#ifndef PROGSETTINGS_H
#define PROGSETTINGS_H

#include <string>
#include <QSettings>




struct ProgSettings {

    std::string clDataFileName
              , interFileName
              , dempFileName;

    double df1
         , df2;

    inline bool validate() {
        return df1
            && df2
            && !clDataFileName.empty()
            && !interFileName.empty()
            && !dempFileName.empty()
                ;
    }


    inline void writeSettings(QSettings &settings) {
        settings.setValue("clDataFileName", QString::fromStdString( clDataFileName ));
        settings.setValue("interFileName", QString::fromStdString( interFileName ));
        settings.setValue("dempFileName",  QString::fromStdString( dempFileName ));

        settings.setValue("df1", df1);
        settings.setValue("df2", df2);
    }

    inline void readSettings(QSettings &settings) {
        clDataFileName = settings.value("clDataFileName").toString().toStdString();
        interFileName = settings.value("interFileName").toString().toStdString();
        dempFileName = settings.value("dempFileName").toString().toStdString();

        df1 = settings.value("df1").toDouble();
        df2 = settings.value("df2").toDouble();
    }

};



#endif // PROGSETTINGS_H
