const { app, BrowserWindow, ipcMain, dialog } = require('electron')
const path = require('path')

// 禁用旧版安全警告（开发环境）
process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = 'true'

// 窗口创建函数（适配 Electron 21）
function createWindow() {
    const win = new BrowserWindow({
        width: 1920,
        height: 1080,
        webPreferences: {
            nodeIntegration: false,          // 必须禁用
            contextIsolation: true,          // 强制启用
            preload: path.join(__dirname, '/preload.js'),
            // devTools: false,                  // 禁用调试工具
        },
        autoHideMenuBar: true
    })
    // 加载页面（区分开发/生产环境）
    if (process.env.WEBPACK_DEV_SERVER_URL) {
        win.loadURL(process.env.WEBPACK_DEV_SERVER_URL)
        // win.webContents.openDevTools()
    } else {
        win.webContents.contextIsolation = false
        win.loadFile(path.join(__dirname, '..', 'dist', 'index.html'))
    }
}

ipcMain.handle('dialog:openFolder', async (event, title = "选择文件夹", buttonLabel = "选择此文件夹") => {
    const { canceled, filePaths } = await dialog.showOpenDialog({
        properties: ['openDirectory', 'createDirectory'],
        title: title,
        buttonLabel: buttonLabel
    })

    if (!canceled) {
        return filePaths[0]
    } else {
        return null
    }
})

ipcMain.handle('dialog:openFileSelect', async (event, title = "选择文件", buttonLabel = "选择此文件", filters = []) => {
    const { canceled, filePaths } = await dialog.showOpenDialog({
        properties: ['openFile'],
        title: title,
        buttonLabel: buttonLabel,
        filters: filters
    })

    if (!canceled) {
        return filePaths[0]
    } else {
        return null
    }
})



// 生命周期管理
app.whenReady().then(createWindow)
app.on('window-all-closed', () => process.platform !== 'darwin' && app.quit())
app.on('activate', () => BrowserWindow.getAllWindows().length === 0 && createWindow())