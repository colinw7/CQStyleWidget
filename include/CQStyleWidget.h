#ifndef CQStyleWidget_H
#define CQStyleWidget_H

#include <QLabel>

#include <set>
#include <map>

#define CQStyleWidgetMgrInst CQStyleWidgetMgr::instance()

class CQStyleWidgetIFace {
 public:
  CQStyleWidgetIFace() { }

  virtual ~CQStyleWidgetIFace() { }

  virtual void setForeground(QWidget *w, const QColor &fg);
  virtual void setBackground(QWidget *w, const QColor &bg, bool bgSet);
  virtual void setFont      (QWidget *w, const QFont &font);
  virtual void setSpace     (QWidget *w, int space);
};

//------

class CQStyleWidgetMgr : public QObject {
  Q_OBJECT

 public:
  static CQStyleWidgetMgr *instance();

  void getStyleNames(std::vector<QString> &styleNames) const;

  QLabel *addHeader1(QLayout *l, const QString &text);
  QLabel *addHeader2(QLayout *l, const QString &text);
  QLabel *addHeader3(QLayout *l, const QString &text);
  QLabel *addHeader4(QLayout *l, const QString &text);

  QLabel *addParagraph(QLayout *l, const QString &text);

  template<typename T>
  T *add(T *w, const QString &style) {
    return static_cast<T *>(addWidget(w, style));
  }

  void update(QWidget *w, const QString &style);

  void remove(QWidget *w);

  QString getDescription(const QString &style) const;
  void setDescription(const QString &style, const QString &desc);

  QColor getForeground(const QString &style) const;
  void setForeground(const QString &style, const QColor &c);

  QColor getBackground(const QString &style) const;
  void setBackground(const QString &style, const QColor &c);

  bool getBackgroundSet(const QString &style) const;
  void setBackgroundSet(const QString &style, bool b);

  QFont getFont(const QString &style) const;
  void setFont(const QString &style, const QFont &font);

  int getSpace(const QString &style) const;
  void setSpace(const QString &style, int space);

 private:
  struct StyleData;

  QWidget *addWidget(QWidget *w, const QString &style);

  bool hasStyle(const QString &style) const;

  const StyleData &getStyle(const QString &style) const;
  StyleData &addStyle(const QString &style);

  void initStyle(const QString &style, const QString &desc, const QColor &fg,
                 const QFont &font, int space);

  void applyStyle(QWidget *w, const StyleData &styleData);

 signals:
  void styleAdded(const QString &style);
  void styleChanged(const QString &style);

 private slots:
  void removeSlot(QObject *o);

 private:
  CQStyleWidgetMgr();
 ~CQStyleWidgetMgr() { }

 private:
  typedef std::set<QWidget *> WidgetSet;

  struct StyleData {
    QString             desc;
    QColor              fg;
    QColor              bg;
    bool                bgSet;
    QFont               font;
    int                 space;
    CQStyleWidgetIFace *iface;
    WidgetSet           widgets;

    StyleData() :
     fg(0,0,0), bg(255,255,255), bgSet(false), font(), space(0), iface(), widgets() {
    }
  };

  typedef std::map<QWidget *,QString> WidgetStyleMap;
  typedef std::map<QString,StyleData> StyleDataMap;

  StyleDataMap   styleData_;
  WidgetStyleMap widgets_;
};

#endif
