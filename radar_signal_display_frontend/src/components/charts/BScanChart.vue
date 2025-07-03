<template>
  <div class="b-scan-chart" ref="root">
    <div class="chart-container" ref="chartContainer"></div>
  </div>
</template>

<script>
import * as echarts from "echarts";
import { debounce } from "lodash-es";
import option from "@/utils/demoHeatmap"
export default {
  name: "AScanChart",
  created() {
    window.addEventListener("resize", this.uiResize);
  },
  beforeDestroy() {
    window.removeEventListener("resize", this.uiResize);
  },
  mounted() {
    this.uiResize();
    this.initChart();
  },
  data() {
    return {
      chart: null,
      chartContainer: null,
      xData: [],
      yData: []
    };
  },
  methods: {
    initChart() {
      this.chartContainer = this.$refs.chartContainer;
      this.chart = echarts.init(this.chartContainer);
      this.chart.setOption(this.getOption());
    },
    getOption() {
      return option
    },
    uiResize: debounce(function () {
      console.log("resize");
      const { offsetWidth, offsetHeight } = this.$refs.root;
      this.chartContainer.style.width = `${offsetWidth - 1}px`;
      this.chartContainer.style.height = `${offsetHeight - 1}px`;
      this.chart && this.chart.resize();
    }, 50)
  }
}
</script>

<style lang="less" scoped>
.b-scan-chart {
  width: 100%;
  height: 100%;
  box-sizing: border-box;

  .chart-container {
    height: 200px;
    width: 200px;
  }
}
</style>
