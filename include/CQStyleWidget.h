#ifndef CQStyleWidget_H
#define CQStyleWidget_H

#include <QLabel>

#include <set>
#include <map>

#define CQStyleWidgetMgrInst CQStyleWidgetMgr::instance()

class CQStyleWidgetMgr : public QObject {
  Q_OBJECT

 public:
  static CQStyleWidgetMgr *instance();

  void getStyleNames(std::vector<QString> &styleNames) const;

  template<typename T>
  T *addT(T *w, const QString &style) {
    return static_cast<T *>(add(w, style));
  }

  QWidget *add(QWidget *w, const QString &style);

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

 private:
  struct StyleData;

  bool hasStyle(const QString &style) const;

  const StyleData &getStyle(const QString &style) const;
  StyleData &addStyle(const QString &style);

  void initStyle(const QString &style, const QString &desc, const QColor &fg, const QFont &font);

  void applyStyle(QWidget *w, const StyleData &styleData);

  void setForeground(QWidget *w, const QColor &fg);
  void setBackground(QWidget *w, const QColor &bg, bool bgSet);

  void setFont(QWidget *w, const QFont &font);

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
    QString   desc;
    QColor    fg;
    QColor    bg;
    bool      bgSet;
    QFont     font;
    WidgetSet widgets;

    StyleData() :
     fg(0,0,0), bg(255,255,255), bgSet(false), font(), widgets() {
    }
  };

  typedef std::map<QWidget *,QString> WidgetStyleMap;
  typedef std::map<QString,StyleData> StyleDataMap;

  StyleDataMap   styleData_;
  WidgetStyleMap widgets_;
};

#endif
