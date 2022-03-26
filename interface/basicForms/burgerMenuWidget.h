#pragma once

#include <QIcon>
#include <QWidget>
#include <QPushButton>
#include <QActionGroup>

class BurgerMenuWidget : public QWidget {
    Q_OBJECT

public:
    BurgerMenuWidget(QWidget* parent = nullptr);

public slots:
    void addMenuAction(QAction* action);
    void setBurgerIcons(const QIcon& compressedStateIcon,
                        const QIcon& expandedStateIcon);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    void setExpanded(bool expanded);

private:
    QIcon expandedStateIcon_;
    QIcon compressedStateIcon_;

    QPushButton*  menuExpandButton_;
    QActionGroup* menuActionsGroup_;

    int menuWidth_;
};
