#include "calculator.h"
#include "ui_calculator.h"
#include <QRegularExpression>
double calcval=0.0;
bool divtrigger=false;
bool multitrigger=false;
bool addtrigger=false;
bool subtrigger=false;
Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcval));
    QPushButton *numbuttons[10];
    for(int i=0;i<10;i++){
        QString butName="Button"+QString::number(i);
         numbuttons[i]=Calculator::findChild<QPushButton *>(butName);
         connect(numbuttons[i],SIGNAL(released()),this,SLOT(NumPressed()));
      }
    connect(ui->Add, SIGNAL(released()), this,
               SLOT(MathButtonPressed()));
       connect(ui->Subtract, SIGNAL(released()), this,
               SLOT(MathButtonPressed()));
       connect(ui->Multiply, SIGNAL(released()), this,
               SLOT(MathButtonPressed()));
       connect(ui->Divide, SIGNAL(released()), this,
               SLOT(MathButtonPressed()));

       // Connect equals button
       connect(ui->Equal, SIGNAL(released()), this,
               SLOT(EqualButton()));

       // Connect change sign
       connect(ui->ChangesSign, SIGNAL(released()), this,
               SLOT(ChangeNumberSign()));
}
void Calculator:: MathButtonPressed()
{
    divtrigger=false;
   multitrigger=false;
     addtrigger=false;
   subtrigger=false;
   QString displayval=ui->Display->text();
   calcval=displayval.toDouble();
   QPushButton *button=(QPushButton *)sender();
   QString butVal=button->text();
   if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0)
       divtrigger=true;
   else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0)
       multitrigger=true;
   else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0)
       addtrigger=true;
   else if(QString::compare(butVal,"-",Qt::CaseInsensitive)==0)
       subtrigger=true;
   ui->Display->setText("");
}
void Calculator:: EqualButton()
{
    double solution=0.0;
     QString displayval= ui->Display->text();
     double dbldisplayval=displayval.toDouble();
     if(addtrigger||subtrigger||multitrigger||divtrigger)
     {
         if(addtrigger)
             solution=calcval+dbldisplayval;
         if(subtrigger)
             solution=calcval-dbldisplayval;
         if(multitrigger)
             solution=calcval*dbldisplayval;
         if(divtrigger)
             solution=calcval/dbldisplayval;
         ui->Display->setText(QString::number(solution));
     }
}

Calculator::~Calculator()
{
    delete ui;
}
void Calculator::NumPressed()
{
    QPushButton *button=(QPushButton *)sender();
    QString butVal=button->text();
    QString displayval=ui->Display->text();
    if((displayval.toDouble()==0)||(displayval.toDouble()==0.0))
    {
        ui->Display->setText(butVal);
    }
    else
    {
        QString newval=displayval+butVal;
    double dblnewval=newval.toDouble();
    ui->Display->setText(QString::number(dblnewval,'g',16));
    }


}
void Calculator::ChangeNumberSign()
{
    QString displayval=ui->Display->text();
    QRegularExpression regex ("[-]?[0-9.]*");
    QRegularExpressionMatch match = regex.match(displayval);
     if(match.hasMatch())
     {
            double dbldisplayval = displayval.toDouble();
            double dblDisplayValSign = -1 * dbldisplayval;

            // Put solution in display
            ui->Display->setText(QString::number(dblDisplayValSign));
        }
}
