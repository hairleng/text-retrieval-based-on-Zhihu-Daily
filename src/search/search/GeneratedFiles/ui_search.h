/********************************************************************************
** Form generated from reading UI file 'search.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_H
#define UI_SEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_searchClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QTextBrowser *textBrowser;
    QLabel *label_3;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *searchClass)
    {
        if (searchClass->objectName().isEmpty())
            searchClass->setObjectName(QStringLiteral("searchClass"));
        searchClass->resize(1780, 1266);
        QIcon icon;
        icon.addFile(QStringLiteral(":/search/8c1001e93901213fc7ec80e957e736d12f2e952c.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        searchClass->setWindowIcon(icon);
        centralWidget = new QWidget(searchClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font.setPointSize(20);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);

        verticalLayout_2->addWidget(label, 0, Qt::AlignHCenter);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font1.setPointSize(12);
        label_2->setFont(font1);

        verticalLayout_2->addWidget(label_2, 0, Qt::AlignHCenter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(8);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMinimumSize(QSize(117, 20));
        lineEdit->setMaximumSize(QSize(200, 35));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(100, 16777215));
        pushButton->setIcon(icon);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy2);
        listWidget->setMaximumSize(QSize(350, 16777215));

        verticalLayout->addWidget(listWidget);


        horizontalLayout_2->addLayout(verticalLayout);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setEnabled(true);

        horizontalLayout_2->addWidget(textBrowser);


        verticalLayout_2->addLayout(horizontalLayout_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font2.setPointSize(10);
        label_3->setFont(font2);

        verticalLayout_2->addWidget(label_3, 0, Qt::AlignHCenter);

        searchClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(searchClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        searchClass->setStatusBar(statusBar);

        retranslateUi(searchClass);

        QMetaObject::connectSlotsByName(searchClass);
    } // setupUi

    void retranslateUi(QMainWindow *searchClass)
    {
        searchClass->setWindowTitle(QApplication::translate("searchClass", "\347\237\245\344\271\216\346\227\245\346\212\245\346\220\234\347\264\242\345\274\225\346\223\216", 0));
        label->setText(QApplication::translate("searchClass", "\347\237\245\344\271\216\346\227\245\346\212\245\347\275\221\351\241\265\345\205\263\351\224\256\350\257\215\346\220\234\347\264\242", 0));
        label_2->setText(QApplication::translate("searchClass", " \346\273\241\350\266\263\346\234\200\345\245\207\345\246\231\347\232\204\345\245\275\345\245\207\345\277\203\357\274\214\346\220\234\347\275\227\345\205\250\347\220\203\345\200\274\345\276\227\350\256\250\350\256\272\347\232\204\350\257\235\351\242\230\357\274\214\347\224\261\346\211\216\346\240\271\344\270\226\347\225\214\345\220\204\345\234\260\347\232\204\346\234\213\345\217\213\344\273\254\345\270\246\347\273\231\344\275\240\346\234\200\347\234\237\345\256\236\347\232\204\345\275\223\345\234\260\346\203\205\345\206\265", 0));
        pushButton->setText(QApplication::translate("searchClass", "\346\220\234\347\264\242", 0));
        label_3->setText(QApplication::translate("searchClass", "\344\275\277\347\224\250\350\257\264\346\230\216\357\274\232\345\234\250\346\220\234\347\264\242\346\241\206\344\270\255\350\276\223\345\205\245\345\205\263\351\224\256\350\257\215\357\274\214\347\202\271\345\207\273\346\220\234\347\264\242\357\274\214\346\220\234\347\264\242\347\273\223\346\236\234\345\260\206\346\230\276\347\244\272\345\234\250\344\270\213\346\226\271\346\241\206\345\206\205\357\274\214\346\203\263\350\246\201\346\237\245\347\234\213\347\233\270\345\205\263\345\214\205\345\220\253\345\205\263\351\224\256\350\257\215\347\232\204\347\275\221\351\241\265\357\274\214\350\257\267\347\202\271\345\207\273\346\220\234\347\264\242\347\273\223\346\236\234\345\215\263\345\217\257", 0));
    } // retranslateUi

};

namespace Ui {
    class searchClass: public Ui_searchClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_H
