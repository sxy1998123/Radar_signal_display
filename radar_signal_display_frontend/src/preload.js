const { contextBridge, ipcRenderer } = require('electron')

const port_arg = process.argv.find(arg => arg.startsWith('--port=') || arg.startsWith('-p='))
const port = port_arg ? parseInt(port_arg.split('=')[1]) : 5000
const backendUrl = `http://localhost:${port}`
// 安全暴露 API 给渲染进程（Electron 21+ 强制要求）
contextBridge.exposeInMainWorld('electronAPI', {
  platform: process.platform,
  backendUrl,
  openFolderDialog: (title, buttonLabel) => ipcRenderer.invoke('dialog:openFolder', title, buttonLabel),
  openFileDialog: (title, buttonLabel, filters) => ipcRenderer.invoke('dialog:openFileSelect', title, buttonLabel, filters),
  showDialog: (options) => ipcRenderer.invoke('dialog:show', options)
})

