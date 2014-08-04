#include <CQStyleWidget.h>
#include <cassert>

CQStyleWidgetMgr *
CQStyleWidgetMgr::
instance()
{
  static CQStyleWidgetMgr *instance;

  if (! instance)
    instance = new CQStyleWidgetMgr;

  return instance;
}

CQStyleWidgetMgr::
CQStyleWidgetMgr()
{
  // define standard styles
  initStyle("h1", "Header 1" , QColor("#E51C23"), QFont("Sans Serif", 16));
  initStyle("h2", "Header 2" , QColor("#9C27B0"), QFont("Sans Serif", 15));
  initStyle("h3", "Header 3" , QColor("#673AB7"), QFont("Sans Serif", 14));
  initStyle("h4", "Header 4" , QColor("#009688"), QFont("Sans Serif", 13));
  initStyle("p" , "Paragraph", QColor("#000000"), QFont("Sans Serif", 10));
}

bool
CQStyleWidgetMgr::
hasStyle(const QString &style) const
{
  QString lstyle = style.toLower();

  return (styleData_.find(lstyle) != styleData_.end());
}

const CQStyleWidgetMgr::StyleData &
CQStyleWidgetMgr::
getStyle(const QString &style) const
{
  QString lstyle = style.toLower();

  StyleDataMap::const_iterator p = styleData_.find(lstyle);

  if (p == styleData_.end())
    assert(false);

  return (*p).second;
}

CQStyleWidgetMgr::StyleData &
CQStyleWidgetMgr::
addStyle(const QString &style)
{
  QString lstyle = style.toLower();

  StyleDataMap::iterator p = styleData_.find(lstyle);

  if (p == styleData_.end()) {
    p = styleData_.insert(p, StyleDataMap::value_type(lstyle, StyleData()));

    emit styleAdded(lstyle);
  }

  return (*p).second;
}

// TODO: initStyle from existing style

void
CQStyleWidgetMgr::
initStyle(const QString &style, const QString &desc, const QColor &fg, const QFont &font)
{
  StyleData &styleData = addStyle(style);

  styleData.desc  = desc;
  styleData.fg    = fg;
  styleData.bg    = QColor(255,255,255);
  styleData.bgSet = false;
  styleData.font  = font;

  emit styleChanged(style.toLower());
}

void
CQStyleWidgetMgr::
getStyleNames(std::vector<QString> &styleNames) const
{
  // Names sorted by font size and name ?
  for (StyleDataMap::const_iterator p = styleData_.begin(); p != styleData_.end(); ++p)
    styleNames.push_back((*p).first);
}

QWidget *
CQStyleWidgetMgr::
add(QWidget *w, const QString &style)
{
  remove(w);

  StyleData &styleData = addStyle(style);

  styleData.widgets.insert(w);

  widgets_[w] = style;

  applyStyle(w, styleData);

  connect(w, SIGNAL(destroyed(QObject *)), this, SLOT(removeSlot(QObject *)));

  return w;
}

void
CQStyleWidgetMgr::
removeSlot(QObject *o)
{
  QWidget *w = qobject_cast<QWidget *>(o);

  remove(w);
}

void
CQStyleWidgetMgr::
remove(QWidget *w)
{
  WidgetStyleMap::iterator pw = widgets_.find(w);

  if (pw == widgets_.end())
    return;

  widgets_.erase(pw);

  const QString &style = (*pw).second;

  StyleData &styleData = addStyle(style);

  WidgetSet::iterator p = styleData.widgets.find(w);

  if (p != styleData.widgets.end())
    styleData.widgets.erase(p);
}

void
CQStyleWidgetMgr::
update(QWidget *w, const QString &style)
{
  WidgetStyleMap::iterator pw = widgets_.find(w);
  assert(pw != widgets_.end());

  QString oldStyle = (*pw).second;
  QString newStyle = style.toLower();

  (*pw).second = newStyle;

  StyleDataMap::iterator p = styleData_.find(oldStyle);

  if (p != styleData_.end()) {
    StyleData &styleData = (*p).second;

    WidgetSet::iterator p = styleData.widgets.find(w);
    assert(p != styleData.widgets.end());

    styleData.widgets.erase(p);
  }

  p = styleData_.find(newStyle);

  bool found = (p != styleData_.end());

  if (! found)
    p = styleData_.insert(p, StyleDataMap::value_type(newStyle, StyleData()));

  StyleData &styleData = (*p).second;

  styleData.widgets.insert(w);

  applyStyle(w, styleData);

  if (! found)
    emit styleAdded(newStyle);
}

void
CQStyleWidgetMgr::
applyStyle(QWidget *w, const StyleData &styleData)
{
  setForeground(w, styleData.fg);
  setBackground(w, styleData.bg, styleData.bgSet);
  setFont      (w, styleData.font);
}

QString
CQStyleWidgetMgr::
getDescription(const QString &style) const
{
  if (! hasStyle(style))
    return QString();

  return getStyle(style).desc;
}

void
CQStyleWidgetMgr::
setDescription(const QString &style, const QString &desc)
{
  StyleData &styleData = addStyle(style);

  styleData.desc = desc;
}

QColor
CQStyleWidgetMgr::
getForeground(const QString &style) const
{
  if (! hasStyle(style))
    return QColor(0,0,0);

  return getStyle(style).fg;
}

void
CQStyleWidgetMgr::
setForeground(const QString &style, const QColor &color)
{
  StyleData &styleData = addStyle(style);

  styleData.fg = color;

  for (WidgetSet::iterator p = styleData.widgets.begin(); p != styleData.widgets.end(); ++p)
    setForeground(*p, styleData.fg);

  emit styleChanged(style.toLower());
}

void
CQStyleWidgetMgr::
setForeground(QWidget *w, const QColor &color)
{
  QPalette palette = w->palette();

  //if (qobject_cast<QGroupBox *>(w)) { QGroupBox *group = qobject_cast<QGroupBox *>(w); }

  palette.setColor(QPalette::Text, color);
  palette.setColor(w->foregroundRole(), color);

  w->setPalette(palette);
}

QColor
CQStyleWidgetMgr::
getBackground(const QString &style) const
{
  if (! hasStyle(style))
    return QColor();

  return getStyle(style).bg;
}

void
CQStyleWidgetMgr::
setBackground(const QString &style, const QColor &color)
{
  StyleData &styleData = addStyle(style);

  styleData.bg    = color;
  styleData.bgSet = color.isValid();

  for (WidgetSet::iterator p = styleData.widgets.begin(); p != styleData.widgets.end(); ++p)
    setBackground(*p, styleData.bg, styleData.bgSet);

  emit styleChanged(style.toLower());
}

bool
CQStyleWidgetMgr::
getBackgroundSet(const QString &style) const
{
  if (! hasStyle(style))
    return false;

  return getStyle(style).bgSet;
}

void
CQStyleWidgetMgr::
setBackgroundSet(const QString &style, bool bgSet)
{
  StyleData &styleData = addStyle(style);

  styleData.bgSet = bgSet;

  for (WidgetSet::iterator p = styleData.widgets.begin(); p != styleData.widgets.end(); ++p)
    setBackground(*p, styleData.bg, styleData.bgSet);

  emit styleChanged(style.toLower());
}

void
CQStyleWidgetMgr::
setBackground(QWidget *w, const QColor &color, bool bgSet)
{
  if (bgSet) {
    QPalette palette = w->palette();

    palette.setColor(w->backgroundRole(), color);

    w->setPalette(palette);
  }

  w->setAutoFillBackground(bgSet);
}

QFont
CQStyleWidgetMgr::
getFont(const QString &style) const
{
  if (! hasStyle(style))
    return QFont();

  return getStyle(style).font;
}

void
CQStyleWidgetMgr::
setFont(const QString &style, const QFont &font)
{
  StyleData &styleData = addStyle(style);

  styleData.font = font;

  for (WidgetSet::iterator p = styleData.widgets.begin(); p != styleData.widgets.end(); ++p)
    setFont(*p, font);

  emit styleChanged(style.toLower());
}

void
CQStyleWidgetMgr::
setFont(QWidget *w, const QFont &font)
{
  w->setFont(font);
}
