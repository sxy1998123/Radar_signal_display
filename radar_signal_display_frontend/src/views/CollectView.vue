<template>
  <div class="collect-view">
    <div class="form">
      <el-card class="card-form">
        <div class="forms">
          <el-form :model="form_generate" label-width="180px" size="medium" :rules="form_generate_rules">
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
          <el-form :model="form_collect" label-width="180px" size="medium" :rules="form_collect_rules">
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
        </div>
      </el-card>
    </div>
  </div>
</template>

<script>
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
  name: 'CollectView',
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
      sigGeneratebtnLoading: false, // 信号生成按钮loading状态
      sigCollectbtnLoading: false, // 信号开始采集按钮loading状态
      sigEndCollectbtnLoading: false, // 信号结束采集按钮loading状态

      collecting: false
    }
  },
  components: {
  },
  methods: {
    async showFolderDialog(title, buttonLabel) {
      const path = await window.electronAPI.openFolderDialog(title, buttonLabel)
      return path
    },
    /***** 工具函数start *****/
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
      if (!this.collecting) {
        this.$message.warning('请先启动信号采集')
        return false
      }
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
    /**** 业务函数end *****/
  }
}
</script>

<style lang="less" scoped>
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

.collect-view {
  width: 100%;
  height: 100%;
  display: flex;

  .form {
    height: 100%;
    width: 100%;
    padding: 20px;
    box-sizing: border-box;
    .card-form {
      height: 100%;
      box-sizing: border-box;
      overflow: auto;
      /deep/ .el-card__body{
        box-sizing: border-box;
        height: 100%;
      }
      .forms{
        height: 100%;
        display: grid;
        grid-template-columns: auto auto;
        gap: 12px;
          >.el-form{
            flex:1;
          }
      }
    }
  }
}
</style>
