// Aseprite
// Copyright (C) 2001-2016  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#pragma once

#include "app/app_brushes.h"
#include "base/debug.h"
#include "base/signal.h"
#include "base/unique_ptr.h"
#include "doc/pixel_format.h"

#include <string>
#include <vector>

namespace doc {
  class Layer;
}

namespace ui {
  class UISystem;
}

namespace app {

  class AppOptions;
  class ContextBar;
  class Document;
  class DocumentExporter;
  class INotificationDelegate;
  class InputChain;
  class LegacyModules;
  class LoggerModule;
  class MainWindow;
  class Preferences;
  class RecentFiles;
  class Timeline;
  class Workspace;

  namespace tools {
    class ActiveToolManager;
    class Tool;
    class ToolBox;
  }

  using namespace doc;

  class App {
  public:
    App();
    ~App();

    static App* instance() { return m_instance; }

    // Returns true if Aseprite is running with GUI available.
    bool isGui() const { return m_isGui; }

    // Returns true if the application is running in portable mode.
    bool isPortable();

    // Runs the Aseprite application. In GUI mode it's the top-level
    // window, in console/scripting it just runs the specified
    // scripts.
    void initialize(const AppOptions& options);
    void run();

    tools::ToolBox* toolBox() const;
    tools::Tool* activeTool() const;
    tools::ActiveToolManager* activeToolManager() const;
    RecentFiles* recentFiles() const;
    MainWindow* mainWindow() const { return m_mainWindow; }
    Workspace* workspace() const;
    ContextBar* contextBar() const;
    Timeline* timeline() const;
    Preferences& preferences() const;

    AppBrushes& brushes() {
      ASSERT(m_brushes.get());
      return *m_brushes;
    }

    void showNotification(INotificationDelegate* del);
    void updateDisplayTitleBar();

    InputChain& inputChain();

    // App Signals
    base::Signal0<void> Exit;
    base::Signal0<void> PaletteChange;

  private:
    typedef std::vector<std::string> FileList;
    class CoreModules;
    class Modules;

    static App* m_instance;

    base::UniquePtr<ui::UISystem> m_uiSystem;
    CoreModules* m_coreModules;
    Modules* m_modules;
    LegacyModules* m_legacy;
    bool m_isGui;
    bool m_isShell;
    base::UniquePtr<MainWindow> m_mainWindow;
    FileList m_files;
    base::UniquePtr<DocumentExporter> m_exporter;
    base::UniquePtr<AppBrushes> m_brushes;
  };

  void app_refresh_screen();
  void app_rebuild_documents_tabs();
  PixelFormat app_get_current_pixel_format();
  void app_default_statusbar_message();
  int app_get_color_to_clear_layer(doc::Layer* layer);

} // namespace app
