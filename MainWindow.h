#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <lvgl/src/lv_core/lv_obj.h>

#include <QListWidgetItem>
#include <QMainWindow>
#include <QSlider>

class LVGLSimulator;
class LVGLObject;
class LVGLProject;
class LVGLImageData;
class LVGLFontData;
class QSortFilterProxyModel;
class LVGLWidgetModel;
class LVGLWidgetModelDisplay;
class LVGLWidgetModelInput;
class LVGLKeyPressEventFilter;
class LVGLCore;
class ListDelegate;
class LVGLWidget;
class QUndoGroup;
class LVGLTabWidget;
class LVGLProcessBar;
class LVGLExportThread;
class LVGLAutoSaveThread;
class QTranslator;
class LVGLConfig;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  LVGLSimulator *simulator() const;

  QHash<QString, const LVGLWidget *> &getW() { return m_widgets; }
  QHash<QString, const LVGLWidget *> &getWDP() { return m_widgetsDisplayW; }
  QHash<QString, const LVGLWidget *> &getWIP() { return m_widgetsInputW; }
  QMap<int, lv_obj_t *> &getCodeMap() { return m_codemap; }
  QTabWidget *getTabW();
  inline void settranslator(QTranslator *t) { m_translator = t; }
  void setconfig(LVGLConfig *config);

 signals:
  void startExport(const QStringList &list);
  void stopExport();

  void startAutoSave(int State);
  void stopAutoSave();
 private slots:
  void onETSuccessful();
  void onETFailed();
  void updateProperty();
  void setCurrentObject(LVGLObject *obj);
  void styleChanged();
  void loadRecent();
  void openNewProject();

  void on_action_load_triggered();
  void on_action_save_triggered();
  void on_combo_style_currentIndexChanged(int index);
  void on_action_export_c_triggered();
  void on_button_add_image_clicked();
  void on_button_remove_image_clicked();
  void on_list_images_customContextMenuRequested(const QPoint &pos);
  void on_list_images_currentItemChanged(QListWidgetItem *current,
                                         QListWidgetItem *previous);
  void on_button_add_font_clicked();
  void on_button_remove_font_clicked();
  void on_list_fonts_customContextMenuRequested(const QPoint &pos);
  void on_list_fonts_currentItemChanged(QListWidgetItem *current,
                                        QListWidgetItem *previous);
  void on_action_run_toggled(bool run);
  void on_combo_state_currentIndexChanged(int index);
  void tabChanged(int index);
  void onObjPressed(LVGLObject *obj);
  void ontabclose(int index);
  void on_eaction_export_triggered();
  void on_actionOFF_triggered();
  void on_action1_Min_triggered();
  void on_action2_Min_triggered();
  void on_action3_Min_triggered();
  void on_action4_Min_triggered();
  void on_action5_Min_triggered();
  void on_action6_Min_triggered();
  void on_action7_Min_triggered();
  void on_action8_Min_triggered();
  void on_action9_Min_triggered();
  void on_action10_Min_triggered();

  void on_actionAbsolute_path_triggered();

  void on_actionRelative_path_triggered();

  void on_actionHierarchical_export_triggered();

  void on_actionHomologous_export_triggered();

  void on_actionEnglish_triggered();

  void on_actionSimplified_Chinese_triggered();

 protected:
  void showEvent(QShowEvent *event) override;
  void keyPressEvent(QKeyEvent *e) override;

 private:
  QPixmap getPix(int type);
  void initNewWidgets();
  void initcodemap();
  void initConnect();
  void initProp();
  void initStyle();
  void initThreads();
  void addWidget(LVGLWidget *w);
  void addWidgetDisplayW(LVGLWidget *w);
  void addWidgetInputW(LVGLWidget *w);

  void initlvglConnect();
  void revlvglConnect();
  void addImage(LVGLImageData *img, QString name);
  void updateImages();

  void addFont(LVGLFontData *font, QString name);
  void updateFonts();

  void updateRecentActionList();
  void adjustForCurrentFile(const QString &fileName);
  void loadProject(const QString &fileName);
  void setEnableBuilder(bool enable);
  void updateItemDelegate();
  void setUndoStack();
  void setAllModelNull();
  void setAutoSaveChecked(int state);
  void setSelectLanguage(int index);

 private:
  Ui::MainWindow *m_ui;
  QSlider *m_zoom_slider;
  LVGLProject *m_project;

  class LVGLPropertyModel *m_propertyModel;
  class LVGLStyleModel *m_styleModel;
  class LVGLObjectModel *m_objectModel;

  QList<QAction *> m_recentFileActionList;
  const int m_maxFileNr;
  QList<lv_state_t> m_liststate;
  LVGLSimulator *m_curSimulation;
  QSortFilterProxyModel *m_proxyModel;
  QSortFilterProxyModel *m_proxyModelDPW;
  QSortFilterProxyModel *m_proxyModelIPW;
  LVGLWidgetModel *m_widgetModel;
  LVGLWidgetModelDisplay *m_widgetModelDPW;
  LVGLWidgetModelInput *m_widgetModelIPW;
  LVGLKeyPressEventFilter *m_filter;
  ListDelegate *m_ld1;
  ListDelegate *m_ld2;
  ListDelegate *m_ld3;

  int m_curTabWIndex;
  bool m_frun;

  QMap<int, lv_obj_t *> m_codemap;
  QHash<QString, const LVGLWidget *> m_widgets;
  QHash<QString, const LVGLWidget *> m_widgetsDisplayW;
  QHash<QString, const LVGLWidget *> m_widgetsInputW;
  bool m_isrun;
  QUndoGroup *m_undoGroup;
  int m_lastindex;
  QMap<LVGLTabWidget *, QString> m_tabFile;
  LVGLProcessBar *m_pcBar;
  LVGLExportThread *m_exportThread;
  QThread *m_etThread;
  LVGLAutoSaveThread *m_autosaveThread;
  QThread *m_asThread;
  QTranslator *m_translator;
  LVGLConfig *m_config;
};
#endif  // MAINWINDOW_H
