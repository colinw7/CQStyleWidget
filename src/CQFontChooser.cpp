#include <CQFontChooser.h>

#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QFontComboBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QFontDialog>
#include <QFontDatabase>

#include <font_dialog.xpm>

CQFontChooser::
CQFontChooser(QWidget *parent) :
 QWidget(parent), style_(FontButton), fixedWidth_(false), exampleText_("Abc")
{
  font_     = font();
  fontName_ = font_.toString();

  //-----

  QHBoxLayout *layout = new QHBoxLayout(this);

  layout->setMargin (2);
  layout->setSpacing(2);

  cedit_   = new QLineEdit  (this);
  cbutton_ = new QToolButton(this);
  clabel_  = new QLabel     (this);
  button_  = new QToolButton(this);

  ncombo_ = new QFontComboBox(this);
  scombo_ = new QComboBox(this);
  zcombo_ = new QComboBox(this);

  button_->setIcon(QIcon(QPixmap((const char **) font_dialog_data)));

  ncombo_->setWritingSystem(QFontDatabase::Latin);

  cbutton_->setFixedSize(QSize(24,24));
//clabel_ ->setFixedSize(QSize(24,24));
  button_ ->setFixedSize(QSize(24,24));

  cbutton_->setText(exampleText_);
  clabel_ ->setText(exampleText_);

  layout->addWidget(cedit_  );
  layout->addWidget(cbutton_);
  layout->addWidget(clabel_ );
  layout->addWidget(button_ );
  layout->addWidget(ncombo_ );
  layout->addWidget(scombo_ );
  layout->addWidget(zcombo_ );
  layout->addStretch();

  cedit_  ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  cbutton_->setSizePolicy(QSizePolicy::Fixed    , QSizePolicy::Fixed);
  clabel_ ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  button_ ->setSizePolicy(QSizePolicy::Fixed    , QSizePolicy::Fixed);

  connect(cedit_  , SIGNAL(editingFinished()), this, SLOT(editFont  ()));
  connect(cbutton_, SIGNAL(clicked()        ), this, SLOT(applyFont ()));
  connect(button_ , SIGNAL(clicked()        ), this, SLOT(chooseFont()));

  connect(ncombo_ , SIGNAL(activated(int)), this, SLOT(nameChanged ()));
  connect(scombo_ , SIGNAL(activated(int)), this, SLOT(styleChanged()));
  connect(zcombo_ , SIGNAL(activated(int)), this, SLOT(sizeChanged ()));

  setStyle(FontEdit);

  setFixedWidth(false);

  //-----

  updateWidgets();
}

void
CQFontChooser::
setStyle(Style style)
{
  if (style_ == style) return;

  style_ = style;

  updateWidgets();
}

void
CQFontChooser::
setFont(const QFont &font)
{
  if (font_ == font)
    return;

  font_     = font;
  fontName_ = font_.toString();

  updateWidgets();

  emit fontChanged(font_);
  emit fontChanged(fontName_);
}

void
CQFontChooser::
setFontName(const QString &fontName)
{
  QFont font;

  if (! font.fromString(fontName))
    return;

  fontName_ = fontName;
  font_     = font;

  updateWidgets();

  emit fontChanged(font_);
  emit fontChanged(fontName_);
}

void
CQFontChooser::
setFixedWidth(bool fixedWidth)
{
  if (fixedWidth == fixedWidth_) return;

  fixedWidth_ = fixedWidth;

  updateWidgets();

  nameChanged();
}

void
CQFontChooser::
setExampleText(const QString &exampleText)
{
  if (exampleText == exampleText_) return;

  exampleText_ = exampleText;

  updateWidgets();
}

void
CQFontChooser::
updateWidgets()
{
  cedit_  ->setVisible(style_ == FontEdit  );
  cbutton_->setVisible(style_ == FontButton);
  clabel_ ->setVisible(style_ == FontLabel || style_ == FontDetailLabel);
  button_ ->setVisible(style_ != FontCombo );
  ncombo_ ->setVisible(style_ == FontCombo );
  scombo_ ->setVisible(style_ == FontCombo );
  zcombo_ ->setVisible(style_ == FontCombo );

  if (fixedWidth_)
    ncombo_->setFontFilters(QFontComboBox::MonospacedFonts);
  else
    ncombo_->setFontFilters(QFontComboBox::AllFonts);

  ncombo_->setCurrentIndex(1);

  cedit_->setText(fontName_);

  cbutton_->setFont(font_);
  cbutton_->setText(exampleText());

  clabel_->setFont(font_);

  if (style_ == FontDetailLabel) {
    QFontDatabase database;

    QString style = database.styleString(font_);

    clabel_->setText(QString("%1, %2, %3").
      arg(font_.substitute(font_.family())).arg(style).arg(font_.pointSize()));
  }
  else
    clabel_->setText(exampleText());

  int nind = ncombo_->findText(font_.family());

  if (nind >= 0)
    ncombo_->setCurrentIndex(nind);

  updateStyles();
  updateSizes ();

  updateCombos();
}

void
CQFontChooser::
updateCombos()
{
  QFontDatabase database;

  QString style = database.styleString(font_);

  int sind = scombo_->findText(style);

  if (sind == -1) {
    bool italic = (style == "Italic" || style == "Bold Italic");

    if (italic) {
      if (style == "Italic"     ) style = "Oblique";
      if (style == "Bold Italic") style = "Bold Oblique";

      sind = scombo_->findText(style);

      if (sind == -1) {
        if (style == "Bold Oblique") style = "Oblique";

        sind = scombo_->findText(style);
      }

      if (sind == -1) {
        if (style == "Oblique") style = "Italic";

        sind = scombo_->findText(style);
      }
    }
  }

  if (sind >= 0)
    scombo_->setCurrentIndex(sind);

  int zind = zcombo_->findText(QString("%1").arg(font_.pointSize()));

  if (zind >= 0)
    zcombo_->setCurrentIndex(zind);
}

void
CQFontChooser::
editFont()
{
  setFontName(cedit_->text());
}

void
CQFontChooser::
applyFont()
{
  emit fontApplied(font_);
  emit fontApplied(fontName_);
}

void
CQFontChooser::
chooseFont()
{
  bool ok;

  QFont font = QFontDialog::getFont(&ok, font_, this);

  if (ok)
    setFont(font);
}

void
CQFontChooser::
nameChanged()
{
  styleChanged();
}

void
CQFontChooser::
updateStyles()
{
  QFontDatabase database;

  const QString &family = ncombo_->itemText(ncombo_->currentIndex());

  scombo_->clear();
  scombo_->addItems(database.styles(family));
}

void
CQFontChooser::
updateSizes()
{
  QFontDatabase database;

  const QString &family = ncombo_->itemText(ncombo_->currentIndex());

  QList<int> sizes = database.pointSizes(family);

  zcombo_->clear();

  for (int i = 0; i < sizes.size(); ++i)
    zcombo_->addItem(QString("%1").arg(sizes[i]));
}

void
CQFontChooser::
styleChanged()
{
  sizeChanged();
}

void
CQFontChooser::
sizeChanged()
{
  QString name = ncombo_->itemText(ncombo_->currentIndex());
  int     size = zcombo_->itemText(zcombo_->currentIndex()).toInt();

  QFont font(name, size);

  QString style = scombo_->itemText(scombo_->currentIndex());

  if (style == "Bold" || style == "Bold Oblique" || style == "Bold Italic")
    font.setBold(true);

  if (style == "Oblique" || style == "Italic" ||
      style == "Bold Oblique" || style == "Bold Italic")
    font.setItalic(true);

  setFont(font);
}
