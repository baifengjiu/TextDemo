#include "Test.h"
#include "ColorGrid/ColorGrid.h"

Test::Test(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ColorGrid *colorGrid = new ColorGrid();
    colorGrid->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui.centralWidget->layout()->addWidget(colorGrid);

}
