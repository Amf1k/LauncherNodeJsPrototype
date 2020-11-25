const { app, BrowserWindow, ipcMain } = require('electron')

let win = null;
ipcMain.on("inGameTimeChanged", (event, args) => {
    console.log(args)
    event.reply('inGameTimeChangedFromMain', 'args')
    win.webContents.send('inGameTimeChangedFromMain', args);
});

function createWindow () {
    win = new BrowserWindow({
      width: 800,
      height: 600,
      webPreferences: {
        nodeIntegration: true
      }
    })
  
    win.loadFile('index.html')
    win.webContents.openDevTools()

    const renderrer = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
          nodeIntegration: true
        }
      })
    
      renderrer.loadFile('renderrer.html')
      renderrer.webContents.openDevTools()
    
    // startLauncher();
  }


app.whenReady().then(createWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow() 
  }
})



