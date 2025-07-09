const { contextBridge, ipcRenderer } = require('electron')

// 安全暴露 API 给渲染进程（Electron 21+ 强制要求）
contextBridge.exposeInMainWorld('electronAPI', {
  platform: process.platform,
  openFolderDialog: (title, buttonLabel) => ipcRenderer.invoke('dialog:openFolder', title, buttonLabel),
  openFileDialog: (title, buttonLabel, filters) => ipcRenderer.invoke('dialog:openFileSelect', title, buttonLabel, filters),
  showDialog: (options) => ipcRenderer.invoke('dialog:show', options)
})

