const path = require('path')
function resolve(dir) {
  return path.join(__dirname, dir)
}

module.exports = {
  runtimeCompiler: true,
  productionSourceMap: false,
  publicPath: '/',
  outputDir: 'frontend',
  lintOnSave: true,
  chainWebpack: (config) => {
    config.plugin('html').tap(args => {
      args[0].title = '雷达信号生成及展示'
      return args
    })

    config.resolve.alias
      .set('@$', resolve('src'))
      .set('@api', resolve('src/api'))
      .set('@assets', resolve('src/assets'))
      .set('@comp', resolve('src/components'))
      .set('@views', resolve('src/views'))

    config.module
      .rule('image')
      .test(/\.png$/)
      .use()
      .loader('url-loader')
      .options({
        esModule: false,
        outputPath: 'static/img'
      })

  },
  pluginOptions: {
    electronBuilder: {
      mainProcessFile: './electron/main/index.js',
      preloadFile: './electron/preload/preload.js',
      preload: './electron/preload/preload.js',
      builderOptions: {
        productName: 'ElectronDemo',
        appId: 'com.example.electrondemo',
        win: {
          icon: 'electron/resources/icon.ico',
          target: 'nsis'
        },
        files: [
          "**/*",
          "dist/**/*",
          {
            from: "electron/resources",
            to: "resources"  // 资源文件打包
          }
        ],
        // 关键：适配打包规则
        asar: true,
        nodeGypRebuild: false,
        buildDependenciesFromSource: false,
        extraResources: [
          {
            from: "dist",          // Vue 构建输出的目录
            to: "dist",            // 目标路径（位于 resources 下）
            filter: ["**/*"]
          }
        ]
      }
    }
  },
  devServer: {
    port: 8080,
    proxy: {
      '/api': {
        target: 'http://localhost:5000',
        ws: false,
        changeOrigin: true
      },
    }
  },
}