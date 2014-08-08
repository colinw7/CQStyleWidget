#include <CQStyleControl.h>
#include <CQStyleWidget.h>
#include <CQColorChooser.h>
#include <CQFontChooser.h>

#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QListWidget>
#include <QItemDelegate>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>

CQStyleControl::
CQStyleControl(QWidget *parent) :
 QFrame(parent)
{
  QVBoxLayout *layout = new QVBoxLayout(this);

  QHBoxLayout *slayout = new QHBoxLayout;

  QGroupBox *styleFrame = new QGroupBox("Styles");

  QVBoxLayout *styleLayout = new QVBoxLayout(styleFrame);

  styleList_ = new CQStyleList;

  connect(styleList_, SIGNAL(styleSelected(const QString &)),
          this, SLOT(setCurrentStyle(const QString &)));

  styleLayout->addWidget(styleList_);

  QGridLayout *clayout = new QGridLayout;

  fgChooser_   = new CQColorChooser;
  bgCheck_     = new QCheckBox("Background");
  bgChooser_   = new CQColorChooser;
  fontChooser_ = new CQFontChooser;
  spaceEdit_   = new QLineEdit;

  fgChooser_->setStyles(CQColorChooser::Text | CQColorChooser::ColorButton);
  bgChooser_->setStyles(CQColorChooser::Text | CQColorChooser::ColorButton);

  fontChooser_->setStyle(CQFontChooser::FontDetailLabel);

  connect(fgChooser_, SIGNAL(colorChanged(const QColor &)),
          this, SLOT(fgColorChanged(const QColor &)));
  connect(bgCheck_, SIGNAL(stateChanged(int)),
          this, SLOT(bgCheckChanged()));
  connect(bgChooser_, SIGNAL(colorChanged(const QColor &)),
          this, SLOT(bgColorChanged(const QColor &)));
  connect(fontChooser_, SIGNAL(fontChanged(const QFont &)),
          this, SLOT(fontChanged(const QFont &)));
  connect(spaceEdit_, SIGNAL(returnPressed()),
          this, SLOT(spaceChanged()));

  clayout->addWidget(new QLabel("Foreground"), 0, 0); clayout->addWidget(fgChooser_, 0, 1);
  clayout->addWidget(bgCheck_                , 1, 0); clayout->addWidget(bgChooser_, 1, 1);

  clayout->addWidget(fontChooser_, 2, 0, 1, 2);

  clayout->addWidget(new QLabel("Space"), 3, 0); clayout->addWidget(spaceEdit_, 3, 1);

  clayout->setRowStretch(4, 1);

  slayout->addWidget(styleFrame);
  slayout->addLayout(clayout);
  slayout->addStretch(1);

  styleLabel_ = CQStyleWidgetMgrInst->add(new QLabel("Example Text"), "p");

  layout->addLayout(slayout);
  layout->addWidget(styleLabel_);
}

void
CQStyleControl::
fgColorChanged(const QColor &c)
{
  QString style = styleList_->currentStyle();

  CQStyleWidgetMgrInst->setForeground(style, c);
}

void
CQStyleControl::
bgCheckChanged()
{
  QString style = styleList_->currentStyle();

  CQStyleWidgetMgrInst->setBackgroundSet(style, bgCheck_->isChecked());
}

void
CQStyleControl::
bgColorChanged(const QColor &c)
{
  QString style = styleList_->currentStyle();

  CQStyleWidgetMgrInst->setBackground(style, c);
}

void
CQStyleControl::
fontChanged(const QFont &font)
{
  QString style = styleList_->currentStyle();

  CQStyleWidgetMgrInst->setFont(style, font);
}

void
CQStyleControl::
spaceChanged()
{
  QString style = styleList_->currentStyle();

  int space = spaceEdit_->text().toInt();

  CQStyleWidgetMgrInst->setSpace(style, space);
}

void
CQStyleControl::
setCurrentStyle(const QString &style)
{
  fgChooser_  ->setColor  (CQStyleWidgetMgrInst->getForeground   (style));
  bgCheck_    ->setChecked(CQStyleWidgetMgrInst->getBackgroundSet(style));
  bgChooser_  ->setColor  (CQStyleWidgetMgrInst->getBackground   (style));
  fontChooser_->setFont   (CQStyleWidgetMgrInst->getFont         (style));
  spaceEdit_  ->setText   (QString("%1").arg(CQStyleWidgetMgrInst->getSpace(style)));

  CQStyleWidgetMgrInst->update(styleLabel_, style);
}

//------

class CQStyleListItem : public QListWidgetItem {
 public:
  CQStyleListItem(CQStyleList *list, const QString &name, const QString &desc) :
   list_(list), name_(name), desc_(desc) {
  }

  const QString &name() const { return name_; }
  const QString &desc() const { return desc_; }

 private:
  CQStyleList *list_;
  QString      name_;
  QString      desc_;
};

class CQStyleListDelegate : public QItemDelegate {
 public:
  CQStyleListDelegate(CQStyleList *list) :
   list_(list) {
  }

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const {
    QItemDelegate::paint(painter, option, index);

    CQStyleListItem *item = static_cast<CQStyleListItem *>(list_->item(index.row()));

    //painter->fillRect(option.rect, QColor(255,255,255));

    painter->setPen(QColor(0,0,0));

    int border = 4;

    QRect r = option.rect.adjusted(border, 0, -border, 0);

    painter->drawText(r.left(), r.top(), r.width(), r.height(),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      item->name());

    painter->drawText(r.left(), r.top(), r.width(), r.height(),
                      Qt::AlignRight | Qt::AlignVCenter,
                      item->desc());

    //if (option.state & QStyle::State_Selected)
    //  painter->drawRect(option.rect.adjusted(0,0,-1,-1));
  }

  QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &index) const {
    CQStyleListItem *item = static_cast<CQStyleListItem *>(list_->item(index.row()));

    QFontMetrics fm(list_->font());

    QString str = QString("%1 %2").arg(item->name()).arg(item->desc());

    return QSize(fm.width(str) + 32, fm.height() + 8);
  }

 private:
  CQStyleList *list_;
};

//------

CQStyleList::
CQStyleList(QWidget *parent) :
 QListWidget(parent)
{
  setItemDelegate(new CQStyleListDelegate(this));

  populateList();

  connect(this, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
          this, SLOT(listItemSlot()));
}

void
CQStyleList::
populateList()
{
  clear();

  std::vector<QString> styleNames;

  CQStyleWidgetMgrInst->getStyleNames(styleNames);

  for (uint i = 0; i < styleNames.size(); ++i) {
    QString desc = CQStyleWidgetMgrInst->getDescription(styleNames[i]);

    addItem(new CQStyleListItem(this, styleNames[i], desc));
  }
}

void
CQStyleList::
listItemSlot()
{
  emit styleSelected(currentStyle());
}

QString
CQStyleList::
currentStyle() const
{
  CQStyleListItem *item = static_cast<CQStyleListItem *>(currentItem());

  return item->name();
}
