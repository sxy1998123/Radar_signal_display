<template>
  <div class="layout">
    <div class="form">
      <el-card class="card-form">
        <el-form ref="form" :model="form_generate" label-width="120px" size="medium">
          <span class="form-title">信号生成：</span>
          <el-form-item label="信号类型" size="medium">
            <el-select v-model="form_generate.region" placeholder="请选择信号类型">
              <el-option label="高斯脉冲" value="1"></el-option>
              <el-option label="步进频连续波" value="2"></el-option>
              <el-option label="步进频脉冲串" value="3"></el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="起始频率">
            <el-input type="number" v-model="form_generate.date1"></el-input>
          </el-form-item>
          <el-form-item label="终止频率">
            <el-input type="number" v-model="form_generate.date2"></el-input>
          </el-form-item>
          <el-form-item label="频率点数">
            <el-input type="number" v-model="form_generate.date3"></el-input>
          </el-form-item>
          <el-form-item label="信号长度">
            <el-input type="number" v-model="form_generate.date3"></el-input>
          </el-form-item>
          <el-form-item label="单个频点时间">
            <el-input type="number" v-model="form_generate.desc"></el-input>
          </el-form-item>
          <el-form-item label="采样率">
            <el-input type="number" v-model="form_generate.desc"></el-input>
          </el-form-item>
          <div class="btns">
            <el-button type="primary" @click="onGenerateSignal">生成信号</el-button>
          </div>
        </el-form>
        <el-form ref="form" :model="form_handle" label-width="140px" size="medium">
          <span class="form-title">信号处理：</span>
          <el-form-item label="采集文件地址">
            <el-input type="file"></el-input>
          </el-form-item>
          <el-form-item label="参考信号文件地址">
            <el-input type="file"></el-input>
          </el-form-item>
          <el-form-item label="加窗处理">
            <el-select v-model="form_generate.region" placeholder="请选择信号类型">
              <el-option label="加窗" value="1"></el-option>
              <el-option label="汉明" value="2"></el-option>
              <el-option label="汉宁" value="3"></el-option>
              <el-option label="Kaiser" value="4"></el-option>
              <el-option label="矩形" value="5"></el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="其他处理" size="medium">
            <el-select v-model="form_generate.region" placeholder="请选择信号类型">
              <el-option label="高斯脉冲" value="1"></el-option>
              <el-option label="步进频连续波" value="2"></el-option>
              <el-option label="步进频脉冲串" value="3"></el-option>
            </el-select>
          </el-form-item>
          <div class="btns">
            <el-button type="primary" @click="onHandleSignal">信号处理</el-button>
          </div>
        </el-form>
      </el-card>
    </div>
    <div class="charts">
      <el-card class="card-charts">
        <div class="charts-container">
          <div class="chart-container">
            <TimeDomainChart></TimeDomainChart>
          </div>
          <div class="chart-container">
            <FrequencyDomainChart></FrequencyDomainChart>
          </div>
          <div class="chart-container">
            <AScanChart></AScanChart>
          </div>
          <div class="chart-container">
            <BScanChart></BScanChart>
          </div>
        </div>
      </el-card>
    </div>
  </div>
</template>

<script>
import TimeDomainChart from '@/components/charts/TimeDomainChart'
import FrequencyDomainChart from '@/components/charts/FrequencyDomainChart'
import AScanChart from '@/components/charts/AScanChart'
import BScanChart from '@/components/charts/BScanChart'
export default {
  name: 'layout',
  data() {
    return {
      form_generate: {
        name: '',
        region: '',
        date1: '',
        date2: '',
        delivery: false,
        type: [],
        resource: '',
        desc: ''
      },
      form_handle: {

      },
      radio1: '频点查看',
      slider1: 0
    }
  },
  components:{
    TimeDomainChart,
    FrequencyDomainChart,
    AScanChart,
    BScanChart
  },
  methods: {
    // 信号生成
    onGenerateSignal() {

    },
    // 信号处理
    onHandleSignal() {

    }
  }
}
</script>

<style lang="less" scoped>
// deep selector is used to override element-ui styles
// /deep/ .el-card__body {
//   padding: 0;
// }
.el-form {
  border: 1px solid #ccc;
  border-radius: 4px;
  padding: 12px;
  margin-bottom: 12px;
  text-align: left;

  .form-title {
    font-weight: 600;
    font-size: 18px;
    color: #303133;

  }

  .btns {
    text-align: right;
  }

  .el-form-item {
    &:first-of-type {
      margin-top: 12px;
    }
  }
}

.layout {
  width: 100%;
  height: 100%;
  display: flex;

  .form {
    height: 100%;

    .card-form {
      height: 100%;
      box-sizing: border-box;
    }
  }

  .charts {
    height: 100%;
    flex: 1;

    .card-charts {
      height: 100%;
      box-sizing: border-box;

      /deep/ .el-card__body {
        height: 100%;
        box-sizing: border-box;
      }

      .charts-container {
        width: 100%;
        height: 100%;
        display: flex;
        flex-wrap: wrap;
        justify-content: space-between;
        align-items: flex-start;

        .chart-container {
          width: 50%;
          height: 50%;
          box-sizing: border-box;
          border: 1px solid #ccc;
          border-radius: 4px;
          padding: 12px;
        }
      }
    }
  }
}
</style>
