#ifndef PROGSETTINGS_H
#define PROGSETTINGS_H

#include <string>
#include <QSettings>




struct ProgSettings {

    ProgSettings()
        : clDataFileName(L"")
        , interFileName(L"")
        , dempFileName(L"")
        , df1(0), df2(0)
    {}

    std::wstring clDataFileName
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
        settings.setValue("clDataFileName", QString::fromStdWString( clDataFileName ));
        settings.setValue("interFileName", QString::fromStdWString( interFileName ));
        settings.setValue("dempFileName",  QString::fromStdWString( dempFileName ));

        settings.setValue("df1", df1);
        settings.setValue("df2", df2);
    }

    inline void readSettings(QSettings &settings) {
        return;
        clDataFileName = settings.value("clDataFileName").toString().toStdWString();
        interFileName = settings.value("interFileName").toString().toStdWString();
        dempFileName = settings.value("dempFileName").toString().toStdWString();

        df1 = settings.value("df1").toDouble();
        df2 = settings.value("df2").toDouble();
    }

};



#endif // PROGSETTINGS_H
