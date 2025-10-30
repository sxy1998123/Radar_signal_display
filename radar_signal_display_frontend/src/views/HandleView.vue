<template>
  <div class="handle">
    <div class="form">
      <el-card class="card-form">
        <el-form ref="form" :model="form_handle" label-width="180px" size="medium" :rules="form_handle_rules">
          <span class="form-title">信号处理：</span>
          <el-form-item label="采集文件夹地址" prop="collectionSigFolder">
            <el-input type="textarea" v-model="form_handle.collectionSigFolder" :readonly="true"></el-input>
            <el-button type="text" @click="selectCollectSigFolder">选择文件夹</el-button>
          </el-form-item>
          <el-form-item label="参考信号文件地址" prop="referenceSig_I">
            <div>
              <el-input type="textarea" v-model="form_handle.referenceSig_I" :readonly="true"></el-input>
              <el-button type="text" @click="selectReferenceSigFile_I">选择I相参考信号文件</el-button>
            </div>
          </el-form-item>
          <el-form-item label="参考信号文件地址" prop="referenceSig_Q">
            <div>
              <el-input type="textarea" v-model="form_handle.referenceSig_Q" :readonly="true"></el-input>
              <el-button type="text" @click="selectReferenceSigFile_Q">选择Q相参考信号文件</el-button>
            </div>
          </el-form-item>

          <el-form-item label="加窗处理" prop="window_type">
            <el-select v-model="form_handle.window_type" placeholder="请选择信号类型">
              <el-option label="加窗" value="1"></el-option>
              <el-option label="汉明" value="2"></el-option>
              <el-option label="汉宁" value="3"></el-option>
              <el-option label="Kaiser" value="4"></el-option>
              <el-option label="矩形" value="5"></el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="其他处理" size="medium" prop="other_process">
            <el-select v-model="form_handle.other_process" placeholder="请选择信号类型">
              <el-option label="高斯脉冲" value="1"></el-option>
              <el-option label="步进频连续波" value="2"></el-option>
              <el-option label="步进频脉冲串" value="3"></el-option>
            </el-select>
          </el-form-item>
          <div class="btns">
            <el-button :loading="sigHandlebtnLoading" type="primary" @click="onHandleBtnClick">信号处理</el-button>
          </div>
        </el-form>
      </el-card>
    </div>
    <div class="charts">
      <el-card class="card-charts">
        <div class="charts-container">
          <div class="chart-container">
            <TimeDomainChart ref="timeDomainChart"></TimeDomainChart>
          </div>
          <div class="chart-container">
            <FrequencyDomainChart ref="frequencyDomainChart"></FrequencyDomainChart>
          </div>
          <div class="chart-container">
            <AScanChart ref="aScanChart"></AScanChart>
          </div>
          <div class="chart-container">
            <BScanChart ref="bScanChart"></BScanChart>
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
      form_handle: {
        collectionSigFolder: '', // 采集信号文件夹
        referenceSig_I: '', // 参考信号 I相文件
        referenceSig_Q: '', // 参考信号 Q相文件
        window_type: '1', // 加窗类型
        other_process: '1' // 其他处理类型
      },
      form_handle_rules: {
        collectionSigFolder: [
          { required: true, message: '请选择采集信号文件夹', trigger: 'change' }
        ],
        referenceSig_I: [
          { required: true, message: '请选择I相参考信号文件', trigger: 'change' }
        ],
        referenceSig_Q: [
          { required: false, message: '请选择Q相参考信号文件', trigger: 'change' }
        ],
        window_type: [
          { required: true, message: '请选择加窗类型', trigger: 'change' }
        ],
        other_process: [
          { required: true, message: '请选择其他处理类型', trigger: 'change' }
        ]
      },
      sigHandlebtnLoading: false, // 信号处理按钮loading状态
      collecting: false
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
    /***** 工具函数start *****/
    async selectCollectSigFolder() {
      const path = await this.showFolderDialog("选择采集信号文件夹", "选择文件夹")
      this.form_handle.collectionSigFolder = path
    },
    async selectReferenceSigFile_I() {
      const path = await window.electronAPI.openFileDialog(
        "选择I相参考信号文件",
        "选择文件",
        [{ name: "信号文件", extensions: ["bin", "npy"] }, { name: "All Files", extensions: ["*"] }]
      )
      this.form_handle.referenceSig_I = path
    },
    async selectReferenceSigFile_Q() {
      const path = await window.electronAPI.openFileDialog(
        "选择Q相参考信号文件",
        "选择文件",
        [{ name: "信号文件", extensions: ["bin", "npy"] }, { name: "All Files", extensions: ["*"] }]
      )
      this.form_handle.referenceSig_Q = path
    },
    /***** 工具函数end *****/
    /***** 业务函数start *****/
    // 信号处理
    onHandleBtnClick() {
      // todo 表单校验
      this.$refs.form.validate((valid) => {
        if (valid) {
          this.handleSignal()
        } else {
          console.log(valid)
          return false
        }
      })
    },
    handleSignal() {
      const {
        collectionSigFolder,
        referenceSig_I,
        referenceSig_Q,
        window_type,
        other_process
      } = this.form_handle

      console.log(collectionSigFolder, referenceSig_I, referenceSig_Q, window_type, other_process);
      // todo 整理函数参数 调用接口
      try {
        this.sigHandlebtnLoading = true
        services.handleSignal({
          collectionSigFolder,
          referenceSig_I,
          referenceSig_Q,
          window_type,
          other_process
        })
          .then(resp => {
            this.$message.success('信号处理成功')
            const {
              data: {
                num_units,
                time_domain_img,
                freq_domain_img,
                ascan_img,
                bscan_img
              }
            } = resp.data
            this.$refs.timeDomainChart.updateImgConifg(time_domain_img, num_units)
            this.$refs.frequencyDomainChart.updateImgConifg(freq_domain_img, num_units)
            this.$refs.aScanChart.updateImgConifg(ascan_img)
            this.$refs.bScanChart.updateImgConifg(bscan_img)
          })
          .catch(err => {
            console.log(err)
            this.$message.error('信号处理失败')
          })
          .finally(() => {
            this.sigHandlebtnLoading = false
          })
      } catch (error) {
        console.log(error)
      }
    }
    /**** 业务函数end *****/
  }
}
</script>

<style lang="less" scoped>
// deep selector is used to override element-ui styles
// /deep/ .el-card__body {
//   padding: 0;
// }

::-webkit-scrollbar {
  width: 6px;
  height: 6px;
}

::-webkit-scrollbar-track-piece {
  background-color: transparent;
  -webkit-border-radius: 3px;
}

::-webkit-scrollbar-thumb:vertical {
  height: 6px;
  background-color: #D0D0D0;
  -webkit-border-radius: 3px;
}

::-webkit-scrollbar-thumb:horizontal {
  width: 6px;
  background-color: #D0D0D0;
  -webkit-border-radius: 3px;
}

::-webkit-scrollbar-thumb:vertical:hover,
::-webkit-scrollbar-thumb:horizontal:hover {
  background-color: #D0D0D0;
}

.el-form-item {
  margin-bottom: 20px;
}

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

.handle {
  width: 100%;
  height: 100%;
  display: flex;

  .form {
    height: 100%;

    .card-form {
      height: 100%;
      box-sizing: border-box;
      overflow: auto;

      &::scr {
        background-color: #ccc;
        border-radius: 4px;
      }
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
        display: grid;
        grid-template-columns: auto auto;
        grid-template-rows: auto auto;
        grid-gap: 12px;
        // flex-wrap: wrap;
        // justify-content: space-between;
        // align-items: flex-start;
        .chart-container {
          display: inline-grid;
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
