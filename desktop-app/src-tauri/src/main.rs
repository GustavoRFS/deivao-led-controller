// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]
use tauri::{ SystemTray, SystemTrayEvent, Manager,SystemTrayMenu,CustomMenuItem};
use tauri_plugin_serialport;
// use serial2::SerialPort;

// Learn more about Tauri commands at https://tauri.app/v1/guides/features/command


fn main() {
  let quit = CustomMenuItem::new("quit".to_string(), "Fechar PC Led");
  let tray_menu = SystemTrayMenu::new()
  .add_item(quit);

  let system_tray = SystemTray::new().with_menu(tray_menu);
    tauri::Builder::default()
        .system_tray(system_tray)
        .plugin(tauri_plugin_serialport::init())
        .on_system_tray_event(|app, event| match event {
            SystemTrayEvent::DoubleClick {
              position: _,
              size: _,
              ..
            } => {
                app.get_window("main").unwrap().show().unwrap();
            }
            SystemTrayEvent::MenuItemClick { id, .. } => {
              match id.as_str() {
                "quit" => {
                  std::process::exit(0);
                }
                _ => {}
              }
            }
            _ => {}
          }).on_window_event(|event| match event.event() {
            tauri::WindowEvent::CloseRequested { api, .. } => {
              event.window().hide().unwrap();
              api.prevent_close();
            }
            _ => {}
          })
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
