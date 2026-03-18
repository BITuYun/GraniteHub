#include "qgranview_window.h"
#include <QApplication>
#include <QMessageBox>
#include <QStyle>
#include <QPainter>
#include <QStyleOption>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QProgressBar>

// QGranViewWindow 实现
// sudo apt install qtbase5-dev libqt5opengl5-dev qtchooser
QGranViewWindow::QGranViewWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

void QGranViewWindow::setupUI()
{
    setWindowTitle("QGranView - Qt + Granite Viewer with Ribbon UI");
    resize(1400, 900);

    // 设置中央部件
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 创建 Ribbon 区域
    setupRibbon();
    mainLayout->addWidget(ribbonTabs);

    // 创建主要内容区域
    setupMainContentArea();
    mainLayout->addWidget(mainContent);

    // 创建状态栏
    setupStatusBar();
}

void QGranViewWindow::setupRibbon()
{
    ribbonTabs = new QTabWidget();
    ribbonTabs->setStyleSheet(
        "QTabWidget::pane { border: none; margin: 0px; padding: 0px; }"
        "QTabBar::tab { min-width: 120px; padding: 10px; font-size: 12px; }"
        "QTabBar::tab:selected { background-color: #e6e6e6; }"
        "QTabBar::tab:!selected { background-color: #f0f0f0; }"
    );

    setupRibbonCategories();
}

void QGranViewWindow::setupRibbonCategories()
{
    // 创建 Home 类别
    homeCategory = new RibbonCategory("Home");
    
    // Home 类别的面板
    RibbonPanel *filePanel = new RibbonPanel("File");
    filePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DirOpenIcon), "Open"));
    filePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogSaveButton), "Save"));
    filePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileDialogNewFolder), "New Project"));
    homeCategory->addPanel(filePanel);
    
    RibbonPanel *editPanel = new RibbonPanel("Edit");
    editPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileIcon), "Undo"));
    editPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_BrowserReload), "Redo"));
    editPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogResetButton), "Cut"));
    editPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogDiscardButton), "Copy"));
    editPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogOkButton), "Paste"));
    homeCategory->addPanel(editPanel);
    
    RibbonPanel *modePanel = new RibbonPanel("Mode");
    modePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_ComputerIcon), "Select"));
    modePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_ArrowForward), "Move"));
    modePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_CommandLink), "Rotate"));
    modePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DirClosedIcon), "Scale"));
    homeCategory->addPanel(modePanel);
    
    ribbonTabs->addTab(homeCategory, "Home");

    // 创建 View 类别
    viewCategory = new RibbonCategory("View");
    
    RibbonPanel *viewportPanel = new RibbonPanel("Viewport");
    viewportPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileDialogDetailedView), "Perspective"));
    viewportPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileDialogListView), "Top"));
    viewportPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileDialogInfoView), "Front"));
    viewportPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileDialogContentsView), "Side"));
    viewCategory->addPanel(viewportPanel);
    
    RibbonPanel *displayPanel = new RibbonPanel("Display");
    displayPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_MessageBoxInformation), "Wireframe"));
    displayPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_ComputerIcon), "Solid"));
    displayPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DesktopIcon), "Material"));
    displayPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DirIcon), "Lit"));
    viewCategory->addPanel(displayPanel);
    
    ribbonTabs->addTab(viewCategory, "View");

    // 创建 Tools 类别
    toolsCategory = new RibbonCategory("Tools");
    
    RibbonPanel *primitivePanel = new RibbonPanel("Primitives");
    primitivePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DirIcon), "Cube"));
    primitivePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileDialogDetailedView), "Sphere"));
    primitivePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileDialogInfoView), "Cylinder"));
    primitivePanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileDialogListView), "Plane"));
    toolsCategory->addPanel(primitivePanel);
    
    RibbonPanel *transformPanel = new RibbonPanel("Transform");
    transformPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_ArrowUp), "Align"));
    transformPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_ArrowDown), "Distribute"));
    transformPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_MediaSeekBackward), "Mirror"));
    transformPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_MediaSeekForward), "Array"));
    toolsCategory->addPanel(transformPanel);
    
    ribbonTabs->addTab(toolsCategory, "Tools");

    // 创建 Render 类别
    renderCategory = new RibbonCategory("Render");
    
    RibbonPanel *settingsPanel = new RibbonPanel("Settings");
    settingsPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_ComputerIcon), "Quality"));
    settingsPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogResetButton), "Lighting"));
    settingsPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogHelpButton), "Environment"));
    renderCategory->addPanel(settingsPanel);
    
    RibbonPanel *exportPanel = new RibbonPanel("Export");
    exportPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogSaveButton), "Screenshot"));
    exportPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogApplyButton), "Video"));
    exportPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogYesButton), "Render"));
    renderCategory->addPanel(exportPanel);
    
    ribbonTabs->addTab(renderCategory, "Render");

    // 创建 Assets 类别
    assetsCategory = new RibbonCategory("Assets");
    
    RibbonPanel *libraryPanel = new RibbonPanel("Library");
    libraryPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DirOpenIcon), "Import"));
    libraryPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogDiscardButton), "Export"));
    libraryPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_FileDialogContentsView), "Browser"));
    assetsCategory->addPanel(libraryPanel);
    
    RibbonPanel *managementPanel = new RibbonPanel("Management");
    managementPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_TrashIcon), "Clean"));
    managementPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogResetButton), "Refresh"));
    managementPanel->addButton(new RibbonButton(style()->standardIcon(QStyle::SP_DialogHelpButton), "Optimize"));
    assetsCategory->addPanel(managementPanel);
    
    ribbonTabs->addTab(assetsCategory, "Assets");
}

void QGranViewWindow::setupMainContentArea()
{
    // 创建主内容区域，用于显示 Granite 渲染输出
    mainContent = new QScrollArea();
    mainContent->setWidgetResizable(true);
    
    QWidget *contentWidget = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    
    QLabel *titleLabel = new QLabel("Granite Rendering Area");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; color: #333; padding: 20px;");
    contentLayout->addWidget(titleLabel);
    
    QLabel *descLabel = new QLabel("This area will display the Granite rendering output.");
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setStyleSheet("font-size: 14px; color: #666; padding: 10px;");
    contentLayout->addWidget(descLabel);
    
    // 这里将来会嵌入 Granite 的渲染输出
    QFrame *renderFrame = new QFrame();
    renderFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    renderFrame->setStyleSheet("background-color: black;");
    renderFrame->setMinimumHeight(600);
    contentLayout->addWidget(renderFrame);
    
    QPushButton *renderBtn = new QPushButton("Start Granite Rendering");
    renderBtn->setFixedSize(200, 40);
    renderBtn->setStyleSheet(
        "QPushButton { "
        "   background-color: #4CAF50; "
        "   color: white; "
        "   border: none; "
        "   padding: 10px; "
        "   font-size: 14px; "
        "   border-radius: 5px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #45a049; "
        "}"
    );
    contentLayout->addWidget(renderBtn, 0, Qt::AlignCenter);
    
    connect(renderBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Rendering", "Starting Granite rendering...");
    });
    
    contentLayout->addStretch();
    mainContent->setWidget(contentWidget);
}

void QGranViewWindow::setupStatusBar()
{
    statusBar = new QStatusBar();
    statusBar->showMessage("Ready");
    setStatusBar(statusBar);
}

// RibbonCategory 实现
RibbonCategory::RibbonCategory(const QString &title, QWidget *parent)
    : QWidget(parent), title(title)
{
    setupUI();
}

void RibbonCategory::setupUI()
{
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    
    container = new QFrame();
    container->setStyleSheet("QFrame { background-color: white; border: 1px solid #ccc; }");
    layout->addWidget(container);
    
    containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(10, 10, 10, 10);
    containerLayout->setSpacing(5);
}

void RibbonCategory::addPanel(RibbonPanel *panel)
{
    containerLayout->addWidget(panel);
}

// RibbonPanel 实现
RibbonPanel::RibbonPanel(const QString &title, QWidget *parent)
    : QFrame(parent), title(title), currentRow(0), currentCol(0)
{
    setupUI();
}

void RibbonPanel::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    
    groupBox = new QGroupBox(title);
    groupBox->setStyleSheet(
        "QGroupBox { "
        "   font-weight: bold; "
        "   border: 1px solid #ccc; "
        "   border-radius: 4px; "
        "   margin-top: 1ex; "
        "} "
        "QGroupBox::title { "
        "   subcontrol-origin: margin; "
        "   left: 10px; "
        "   padding: 0 5px 0 5px; "
        "}"
    );
    
    gridLayout = new QGridLayout(groupBox);
    gridLayout->setColumnStretch(MAX_COLS, 1); // 最后一列拉伸以填充空间
    
    mainLayout->addWidget(groupBox);
}

void RibbonPanel::addButton(QAbstractButton *button)
{
    // 将按钮包装在一个 QWidget 中以便添加到网格布局
    QWidget *wrapper = new QWidget();
    QVBoxLayout *wrapperLayout = new QVBoxLayout(wrapper);
    wrapperLayout->setContentsMargins(2, 2, 2, 2);
    wrapperLayout->addWidget(button);
    wrapperLayout->addStretch();
    
    gridLayout->addWidget(wrapper, currentRow, currentCol);
    
    currentCol++;
    if (currentCol >= MAX_COLS) {
        currentCol = 0;
        currentRow++;
    }
}

void RibbonPanel::addWidget(QWidget *widget)
{
    gridLayout->addWidget(widget, currentRow, currentCol);
    
    currentCol++;
    if (currentCol >= MAX_COLS) {
        currentCol = 0;
        currentRow++;
    }
}

void RibbonPanel::addSeparator()
{
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::VLine);
    separator->setFrameShadow(QFrame::Sunken);
    
    gridLayout->addWidget(separator, currentRow, currentCol);
    
    currentCol++;
    if (currentCol >= MAX_COLS) {
        currentCol = 0;
        currentRow++;
    }
}

void RibbonPanel::addRow(QList<QWidget*> widgets)
{
    for (int i = 0; i < widgets.size() && currentCol < MAX_COLS; ++i) {
        gridLayout->addWidget(widgets[i], currentRow, currentCol);
        currentCol++;
    }
    
    if (currentCol < MAX_COLS) {
        currentRow++; // 换行
        currentCol = 0;
    }
}

// RibbonButton 实现
RibbonButton::RibbonButton(const QIcon &icon, const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setupUI();
    setIcon(icon);
    setText(text);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setFixedWidth(60);
    setFixedHeight(60);
}

void RibbonButton::setupUI()
{
    setStyleSheet(
        "QToolButton { "
        "   border: 1px solid transparent; "
        "   background-color: transparent; "
        "   color: #333; "
        "   padding: 5px; "
        "   margin: 2px; "
        "   border-radius: 3px; "
        "} "
        "QToolButton:hover { "
        "   background-color: #e6f3ff; "
        "   border: 1px solid #99d6ff; "
        "} "
        "QToolButton:pressed { "
        "   background-color: #cce6ff; "
        "}"
    );
}