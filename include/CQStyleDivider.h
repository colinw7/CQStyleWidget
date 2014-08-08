#ifndef CQStyleDivider_H
#define CQStyleDivider_H

#include <QFrame>

class CQStyleDivider : public QFrame {
  Q_OBJECT

  Q_PROPERTY(int height READ height WRITE setHeight)

 public:
  enum Type {
    LineType,
    NoType
  };

 public:
  CQStyleDivider(QWidget *parent, const QString &style, const Type &type, int height=8);
  CQStyleDivider(QWidget *parent, const QString &style, int height=8);

  CQStyleDivider(const QString &style, const Type &type, int height=8);
  CQStyleDivider(const QString &style, int height=8);

  const Qt::Orientation &orient() const { return orient_; }
  void setOrientation(Qt::Orientation orient);

  const Type &type() const { return type_; }
  void setType(Type type);

  int height() const { return height_; }
  void setHeight(int height);

 private:
  void updateState();

  void paintEvent(QPaintEvent *);

 private:
  QString         style_;
  Qt::Orientation orient_;
  Type            type_;
  int             height_;
  int             lindent_, rindent_;
};

#endif
