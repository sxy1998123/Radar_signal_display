<template>
    <div class="a-scan-chart" ref="root">
        <div class="chart-container" ref="chartContainer"></div>
    </div>
</template>

<script>
import * as echarts from "echarts";
import { debounce } from 'lodash-es';
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
            chartContainer: null
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
                title: {
                    text: "A-Scan"
                },
                grid: {
                    containLabel: true // 防止数值标签超出图表画布范围
                },
                xAxis: {
                    type: "value",
                    splitLine: {
                        show: true
                    }
                },
                yAxis: {
                    type: "value",
                    splitLine: {
                        show: true
                    }
                },
                series: [
                    {
                        data: [],
                        type: "line",

                    }
                ],
                emphasis: {
                    focus: 'series', // 高亮显示
                    scale: true // 鼠标放上去时，放大显示
                }
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
.a-scan-chart {
    width: 100%;
    height: 100%;
    box-sizing: border-box;

    .chart-container {
        height: 200px;
        width: 200px;
    }
}
</style>
