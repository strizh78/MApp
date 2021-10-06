#include "textEditor.h"
#include "ui_textEditor.h"

#include <QPainter>
#include <QTextList>
#include <QColorDialog>
#include <QIntValidator>

namespace  {
QPixmap createColorPixmap(const QColor& color) {
    QPixmap pix(20, 20);

    QPainter painter(&pix);
    painter.setPen(color);
    painter.setBrush(color);

    painter.drawRect(pix.rect());
    return pix;
}
}

TextEditor::TextEditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    ui->fontSize->setValidator(new QIntValidator(1, 100));
    ui->fontSize->setText("14");
    ui->textEdit->setFocus();

    ui->textColor->setIcon(createColorPixmap(palette().text().color()));
    ui->backColor->setIcon(createColorPixmap(palette().window().color()));
}

TextEditor::~TextEditor() {
    delete ui;
}

QString TextEditor::toHtml() {
    return ui->textEdit->toHtml();
}

void TextEditor::setHtml(const QString& html) {
    return ui->textEdit->setHtml(html);
}

void TextEditor::on_bold_clicked() {
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();

    QFont font = fmt.font();
    font.setBold(ui->bold->isChecked() );

    fmt.setFont(font);
    applyToSelected(fmt);
}

void TextEditor::on_italic_clicked() {
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();

    QFont font = fmt.font();
    font.setItalic(ui->italic->isChecked());

    fmt.setFont(font);
    applyToSelected(fmt);
}

void TextEditor::on_underline_clicked(){
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();

    QFont font = fmt.font();
    font.setUnderline(ui->underline->isChecked());

    fmt.setFont(font);
    applyToSelected(fmt);
}

void TextEditor::on_cross_clicked() {
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();

    QFont font = fmt.font();
    font.setStrikeOut(ui->cross->isChecked());

    fmt.setFont(font);
    applyToSelected(fmt);
}

void TextEditor::on_inc_fontSize_clicked() {
    auto currentSize = ui->fontSize->text().toInt();
    ui->fontSize->setText(QString::number(currentSize + 1));
}

void TextEditor::on_dec_fontSize_clicked() {
    auto currentSize = ui->fontSize->text().toInt();
    ui->fontSize->setText(QString::number(currentSize - 1));
}

void TextEditor::on_fontSize_returnPressed() {
    QTextCharFormat fmt = ui->textEdit->currentCharFormat();

    QFont font = fmt.font();
    font.setPointSize(ui->fontSize->text().toInt());

    fmt.setFont(font);
    applyToSelected(fmt);
}

void TextEditor::on_dotList_clicked() {
    applyListFormat(QTextListFormat::Style::ListDisc);
}

void TextEditor::on_numberList_clicked() {
    applyListFormat(QTextListFormat::Style::ListDecimal);
}

void TextEditor::on_decIndent_clicked() {
    applyIndent(-1);
}

void TextEditor::on_incIndent_clicked() {
    applyIndent(1);
}

void TextEditor::on_textColor_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this);

    ui->textColor->setIcon(createColorPixmap(color));

    QTextCharFormat fmt = ui->textEdit->currentCharFormat();
    fmt.setForeground(color);

    applyToSelected(fmt);
}

void TextEditor::on_backColor_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this);

    ui->backColor->setIcon(createColorPixmap(color));

    QTextCharFormat fmt;
    fmt.setBackground(color);

    applyToSelected(fmt);
}

void TextEditor::on_textEdit_cursorPositionChanged() {
    auto fmt = ui->textEdit->currentCharFormat();

    ui->fontSize->setText(QString::number(fmt.font().pointSize()));

    QColor textColor = fmt.foreground().color();
    ui->textColor->setIcon(createColorPixmap(textColor));

    QColor backgroundColor = fmt.background().color();
    ui->backColor->setIcon(createColorPixmap(backgroundColor));

    ui->bold->setChecked(fmt.font().bold());
    ui->italic->setChecked(fmt.font().italic());
    ui->underline->setChecked(fmt.font().underline());
    ui->cross->setChecked(fmt.font().strikeOut());
}

void TextEditor::applyListFormat(QTextListFormat::Style listType) {
    auto cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextListFormat listFmt;
    if (cursor.currentList()) {
        listFmt = cursor.currentList()->format();
    }
    listFmt.setStyle(listType);
    cursor.createList(listFmt);

    cursor.endEditBlock();
}

void TextEditor::applyIndent(int indentDelta) {
    auto cursor = ui->textEdit->textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat bfmt = cursor.blockFormat();
    bfmt.setIndent(bfmt.indent() + indentDelta);

    cursor.setBlockFormat(bfmt);
    cursor.endEditBlock();
}

void TextEditor::applyToSelected(const QTextCharFormat &format, bool needNotSelected) {
    auto cursor = ui->textEdit->textCursor();
    if (needNotSelected && cursor.hasSelection() == false) {
        cursor.select(QTextCursor::SelectionType::WordUnderCursor);
    }
    ui->textEdit->mergeCurrentCharFormat(format);
}
