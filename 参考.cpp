//void MyExcel::on_ConfirmButton_pressed()
//{
//    int calculate_row = -1;
//    int calculate_column = -1;
//
//    if (ui->RCBox->currentText() == "行")
//    {
//        calculate_row = ui->lineEdit->text().toInt();
//        if (calculate_row<1 || calculate_row>ui->tableWidget->columnCount())
//        {
//            QMessageBox::about(this, "Warning", "输入错误的行数");
//        }
//
//    }
//    else if (ui->RCBox->currentText() == "列")
//    {
//        calculate_column = ui->lineEdit->text().toInt();
//        if (calculate_column<1 || calculate_column>ui->tableWidget->columnCount())
//        {
//            QMessageBox::about(this, "Warning", "输入错误的列数");
//        }
//
//    }
//    if (ui->FunctionBox->currentText() == "合计")
//    {
//        if (calculate_row != -1)
//        {
//            if (SumColumnPos == -1)
//            {
//                SumColumnPos = ui->tableWidget->columnCount();
//                ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
//                //计算某一行的合计时，就是插入新的一列，专门用于计算合计的
//            }
//            double sum = 0;
//            for (int i = 0; i < Column; i++)
//            {
//                if (ui->tableWidget->item(calculate_row - 1, i) == 0)
//                {
//                    QMessageBox::about(this, "Warning", "有格没有被定义");
//                    break;
//                }
//                else {
//                    sum = sum + ui->tableWidget->item(calculate_row - 1, i)->text().toDouble();
//                }
//                qDebug() << sum;
//
//            }
//            QTableWidgetItem* SUM = new QTableWidgetItem(QString::number(sum));
//            ui->tableWidget->setItem(calculate_row - 1, SumColumnPos, SUM);
//        }
//        else if (calculate_column != -1)
//        {
//            if (SumRowPos == -1)
//            {
//                SumRowPos = ui->tableWidget->rowCount();
//                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
//                //就是插入新的一行，专门用于计算合计的
//            }
//            double sum = 0;
//            for (int i = 0; i < Row; i++)
//            {
//                if (ui->tableWidget->item(i, calculate_column - 1) == 0)
//                {
//                    QMessageBox::about(this, "Warning", "有格没有被定义");
//                    break;
//                }
//                else {
//                    sum = sum + ui->tableWidget->item(i, calculate_column - 1)->text().toDouble();
//                }
//                qDebug() << sum;
//            }
//            QTableWidgetItem* SUM = new QTableWidgetItem(QString::number(sum));
//            ui->tableWidget->setItem(SumRowPos, calculate_column - 1, SUM);
//        }
//    }
//
//
//    else if (ui->FunctionBox->currentText() == "求平均")
//    {
//        if (calculate_row != -1)
//        {
//            if (AverageColumnPos == -1)
//            {
//                AverageColumnPos = ui->tableWidget->columnCount();
//                ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
//                //计算某一行的平均时，就是插入新的一列，专门用于计算合计的
//            }
//            double sum = 0;
//            for (int i = 0; i < Column; i++)
//            {
//                if (ui->tableWidget->item(calculate_row - 1, i) == 0)
//                {
//                    QMessageBox::about(this, "Warning", "有格没有被定义");
//                    break;
//                }
//                else {
//                    sum = sum + ui->tableWidget->item(calculate_row - 1, i)->text().toDouble();
//                }
//                qDebug() << sum;
//
//            }
//            QTableWidgetItem* Average = new QTableWidgetItem(QString::number(sum / Column));
//            ui->tableWidget->setItem(calculate_row - 1, AverageColumnPos, Average);
//        }
//        else if (calculate_column != -1)
//        {
//            if (AverageRowPos == -1)
//            {
//                AverageRowPos = ui->tableWidget->rowCount();
//                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
//                //计算某一行的平均时，就是插入新的一列，专门用于计算合计的
//            }
//            double sum = 0;
//            for (int i = 0; i < Row; i++)
//            {
//                if (ui->tableWidget->item(i, calculate_column - 1) == 0)
//                {
//                    QMessageBox::about(this, "Warning", "有格没有被定义");
//                    break;
//                }
//                else {
//                    sum = sum + ui->tableWidget->item(i, calculate_column - 1)->text().toDouble();
//                }
//                qDebug() << sum;
//            }
//            QTableWidgetItem* Average = new QTableWidgetItem(QString::number(sum / Row));
//            ui->tableWidget->setItem(AverageRowPos, calculate_column - 1, Average);
//        }
//    }
//    else if (ui->FunctionBox->currentText() == "最大值")
//    {
//
//        if (calculate_row != -1)
//        {
//            if (MaxColumnPos == -1)
//            {
//                MaxColumnPos = ui->tableWidget->columnCount();
//                ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
//                //计算某一行的平均时，就是插入新的一列，专门用于计算合计的
//            }
//            double maxNumber = 0;
//            for (int i = 0; i < Column; i++)
//            {
//                if (maxNumber < ui->tableWidget->item(calculate_row - 1, i)->text().toDouble())
//                {
//                    if (ui->tableWidget->item(calculate_row - 1, i) == 0)
//                    {
//                        QMessageBox::about(this, "Warning", "有格没有被定义");
//                        break;
//                    }
//                    else {
//                        maxNumber = ui->tableWidget->item(calculate_row - 1, i)->text().toDouble();
//                    }
//                    qDebug() << maxNumber;
//                }
//
//            }
//            QTableWidgetItem* MaxNumber = new QTableWidgetItem(QString::number(maxNumber));
//            ui->tableWidget->setItem(calculate_row - 1, MaxColumnPos, MaxNumber);
//        }
//        else if (calculate_column != -1)
//        {
//            if (MaxRowPos == -1)
//            {
//                MaxRowPos = ui->tableWidget->rowCount();
//                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
//                //计算某一行的平均时，就是插入新的一列，专门用于计算合计的
//            }
//            double maxNumber = 0;
//            for (int i = 0; i < Row; i++)
//            {
//                if (maxNumber < ui->tableWidget->item(i, calculate_column - 1)->text().toDouble())
//                {
//                    if (ui->tableWidget->item(i, calculate_column - 1) == 0)
//                    {
//                        QMessageBox::about(this, "Warning", "有格没有被定义");
//                        break;
//                    }
//                    else {
//                        maxNumber = ui->tableWidget->item(i, calculate_column - 1)->text().toDouble();
//                    }
//                    qDebug() << maxNumber;
//                }
//            }
//            QTableWidgetItem* MaxNumber = new QTableWidgetItem(QString::number(maxNumber));
//            ui->tableWidget->setItem(MaxRowPos, calculate_column - 1, MaxNumber);
//        }
//    }
//    else if (ui->FunctionBox->currentText() == "最小值")
//    {
//
//        if (calculate_row != -1)
//        {
//            if (MinColumnPos == -1)
//            {
//                MinColumnPos = ui->tableWidget->columnCount();
//                ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
//                //计算某一行的平均时，就是插入新的一列，专门用于计算合计的
//            }
//            double minNumber = ui->tableWidget->item(calculate_row - 1, 0)->text().toDouble();
//            for (int i = 0; i < Column; i++)
//            {
//                if (minNumber > ui->tableWidget->item(calculate_row - 1, i)->text().toDouble())
//                {
//                    if (ui->tableWidget->item(calculate_row - 1, i) == 0)
//                    {
//                        QMessageBox::about(this, "Warning", "有格没有被定义");
//                        break;
//                    }
//                    else {
//                        minNumber = ui->tableWidget->item(calculate_row - 1, i)->text().toDouble();
//                    }
//                    qDebug() << minNumber;
//                }
//
//            }
//            QTableWidgetItem* MinNumber = new QTableWidgetItem(QString::number(minNumber));
//            ui->tableWidget->setItem(calculate_row - 1, MinColumnPos, MinNumber);
//        }
//        else if (calculate_column != -1)
//        {
//            if (MinRowPos == -1)
//            {
//                MinRowPos = ui->tableWidget->rowCount();
//                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
//                //计算某一行的平均时，就是插入新的一列，专门用于计算合计的
//            }
//            double minNumber = ui->tableWidget->item(0, calculate_column - 1)->text().toDouble();
//            for (int i = 0; i < Row; i++)
//            {
//                if (minNumber > ui->tableWidget->item(i, calculate_column - 1)->text().toDouble())
//                {
//                    if (ui->tableWidget->item(i, calculate_column - 1) == 0)
//                    {
//                        QMessageBox::about(this, "Warning", "有格没有被定义");
//                        break;
//                    }
//                    else {
//                        minNumber = ui->tableWidget->item(i, calculate_column - 1)->text().toDouble();
//                    }
//                    qDebug() << minNumber;
//                }
//            }
//            QTableWidgetItem* MinNumber = new QTableWidgetItem(QString::number(minNumber));
//            ui->tableWidget->setItem(MinRowPos, calculate_column - 1, MinNumber);
//        }
//    }
//    else if (ui->FunctionBox->currentText() == "升序排序")
//    {
//        if (calculate_row != -1)
//        {
//            double array[100];
//            for (int i = 0; i < Column; i++)
//            {
//                if (ui->tableWidget->item(calculate_row - 1, i) == 0)
//                {
//                    QMessageBox::about(this, "Warning", "有格没有被定义");
//                    break;
//                }
//                else {
//                    array[i] = ui->tableWidget->item(calculate_row - 1, i)->text().toDouble();
//                }
//
//            }
//            std::sort(array, array + Column);
//            for (int i = 0; i < Column; i++)
//            {
//                QTableWidgetItem* arrayItem = new QTableWidgetItem(QString::number(array[i]));
//                ui->tableWidget->setItem(calculate_row - 1, i, arrayItem);
//
//            }
//
//        }
//
//        else if (calculate_column != -1)
//        {
//            double array[100];
//            for (int i = 0; i < Row; i++)
//            {
//                if (ui->tableWidget->item(i, calculate_column - 1) == 0)
//                {
//                    QMessageBox::about(this, "Warning", "有格没有被定义");
//                    break;
//                }
//                else {
//                    array[i] = ui->tableWidget->item(i, calculate_column - 1)->text().toDouble();
//                }
//
//            }
//            std::sort(array, array + Row);
//            for (int i = 0; i < Row; i++)
//            {
//                QTableWidgetItem* arrayItem = new QTableWidgetItem(QString::number(array[i]));
//                ui->tableWidget->setItem(i, calculate_column - 1, arrayItem);
//
//            }
//
//        }
//
//
//
//
//    }
//
//    else if (ui->FunctionBox->currentText() == "降序排序")
//    {
//        if (calculate_row != -1)
//        {
//            double array[100];
//            for (int i = 0; i < Column; i++)
//            {
//                if (ui->tableWidget->item(calculate_row - 1, i) == 0)
//                {
//                    QMessageBox::about(this, "Warning", "有格没有被定义");
//                    break;
//                }
//                else {
//                    array[i] = ui->tableWidget->item(calculate_row - 1, i)->text().toDouble();
//                }
//
//            }
//            std::sort(array, array + Column);
//            for (int i = Column - 1; i >= 0; i--)
//            {
//
//                QTableWidgetItem* arrayItem = new QTableWidgetItem(QString::number(array[i]));
//                ui->tableWidget->setItem(calculate_row - 1, Column - 1 - i, arrayItem);
//
//            }
//
//        }
//
//        else if (calculate_column != -1)
//        {
//            double array[100];
//            for (int i = 0; i < Row; i++)
//            {
//                if (ui->tableWidget->item(i, calculate_column - 1) == 0)
//                {
//                    QMessageBox::about(this, "Warning", "有格没有被定义");
//                    break;
//                }
//                else
//                {
//                    array[i] = ui->tableWidget->item(i, calculate_column - 1)->text().toDouble();
//                }
//            }
//            std::sort(array, array + Row);
//            for (int i = Row - 1; i >= 0; i--)
//            {
//
//                QTableWidgetItem* arrayItem = new QTableWidgetItem(QString::number(array[i]));
//                ui->tableWidget->setItem(Row - 1 - i, calculate_column - 1, arrayItem);
//
//            }
//
//        }
//    }
//
//    //调整行列宽度，避免和原来的表格数据混淆
//    for (int i = Column; i < ui->tableWidget->columnCount(); i++)
//    {
//        ui->tableWidget->setColumnWidth(i, 5);
//    }
//    for (int i = Column; i < ui->tableWidget->rowCount(); i++)
//    {
//        ui->tableWidget->setRowHeight(i, 3);
//    }
//}