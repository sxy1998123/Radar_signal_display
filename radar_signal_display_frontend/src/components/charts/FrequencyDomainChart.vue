<template>
    <div class="frequency-domain-chart" ref="root">
        <span class="chart-title">频域图</span>
        <div class="img-container">
            <el-image :src="src" :style="{ width: '100%', height: '100%' }">
                <div slot="error" class="image-slot">
                    <i class="el-icon-picture-outline"></i>
                </div>
            </el-image>
        </div>
        <div class="slider-container">
            <el-slider @change="handleSliderChange" :disabled="num_unit_max === 0" :min="0" :max="num_unit_max" v-model="num_unit" show-input></el-slider>
        </div>
    </div>
</template>

<script>
export default {
    data() {
        return {
            src_init: "",
            src: "",
            num_unit: 0,
            num_unit_max: 0
        };
    },
    methods: {
        updateImg() {
            const src = `${this.$backendUrl}${this.src_init}?num_unit=${this.num_unit}`;
            if (this.src !== src)
                this.src = src;
            else {
                // 强制刷新图片
                this.src = `${src}&t=${Date.now()}`
            }
        },
        updateImgConifg(url, num_units) {
            this.src_init = url;
            this.num_unit_max = num_units - 1; // 信号单元数 作为下标时需要减一
            if (this.num_unit >= this.num_unit_max) {
                this.num_unit = this.num_unit_max
            }
            this.updateImg()
        },
        handleSliderChange(value) {
            if (isNaN(value)) {
                console.log("slider value is NaN")
            } else {
                this.updateImg()
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

.frequency-domain-chart {
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

    .img-container {
        flex: 1;
        width: 100%;
    }

    .slider-container {
        width: 100%;
    }

    .el-icon-picture-outline {
        font-size: 40px;
    }
}
</style>
