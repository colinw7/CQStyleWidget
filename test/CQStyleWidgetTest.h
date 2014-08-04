#include <QDialog>

class CQStyleWidget;

class CQStyleWidgetTest : public QDialog {
  Q_OBJECT

 public:
  CQStyleWidgetTest();

 private:
  CQStyleWidget *label_;
};
