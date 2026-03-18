#ifndef QGRANVIEW_WINDOW_H
#define QGRANVIEW_WINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QToolButton>
#include <QLabel>
#include <QFrame>
#include <QScrollArea>
#include <QGridLayout>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QSplitter>
#include <QDockWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QStackedWidget>
#include <QListWidget>
#include <QTreeWidget>
#include <QTextEdit>

class RibbonTabBar;
class RibbonPanel;
class RibbonCategory;

// 主窗口类，包含 Ribbon 样式的菜单栏
class QGranViewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QGranViewWindow(QWidget *parent = nullptr);

private:
    void setupUI();
    void setupRibbon();
    void setupRibbonCategories();
    void setupMainContentArea();
    void setupStatusBar();

    // UI 组件
    QWidget *centralWidget;
    QTabWidget *ribbonTabs;
    QScrollArea *mainContent;
    QStatusBar *statusBar;

    // Ribbon 相关组件
    RibbonCategory *homeCategory;
    RibbonCategory *viewCategory;
    RibbonCategory *toolsCategory;
    RibbonCategory *renderCategory;
    RibbonCategory *assetsCategory;
};

// Ribbon 类别容器
class RibbonCategory : public QWidget
{
    Q_OBJECT

public:
    explicit RibbonCategory(const QString &title, QWidget *parent = nullptr);

    void addPanel(RibbonPanel *panel);
    QString getTitle() const { return title; }

private:
    void setupUI();

    QString title;
    QHBoxLayout *layout;
    QFrame *container;
    QVBoxLayout *containerLayout;
};

// Ribbon 面板容器
class RibbonPanel : public QFrame
{
    Q_OBJECT

public:
    explicit RibbonPanel(const QString &title, QWidget *parent = nullptr);

    void addButton(QAbstractButton *button);
    void addWidget(QWidget *widget);
    void addSeparator();
    void addRow(QList<QWidget*> widgets);

private:
    void setupUI();

    QString title;
    QVBoxLayout *mainLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    int currentRow;
    int currentCol;
    static const int MAX_COLS = 6; // 每行最多6个控件
};

// 自定义按钮类，用于 Ribbon 界面
class RibbonButton : public QToolButton
{
    Q_OBJECT

public:
    explicit RibbonButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);

private:
    void setupUI();
};

#endif // QGRANVIEW_WINDOW_H