<template>
  <div class="b-scan-chart" ref="root">
    <div class="chart-container" ref="chartContainer"></div>
  </div>
</template>

<script>
import * as echarts from "echarts";
import { debounce } from "lodash-es";
export default {
  name: "BScanChart",
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
      yData: [],
      data: []
    };
  },
  methods: {
    initChart() {
      this.chartContainer = this.$refs.chartContainer;
      this.chart = echarts.init(this.chartContainer);
      this.chart.setOption(this.getOption());
    },
    getOption() {
      return {
        tooltip: {},
        title: {
          text: "B-Scan Heatmap"
        },
        xAxis: {
          type: 'category',
          data: this.xData
        },
        yAxis: {
          type: 'category',
          data: this.yData
        },
        visualMap: {
          min: 0,
          max: 1,
          calculable: true,
          realtime: false,
          inRange: {
            color: [
              '#313695',
              '#4575b4',
              '#74add1',
              '#abd9e9',
              '#e0f3f8',
              '#ffffbf',
              '#fee090',
              '#fdae61',
              '#f46d43',
              '#d73027',
              '#a50026'
            ]
          }
        },
        series: [
          {
            name: 'Gaussian',
            type: 'heatmap',
            data: this.data,
            emphasis: {
              itemStyle: {
                borderColor: '#333',
                borderWidth: 1
              }
            },
            progressive: 1000,
            animation: false
          }
        ]
      }
    },
    uiResize: debounce(function () {
      // console.log("resize");
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
