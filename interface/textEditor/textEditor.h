#pragma once

#include <QWidget>
#include <QString>
#include <QTextListFormat>

QT_BEGIN_NAMESPACE
namespace Ui { class TextEditor; }
QT_END_NAMESPACE

class QTextCharFormat;

class TextEditor : public QWidget {
    Q_OBJECT

public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

    QString toHtml();
    void setHtml(const QString& html);

private slots:
    void on_bold_clicked();
    void on_italic_clicked();
    void on_underline_clicked();
    void on_cross_clicked();

    void on_inc_fontSize_clicked();
    void on_dec_fontSize_clicked();
    void on_fontSize_returnPressed();

    void on_dotList_clicked();
    void on_numberList_clicked();

    void on_decIndent_clicked();
    void on_incIndent_clicked();

    void on_textColor_clicked();
    void on_backColor_clicked();

    void on_textEdit_cursorPositionChanged();

private:
    void applyListFormat(QTextListFormat::Style listType);
    void applyIndent(int indentDelta);
    void applyToSelected(const QTextCharFormat &format, bool needNotSelected = true);

private:
    Ui::TextEditor *ui;
};

