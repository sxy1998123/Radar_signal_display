<template>
    <div class="layout">
      <div class="form">
        <el-card class="card-form">
          <el-form ref="form" :model="form_generate" label-width="180px" size="medium" :rules="form_generate_rules">
            <span class="form-title">信号生成：</span>
            <el-form-item label="信号类型" size="medium" prop="signal_type">
              <el-select v-model="form_generate.signal_type" placeholder="请选择信号类型">
                <el-option label="高斯脉冲" value="1"></el-option>
                <el-option label="步进频连续波" value="2"></el-option>
                <el-option label="步进频脉冲串" value="3"></el-option>
              </el-select>
            </el-form-item>
            <el-form-item label="采样率(MHz)" prop="fs">
              <el-input type="number" v-model="form_generate.fs"></el-input>
            </el-form-item>
            <el-form-item label="起始频率(MHz)" prop="fc_start">
              <el-input type="number" v-model="form_generate.fc_start"></el-input>
            </el-form-item>
            <el-form-item label="终止频率(MHz)" prop="fc_end">
              <el-input type="number" v-model="form_generate.fc_end"></el-input>
            </el-form-item>
            <el-form-item label="步进频率点数" prop="num_steps">
              <el-input type="number" v-model="form_generate.num_steps"></el-input>
            </el-form-item>
            <el-form-item label="同时生成I/Q信号" prop="use_iq">
              <el-switch v-model="form_generate.use_iq"></el-switch>
            </el-form-item>
            <el-form-item label="单个频点持续时间(ns)" prop="T">
              <el-input type="number" v-model="form_generate.T"></el-input>
            </el-form-item>
            <div class="btns">
              <el-button :loading="sigGeneratebtnLoading" type="primary" @click="onGenerateSignal">生成并保存信号</el-button>
            </div>
          </el-form>
          <el-form ref="form" :model="form_collect" label-width="180px" size="medium" :rules="form_collect_rules">
            <span class="form-title">信号采集：</span>
            <el-form-item label="DA延迟时间（us）" prop="DA_delaytime">
              <el-input type="number" v-model="form_collect.DA_delaytime"></el-input>
            </el-form-item>
            <el-form-item label="AD延迟时间（us）" prop="AD_delaytime">
              <el-input type="number" v-model="form_collect.AD_delaytime"></el-input>
            </el-form-item>
            <el-form-item label="触发延迟长度" prop="trigDelay">
              <el-input type="number" v-model="form_collect.trigDelay"></el-input>
            </el-form-item>
            <el-form-item label="播放文件地址" prop="bin_file_path">
              <el-input type="textarea" v-model="form_collect.bin_file_path" :readonly="true"></el-input>
              <el-button type="text" @click="selectPlayFile">选择文件</el-button>
            </el-form-item>
            <el-form-item label="是否使用帧头" prop="Frameswitch">
              <el-switch v-model="form_collect.Frameswitch"></el-switch>
            </el-form-item>
            <el-form-item label="信号保存地址" prop="collectionSaveFolder">
              <el-input type="textarea" v-model="form_collect.collectionSaveFolder" :readonly="true"></el-input>
              <el-button type="text" @click="selectCollectSaveFolder">选择文件夹</el-button>
            </el-form-item>
            <el-form-item label="段长(字节)" prop="Segment">
              <el-input type="number" v-model="form_collect.Segment"></el-input>
            </el-form-item>
            <el-form-item label="预触发点数" prop="Pretrigdots">
              <el-input type="number" v-model="form_collect.Pretrigdots"></el-input>
            </el-form-item>
            <el-form-item label="触发频率（Hz）" prop="RepetitionFrequency_input">
              <el-input type="number" v-model="form_collect.RepetitionFrequency_input"></el-input>
            </el-form-item>
            <el-form-item label="文件大小(B)" prop="save_file_size">
              <el-input type="number" v-model="form_collect.save_file_size"></el-input>
            </el-form-item>
            <div class="btns">
              <el-button :loading="sigCollectbtnLoading || collecting" type="primary" @click="onCollectSignal">
                {{collecting ? '正在采集' : '开始采集'}}
              </el-button>
              <el-button :loading="sigEndCollectbtnLoading" type="primary" @click="onEndCollectSignal">结束采集</el-button>
            </div>
          </el-form>
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
              <el-button :loading="sigHandlebtnLoading" type="primary" @click="onHandleSignal">信号处理</el-button>
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
  const checkNumber = (rule, value, callback) => {
    if (isNaN(value)) {
      callback(new Error('请输入数字'))
    } else if(value < 0){
      callback(new Error('请输入正数'))
    } else {
      callback()
    }
  }
  export default {
    name: 'layout',
    data() {
      return {
        form_generate: {
          signal_type: '1', // 信号类型
          fs: 3000, // 采样率 (MHz)
          fc_start: 300, // 起始频率 (MHz)
          fc_end: 1000, // 结束频率 (MHz)
          num_steps: 101, // 步进频率点数
          use_iq: false, // 是否生成I/Q向信号
          T: 500 // 单个频率持续时间 (ns)
        },
        form_generate_rules:{
          signal_type: [
            { required: true, message: '请选择信号类型', trigger: 'change' }
          ],
          fs: [
            { required: true, message: '请输入采样率', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          fc_start: [
            { required: true, message: '请输入起始频率', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          fc_end: [
            { required: true, message: '请输入终止频率', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          num_steps: [
            { required: true, message: '请输入步进频率点数', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          T: [
            { required: true, message: '请输入单个频率持续时间', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ]
        },
        form_collect:{
          DA_delaytime: 0,
          AD_delaytime: 0,
          trigDelay: 0,
          bin_file_path: '',
          Frameswitch: false,
          collectionSaveFolder: '',
          Segment: 1024,
          Pretrigdots: 10,
          RepetitionFrequency_input: 60,
          save_file_size: 1024 * 500
        },
        form_collect_rules:{
          DA_delaytime: [
            { required: true, message: '请输入DA延迟时间', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          AD_delaytime: [
            { required: true, message: '请输入AD延迟时间', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          trigDelay: [
            { required: true, message: '请输入触发延迟长度', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          bin_file_path: [
            { required: true, message: '请选择播放文件', trigger: 'change' }
          ],
          Segment: [
            { required: true, message: '请输入段长', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          Pretrigdots: [
            { required: true, message: '请输入预触发点数', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          RepetitionFrequency_input: [
            { required: true, message: '请输入触发频率', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ],
          save_file_size: [
            { required: true, message: '请输入文件大小', trigger: 'blur' },
            { validator: checkNumber, trigger: 'blur' }
          ]
        },
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
          window_type: [
            { required: true, message: '请选择加窗类型', trigger: 'change' }
          ],
          other_process: [
            { required: true, message: '请选择其他处理类型', trigger: 'change' }
          ]
        },
        sigGeneratebtnLoading: false, // 信号生成按钮loading状态
        sigHandlebtnLoading: false, // 信号处理按钮loading状态
        sigCollectbtnLoading: false, // 信号开始采集按钮loading状态
        sigEndCollectbtnLoading: false, // 信号结束采集按钮loading状态
  
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
      async selectPlayFile() {
        const path = await window.electronAPI.openFileDialog(
          "选择播放的bin文件",
          "选择文件",
          [{ name: "信号文件", extensions: ["bin"] }, { name: "All Files", extensions: ["*"] }]
        )
        this.form_collect.bin_file_path = path
      },
      async selectCollectSaveFolder() {
        const path = await this.showFolderDialog("选择采集信号保存文件夹", "选择文件夹")
        this.form_collect.collectionSaveFolder = path
      },
      /***** 工具函数end *****/
      /***** 业务函数start *****/
      // 信号生成
      async onGenerateSignal() {
        // 弹出文件夹选择框
        const save_dir = await this.showFolderDialog("选择信号保存位置", "保存")
        console.log(save_dir)
        if (!save_dir) {
          return false
        }
        // 上传参数及保存位置到服务端
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
        try {
          this.sigGeneratebtnLoading = true
          services.generateSignal(data)
            .then(resp => {
              this.$message.success('信号生成并保存成功')
              console.log(resp)
            }).catch(err => {
              this.$message.error('信号生成失败')
              console.log(err)
            }).finally(() => {
              this.sigGeneratebtnLoading = false
            })
        } catch (error) {
          console.log(error)
        }
      },
      // 信号采集开始
      async onCollectSignal() {
          try {
            const form_collect = {
              DA_delaytime: Number(this.form_collect.DA_delaytime),
              AD_delaytime: Number(this.form_collect.AD_delaytime),
              trigDelay: Number(this.form_collect.trigDelay),
              bin_file_path: String(this.form_collect.bin_file_path),
              Frameswitch: Boolean(this.form_collect.Frameswitch),
              collectionSaveFolder: String(this.form_collect.collectionSaveFolder),
              Segment: Number(this.form_collect.Segment),
              Pretrigdots: Number(this.form_collect.Pretrigdots),
              RepetitionFrequency_input: Number(this.form_collect.RepetitionFrequency_input),
              save_file_size: Number(this.form_collect.save_file_size)
            }
            this.sigCollectbtnLoading = true
            const resp = await services.collectSignal(form_collect)
            console.log(resp)
            this.$message.success('信号采集启动成功')
            this.collecting = true
          } catch (error) {
            this.$message.error('信号采集启动失败')
            console.log(error)
          } finally {
            this.sigCollectbtnLoading = false
          }
      },
      // 信号采集结束
      async onEndCollectSignal() {
          try {
            this.endCollectSignalbtnLoading = true
            const resp = await services.endCollectSignal()
            console.log(resp)
            this.$message.success('信号采集结束成功')
            this.collecting = false
          } catch (error) {
            this.$message.error('信号采集结束失败')
            console.log(error)
          } finally {
            this.endCollectSignalbtnLoading = false
          }
      },
      // 信号处理
      onHandleSignal() {
        const {
          collectionSigFolder,
          referenceSig_I,
          referenceSig_Q,
          window_type,
          other_process
        } = this.form_handle
        // todo 表单校验
        // console.log(collectionSigFolder, referenceSig_I, referenceSig_Q, window_type, other_process);
        // todo 调用接口
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
  
  .layout {
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
  