//
// Created by Vladimir on 19.05.2021.
//

#ifndef DB_COURSEWORK__INPUT_DIALOG_HPP_
#define DB_COURSEWORK__INPUT_DIALOG_HPP_

#include <QCloseEvent>
#include <QDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <utility>

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    InputDialog()
    {
        setModal(true);
        layout = std::make_unique<QGridLayout>();
        formLayout = std::make_unique<QFormLayout>();

        auto font = headerLabel.font();
        font.setPixelSize(20);
        headerLabel.setFont(font);

        add_btn = std::make_unique<QPushButton>("Save", this);
        add_btn->setObjectName("add-btn");
        cancel_btn = std::make_unique<QPushButton>("Cancel", this);
        cancel_btn->setObjectName("clear-btn");

        setLayout(layout.get());
        layout->addWidget(&headerLabel, 0, 0);
        layout->addLayout(formLayout.get(), 1, 0, 1, 2);
        layout->addWidget(add_btn.get(), 2, 1);
        layout->addWidget(cancel_btn.get(), 2, 0);

        connect(cancel_btn.get(), &QPushButton::clicked, this, [this]() {
            spdlog::info("InputDialog::Cancel");
            close();
        });
        connect(add_btn.get(), &QPushButton::clicked, this, [this]() {
            spdlog::info("InputDialog::Add");
            for (auto &inputField : findChildren<QLineEdit *>()) {
                results.push_back(inputField->text());
            }
            spdlog::info("results size {}", results.size());
            close();
        });
    }

    void setTitle(const QString &title)
    {
        setWindowTitle(title);
        headerLabel.setText(title);
    }

    void addField(const QString &title, QValidator *validator = nullptr,
                  QLineEdit::EchoMode echoMode = QLineEdit::NoEcho)
    {
        auto label = new QLabel;
        auto inputField = new QLineEdit;

        if (validator != nullptr) {
            inputField->setValidator(validator);
        }
        if (echoMode != QLineEdit::NoEcho) {
            inputField->setEchoMode(echoMode);
        }

        formLayout->addRow(title, inputField);
        update();
    }

    std::list<QString> &getResults()
    {
        return results;
    }

private:
    std::unique_ptr<QGridLayout> layout;
    std::unique_ptr<QFormLayout> formLayout;
    std::list<QString> results;
    std::unique_ptr<QPushButton> add_btn;
    std::unique_ptr<QPushButton> cancel_btn;
    QLabel headerLabel;

    int countInputFields()
    {
        int inputCount = 0;
        for (auto &inputField : findChildren<QLineEdit *>()) {
            inputCount++;
        }
        spdlog::info("InputDialog->countInputFields: {}", inputCount);
        return inputCount;
    }
};
#endif // DB_COURSEWORK__INPUT_DIALOG_HPP_