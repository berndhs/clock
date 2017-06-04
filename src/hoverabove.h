#ifndef HOVERABOVE_H
#define HOVERABOVE_H

#include <QHoverEvent>

class HoverAbove : public QObject
{
  Q_OBJECT
public:
  explicit HoverAbove(QObject *parent = 0);

signals:

public slots:
};

#endif // HOVERABOVE_H
