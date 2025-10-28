<template>
  <div class="layout">
    <el-header v-if="showHeader" :height="`${headerHeight}px`">
      <el-button @click="$router.go(-1)" type="primary" icon="el-icon-arrow-left">返回</el-button>
    </el-header>
    <div class="main" :style="`height:calc(100% - ${headerHeight}px)`">
      <router-view></router-view>
    </div>
  </div>
</template>

<script>
export default {
  name: "Layout",
  data() {
    return {
      headerHeight: 60,
      showHeader: true
    }
  },
  created() {
    this.showHeader = this.$route.meta.showHeader || false
  },
  watch: {
    $route()  {
      this.showHeader = this.$route.meta.showHeader || false
      console.log(this.$route)
    }
  },
}
</script>

<style lang="less" scoped>
.layout {
  height: 100%;
  .el-header {
    display: flex;
    align-items: center;
    border-bottom: 1px solid #dcdfe6;
  }
}
</style>
