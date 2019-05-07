/****************************************************************************
**
** Qtitan Library by Developer Machines (DataGrid component for Qt.C++)
** 
** Copyright (c) 2009-2016 Developer Machines (http://www.devmachines.com)
**           ALL RIGHTS RESERVED
** 
**  The entire contents of this file is protected by copyright law and
**  international treaties. Unauthorized reproduction, reverse-engineering
**  and distribution of all or any portion of the code contained in this
**  file is strictly prohibited and may result in severe civil and 
**  criminal penalties and will be prosecuted to the maximum extent 
**  possible under the law.
**
**  RESTRICTIONS
**
**  THE SOURCE CODE CONTAINED WITHIN THIS FILE AND ALL RELATED
**  FILES OR ANY PORTION OF ITS CONTENTS SHALL AT NO TIME BE
**  COPIED, TRANSFERRED, SOLD, DISTRIBUTED, OR OTHERWISE MADE
**  AVAILABLE TO OTHER INDIVIDUALS WITHOUT WRITTEN CONSENT
**  AND PERMISSION FROM DEVELOPER MACHINES
**
**  CONSULT THE END USER LICENSE AGREEMENT FOR INFORMATION ON
**  ADDITIONAL RESTRICTIONS.
**
****************************************************************************/

#ifndef QTN_GRID_H
#define QTN_GRID_H

#include <QIcon>
#include <QTabWidget>
#include <QStyleOption>
#include <QApplication>
#include <QMenu>
#include <QCheckBox>
#include <QLabel>
#include <QToolButton>
#include <QTextDocument>
#include <QPrinter>
#include <QAbstractItemView>
#include <QtCore/qhash.h>

#ifndef QTN_NOUSE_XML_MODULE
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#endif
#include "QtnGridDef.h"
#include "QtnGridGraphics.h"
#include "QtnGridModelController.h"

inline uint qHash(const QSize& size, uint seed = 0) Q_DECL_NOTHROW
{
    return (size.width() ^ seed) + (size.height() ^ seed);
}

inline void exchange_int(int& i1, int& i2)
{
    int temp = i1;
    i1 = i2;
    i2 = temp;
}

inline void initGridResource()
{
  Q_INIT_RESOURCE(QtnGridResources);
  Q_INIT_RESOURCE(QtnGridTranslations);
}

QTITAN_BEGIN_NAMESPACE

class Grid;
class GridViewBase;
class GridColumnBase;
class GridTableHeaderGraphic;
class GridViewPrimitiveBase;
class GridTabColumnPrimitiveBase;
class GridRowsPrimitiveAbstract;
class GridTableCellPrimitiveAbstract;
class GridFloatToolWidget;
class DragColumnWidget;
class ColumnArrowWidget;
class GridTabColumnPrimitive;
class GridFieldChooserProvider;
class GridViewOptions;
class EditorEventArgs;
class EditorValidationEventArgs;
class ColumnGroupArgs;
class GridEditor;
class GridEditorRepository;
class GridEditorStyleOption;
class GridZoomIndicatorGraphic;
class FilterDialog;
class FilterHistoryPopup;
class GridTableCellPrimitive;
class CellMouseClickHandler;
class GridRowLayoutItem;
class GridRowsLayoutEngine;
class GridTableColumn;
class GridDataTableColumn;
class EditorLinkEventArgs;
class GridTableColumnEditor;
class GridSummaryCellPrimitive;
class GridTableQuickRowButtonPrimitive;
class GridDataRowPrimitive;
class GridGroupRowPrimitive;
class GridSummaryRowPrimitive;
class GridSummaryLayoutEngine;
class GridColumnPrimitive;
class GridFooterSummaryPrimitive;
class GridTableDragColumnObject;
class GridViewSelectionHandler;

enum GridScrollStyle
{
    ScrollByItem,
    ScrollByPixel
};

enum ColumnMovePosition
{
    UndefinedPosition,
    PreviousColumnPosition,
    NextColumnPosition,
    PreviousRowPosition,
    NextRowPosition
};

enum IconApperance
{
    IconInvisible = 0,
    IconOnly,
    IconAlignLeft,
    IconAlignRight
};

enum GridNewRowPlace
{
    NewRowNone = 0,
    NewRowTop,
    NewRowBottom
};

enum GridGroupSummaryPlace
{
    GroupSummaryHide,
    GroupSummaryRow,
    GroupSummaryRowPlus,
    GroupSummaryFooter
};

enum GridGroupRowStyle
{
    GridGroupStandard,
    GridGroupOfficeOutlook
};

enum GridPreviewRowExpandStyle
{
    PreviewRowExpandKeepExpanded,
    PreviewRowExpandTextButton,
    PreviewRowExpandButton
};

class QTITAN_EXPORT GridHitInfo
{
public:
    enum Info {
        Unknown = 0,
        GroupPanel,
        FieldChooser,
        View,
        Column,
        TabColumn,
        ColumnFilterButton,
        Band,
        Cell,
        PreviewCell,
        Row,
        CellButton,
        GroupSummaryCell,
        FooterSummaryCell,
        GroupRow,
        GroupBranchButton,
    };
    GridHitInfo(Info info, GridViewBase* view, const QRect& rect, GridRow* row, int columnIndex);
    Info info() const;
    GridViewBase* view() const;
    const QRect& rect() const;
    GridRow* row() const;
    int columnIndex() const;
    QModelIndex modelIndex() const;
private:
    Info m_info;
    GridViewBase* m_view;
    QRect m_rect;
    GridCell m_cell;
    friend class Grid;
};

class QTITAN_EXPORT GridThemeManager
{
public:
    friend class Grid;
    enum IconKind
    {
        QuickButtonIcon,
        FocusRowIndicatorIcon,
        FilterToolButtonIcon,
        FilterToolButtonBoldIcon,
        ColumnMenuToolButtonIcon,
        SortIndicatorASCIcon,
        SortIndicatorDESCIcon,
        FrozenPinOnIcon,
        FrozenPinOffIcon,
        FrozenPlaceTopIcon,
        FrozenPlaceBottomIcon,
        DragDropBoxIcon,
        FocusRowEditIcon,
        FocusRowEditModifyIcon,
        FocusRowEditValidIcon,
        ZoomInIcon,
        ZoomOutIcon,
        NewRowIcon,
        TextButtonIcon,
        ClearButtonIcon,
        ChoiceButtonIcon,
        SettingsButtonIcon,
        SelectButtonIcon,
        FieldChooserIcon,
        GroupByBoxIcon,
        GroupByColumnIcon,
        AlignLeftIcon,
        AlignCenterIcon,
        AlignRightIcon,
        FixedLeftIcon,
        FixedRightIcon,
        PreviewRowButtonExpand,
        PreviewRowButtonCollapse
    };
    void setShadeColor(const QColor& color);
    const QColor& shadeColor() const;
    const QPalette& shadePalette() const;
    void setShadePalette(const QPalette& palette);
    const QPen& shadePen() const;
    const QPixmap& getIcon(IconKind kind, const QSize& size) const;
    void setIcon(IconKind kind, const QPixmap& pixmap);
    QPalette createGroupPalette(int depth);
    const QBrush& shadeBackgroundBrush() const;
    void setShadeBackgroundBrush(const QBrush& background);
    void setShadeBackground(const QPixmap& background);
    QGradient shadeGradient(const QRect& rect);
protected:
    GridThemeManager();
    void addGrid(Grid* grid);
    void removeGrid(Grid* grid);
    bool hasGrid() const;
    void updateViews();
private:
    QList<Grid *> m_grids;
    QPalette m_shadePalette;
    QPen m_shadePen;
    QBrush m_shadeBackground;
    typedef QHash<QSize, QPixmap> IconSizeMap;
    typedef QHash<QString, IconSizeMap> IconCache;
    typedef QHash<IconKind, QPixmap> CustomIconMap;
    IconCache m_iconCache;
    CustomIconMap m_customIconMap;
};


class QTITAN_EXPORT Grid: public GraphicControl
{
    Q_OBJECT
    Q_ENUMS(GridViewType)
    Q_PROPERTY(GridViewType viewType READ viewType WRITE setViewType)
    Q_PROPERTY(GridViewBase* rootView READ rootView)
public:
    enum GridViewType
    {
        UndefinedView = 0,
        TableView = 1,
        BandedTableView = 2,
        CardView = 3
    };
    Grid(QWidget* parent = 0);
    virtual ~Grid();
    GridViewType viewType() const;
    void setViewType(GridViewType type);
    template<typename ViewType> ViewType* view() const { return qobject_cast<ViewType *>(rootView()); }
    GridViewBase* rootView() const;
#ifndef QTN_NOUSE_XML_MODULE
    bool saveLayoutToFile(const QString& fileName);
    bool loadLayoutFromFile(const QString& fileName);
    bool saveLayoutToDevice(QIODevice* device);
    bool loadLayoutFromDevice(QIODevice* device);
#endif
    virtual QSize sizeHint() const;
    GridHitInfo hitInfo(const QPoint& pos);
    QList<GridHitInfo> hitInfoAll() const;
    static GridThemeManager* themeManager();
    static bool loadTranslation(const QString& country = QString()); //Format de_de, fr_fr, ru_ru
    static QString tr_compatible(const char *s, const char *c = 0);
protected:
    virtual GridViewBase* createView(GridViewType type);
    virtual void paintEvent(QPaintEvent *);
    void setRootView(GridViewBase* view);
    virtual GridNativeDragObject* createNativeDragDropObject(const QPoint& pos);
    virtual bool isPaintLocked() const;
    virtual void paletteChanged();
    virtual void fontChanged();
    virtual void styleChanged();
    GridViewBase* m_view;
    int m_viewType;
protected Q_SLOTS:
};

inline GridThemeManager* qtn_get_thememanager(QWidget* control) { return static_cast<Grid *>(control)->themeManager(); }

class QTITAN_EXPORT DragDropArgs: public BaseEventArgs
{
public:
    DragDropArgs();
    QMimeData* mimeData() const;
    void setMimeData(QMimeData* data);
    Qt::DropActions supportedDropActions() const;
    void setSupportedDropActions(Qt::DropActions actions);
    Qt::DropAction defaultDropAction() const;
    void setDefaultDropAction(Qt::DropAction action);
    bool isAccepted() const;
    void setAccepted(bool accepted);
private:
    QMimeData* m_mimeData;
    Qt::DropActions m_supportedDropActions;
    Qt::DropAction m_defaultDropAction;
    bool m_accepted;
};

class QTITAN_EXPORT DragArgs: public DragDropArgs
{
public:
    DragArgs();
    const QModelIndexList& indexes() const;
    void setIndexes(const QModelIndexList& indexes);
private:
    QModelIndexList m_indexes;
};

class QTITAN_EXPORT NewRowEventArgs: public BaseEventArgs
{
public:
    NewRowEventArgs();
    bool isModified() const;
    void setModified(bool modified);
private:
    bool m_modified;
};

class QTITAN_EXPORT ColumnGroupArgs: public BaseEventArgs
{
public:
    ColumnGroupArgs(GridColumnBase* column, int groupIndex);
    GridColumnBase* column() const;
    int groupIndex() const;
private:
    GridColumnBase* m_column;
    int m_groupIndex;
};

class QTITAN_EXPORT ErrorEventArgs: public BaseEventArgs
{
public:
    ErrorEventArgs(GridViewBase* view, const QString& error, const QString& description);
    virtual ~ErrorEventArgs();
    GridViewBase* view() const;
    const QString& error() const;
    const QString& description() const;
    void setDescription(const QString& description);
private:
    GridViewBase* m_view;
    QString m_error;
    QString m_description;
};

class QTITAN_EXPORT ContextMenuEventArgs: public BaseEventArgs
{
public:
    ContextMenuEventArgs(GridViewBase* view, QMenu* contextMenu, const GridHitInfo& info);
    virtual ~ContextMenuEventArgs();
    GridViewBase* view() const;
    QMenu* contextMenu() const;
    const GridHitInfo& hitInfo() const;
private:
    GridViewBase* m_view;
    QMenu* m_contextMenu;
    GridHitInfo m_hitInfo;
};

class QTITAN_EXPORT RowRemovingEventArgs : public BaseEventArgs
{
public:
    RowRemovingEventArgs(GridViewBase* view, const QList<int>& modelRows);
    QModelIndex index(int i) const;
    int count() const;
private:
    GridViewBase* m_view;
    const QList<int>& m_modelRows;
};

class QTITAN_EXPORT ColumnClickEventArgs : public BaseEventArgs
{
public:
    ColumnClickEventArgs(GridColumnBase* column);
    GridColumnBase* column() const;
private:
    GridColumnBase* m_column;
};

class QTITAN_EXPORT RowClickEventArgs : public BaseEventArgs
{
public:
    RowClickEventArgs(GridRow* row);
    GridRow* row() const;
private:
    GridRow* m_row;
};

class QTITAN_EXPORT CellClickEventArgs : public BaseEventArgs
{
public:
    CellClickEventArgs(GridCell* cell);
    virtual ~CellClickEventArgs();
    GridCell* cell() const;
private:
    GridCell* m_cell;
};

class QTITAN_EXPORT SummaryTextEventArgs : public BaseEventArgs
{
public:
    SummaryTextEventArgs(GridModelDataBinding* binding, GridSummaryType type, QVariant value, const QString& text);
    GridModelDataBinding* dataBinding() const;
    const QString& text() const;
    void setText(const QString& t);
    const QColor& textColor() const;
    void setTextColor(const QColor& color);
    GridSummaryType type() const;
    const QVariant& value() const;
private:
    GridModelDataBinding* m_binding;
    QString m_text;
    GridSummaryType m_type;
    QVariant m_value;
    QColor m_color;
};

class QTITAN_EXPORT SummaryGroupTextEventArgs : public SummaryTextEventArgs
{
public:
    SummaryGroupTextEventArgs(GridModelDataBinding* binding, GridSummaryType type, QVariant value, int modelGroupColumn, const QString& text);
    int modelGroupColumn() const;
private:
    int m_modelGroupColumn;
};

class QTITAN_EXPORT PreviewRowArgs : public BaseEventArgs
{
public:
    PreviewRowArgs(GridRow* row, QWidget* widget);
    GridRow* row() const;
    QModelIndex index() const;
    QWidget* widget() const;
    void setWidget(QWidget* widget);
private:
    GridRow* m_row;
    QWidget* m_widget;
};

enum GridActionType
{
    ExpandAllAction = 0,
    CollapseAllAction,
    SortNoneAction,
    SortAscendingAction,
    SortDescendingAction,
    HideColumnAction,
    GroupByColumnAction,
    GroupByBoxAction,
    FieldChooserAction,
    FooterAction,
    GroupFootersAction,
    AlignmentGroupAction,
    AlignLeftAction,
    AlignRightAction,
    AlignCenterAction,
    FilterAction,
    FindAction,
    FindNextAction,
    FindPreviousAction,
    ZoomInAction,
    ZoomOutAction,
    DeleteRowAction,
    BestFitAction,
    CopyAction,
    PasteAction
};

enum GridEditorActivationPolicyFlag
{
    NoPolicy = 0x0000,
    ClickNoFocused = 0x0001,
    ClickFocused = 0x0002,
    Click = ClickNoFocused | ClickFocused,
    MousePressNoFocused = 0x0004,
    MousePressFocused = 0x0008,
    MousePress = MousePressNoFocused | MousePressFocused,
    DblClickNoFocused = 0x0010,
    DblClickFocused = 0x0020,
    DblClick = DblClickNoFocused | DblClickFocused,
    KeyboardFocus = 0x0040,
    KeyPress = 0x0080,
    Enter = 0x0100,
    KeyPress_F2 = 0x0200, 
    EditPress = Enter | KeyPress_F2,
    EatingKeyEvents = 0x0400,
    EatingMouseEvents = 0x0800,
    SelectCurrentEvent = 0x1000,
    KeyPress_WithEating = KeyPress | EatingKeyEvents,
    AnyEvents = Click | DblClick | MousePress | KeyPress | EditPress | KeyboardFocus
};

Q_DECLARE_FLAGS(GridEditorActivationPolicy, GridEditorActivationPolicyFlag)

enum GridSelectionPolicy
{
    SelectIgnore,
    SelectSingleRow,
    SelectSingleCell,
    SelectMultiRow,
    SelectMultiCell
};

class GridRowLayoutItem
{
public:
    enum Type
    {
        Undefined,
        NewData,
        FrozenData,
        Data,
        Group,
        Summary
    };
    GridRowLayoutItem(GridRowsLayoutEngine* rowsLayout);
    virtual ~GridRowLayoutItem();
    Type type() const;
    GridViewBase* viewBase() const;
    void initialize(GridRow* row, Type type);
    bool isLocked() const;
    void setLocked(bool locked);
    bool isJustShowed() const;
    void setJustShowed(bool justShowed);
    void setOpacity(double value);
    double opacity() const;
    void setRowMask(const QRect& maskRect);
    void setRect(const QRect& rect, bool forceUpdate = false);
    const QRect& rect() const;
    GridRow* gridRow() const;
    void updateModelData();
    GridRowLayoutItem* nextRowLayoutItem() const;
    void setNextRowLayoutItem(GridRowLayoutItem* row);
    bool isRowFocused() const;
    bool isRowSelected() const;
    bool isCellSelected(int cellIndex) const;
    GridTableCellPrimitive* getCellGraphic(int cellIndex);

    GridTableQuickRowButtonPrimitive* quickRowButtonGP() const;
    GridDataRowPrimitive* dataRowGP() const;
    GridGroupRowPrimitive* groupRowGP() const;
    GridSummaryRowPrimitive* summaryRowGP() const;
    GridSummaryLayoutEngine* summarylayoutEngine() const;
    GridRowsLayoutEngine* layoutEngine() const { return m_rowsLayout; }
    void setParentGP(GraphicPrimitive* parent);
    QRect mapToSite() const;
    void checkMasked(GraphicPrimitive* rowPrimitive);
    void update();
    
    void updateCellButtons(const GridColumnPrimitive* columnPrimitive);
    void editorChanging(const GridColumnPrimitive* columnPrimitive, bool reset);

    const QRect& indentRect() const;
    virtual bool isFirstItem();
    virtual void create();
    virtual void updateSummaryLayoutParent();
protected:
    virtual void columnCreated(const GridDataTableColumn* column) = 0;
    virtual void columnDestroying(const GridDataTableColumn* column) = 0;

    void registrColumns();

    virtual void updateDataRowLayout(bool visible);
    virtual void updateGroupRowLayout(bool visible);
    virtual void updateGroupSummaryLayout(bool visible);

    void createQuickRowButtonGraphic();
    virtual void createDataRowGraphic() = 0;
    virtual void createGroupGraphic() = 0;
    virtual void createSummaryPanelGraphic() = 0;

    void setRectLayout();
    GridRowsLayoutEngine* m_rowsLayout;
    GridViewBase* m_view;
private:
    void updateGroupIndentRect();
    Type m_type;
    GridRow* m_gridRow;
    QRect m_rect;
    bool m_locked;
    bool m_justShowed;
    double m_opacity;
    GridRowLayoutItem* m_nextRowLayoutItem;
protected:
    QRect m_indentRect;
    GridTableQuickRowButtonPrimitive* m_quickRowButtonGP;
    GridDataRowPrimitive* m_dataRowGP;
    GridGroupRowPrimitive* m_groupRowGP;
    GridSummaryRowPrimitive* m_summaryRowGP;
    GridSummaryLayoutEngine* m_summarylayoutEngine;
    friend class GridRowsLayoutEngine;
};

class GridRowsLayoutEngine : public QObject
{
    Q_OBJECT
public:
    friend class GridRowLayoutItem;
    GridRowsLayoutEngine(GridViewBase* view, GraphicPrimitive* parent);
    virtual ~GridRowsLayoutEngine();

    virtual void beginUpdate(int columnsLength, int rowsLength, int offsetY, bool forceUpdateLayout);
    virtual void endUpdate();
    virtual bool isRowVisible(GridRow* row);

    virtual void editorChanging(const GridDataTableColumn* column, bool reset) = 0;
    virtual void updateCellButtons(const GridDataTableColumn* column) = 0;
    virtual GridRowLayoutItem* createItem() = 0;
    virtual bool appendNextGridRowRect(GridRow* gridRow, bool summary, GridRow::FrozenPlace frozenPlace, QRect& newRect) = 0;

    void updateSummaryLayoutParent();
    void columnCreated(const GridDataTableColumn* column);
    void columnDestroying(const GridDataTableColumn* column);
    bool isPrintLayout() const;
    void printer_setRowsPageSize(int w, int h);
    QList<GridRowLayoutItem *> printer_rows() const;
    void render(QPainter* painter, int& rowsLength);
public:
    void initialize();

    bool appendGridRow(GridRow* gridRow);
    bool appendFrozenGridRow(GridRow* gridRow, bool topPosition);
    bool appendNextGridRow(GridRow* gridRow, bool summary, GridRow::FrozenPlace frozenPlace);

    GraphicPrimitive* getRowsParent() const;
    GridRowLayoutItem* editLayoutItem() const;
    GridRowLayoutItem* newRowLayoutItem() const;
    GridRow* firstGridRow() const;
    GridRow* lastGridRow() const;
    GridRowLayoutItem* firstRowLayoutItem() const;
    GridRowLayoutItem* lastRowLayoutItem() const;

    GridTableCellPrimitive* getCellGraphic(GridRow* modelRow, int columnIndex);

    bool fastScrollEffect() const;

    void createVirtualRows(int rowsCount);
    void deleteVirtualRows();
    void resetVirtualRows();
    int getVirtualRowsCount() const;
    GridRowLayoutItem* getVirtualRowByIndex(int index);
    GridRowLayoutItem* findVirtualRow(GridRow* gridRow, bool symmaryRow);
    void setRowMask(const QRect& maskRect);
protected Q_SLOTS:
    void updateNewRowOpacity();
protected:
    GridViewBase* m_view;
    GraphicPrimitive* m_rowsParent;
    GridRowLayoutItem* m_newRowLayoutItem;

    GridRowLayoutItem* m_transparentRow;
    GridRowLayoutItem* m_focusLayoutItem;
    GridRowLayoutItem* m_firstRowLayoutItem;
    GridRowLayoutItem* m_lastRowLayoutItem;

    QRect m_maskRect;
    QVector<GridRowLayoutItem *> m_virtualRows;
    struct WaitingRowParam
    {
        WaitingRowParam() : rowType(GridRowLayoutItem::Undefined), gridRow(Q_NULL), focused(false), row(Q_NULL) {}
        QRect rect;
        GridRowLayoutItem::Type rowType;
        GridRow* gridRow;
        bool focused;
        GridRowLayoutItem* row;
    };

    typedef QVector<WaitingRowParam> WaitingRowParamList;
    WaitingRowParamList m_waiting;
    int m_waitingIndex;
    int m_viewColumnsLength;
    int m_viewRowsLength;
    int m_offsetY;
    bool m_forceUpdateLayout;
    QTimer* m_newRowAnimationTimer;
    GridRow* m_focusedGridRow;
    double m_transparentRowOpacity;
    bool m_transparentRowAnimationOrder;
    QRect m_currentRowRect, m_currentTopFrozenRowRect, m_currentBottomFrozenRowRect;
    bool m_printerLayout;
private:
};

enum GridViewState
{
    NoChanges = 0x0000,
    ColumnsChanged = 0x0001,
    ControllerChanged = 0x0002,
    RequestUpdateLayout = 0x0004,
    GroupExpanded = 0x0008,
    GroupCollapsed = 0x0010,
    ViewDestroying = 0x0020,
    RESERVEDFLAG0 = 0x0040,
    RESERVEDFLAG1 = 0x0080,
};

Q_DECLARE_FLAGS(GridViewStates, GridViewState)

enum BestFitMode
{
    FitToHeader,
    FitToViewContents,
    FitToContents
};

class QTITAN_EXPORT GridViewBase: public QObject
{
    Q_OBJECT
public:
    friend class Grid;
    friend class GridTableRowsGraphic;
    friend class GridColumnBase;
    friend class GridTableColumnBase;
    friend class GridDataTableColumn;
    friend class GridColumnPrimitive;
    friend class GridFieldChooserPrimitive;
    friend class QuickCustomizationPopup;
    friend class GridTableDragColumnObject;
    friend class GridViewOptions;
    friend class GridTableViewOptions;
    friend class GridEditorBase;
    friend class GridTabColumnPrimitive;
    friend class GridZoomIndicatorGraphic;
    friend class GridFilterPanelPrimitive;
    friend class GridEditorRepository;
    friend class GridSummaryLayoutEngine;
    friend class GridTableSummaryLayoutEngine;
    friend class GridCardSummaryLayoutEngine;
    friend class GridThemeManager;
    friend class GridFieldChooserColumnProvider;
    friend class GridFieldChooserCardColumnProvider;
    friend class GridViewPrimitiveBase;
    friend class GridRowsPrimitiveAbstract;
    friend class GridRowLayoutItem;
    friend class GridTableRowLayoutItem;
    friend class GridTableCellPrimitiveAbstract;
    friend class GridTableCellPrimitive;
    friend class CellMouseClickHandler;
    friend class GridViewSelectionObject;
    friend class GridTablePreviewRowPrimitive;
    friend class GridCellDragObject;
    friend class GridTableViewSelectionObject;
    friend class GridCardRowLayoutItem;
    friend class GridFilterColumnPopup;
    friend class GridColumnCustomizationBar;

    GridColumnBase* addColumn(const QString& modelColumnName, const QString& caption = QString());
    GridColumnBase* addColumn(int modelColumn, const QString& caption = QString());
    int getColumnCount() const;
    GridColumnBase* getColumn(int index) const;
    GridColumnBase* getColumnByModelColumn(int modelColumn) const;
    GridColumnBase* getColumnByModelColumnName(const QString& modelColumnName) const;
    GridColumnBase* getColumnByDataBinding(GridModelDataBinding* dataBinding) const;
    GridColumnBase* getColumnByCaption(const QString& caption) const;

    GridColumnBase* getPrevious(const GridColumnBase* column) const;
    GridColumnBase* getNext(const GridColumnBase* column) const;
    bool removeColumn(int index);

    int groupColumnCount() const;
    GridColumnBase* groupColumnByIndex(int groupIndex) const;
    void clearGrouping();
    GridModelDataBinding* getDataBinding(const GridColumnBase* columnBase) const;
    virtual void beginUpdate();
    virtual void endUpdate();
    void requestUpdateLayout(bool showZoomIndicator = false);
    Grid* grid() const;
    GridModelController* modelController() const;
    virtual bool showEditor(GridEditorActivationPolicyFlag policyFlag = NoPolicy);
    virtual bool closeEditor();
    virtual void hideEditor();
    virtual bool postEditor();
    bool validateEditor();
    bool isEditing() const;
    GridEditor* activeEditor() const;
    bool isModified() const;
    virtual bool showNewRowEditor();
    virtual bool closeNewRowEditor();
    virtual void hideNewRowEditor();
    bool isNewRowEditing() const;
    void print(QPrinter* printer);
    QAbstractItemModel* model() const;
    void setModel(QAbstractItemModel* model);
    GridFilter* filter() const;
    virtual void addColumns();
    virtual void removeColumns();
    GridRow* focusedRow();
    int focusedRowIndex();
    int focusedColumnIndex();
    bool setCellFocus(int rowIndex, int columnIndex, Qt::KeyboardModifiers modifiers = Qt::NoModifier, const GridEditorActivationPolicyFlag& activationFlag = NoPolicy);
    bool setFocusedRowIndex(int rowIndex, Qt::KeyboardModifiers modifiers = Qt::NoModifier, GridEditorActivationPolicyFlag flag = NoPolicy);
    bool setFocusedColumnIndex(int columnIndex, Qt::KeyboardModifiers modifiers = Qt::NoModifier, GridEditorActivationPolicyFlag flag = NoPolicy);
    GridRow* getRow(const QModelIndex& index) const;
    GridRow* getRow(int rowIndex) const;
    int getRowCount() const;
    bool removeRow(GridRow* row);
    bool removeRows(GridRow* row, int count);

    void selectRow(int rowIndex, const SelectionOperation& operation = Qtitan::Select);
    void selectRowRange(int firstRowIndex, int lastRowIndex, const SelectionOperation& operation = Qtitan::Select);
    void selectRange(int firstRowIndex, int lastRowIndex,
        int firstColumnIndex, int lastColumnIndex,
        const SelectionOperation& operation = Qtitan::Select);
    void selectAll();
    void deselectAll();
    GridSelection* selection() const;

    virtual void navigatePageUp(Qt::KeyboardModifiers modifiers = Qt::NoModifier);
    virtual void navigatePageDown(Qt::KeyboardModifiers modifiers = Qt::NoModifier);
    virtual void navigateTab(Qt::KeyboardModifiers modifiers = Qt::NoModifier);
    virtual void navigateBacktab(Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual void navigateUp(Qt::KeyboardModifiers modifiers = Qt::NoModifier) = 0;
    virtual void navigateDown(Qt::KeyboardModifiers modifiers = Qt::NoModifier) = 0;
    virtual void navigateLeft(Qt::KeyboardModifiers modifiers = Qt::NoModifier) = 0;
    virtual void navigateRight(Qt::KeyboardModifiers modifiers = Qt::NoModifier) = 0;

    void scrollToIndex(const QModelIndex& index, bool topPosition = true);
    bool isRowShowing(GridRow* row) const;
    void scrollToRow(GridRow* row, bool firstPosition = true);
    QScrollBar* verticalScrollBar() const;
    QScrollBar* horizontalScrollBar() const;
public:
    typedef QList<GridColumnBase *> GridColumns;
    GridViewBase(Grid* grid);
    virtual ~GridViewBase();
    GridViewOptions* optionsref() const;
    virtual QFont getColumnFont(const GridColumnBase* column) const;
    virtual QPen getColumnPen(const GridColumnBase* column) const;
    virtual int getColumnHeight(const GridColumnBase* column) const;
    const GridColumns& groups() const { return m_groups; }
    GridViewPrimitiveBase* layout() const;
    QHash<GridActionType, QAction*>& actions();
    virtual GridDataTableColumn* getFirstColumn() const;
    virtual GridDataTableColumn* getLastColumn() const;
    virtual GridDataTableColumn* getNextColumn(const GridDataTableColumn* anchor) const;
    virtual GridDataTableColumn* getPrevColumn(const GridDataTableColumn* anchor) const;
    bool isColumnVisible(const GridColumnBase* column) const;
    void showSummaryContextMenu(const QPoint& pos);
protected:
    virtual bool hasVisibleParent(const GridColumnBase* column) const;
    /*! \internal */
    virtual GridNativeDragObject* createNativeDragDropObject(const QPoint& pos) = 0;
    /*! \internal */
    virtual GridColumnBase* createColumn(int modelColumn, const QString& caption) = 0;
    /*! \internal */
    virtual GridViewOptions* createOptions() = 0;
    /*! \internal */
    virtual GridViewPrimitiveBase* createLayout() = 0;
    /*! \internal */
    virtual GridRowsPrimitiveAbstract* createRowsGraphic(GraphicPrimitive* parent) = 0;
    /*! \internal */
    virtual GridFooterSummaryPrimitive* createFooterSummaryPanel(GraphicPrimitive* parent) = 0;

    void doNavigatePrevColumn(Qt::KeyboardModifiers modifiers = Qt::NoModifier);
    void doNavigateNextColumn(Qt::KeyboardModifiers modifiers = Qt::NoModifier);
    void doNavigatePrevRow(Qt::KeyboardModifiers modifiers = Qt::NoModifier);
    void doNavigateNextRow(Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual void initialize();
    virtual void finalize();
    static void destroyView(GridViewBase* &view);
    virtual void updateControllerModel();

    GridEditorRepository* createEditorRepository(const GridDataTableColumn* column);
    GridRowsPrimitiveAbstract* rowsGraphic() const;
    virtual int getVisualIndex(const GridColumnBase* columnBase) const;
    virtual void setVisualIndex(const GridColumnBase* columnBase, int visualIndex);
    virtual int getColumnIndex(const GridColumnBase* columnBase) const;
    int getColumnSortIndex(const GridColumnBase* columnBase) const;
    void setColumnSortIndex(const GridColumnBase* columnBase, int sortIndex);
    SortOrder getColumnSortOrder(const GridColumnBase* columnBase) const;
    void setColumnSortOrder(GridColumnBase* columnBase, SortOrder order, bool caseSensitivity, bool localeAware);
    void clearSorting();
    int columnGroupIndex(const GridColumnBase* columnBase) const;
    void setColumnGroupIndex(GridColumnBase* columnBase, int groupIndex, bool caseSensitivity, bool localeAware);

    virtual int getColumnRowIndex(const GridDataTableColumn* column) const;
    virtual void columnVisibleChanged(GridColumnBase* columnBase, bool visible);
    virtual void raiseError(const QString& error, const QString& description);
    virtual void columnCreated(GridColumnBase* column);
    virtual void columnDestroying(GridColumnBase* column);
    virtual void columnWidthChanged(GridColumnBase* column);
    void updateBorder();

    virtual bool checkMove(const GridColumnBase* columnBase) const;
    virtual bool checkRemove(const GridColumnBase* columnBase) const;
    virtual bool checkGrouping(const GridColumnBase* columnBase) const;
 
    void raiseEditorCreated(GridEditor* editor);
    void raiseEditorDestroying(GridEditor* editor);
    void raiseEditorModifying(GridEditor* editor);
    void raiseEditorValidating(EditorValidationEventArgs* args);
    void raiseEditorEditModeChanged(GridEditor* editor);
    void createActions();
    void removeActions();
    void setActionIcons();
    int actualWidth() const;
protected:
#ifndef QTN_NOUSE_XML_MODULE
    bool saveLayoutToXML(QXmlStreamWriter* xmlwriter);
    bool loadLayoutFromXML(QXmlStreamReader* xmlreader);
    virtual bool saveLayoutToStream(QXmlStreamWriter* xmlwriter);
    virtual bool loadLayoutFromStream(QXmlStreamReader* xmlreader);
    virtual bool saveTableColumnLayout(const GridDataTableColumn* column, QXmlStreamWriter* xmlwriter);
    virtual bool loadTableColumnLayout(GridDataTableColumn* column, QXmlStreamReader* xmlreader);
    bool loadColumnBaseLayout(GridColumnBase* column, QXmlStreamReader* xmlreader);
    bool saveColumnBaseLayout(const GridColumnBase* column, QXmlStreamWriter* xmlwriter);
    bool isLayoutLoading() const;
#endif
    void addTextToMimeData(QMimeData * mimeData, const QModelIndexList& indexes);
    virtual void showRowOnScreen(int oldRowIndex, int newRowIndex);
    /*! \internal */
    virtual void showColumnOnScreen(int oldColumnIndex, int columnIndex) = 0;
    /*! \internal */
    virtual void bestFitForView(BestFitMode mode) = 0;
protected:
    virtual void focusInEvent(QFocusEvent *);
    virtual void focusOutEvent(QFocusEvent *);
    virtual bool event(QEvent* event);
protected:
    int getRowGroupIndent(GridRow* gridRow) const;
    virtual bool hasGroupingIndent(const GridColumnBase* column) const;
    void controllerChanged(GridControllerChanges changes);
    void changeGrouping(GridColumnBase* columnBase, int groupIndex, bool caseSensitivity, bool localeAware);
    bool isUpdating() const;
    bool checkActivationEditorPolicy(GridEditorActivationPolicyFlag policyFlag);
    bool showEditorInternal(GridEditorActivationPolicyFlag policyFlag);
    bool closeEditorInternal();
    void cancelEditing();
    void updateFocusedGP();
    void applyChanges(GridControllerChanges controllerChanges, GridViewStates viewStates);
    void markColumnsChanged();
    void editorChanging(const GridDataTableColumn* column, bool reset);
    void editorRepositoryChanged(GridEditorRepository* repository);
    void textAlignmentChanged(GridColumnBase* columnBase);
    QMenu* createSummaryContextMenu(QHash<GridSummaryType, QAction*>& summaryActions) const;
    void selectCurrentRanges(const SelectionRanges& ranges, const SelectionOperation& operation);
    void selectColumnRange(GridRow* firstRow, GridRow* lastRow, const QList<GridDataTableColumn *>& columns, const SelectionOperation& operation);
    void removeSelectedRows();
    virtual void getColumnLine(const GridColumnBase* column, GridColumns& retval) const;
    bool removeModelRows(QList<int>& modelRows);

    /*! \internal */
    struct PrinterColumnLayoutItem
    {
        int offset;
    };
    /*! \internal */
    virtual void printPage(GridRowsLayoutEngine* rowsLayout, const int rowsHeight, QPainter& painter, QPrinter* printer,
        const bool header, const bool footer, QList<PrinterColumnLayoutItem>& items, bool& isLastRowPrinted, bool& isFooterPrinted);
    /*! \internal */
    virtual bool printHeader(QPainter& painter, int& pageLength, int& itemIndex) = 0;

    GridColumns m_columnslist;
    GridColumns m_columnVisualIndexies;
    GridColumns m_groups;
    GridViewStates m_viewStates;
    GridViewStates m_contextStates;
    QHash<GridActionType, QAction*> m_actions;
    QList<GridFieldChooserProvider *> m_fieldProviders;
    struct EditContext
    {
        GridPersistentRow* persistentRow;
        GridEditor* editor;
        GridTableCellPrimitive* cellGP;
        bool changed;
        EditContext() : persistentRow(Q_NULL), editor(Q_NULL), cellGP(Q_NULL), changed(false) {}
    };
    EditContext m_editContext;
    CellMouseClickHandler* m_clickHandler;
    GridViewSelectionHandler* m_selectionHandler;
    bool m_isNewRowModify;
    
 
#ifndef QTN_NOUSE_XML_MODULE
    bool m_layoutLoading;
#endif
private Q_SLOTS:
    void slot_removeRow();
    void sortNone();
    void sortAscending();
    void sortDescending();
    void hideColumn();
    void groupByColumn();
    void alignLeftAct();
    void alignRightAct();
    void alignCenterAct();
    void groupByBox();
    void showHideFooter();
    void showHideGroupFooters();
public Q_SLOTS:
    void expandAll();
    void collapseAll();
    void printAreaRequested(QPrinter *printer);
    void zoomIn();
    void zoomOut();
    void printPreview();
    void showFieldChooser();
    void hideFieldChooser();
    bool isFieldChooserVisible() const;
    void showFilterPanel();
    void hideFilterPanel();
    void showFindPanel(bool filterActive = false);
    void hideFindPanel(bool cancel = false);
    bool isFindPanelVisible() const;
    void findNext();
    void findPrevious();
    void executeFilterDialog();
    void copy();
    void paste();
    void bestFit(BestFitMode mode = FitToHeader);
    void showContextMenu(const QPoint& pos);
private:
    void buildColumnFilters();
    void destroyColumnFilters();
    void destroyFilterDialog();

    void summaryNone(GridSummaryCellPrimitive* cell);
    void summarySum(GridSummaryCellPrimitive* cell);
    void summaryMin(GridSummaryCellPrimitive* cell);
    void summaryMax(GridSummaryCellPrimitive* cell);
    void summaryCount(GridSummaryCellPrimitive* cell);
    void summaryAvg(GridSummaryCellPrimitive* cell);
    Grid* m_grid;
    GridModelController* m_modelController;
    GridViewOptions* m_options;
    GridViewPrimitiveBase* m_viewPrimitive;
    FilterDialog* m_filterDlg;
    GraphicPrimitive* m_contextHit;
Q_SIGNALS:
    void columnClicked(ColumnClickEventArgs* args);
    void rowClicked(RowClickEventArgs* args);
    void rowDblClicked(RowClickEventArgs* args);
    void cellClicked(CellClickEventArgs* args);
    void cellDblClicked(CellClickEventArgs* args);
    void summaryCalculated();

    void contextMenu(ContextMenuEventArgs* args);
    void error(ErrorEventArgs* args);
    void columnsUpdated();
    void columnMoved(const GridColumnBase* column, int fromVisualIndex);

    void groupExpanding(GridModelGroup* group, bool& allow);
    void groupExpanded(GridModelGroup* group);
    void groupCollapsing(GridModelGroup* group, bool& allow);
    void groupCollapsed(GridModelGroup* group);

    void rowRemoving(RowRemovingEventArgs* args);

    void filterActivated();
    void filterDeactivated();

    void focusRowChanged(int oldRowIndex, int rowIndex);
    void focusColumnChanged(int oldColumnIndex, int columnIndex);

    void editorRepositoryCreated(const GridDataTableColumn* column, GridEditorRepository* repository);
    void editorCreated(GridEditor* editor);
    void editorDestroying(GridEditor* editor);
    void editorModifying(GridEditor* editor);
    void editorEditModeChanged(GridEditor* editor);
    void editorStarting(EditorEventArgs* args);
    void editorStarted(EditorEventArgs* args);
    void editorStoping(EditorEventArgs* args);
    void editorStoped(EditorEventArgs* args);
    void editorValidating(EditorValidationEventArgs* args);
    void relationConnecting(RelationEventArgs* args);
    void startDragDrop(DragArgs* args);
    void endDragDrop(DragArgs* args);
    void checkDragDrop(DragDropArgs* args);
    void dragDrop(DragDropArgs* args);
    void newRowEditorClicked(NewRowEventArgs* args);
    void startGrouping(ColumnGroupArgs* args);
    void groupingChanged();
    void sortingChanged();
    void selectionChanged(GridSelection* selection, GridSelection* oldSelection);
    void zoomFactorChanged(double factor);
    void zoomChanged(int value);

    void summaryFooterTextChanging(SummaryTextEventArgs* args);
    void summaryGroupTextChanging(SummaryGroupTextEventArgs* args);

    void previewLinkActivated(const GridRow* row, const QString& anchor);
    void columnLinkActivated(const GridColumnBase* column, const QString& anchor);
    void editorLinkActivated(EditorLinkEventArgs* args);

    void previewRowChanged(PreviewRowArgs* args);
};

class QTITAN_EXPORT GridColumnBase: public QObject
{
public:
    friend class GridColumnPrimitive;
    friend class DragColumnWidget;
    friend class GridViewBase;
    friend class GridTabColumnPrimitiveBase;
    friend class GridTableViewOptions;
    GridColumnBase(GridViewBase* view, const QString& caption);
    virtual ~GridColumnBase();
    int index() const;
    const QString& caption() const;
    void setCaption(const QString& caption);
    const QString& htmlCaption() const;
    void setHtmlCaption(const QString& caption);
    const QString& toolTip() const;
    void setToolTip(const QString& toolTip);
    const QFont& font() const;
    void setFont(const QFont& font);
    virtual bool isShowingFirst() const = 0;
    virtual bool isShowingLast() const = 0;
    Qt::Alignment textAlignment() const;
    void setTextAlignment(Qt::Alignment alignment);
    Qt::TextElideMode textElideMode() const;
    void setTextElideMode(Qt::TextElideMode mode);
    Qt::Orientation textOrientation() const;
    void setTextOrientation(Qt::Orientation orientation);
    void setIcon(const QIcon& icon);
    const QIcon& icon() const;
    IconApperance iconApperance() const;
    void setIconApperance(IconApperance apperance);
    bool isVisible() const;
    void setVisible(bool visible);
    const QColor& decorationColor() const;
    void setDecorationColor(const QColor& color);
    const QPen& pen() const;
    void setPen(const QPen& pen);
    GridViewBase* viewBase() const { return m_view; }
    QList<QAction *>& actionGroup();
    GridTableColumnEditor* columnEditor() const;
    void setColumnEditor(GridTableColumnEditor* editor);
protected:
    virtual void initialize();
    virtual void finalize();
    virtual void initStyleOption(QStyleOptionHeader& styleOption) = 0;
    virtual void click(QMouseEvent* e) = 0;
    virtual QString getToolTipText() const = 0;
    virtual GridTableDragColumnObject* createDragDropColumnObject(const QPoint& point, GraphicPrimitive* graphic) = 0;
    bool m_visible;
private:
    GridViewBase* m_view;
    QString m_caption;
    QString m_htmlCaption;
    QString m_toolTip;
    QIcon m_icon;
    QFont m_font;
    QPen m_pen;
    IconApperance m_iconApperance;
    Qt::Alignment m_textAlignment;
    Qt::TextElideMode m_textElideMode;
    Qt::Orientation m_textOrientation;
    QColor m_decorationColor;
    QList<QAction *> m_actionGroup;
    GridTableColumnEditor* m_columnEditor;
};

class GridViewAutoUpdater
{
public:
    GridViewAutoUpdater(GridViewBase* view)
        : m_view(view)
    {
        m_view->beginUpdate();
    }

    ~GridViewAutoUpdater()
    {
        m_view->endUpdate();
    }
private:
    GridViewBase* m_view;
};

class GridViewSelectionHandler
{
public:
    GridViewSelectionHandler(GridViewBase* view);
    const Qt::KeyboardModifiers& keyboardModifiers() const;
    void setKeyboardModifiers(Qt::KeyboardModifiers modifiers);
    GridEditorActivationPolicyFlag activationPolicy() const;
    void setActivationPolicy(GridEditorActivationPolicyFlag policy);
    void updateSelection(int rowIndex, int columnIndex, bool focusChanged);
    bool keepSelected() const;
    void setKeepSelected(bool keepSelected);
    bool isSelected(GridRow* row, int columnIndex);
private:
    GridViewBase* m_view;
    Qt::KeyboardModifiers m_keyboardModifiers;
    GridEditorActivationPolicyFlag m_activationPolicy;
    int m_shiftColumnIndex;
    int m_shiftRowIndex;
    bool m_shiftSelect;
    bool m_keepSelected;
};

class GridFieldChooserProvider
{
public:
    GridFieldChooserProvider(GridViewBase* view) : m_view(view) {}
    virtual ~GridFieldChooserProvider() {}
    GridViewBase* view() const { return m_view; }
public:
    virtual QString title() const = 0;
    virtual QString description() const = 0;
    virtual GridViewBase::GridColumns fields() const = 0;
private:
    GridViewBase* m_view;
};

class GridFieldChooserColumnProvider : public GridFieldChooserProvider
{
public:
    GridFieldChooserColumnProvider(GridViewBase* view);
    virtual QString title() const;
    virtual QString description() const;
    virtual GridViewBase::GridColumns fields() const;
private:
};

class GridFloatToolWidget: public QWidget
{
public:
    GridFloatToolWidget(QWidget* parent);
};

class DragColumnWidget: public GridFloatToolWidget
{
public:
    DragColumnWidget(QWidget* parent, GridColumnBase* columnBase, const QSize& size);
protected:
    virtual void paintEvent(QPaintEvent *);
private:
    GridColumnBase* m_columnBase;
};

class ColumnArrowWidget: public GridFloatToolWidget
{
public:
    ColumnArrowWidget(QWidget* parent, const QColor& shadeColor, ColumnMovePosition position);
protected:
    virtual void paintEvent(QPaintEvent *);
private:
    QImage m_arrow;
};

enum ScrollBarsMode
{
    ScrollNone,
    ScrollBoth,
    ScrollHorizontal, 
    ScrollVertical,
    ScrollAuto
};

enum GridLinesStyle
{
    LinesNone = 0,
    LinesBoth,
    LinesBoth2D,
    LinesHorizontal,
    LinesHorizontal2D,
    LinesVertical,
    LinesVertical2D
};

enum RowHighlightEffect
{
    RowFlashEffect,
    RowAlphaEffect
};

class QTITAN_EXPORT GridViewOptions: public QObject
{
    Q_OBJECT
public:
    GridViewOptions(GridViewBase* view);
    ScrollBarsMode scrollBars() const;
    void setScrollBars(ScrollBarsMode mode);
    bool groupsHeader() const;
    void setGroupsHeader(bool groupsHeader);
    GridScrollStyle scrollRowStyle() const;
    void setScrollRowStyle(GridScrollStyle style);
    bool columnAutoScroll() const;
    void setColumnAutoScroll(bool autoScroll);
    GridLinesStyle gridLines() const;
    void setGridLines(GridLinesStyle lines);
    QColor gridLineColor() const;
    void setGridLineColor(const QColor& color);
    int gridLineWidth() const;
    void setGridLineWidth(int width);
    const QPen& gridLinePen() const;
    void setGridLinePen(const QPen& pen);
    QBrush gridLineBrush() const;
    void setGridLineBrush(const QBrush& brush);
    const QFont& columnFont() const;
    void setColumnFont(const QFont& font);
    int columnHeight() const;
    void setColumnHeight(int height);
    const QPen& columnPen() const;
    void setColumnPen(const QPen& pen);
    int cellHeight() const;
    void setCellHeight(int height);
    int cellWidth() const;
    void setCellWidth(int width);
    const QPalette& cellPalette() const;
    void setCellPalette(const QPalette& palette);
    const QFont& cellFont() const;
    void setCellFont(const QFont& font);
    const QFont& groupRowFont() const;
    void setGroupRowFont(const QFont& font);
    bool isSortEnabled() const;
    void setSortEnabled(bool enabled);
    bool isGroupSortEnabled() const;
    void setGroupSortEnabled(bool enabled);
    bool modelDecoration() const;
    void setModelDecoration(bool enabled);
    double selectedDecorationOpacity() const;
    void setSelectedDecorationOpacity(double opacity);
    bool rubberBandSelection() const;
    void setRubberBandSelection(bool enabled);
    int borderWidth() const;
    void setBorderWidth(int width);
    const QMargins& borderMargins() const;
    void setBorderMargins(const QMargins& margins);
    const QColor& borderColor() const;
    void setBorderColor(const QColor& color);
    bool borderStyled() const;
    void setBorderStyled(bool styled);
    const QBrush& groupsHeaderBrush() const;
    void setGroupsHeaderBrush(const QBrush& brush);
    const QColor& groupsHeaderColor() const;
    void setGroupsHeaderColor(const QColor& color);
    const QColor& groupsHeaderTextColor() const;
    void setGroupsHeaderTextColor(const QColor& color);
    const QString& groupsHeaderText() const;
    void setGroupsHeaderText(const QString& text);
    const QColor& backgroundColor() const;
    void setBackgroundColor(const QColor& color);
    bool isTransparentBackground() const;
    void setTransparentBackground(bool transparent);
    bool isFilterEnabled() const;
    void setFilterEnabled(bool enabled);
    bool filterAutoHide() const;
    void setFilterAutoHide(bool autoHide);
    int filterPanelHeight() const;
    void setFilterPanelHeight(int height);
    const QString& findPanelPlaceholderText() const;
    void setFindPanelPlaceholderText(const QString& text);
    bool dragEnabled() const;
    void setDragEnabled(bool enabled);
    bool dropEnabled() const;
    void setDropEnabled(bool enabled);
    QAbstractItemView::DragDropMode dragDropMode() const;
    void setDragDropMode(QAbstractItemView::DragDropMode mode);
    bool zoomEnabled() const;
    void setZoomEnabled(bool enabled);
    double zoomFactor() const;
    void setZoomFactor(double factor);
    bool isZoomIndicatorActive() const;
    void setZoomIndicatorActive(bool active);
    bool isWindowsAirSupported() const;
    void setWindowsAirSupported(bool b);
    bool cellButtonAutoRaise() const;
    void setCellButtonAutoRaise(bool b);
    int cellButtonWidth() const;
    void setCellButtonWidth(int width);
    bool autoCreateColumns() const;
    void setAutoCreateColumns(bool autoCreate);
    Qt::Orientation viewOrientation() const;
    void setViewOrientation(Qt::Orientation orientation);
    bool isMainMenuDisabled() const;
    void setMainMenuDisabled(bool disabled);
    bool isSummaryMenuDisabled() const;
    void setSummaryMenuDisabled(bool disabled);
    bool isFieldChooserEnabled() const;
    void setFieldChooserEnabled(bool enabled);
    bool isFindEnabled() const;
    void setFindEnabled(bool enabled);
    const QStringList& findColumnList() const;
    void setFindColumnList(const QStringList& list);
    GridSelectionPolicy selectionPolicy() const;
    void setSelectionPolicy(GridSelectionPolicy policy);
    bool isMultiSelect() const;
    GridNewRowPlace newRowPlace() const;
    void setNewRowPlace(GridNewRowPlace place);
    const QString& newRowText() const;
    void setNewRowText(const QString& text);
    bool alternatingRowColors() const;
    void setAlternatingRowColors(bool alternating);
    bool focusFrameEnabled() const;
    void setFocusFrameEnabled(bool enabled);
    int groupRowHeight() const;
    void setGroupRowHeight(int height);
    GridGroupRowStyle groupRowStyle() const;
    void setGroupRowStyle(GridGroupRowStyle style);
    QPalette groupPalette(int depth) const;
    void setGroupPalette(int depth, const QPalette& palette);
    bool isFooterSummaryVisible() const;
    void setFooterSummaryVisible(bool visible);
    GridGroupSummaryPlace groupSummaryPlace() const;
    void setGroupSummaryPlace(GridGroupSummaryPlace place);
    bool isColumnHidingEnabled() const;
    void setColumnHidingEnabled(bool enabled);
    bool isColumnMovingEnabled() const;
    void setColumnMovingEnabled(bool enabled);
    bool isLastColumnMovingEnabled() const;
    void setLastColumnMovingEnabled(bool enabled);
    bool isColumnHidingOnGroupingEnabled() const;
    void setColumnHidingOnGroupingEnabled(bool enabled);
    bool isGroupingEnabled() const;
    void setGroupingEnabled(bool enabled);
    bool fastScrollEffect() const;
    void setFastScrollEffect(bool value);
    bool isFocusFollowsMouse() const;
    void setFocusFollowsMouse(bool enabled);
    bool isPreviewRowEnabled() const;
    void setPreviewRowEnabled(bool enabled);
    GridPreviewRowExpandStyle previewRowExpandStyle() const;
    void setPreviewRowExpandStyle(GridPreviewRowExpandStyle style);
    int previewRowHeight() const;
    void setPreviewRowHeight(int height);
    const QString& previewRowText() const;
    void setPreviewRowText(const QString& text);
    void setPreviewExpandButtonVisible(bool visible);
    RowHighlightEffect newRowHighlightEffect() const;
    void setNewRowHighlightEffect(RowHighlightEffect effect);
    int newRowFlashInterval() const;
    void setNewRowFlashInterval(int interval);
    double newRowOpacity() const;
    void setNewRowOpacity(double opcity);
    bool showFocusDecoration() const;
    void setShowFocusDecoration(bool value);
    bool rowAutoHeight() const;
    void setRowAutoHeight(bool autoHeight);
    bool columnHeaderHints() const;
    void setColumnHeaderHints(bool headerHints);
protected:
    GridViewBase* view() const;
    virtual void paletteChanged();
    virtual void fontChanged();
    virtual void styleChanged();
protected:
    GridViewBase* m_view;
    ScrollBarsMode m_scrollBarsMode;
    bool m_groupsHeader;
    GridScrollStyle m_scrollRowStyle;
    bool m_columnAutoScroll;
    GridLinesStyle m_gridLines;
    QPen m_gridLinePen;
    int m_columnHeight;
    QFont m_columnFont;
    QPen m_columnPen;
    int m_cellWidth;
    int m_cellHeight;
    QFont m_cellFont;
    QFont m_groupRowFont;
    bool m_isSortEnabled;
    bool m_isGroupSortEnabled;
    bool m_modelDecoration;
    double m_selectedDecorationOpacity;
    bool m_rubberBandSelection;
    QMargins m_borderMargins;
    QColor m_borderColor;
    bool m_borderStyled;
    QBrush m_groupsHeaderBrush;
    QColor m_groupsHeaderTextColor;
    QString m_groupsHeaderText;
    bool m_transparent;
    bool m_filterEnabled;
    int m_filterPanelHeight;
    QString m_findPanelPlaceholderText;
    bool m_dragEnabled;
    QAbstractItemView::DragDropMode m_dragDropMode;
    bool m_zoomEnabled;
    double m_zoomFactor;
    bool m_zoomIndicatorActive;
    bool m_windowsAirSupported;
    bool m_cellButtonAutoRaise;
    int m_cellButtonWidth;
    bool m_autoCreateColumns;
    bool m_mainMenuDisabled;
    bool m_summaryMenuDisabled;
    bool m_fieldChooserEnabled;
    bool m_findEnabled;
    QStringList m_findColumnList;
    GridSelectionPolicy m_selectionPolicy;
    GridNewRowPlace m_newRowPlace;
    QString m_newRowText;
    bool m_alternatingRowColors;
    bool m_focusFrameEnabled;
    int m_groupRowHeight;
    GridGroupRowStyle m_groupRowStyle;
    QHash<int, QPalette> m_groupPalette;
    bool m_footerSummaryVisible;
    GridGroupSummaryPlace m_groupSummaryPlace;
    bool m_columnHidingEnabled;
    bool m_columnMovingEnabled;
    bool m_lastColumnMovingEnabled;
    bool m_isColumnHidingOnGroupingEnabled;
    bool m_isGroupingEnabled;
    bool m_fastScrollEffect;
    bool m_focusFollowsMouse;
    bool m_previewRowEnabled;
    GridPreviewRowExpandStyle m_previewRowExpandStyle;
    int m_previewRowHeight;
    QString m_previewRowText;
    RowHighlightEffect m_newRowHighlightEffect;
    int m_newRowFlashInterval;
    double m_newRowOpacity;
    bool m_showFocusDecoration;
    bool m_rowAutoHeight;
    bool m_columnHeaderHints;
};

extern QSize get_column_sizeHint(const GridColumnBase* column, QStyle* style, const QFont& font, double scaleFactor, const QString& text = "Ag", QTextDocument* document = Q_NULL);
extern int get_column_width_by_font(const QFont& font, const QString& text);
extern void init_editor_option(GridViewBase* view, GridEditorStyleOption* option, GridModelDataBinding* dataBinding,
                                    GridRow* gridRow, int columnIndex,
                                    bool alternatingRowColors, bool isNewRow,
                                    bool isSelected,
                                    bool isEnabled,
                                    bool isFocused,
                                    const QRect& boundedRect,
                                    Qt::Alignment alignment);
extern QFont qtn_font_apply_scale(const QFont& font, double factor);
extern QSize qtn_size_apply_scale(const QSize& size, double factor);
extern ColumnMovePosition qtn_get_column_layout_zone(const GraphicPrimitive* gp, const QPoint& point, Qt::Orientation orientation, bool canRowChange);
extern ColumnMovePosition qtn_get_cell_layout_zone(const GridTableCellPrimitive* gp, const QPoint& point, Qt::Orientation orientation, bool rowSelectionPolicy);
extern void qtn_set_shadecolor(QImage& image, const QColor& color);
extern void qtn_do_update_fixed(bool verticalLayout, bool fixed, GraphicPrimitive* primitive);
extern QVariant qtn_pixmap_to_qvariant(QVariant::Type type, const QPixmap& pixmap);
extern void qtn_draw_path(QPainter& painter, QPainterPath& path, const QBrush& background, const QColor& frameColor);
extern QGradient qtn_create_gradient(const QColor& color, const QRect& rect);
extern bool qtn_check_native_border(Grid* grid);

extern GridTableCellPrimitive* query_cell_primitive(GraphicPrimitive* primitive);
extern GridColumnPrimitive* query_column_primitive(GraphicPrimitive* primitive);
extern GridTableCellPrimitiveAbstract* query_cell_abstract_primitive(GraphicPrimitive* primitive);
extern GridTabColumnPrimitiveBase* query_tab_column_primitive(GraphicPrimitive* primitive);

QTITAN_END_NAMESPACE

//Q_DECLARE_OPERATORS_FOR_FLAGS(Qtitan::IconApperance)

#endif //QTN_GRID_H

