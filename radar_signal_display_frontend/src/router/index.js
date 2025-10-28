import Vue from 'vue'
import VueRouter from 'vue-router'
import HomeView from '../views/HomeView.vue'
Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    redirect: '/home'
  },
  {
    path: '/home',
    name: 'home',
    component: HomeView,
    meta: {
      showHeader: false
    }
  },
  {
    // 信号生成及采集
    path: '/collect',
    name: 'collect',
    component: () => import('../views/CollectView.vue'),
    meta: {
      showHeader: true
    }
  },
  {
    // 信号处理
    path: '/handle',
    name: 'handle',
    component: () => import('../views/HandleView.vue'),
    meta: {
      showHeader: true
    }
  },
  {
    // 信号回放
    path: '/replay',
    name:'replay',
    component: () => import('../views/ReplayView.vue'),
    meta: {
      showHeader: true
    }
  }
  
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
