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
  llayout->setMargin(0); llayout->setSpacing(0);

  CQStyleWidgetMgr *mgr = CQStyleWidgetMgrInst;

  mgr->addHeader1(llayout, "Header 1");
  mgr->addHeader2(llayout, "Header 2");
  mgr->addHeader3(llayout, "Header 3");
  mgr->addHeader4(llayout, "Header 4");

  QLabel *label = mgr->add(new QLabel(
    "Lorem ipsum dolor sit amet, consectetur adipisicing elit, \n"
    "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \n"
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris \n"
    "nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in \n"
    "reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla \n"
    "pariatur. Excepteur sint occaecat cupidatat non proident, sunt in \n"
    "culpa qui officia deserunt mollit anim id est laborum."), "p");

  llayout->addWidget(label);
  llayout->addStretch(1);

  CQStyleControl *control = new CQStyleControl;

  layout->addLayout(llayout);
  layout->addWidget(control);
}
