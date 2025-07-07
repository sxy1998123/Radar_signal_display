<template>
  <div class="layout">
    <div class="form">
      <el-card class="card-form">
        <el-form ref="form" :model="form_generate" label-width="150px" size="medium">
          <span class="form-title">信号生成：</span>
          <el-form-item label="信号类型" size="medium">
            <el-select v-model="form_generate.signal_type" placeholder="请选择信号类型">
              <el-option label="高斯脉冲" value="1"></el-option>
              <el-option label="步进频连续波" value="2"></el-option>
              <el-option label="步进频脉冲串" value="3"></el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="采样率(Hz)">
            <el-input type="number" v-model="form_generate.fs"></el-input>
          </el-form-item>
          <el-form-item label="起始频率(Hz)">
            <el-input type="number" v-model="form_generate.fc_start"></el-input>
          </el-form-item>
          <el-form-item label="终止频率(Hz)">
            <el-input type="number" v-model="form_generate.fc_end"></el-input>
          </el-form-item>
          <el-form-item label="步进频率点数">
            <el-input type="number" v-model="form_generate.num_steps"></el-input>
          </el-form-item>
          <el-form-item label="同时生成I/Q信号">
            <el-switch v-model="form_generate.use_iq"></el-switch>
          </el-form-item>
          <el-form-item label="单个频点持续时间(s)">
            <el-input type="number" v-model="form_generate.T"></el-input>
          </el-form-item>
          <div class="btns">
            <el-button :loading="sigGeneralbtnLoading" type="primary" @click="onGenerateSignal">生成并保存信号</el-button>
          </div>
        </el-form>
        <el-form ref="form" :model="form_handle" label-width="140px" size="medium">
          <span class="form-title">信号处理：</span>
          <el-form-item label="采集文件夹地址">
            <el-input type="textarea" v-model="form_handle.collectionSigFolder" :readonly="true"></el-input>
            <el-button type="text" @click="selectCollectSigFolder">选择文件夹</el-button>
          </el-form-item>
          <el-form-item label="参考信号文件地址">
            <el-input type="textarea" v-model="form_handle.referenceSigFolder" :readonly="true"></el-input>
            <el-button type="text" @click="selectReferenceSigFolder">选择文件夹</el-button>
          </el-form-item>
          <el-form-item label="加窗处理">
            <el-select v-model="form_generate.window_type" placeholder="请选择信号类型">
              <el-option label="加窗" value="1"></el-option>
              <el-option label="汉明" value="2"></el-option>
              <el-option label="汉宁" value="3"></el-option>
              <el-option label="Kaiser" value="4"></el-option>
              <el-option label="矩形" value="5"></el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="其他处理" size="medium">
            <el-select v-model="form_generate.other_process" placeholder="请选择信号类型">
              <el-option label="高斯脉冲" value="1"></el-option>
              <el-option label="步进频连续波" value="2"></el-option>
              <el-option label="步进频脉冲串" value="3"></el-option>
            </el-select>
          </el-form-item>
          <div class="btns">
            <el-button :loading="sigHandlebtnLoading" type="primary" @click="onHandleSignal">信号处理</el-button>
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
/***** 图表组件引入start *****/
import TimeDomainChart from '@/components/charts/TimeDomainChart'
import FrequencyDomainChart from '@/components/charts/FrequencyDomainChart'
import AScanChart from '@/components/charts/AScanChart'
import BScanChart from '@/components/charts/BScanChart'
/***** 图表组件引入end ******/
import services from '@/services/signal'

export default {
  name: 'layout',
  data() {
    return {
      form_generate: {
        signal_type: "1", // 信号类型
        fs: 3e9, // 采样率
        fc_start: 1e9, // 起始频率
        fc_end: 1e9, // 终止频率
        num_steps: 10, // 步进频率点数
        use_iq: false, // 是否生成I/Q向信号
        T: 5e-7
      },
      form_handle: {
        collectionSigFolder: '', // 采集信号文件夹
        referenceSigFolder: '', // 参考信号文件夹
        window_type: "1", // 加窗类型
        other_process: "1" // 其他处理类型
      },
      sigGeneralbtnLoading: false, // 信号生成按钮loading状态
      sigHandlebtnLoading: false, // 信号处理按钮loading状态

      radio1: '频点查看',
      slider1: 0
    }
  },
  components: {
    TimeDomainChart,
    FrequencyDomainChart,
    AScanChart,
    BScanChart
  },
  methods: {
    async showFolderDialog(title, buttonLabel) {
      const path = await window.electronAPI.openFolderDialog(title, buttonLabel)
      return path
    },
    // 选择采集信号文件夹
    async selectCollectSigFolder() {
      const path = await this.showFolderDialog("选择采集信号文件夹", "选择文件夹")
      this.form_handle.collectionSigFolder = path
    },
    // 选择参考信号文件夹
    async selectReferenceSigFolder() {
      const path = await this.showFolderDialog("选择参考信号文件夹", "选择文件夹")
      this.form_handle.referenceSigFolder = path
    },
    // 信号生成
    async onGenerateSignal() {
      // todo 弹出文件夹选择框
      const save_dir = await this.showFolderDialog("选择信号保存位置", "保存")
      console.log(save_dir)
      if (!save_dir) {
        return false
      }
      // todo 表单校验

      this.sigGeneralbtnLoading = true
      // todo 上传参数及保存位置到服务端
      const {
        signal_type,
        fs,
        fc_start,
        fc_end,
        num_steps,
        use_iq,
        T,
      } = this.form_generate
      const data = {
        signal_type: Number(signal_type),
        fs: Number(fs),
        fc_start: Number(fc_start),
        fc_end: Number(fc_end),
        num_steps: Number(num_steps),
        use_iq: Boolean(use_iq),
        T: Number(T),
        save_dir
      }
      services.generateSignal(data)
        .then(resp => {
          this.$message.success('信号生成并保存成功')
          console.log(resp)
        }).catch(err => {
          this.$message.error('信号生成失败')
          console.log(err)
        }).finally(() => {
          this.sigHandlebtnLoading = false
        })
    },
    // 信号处理
    onHandleSignal() {
      const {
        collectionSigFolder,
        referenceSigFolder,
        window_type,
        other_process
      } = this.form_handle
      // todo 表单校验
      console.log(collectionSigFolder, referenceSigFolder, window_type, other_process);
      // todo 调用接口
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
