#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("黑鸦遴选计算器");
    this->setFixedSize(530, 480);

    ui->res_type_1->setEditable(false);
    ui->res_type_2->setEditable(false);
    ui->res_type_3->setEditable(false);
    ui->res_type_4->setEditable(false);

    ui->check_halo->setCheckState(Qt::CheckState::Unchecked);
    ui->label_halo->setEnabled(false);
    ui->com_type_5->setEnabled(false);

    mHalo[0] = Damage::HUANG_ZI;
    mHalo[1] = Damage::BAO_SHANG;
    mHalo[2] = Damage::SAN_GONG;
}

Widget::~Widget()
{
    delete ui;
}

float Damage::getDamageTotal()
{
    float res = 1.0;
    for(int i = 0; i < 6; i++)
        res *= 1 + (0.01 * mValue[i]);

    return  res;
}

void Widget::on_pushButton_clicked()
{
    mDamage.init();

    bool hasHalo = ui->check_halo->checkState() == 0? false: true;

    if(hasHalo)
        calculateDamage_Halo();
    else
        calculateDamage();

    ui->out_value_1->setText(QString::number(mDamage.mValue[Damage::BAI_ZI]   ));
    ui->out_value_2->setText(QString::number(mDamage.mValue[Damage::HUANG_ZI] ));
    ui->out_value_3->setText(QString::number(mDamage.mValue[Damage::BAO_SHANG]));
    ui->out_value_4->setText(QString::number(mDamage.mValue[Damage::ZUI_ZHONG]));
    ui->out_value_5->setText(QString::number(mDamage.mValue[Damage::SAN_GONG] ));
    ui->out_value_6->setText(QString::number(mDamage.mValue[Damage::LI_ZHI]   ));
}

void Widget::calculateDamage()
{
    ui->label_16->setEnabled(false);
    ui->res_type_5->setEnabled(false);

    mDamage.mValue[Damage::BAI_ZI]    = ui->in_value_1->text().toFloat();
    mDamage.mValue[Damage::HUANG_ZI]  = ui->in_value_2->text().toFloat();
    mDamage.mValue[Damage::BAO_SHANG] = ui->in_value_3->text().toFloat();
    mDamage.mValue[Damage::ZUI_ZHONG] = ui->in_value_4->text().toFloat();
    mDamage.mValue[Damage::SAN_GONG]  = ui->in_value_5->text().toFloat();
    mDamage.mValue[Damage::LI_ZHI]    = ui->in_value_6->text().toFloat();

    int index;
    index = ui->com_type_1->currentIndex();
    mDamage.mValue[index] -= ui->equ_value_1->currentText().toFloat();

    index = ui->com_type_2->currentIndex();
    mDamage.mValue[index] -= ui->equ_value_2->text().toFloat();

    index = ui->com_type_3->currentIndex();
    mDamage.mValue[index] -= ui->equ_value_3->text().toFloat();

    index = ui->com_type_4->currentIndex();
    mDamage.mValue[index] -= ui->equ_value_4->text().toFloat();

    float equ_max[4];
    equ_max[0] = ui->equ_max_1->currentIndex() == 0? 16.0: 30.0;
    equ_max[1] = ui->equ_max_2->text().toFloat();
    equ_max[2] = ui->equ_max_3->text().toFloat();
    equ_max[3] = ui->equ_max_4->text().toFloat();

    float tmpMax = 0.0;

    for (int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            for(int k = 0; k < 6; k++)
            {
                for(int l = 0; l < 6; l++)
                {
                    Damage tmpDamage = mDamage;
                    tmpDamage.mValue[i] += equ_max[0];
                    tmpDamage.mValue[j] += equ_max[1];
                    tmpDamage.mValue[k] += equ_max[2];
                    tmpDamage.mValue[l] += equ_max[3];

                    if(tmpMax < tmpDamage.getDamageTotal())
                    {
                        tmpMax = tmpDamage.getDamageTotal();
                        mType[0] = i;
                        mType[1] = j;
                        mType[2] = k;
                        mType[3] = l;
                    }
                }
            }
        }
    }

    mDamage.mValue[mType[0]] += equ_max[0];
    mDamage.mValue[mType[1]] += equ_max[1];
    mDamage.mValue[mType[2]] += equ_max[2];
    mDamage.mValue[mType[3]] += equ_max[3];

    ui->res_type_1->setCurrentIndex(mType[0]);
    ui->res_type_2->setCurrentIndex(mType[1]);
    ui->res_type_3->setCurrentIndex(mType[2]);
    ui->res_type_4->setCurrentIndex(mType[3]);

    ui->res_value_1->setText(QString::number(equ_max[0]));
    ui->res_value_2->setText(QString::number(equ_max[1]));
    ui->res_value_3->setText(QString::number(equ_max[2]));
    ui->res_value_4->setText(QString::number(equ_max[3]));
}

void Widget::calculateDamage_Halo()
{
    ui->label_16->setEnabled(true);
    ui->res_type_5->setEnabled(true);

    mDamage.mValue[Damage::BAI_ZI]    = ui->in_value_1->text().toFloat();
    mDamage.mValue[Damage::HUANG_ZI]  = ui->in_value_2->text().toFloat();
    mDamage.mValue[Damage::BAO_SHANG] = ui->in_value_3->text().toFloat();
    mDamage.mValue[Damage::ZUI_ZHONG] = ui->in_value_4->text().toFloat();
    mDamage.mValue[Damage::SAN_GONG]  = ui->in_value_5->text().toFloat();
    mDamage.mValue[Damage::LI_ZHI]    = ui->in_value_6->text().toFloat();

    int index;
    index = ui->com_type_1->currentIndex();
    mDamage.mValue[index] -= ui->equ_value_1->currentText().toFloat();

    index = ui->com_type_2->currentIndex();
    mDamage.mValue[index] -= ui->equ_value_2->text().toFloat();

    index = ui->com_type_3->currentIndex();
    mDamage.mValue[index] -= ui->equ_value_3->text().toFloat();

    index = ui->com_type_4->currentIndex();
    mDamage.mValue[index] -= ui->equ_value_4->text().toFloat();

    //光环
    index = ui->com_type_5->currentIndex();
    switch (index)
    {
    case 1:
        mDamage.mValue[Damage::HUANG_ZI] -= 5.0;
        break;
    case 2:
        mDamage.mValue[Damage::BAO_SHANG] -= 5.0;
        break;
    case 3:
        mDamage.mValue[Damage::SAN_GONG] -= 5.0;
        break;
    default:
        break;
    }

    float equ_max[4];
    equ_max[0] = ui->equ_max_1->currentIndex() == 0? 16.0: 30.0;
    equ_max[1] = ui->equ_max_2->text().toFloat();
    equ_max[2] = ui->equ_max_3->text().toFloat();
    equ_max[3] = ui->equ_max_4->text().toFloat();

    float tmpMax = 0.0;


    for (int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            for(int k = 0; k < 6; k++)
            {
                for(int l = 0; l < 6; l++)
                {
                    for (int m = 0; m < 3; m++)
                    {
                        Damage tmpDamage = mDamage;
                        tmpDamage.mValue[i] += equ_max[0];
                        tmpDamage.mValue[j] += equ_max[1];
                        tmpDamage.mValue[k] += equ_max[2];
                        tmpDamage.mValue[l] += equ_max[3];
                        tmpDamage.mValue[mHalo[m]] += 5.0;

                        if(tmpMax < tmpDamage.getDamageTotal())
                        {
                            tmpMax = tmpDamage.getDamageTotal();
                            mType[0] = i;
                            mType[1] = j;
                            mType[2] = k;
                            mType[3] = l;

                            mHaloSelection = m;
                        }
                    }
                }
            }
        }
    }

    mDamage.mValue[mType[0]] += equ_max[0];
    mDamage.mValue[mType[1]] += equ_max[1];
    mDamage.mValue[mType[2]] += equ_max[2];
    mDamage.mValue[mType[3]] += equ_max[3];
    mDamage.mValue[mHalo[mHaloSelection]] += 5.0;

    ui->res_type_1->setCurrentIndex(mType[0]);
    ui->res_type_2->setCurrentIndex(mType[1]);
    ui->res_type_3->setCurrentIndex(mType[2]);
    ui->res_type_4->setCurrentIndex(mType[3]);

    ui->res_value_1->setText(QString::number(equ_max[0]));
    ui->res_value_2->setText(QString::number(equ_max[1]));
    ui->res_value_3->setText(QString::number(equ_max[2]));
    ui->res_value_4->setText(QString::number(equ_max[3]));

    //光环选择
    ui->res_type_5->setCurrentIndex(mHaloSelection + 1);
}

void Widget::on_check_halo_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->label_halo->setEnabled(false);
        ui->com_type_5->setEnabled(false);
    }
    else
    {
        ui->label_halo->setEnabled(true);
        ui->com_type_5->setEnabled(true);
    }
}
