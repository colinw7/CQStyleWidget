#include <CQStyleWidget.h>
#include <CQStyleDivider.h>
#include <QLayout>
#include <cassert>

namespace CQStyleWidgetUtil {

void setForeground(QWidget *w, const QColor &fg) {
  QPalette palette = w->palette();

  palette.setColor(QPalette::Text, fg);
  palette.setColor(w->foregroundRole(), fg);

  w->setPalette(palette);
}

void setBackground(QWidget *w, const QColor &bg, bool bgSet) {
  CQStyleDivider *divider = qobject_cast<CQStyleDivider *>(w);
  if (divider) return;

  if (bgSet) {
    QPalette palette = w->palette();

    palette.setColor(w->backgroundRole(), bg);

    w->setPalette(palette);
  }

  w->setAutoFillBackground(bgSet);
}

void setFont(QWidget *w, const QFont &font) {
  w->setFont(font);
}

void setSpace(QWidget *w, int space) {
  CQStyleDivider *divider = qobject_cast<CQStyleDivider *>(w);

  if (divider)
    divider->setHeight(space);
}

}

//------

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
  QString fontName("Sans Serif");

  // define standard styles
  initStyle("h1", "Header 1" , QColor("#E51C23"), QFont(fontName, 16), 8);
  initStyle("h2", "Header 2" , QColor("#9C27B0"), QFont(fontName, 15), 4);
  initStyle("h3", "Header 3" , QColor("#673AB7"), QFont(fontName, 14), 2);
  initStyle("h4", "Header 4" , QColor("#009688"), QFont(fontName, 13), 0);
  initStyle("p" , "Paragraph", QColor("#000000"), QFont(fontName, 10), 0);
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
initStyle(const QString &style, const QString &desc, const QColor &fg,
          const QFont &font, int space)
{
  StyleData &styleData = addStyle(style);

  styleData.desc  = desc;
  styleData.fg    = fg;
  styleData.bg    = QColor(255,255,255);
  styleData.bgSet = false;
  styleData.font  = font;
  styleData.space = space;
  styleData.iface = 0;

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

QLabel *
CQStyleWidgetMgr::
addHeader1(QLayout *l, const QString &text)
{
  QLabel *label = add(new QLabel(text), "h1");

  l->addWidget(label);
  l->addWidget(add(new CQStyleDivider("h1", 8), "h1"));

  return label;
}

QLabel *
CQStyleWidgetMgr::
addHeader2(QLayout *l, const QString &text)
{
  QLabel *label = add(new QLabel(text), "h2");

  l->addWidget(label);
  l->addWidget(add(new CQStyleDivider("h2", 4), "h2"));

  return label;
}

QLabel *
CQStyleWidgetMgr::
addHeader3(QLayout *l, const QString &text)
{
  QLabel *label = add(new QLabel(text), "h3");

  l->addWidget(label);
  l->addWidget(add(new CQStyleDivider("h3", 2), "h3"));

  return label;
}

QLabel *
CQStyleWidgetMgr::
addHeader4(QLayout *l, const QString &text)
{
  QLabel *label = add(new QLabel(text), "h4");

  l->addWidget(label);
  l->addWidget(add(new CQStyleDivider("h4", 1), "h4"));

  return label;
}

QLabel *
CQStyleWidgetMgr::
addParagraph(QLayout *l, const QString &text)
{
  QLabel *label = add(new QLabel(text), "p");

  l->addWidget(label);
  l->addWidget(add(new CQStyleDivider("p", 0), "p"));

  return label;
}

QWidget *
CQStyleWidgetMgr::
addWidget(QWidget *w, const QString &style)
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
  if (styleData.iface) {
    styleData.iface->setForeground(w, styleData.fg);
    styleData.iface->setBackground(w, styleData.bg, styleData.bgSet);
    styleData.iface->setFont      (w, styleData.font);
    styleData.iface->setSpace     (w, styleData.space);
  }
  else {
    CQStyleWidgetUtil::setForeground(w, styleData.fg);
    CQStyleWidgetUtil::setBackground(w, styleData.bg, styleData.bgSet);
    CQStyleWidgetUtil::setFont      (w, styleData.font);
    CQStyleWidgetUtil::setSpace     (w, styleData.space);
  }
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

  for (WidgetSet::iterator p = styleData.widgets.begin(); p != styleData.widgets.end(); ++p) {
    if (styleData.iface)
      styleData.iface->setForeground(*p, styleData.fg);
    else
      CQStyleWidgetUtil::setForeground(*p, styleData.fg);
  }

  emit styleChanged(style.toLower());
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

  for (WidgetSet::iterator p = styleData.widgets.begin(); p != styleData.widgets.end(); ++p) {
    if (styleData.iface)
      styleData.iface->setBackground(*p, styleData.bg, styleData.bgSet);
    else
      CQStyleWidgetUtil::setBackground(*p, styleData.bg, styleData.bgSet);
  }

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

  for (WidgetSet::iterator p = styleData.widgets.begin(); p != styleData.widgets.end(); ++p) {
    if (styleData.iface)
      styleData.iface->setBackground(*p, styleData.bg, styleData.bgSet);
    else
      CQStyleWidgetUtil::setBackground(*p, styleData.bg, styleData.bgSet);
  }

  emit styleChanged(style.toLower());
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

  for (WidgetSet::iterator p = styleData.widgets.begin(); p != styleData.widgets.end(); ++p) {
    if (styleData.iface)
      styleData.iface->setFont(*p, styleData.font);
    else
      CQStyleWidgetUtil::setFont(*p, styleData.font);
  }

  emit styleChanged(style.toLower());
}

int
CQStyleWidgetMgr::
getSpace(const QString &style) const
{
  if (! hasStyle(style))
    return 0;

  return getStyle(style).space;
}

void
CQStyleWidgetMgr::
setSpace(const QString &style, int space)
{
  StyleData &styleData = addStyle(style);

  styleData.space = space;

  for (WidgetSet::iterator p = styleData.widgets.begin(); p != styleData.widgets.end(); ++p) {
    if (styleData.iface)
      styleData.iface->setSpace(*p, styleData.space);
    else
      CQStyleWidgetUtil::setSpace(*p, styleData.space);
  }

  emit styleChanged(style.toLower());
}

//------

void
CQStyleWidgetIFace::
setForeground(QWidget *w, const QColor &fg)
{
  CQStyleWidgetUtil::setForeground(w, fg);
}

void
CQStyleWidgetIFace::
setBackground(QWidget *w, const QColor &bg, bool bgSet)
{
  CQStyleWidgetUtil::setBackground(w, bg, bgSet);
}

void
CQStyleWidgetIFace::
setFont(QWidget *w, const QFont &font)
{
  CQStyleWidgetUtil::setFont(w, font);
}

void
CQStyleWidgetIFace::
setSpace(QWidget *w, int space)
{
  CQStyleWidgetUtil::setSpace(w, space);
}
