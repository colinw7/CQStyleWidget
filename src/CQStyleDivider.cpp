#include <CQStyleDivider.h>

#include <QPainter>

CQStyleDivider::
CQStyleDivider(QWidget *parent, const QString &style, const Type &type, int height) :
 QFrame(parent), style_(style), orient_(Qt::Horizontal), type_(type), height_(height),
 lindent_(6), rindent_(6)
{
  updateState();
}

CQStyleDivider::
CQStyleDivider(QWidget *parent, const QString &style, int height) :
 QFrame(parent), style_(style), orient_(Qt::Horizontal), type_(NoType), height_(height),
 lindent_(6), rindent_(6)
{
  updateState();
}

CQStyleDivider::
CQStyleDivider(const QString &style, const Type &type, int height) :
 QFrame(0), style_(style), orient_(Qt::Horizontal), type_(type), height_(height),
 lindent_(6), rindent_(6)
{
  updateState();
}

CQStyleDivider::
CQStyleDivider(const QString &style, int height) :
 QFrame(0), style_(style), orient_(Qt::Horizontal), type_(NoType), height_(height),
 lindent_(6), rindent_(6)
{
  updateState();
}

void
CQStyleDivider::
setOrientation(Qt::Orientation orient)
{
  orient_ = orient;

  updateState();
}

void
CQStyleDivider::
setType(Type type)
{
  type_ = type;

  update();
}

void
CQStyleDivider::
setHeight(int height)
{
  height_ = height;

  updateState();
}

void
CQStyleDivider::
updateState()
{
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  setMinimumSize(QSize(0, 0));
  setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));

  if (orient_ == Qt::Horizontal)
    setFixedHeight(height_);
  else
    setFixedWidth(height_);
}

void
CQStyleDivider::
paintEvent(QPaintEvent *)
{
  if (type_ != LineType) return;

  QPainter painter(this);

  painter.setPen(QColor(128, 128, 128));

  if (orient_ == Qt::Horizontal) {
    int y = rect().center().y();

    int x1 = lindent_;
    int x2 = width() - rindent_ - 1;

    painter.drawLine(x1, y, x2, y);
  }
  else {
    int x = rect().center().x();

    int y1 = lindent_;
    int y2 = height() - rindent_ - 1;

    painter.drawLine(x, y1, x, y2);
  }
}
