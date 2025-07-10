import Vue from 'vue'
import App from './App.vue'
// element-ui
import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';
import axios from 'axios'

// axios
Vue.prototype.$axios = axios;

Vue.use(ElementUI);

// electron
const backendUrl = window.electronAPI && window.electronAPI.backendUrl ? window.electronAPI.backendUrl : ''
Vue.prototype.$backendUrl = backendUrl;
Vue.config.productionTip = false
new Vue({
  render: h => h(App),
}).$mount('#app')
