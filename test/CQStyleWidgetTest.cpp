#include <CQStyleWidgetTest.h>
#include <CQStyleWidget.h>
#include <CQStyleControl.h>
#include <QApplication>
#include <QVBoxLayout>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQStyleWidgetTest *test = new CQStyleWidgetTest;

  test->show();

  return app.exec();
}

CQStyleWidgetTest::
CQStyleWidgetTest()
{
  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->setMargin(2); layout->setSpacing(2);

  QVBoxLayout *llayout = new QVBoxLayout;
  llayout->setMargin(2); llayout->setSpacing(2);

  QLabel *label1 = CQStyleWidgetMgrInst->addT(new QLabel("Header 1" ), "h1");
  QLabel *label2 = CQStyleWidgetMgrInst->addT(new QLabel("Header 2" ), "h2");
  QLabel *label3 = CQStyleWidgetMgrInst->addT(new QLabel("Header 3" ), "h3");
  QLabel *label4 = CQStyleWidgetMgrInst->addT(new QLabel("Header 4" ), "h4");
  QLabel *label5 = CQStyleWidgetMgrInst->addT(new QLabel("Paragraph"), "p");

  llayout->addWidget(label1);
  llayout->addWidget(label2);
  llayout->addWidget(label3);
  llayout->addWidget(label4);
  llayout->addWidget(label5);
  llayout->addStretch(1);

  CQStyleControl *control = new CQStyleControl;

  layout->addLayout(llayout);
  layout->addWidget(control);
}
