#ifndef CQStyleControl_H
#define CQStyleControl_H

#include <QFrame>
#include <QListWidget>

class CQStyleList;
class CQColorChooser;
class CQFontChooser;
class QCheckBox;
class QLineEdit;
class QLabel;

class CQStyleControl : public QFrame {
  Q_OBJECT

 public:
  CQStyleControl(QWidget *parent = 0);

 public slots:
  void setCurrentStyle(const QString &style);

 private slots:
  void fgColorChanged(const QColor &c);

  void bgCheckChanged();
  void bgColorChanged(const QColor &c);

  void fontChanged(const QFont &font);

  void spaceChanged();

 private:
  CQStyleList    *styleList_;
  CQColorChooser *fgChooser_;
  QCheckBox      *bgCheck_;
  CQColorChooser *bgChooser_;
  CQFontChooser  *fontChooser_;
  QLineEdit      *spaceEdit_;
  QLabel         *styleLabel_;
};

class CQStyleList : public QListWidget {
  Q_OBJECT

 public:
  CQStyleList(QWidget *parent = 0);

  QString currentStyle() const;

 private:
  void populateList();

 private slots:
  void listItemSlot();

 signals:
  void styleSelected(const QString &);
};

#endif
