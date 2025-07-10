const { app, BrowserWindow, ipcMain, dialog, protocol } = require('electron')
const path = require('path')

// 禁用旧版安全警告（开发环境）
process.env.ELECTRON_DISABLE_SECURITY_WARNINGS = 'true'

// 窗口创建函数（适配 Electron 21）
function createWindow() {
    // 注册文件协议处理函数
    protocol.registerFileProtocol('app', (request, callback) => {
        const url = request.url.substr(6); // 去掉 'app://'
        const filePath = path.join(__dirname, url);
        callback({ path: filePath });
    });

    // 创建浏览器窗口
    const win = new BrowserWindow({
        width: 1920,
        height: 1080,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: true,          // 强制启用
            preload: path.join(__dirname, '/preload.js'),
            // devTools: false,                  // 禁用调试工具
            webSecurity: false,               // 禁用 web 安全限制
        },
        autoHideMenuBar: true
    })
    // 加载页面（区分开发/生产环境）
    if (process.env.WEBPACK_DEV_SERVER_URL) {
        win.loadURL(process.env.WEBPACK_DEV_SERVER_URL)
        // win.webContents.openDevTools()
    } else {
        win.webContents.contextIsolation = false
        win.loadFile(path.join(__dirname, 'index.html'))
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