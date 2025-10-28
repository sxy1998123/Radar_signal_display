<template>
  <div class="home">
    <div class="routes">
      <div class="route-box" @click="handleJumpTo('collect')">
        <div class="title">信号生成采集</div>
      </div>
      <div class="route-box" @click="handleJumpTo('handle')">
        <div class="title">信号处理分析</div>
      </div>
      <div class="route-box" @click="handleJumpTo('replay')">
        <div class="title">数据回放</div>
      </div>
    </div>
  </div>
</template>

<script>

export default {
  name: 'HomeView',
  components: {

  },
  methods: {
    handleJumpTo(routeName) {
      console.log(`跳转到${routeName}`)
      this.$router.push({
        name: routeName
      })
    }
  }
}
</script>

<style lang="less">
.home{
  .routes{
    display: flex;
    flex-wrap: wrap;
    padding: 20px;
    gap: 40px;
    > .route-box{
      width: 200px;
      height: 200px;
      padding: 12px;
      background-color: #3d686e;
      border-radius: 4px;


      >.title{
        font-weight: bold;
        font-size: 22px;
        color: #f2f2f2;
      }
      cursor: pointer;
      &:hover{
        background-color: #4c7e80;
      }
    }
  }
}
</style>
