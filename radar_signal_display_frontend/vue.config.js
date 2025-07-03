const path = require('path')
function resolve(dir) {
  return path.join(__dirname, dir)
}
const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  lintOnSave: 'warning',
  chainWebpack: config => {
    config.resolve.alias.set('@', resolve('src'))
  }
})
