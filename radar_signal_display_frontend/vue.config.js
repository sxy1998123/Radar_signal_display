const path = require('path')
function resolve(dir) {
  return path.join(__dirname, dir)
}

module.exports = {
  runtimeCompiler: true,
  productionSourceMap: false,
  publicPath: process.env.NODE_ENV === 'production'
    ? './' // 生产环境使用相对路径
    : '/', // 开发环境保持默认
  outputDir: 'dist',
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
      preload: 'src/preload.js',
      builderOptions: {
        productName: 'RadarSignalDisplay',
        appId: 'com.example.radar-signal-display',
        asar: false,
        extraResources: [
          {
            from: 'src/preload.js', // 渲染进程预加载文件
            to: 'app/preload.js'
          },
          {
            from: 'src/background.js', // 入口文件
            to: 'app/index.js'
          }
        ],
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