<template>
  <div class="b-scan-chart" ref="root">
    <span class="chart-title">B-scan</span>
    <el-image :src="src" :style="{ width: '100%', height: '100%' }">
      <div slot="error" class="image-slot">
        <i class="el-icon-picture-outline"></i>
      </div>
    </el-image>
  </div>
</template>

<script>
export default {
  name: "BScanChart",
  data() {
    return {
      src: ""
    };
  },
  methods: {
    updateImgConifg(url) {
      const src = `${this.$backendUrl}${url}`;
      if (src !== this.src) {
        this.src = src;
      } else {
        // 强制刷新图片
        this.src = `${this.src}?t=${Date.now()}`;
      }
    }
  }
}
</script>

<style lang="less" scoped>
/deep/ .image-slot {
  display: flex;
  justify-content: center;
  align-items: center;
  color: #999;
  font-size: 20px;
  font-weight: bold;
  text-align: center;
  background-color: #fff;
  width: 100%;
  height: 100%;
}

.b-scan-chart {
  width: 100%;
  height: 100%;
  box-sizing: border-box;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;

  .chart-title {
    width: 100%;
    text-align: left;
    font-size: 20px;
    font-weight: bold;
    margin-bottom: 10px;
  }

  .el-icon-picture-outline {
    font-size: 40px;
  }
}
</style>
