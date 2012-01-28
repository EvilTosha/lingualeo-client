#ifndef COMREADER_H
#define COMREADER_H

#include <QObject>

class COMReader : public QObject{
  Q_OBJECT
public:
  explicit COMReader(QObject *parent = 0);
  
signals:
  
public slots:
  
};

#endif // COMREADER_H
